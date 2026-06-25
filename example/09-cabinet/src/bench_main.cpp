// ============================================================================
//  СТЕНДОВЫЙ ТЕСТ главы 9 (env:bench). Без облака.
//
//  Что проверяет по логам Serial:
//   1. SHT31 (I2C) — реальные температура и влажность;
//   2. термистор (ADC) — температура нагревателя + сырой код АЦП;
//   3. логику controlLoop/applyHeater/applyFan (та же, что в проде);
//   4. что выходы нагревателя/вентилятора ФИЗИЧЕСКИ переключаются —
//      через петлю обратной связи на отдельные входы (readback).
//
//  Целевая температура искусственно качается выше/ниже измеренной каждые 8 с,
//  чтобы нагрев включался и выключался без реального нагревателя.
//
//  ПЕТЛЯ (перемычки):  GPIO5 -> GPIO6   (нагреватель -> readback)
//                      GPIO10 -> GPIO7  (вентилятор  -> readback)
// ============================================================================
#include <Wire.h>
#include <math.h>
#include <iDryer.h>
#include "Sht31ClimateSensor.h"
#include <menu_state.h>

// --- пины стенда (можно переопределить через build_flags -D...) ------------
#ifndef PIN_SDA
#define PIN_SDA 8
#endif
#ifndef PIN_SCL
#define PIN_SCL 9
#endif
#ifndef PIN_THERM
#define PIN_THERM 3        // ADC1, НЕ strapping (в отличие от GPIO2)
#endif
#ifndef PIN_HEATER
#define PIN_HEATER 5
#endif
#ifndef PIN_FAN
#define PIN_FAN 10
#endif
#ifndef PIN_HEATER_FB
#define PIN_HEATER_FB 6    // перемычка с PIN_HEATER
#endif
#ifndef PIN_FAN_FB
#define PIN_FAN_FB 7       // перемычка с PIN_FAN
#endif

static const iDryer::Config CFG = {
    .deviceType        = iDryer::DeviceType::Dryer,
    .unitsCount        = 1,
    .hasHeater         = true,
    .hasFan            = true,
    .hasAirTemp        = true,
    .hasAirHumidity    = true,
    .hasHeaterTemp     = true,
    .telemetryPeriodMs = 5000,
    .statusPeriodMs    = 10000,
    .hardwareVersion   = "1.0",
    .firmwareVersion   = "bench",
    .model             = "DIY Cabinet BENCH",
};
static iDryer::Link s_link(CFG);

static Sht31ClimateSensor s_climate(&Wire);
static bool               s_climateOk = false;

// --- термистор (как в проде) -----------------------------------------------
static const int   THERM_PIN  = PIN_THERM;
static const float SERIES_R   = 4700.0f;
static const float NOMINAL_R  = 100000.0f;
static const float NOMINAL_T  = 25.0f;
static const float BETA       = 3950.0f;

static int   s_thermRaw = 0;
static float readHeaterTempC() {
    int   raw = analogRead(THERM_PIN);
    s_thermRaw = raw;
    float v   = (float)raw / 4095.0f;
    if (v <= 0.0f)  v = 0.0001f;
    if (v >= 1.0f)  v = 0.9999f;
    float r   = SERIES_R * (1.0f - v) / v;
    float tK  = 1.0f / (1.0f / (NOMINAL_T + 273.15f) + logf(r / NOMINAL_R) / BETA);
    return tK - 273.15f;
}

// --- ключи (как в проде) ----------------------------------------------------
struct GpioOutput {
    int pin;
    void begin() { pinMode(pin, OUTPUT); digitalWrite(pin, LOW); }
    void on()    { digitalWrite(pin, HIGH); }
    void off()   { digitalWrite(pin, LOW); }
};
static GpioOutput myHeater{PIN_HEATER};
static GpioOutput myFan{PIN_FAN};

// --- логика (ровно как в проде) --------------------------------------------
static bool        s_heating    = false;
static const float HEATER_MAX_C = 80.0f;

static void controlLoop() {
    float air    = s_link.telemetry.airTempC[0];
    float target = (float)menu.target_temp;
    float hyst   = (float)menu.hysteresis;
    if (air < target - hyst)  s_heating = true;
    else if (air >= target)   s_heating = false;
}

static void applyHeater() {
    float heaterTemp = s_link.telemetry.heaterTempC[0];
    bool  allow = s_heating && heaterTemp < HEATER_MAX_C;
    if (allow) myHeater.on(); else myHeater.off();
    s_link.telemetry.heaterPower01[0] = allow ? 1.0f : 0.0f;
}

static void applyFan() {
    if (s_heating) myFan.on(); else myFan.off();
    s_link.telemetry.fanOn[0] = s_heating;
}

void setup() {
    Serial.begin(115200);
    pinMode(PIN_HEATER_FB, INPUT);
    pinMode(PIN_FAN_FB, INPUT);

    Wire.begin(PIN_SDA, PIN_SCL);
    s_climateOk = s_climate.begin();

    myHeater.begin();
    myFan.begin();

    menu.initDefaults();   // даёт menu.hysteresis (=2) и menu.target_temp

    Serial.println();
    Serial.println("==== BENCH START (без облака) ====");
    Serial.printf("pins: SDA=%d SCL=%d THERM=%d HEAT=%d->FB%d FAN=%d->FB%d\n",
                  PIN_SDA, PIN_SCL, PIN_THERM,
                  PIN_HEATER, PIN_HEATER_FB, PIN_FAN, PIN_FAN_FB);
    Serial.printf("SHT31: %s\n", s_climateOk ? "OK" : "НЕ НАЙДЕН");
}

void loop() {
    // 1. датчики
    float air = 25.0f;
    float hum = NAN;
    if (s_climateOk) {
        s_climate.tick(millis());
        SensorReading r = s_climate.get();
        if (r.ok) { air = r.temperature; hum = r.humidity; }
    }
    s_link.telemetry.airTempC[0]       = air;
    s_link.telemetry.airHumidityPct[0] = hum;
    s_link.telemetry.heaterTempC[0]    = readHeaterTempC();

    // 2. качаем целевую температуру ±10° вокруг измеренной, период 8 с
    bool wantHigh = ((millis() / 8000) % 2) == 0;   // фаза теста
    float tgt = wantHigh ? (air + 10.0f) : (air - 10.0f);
    if (tgt < 0) tgt = 0;
    menu.target_temp = (uint16_t)(tgt + 0.5f);

    // 3. та же логика, что в проде
    controlLoop();
    applyHeater();
    applyFan();

    // 4. лог раз в секунду + сверка выходов с петлёй обратной связи
    static uint32_t lastLog = 0;
    if (millis() - lastLog >= 1000) {
        lastLog = millis();

        bool heatCmd = s_link.telemetry.heaterPower01[0] > 0.5f;
        bool fanCmd  = s_link.telemetry.fanOn[0];
        bool heatFb  = digitalRead(PIN_HEATER_FB);
        bool fanFb   = digitalRead(PIN_FAN_FB);

        Serial.printf(
            "[BENCH] t=%lus air=%.1f hum=%.0f heaterT=%.1f(raw=%d) "
            "target=%u hyst=%u heating=%d | "
            "HEAT cmd=%d fb=%d %s | FAN cmd=%d fb=%d %s\n",
            millis() / 1000, air, hum,
            s_link.telemetry.heaterTempC[0], s_thermRaw,
            menu.target_temp, menu.hysteresis, s_heating ? 1 : 0,
            heatCmd, heatFb, (heatCmd == heatFb) ? "OK" : "FAIL",
            fanCmd, fanFb, (fanCmd == fanFb) ? "OK" : "FAIL");
    }
}
