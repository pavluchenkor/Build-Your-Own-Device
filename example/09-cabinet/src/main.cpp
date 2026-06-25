// Нагреваемый шкаф хранения филамента на ESP32 + idryer-core.
// Эталонный пример к главе 9. Собирается: pio run -e cabinet.
#include <Wire.h>
#include <ArduinoJson.h>
#include <string.h>
#include <math.h>
#include <iDryer.h>
#include "Sht31ClimateSensor.h"
#include <menu_state.h>

// ── Паспорт устройства (глава 4) ─────────────────────────────────────
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
    .firmwareVersion   = "0.1.0",
    .model             = "DIY Storage Cabinet",
};
static iDryer::Link s_link(CFG);

// ── Датчик климата SHT31 (глава 5) ───────────────────────────────────
static Sht31ClimateSensor s_climate(&Wire);
static bool               s_climateOk = false;

// ── Термистор нагревателя (глава 5) ──────────────────────────────────
static const int   THERM_PIN  = 2;         // вывод ADC
static const float SERIES_R   = 4700.0f;   // резистор делителя, Ом
static const float NOMINAL_R  = 100000.0f; // сопротивление термистора при 25 °C, Ом
static const float NOMINAL_T  = 25.0f;     // °C
static const float BETA       = 3950.0f;   // B-коэффициент из техописания термистора

static float readHeaterTempC() {
    int   raw = analogRead(THERM_PIN);
    float v   = (float)raw / 4095.0f;
    float r   = SERIES_R * (1.0f - v) / v;
    float tK  = 1.0f / (1.0f / (NOMINAL_T + 273.15f) + logf(r / NOMINAL_R) / BETA);
    return tK - 273.15f;
}

// ── Ключи нагревателя и вентилятора (глава 7) ────────────────────────
// Простой ключ на GPIO: вывод управляет MOSFET-модулем (версия A) или
// SSR (версия B). on() = HIGH, off() = LOW.
struct GpioOutput {
    int pin;
    void begin() { pinMode(pin, OUTPUT); digitalWrite(pin, LOW); }
    void on()    { digitalWrite(pin, HIGH); }
    void off()   { digitalWrite(pin, LOW); }
};
static GpioOutput myHeater{4};   // GPIO4 — управление нагревателем
static GpioOutput myFan{5};      // GPIO5 — управление вентилятором

// ── Логика поддержания температуры (глава 7) ─────────────────────────
static bool        s_heating    = false;
static const float HEATER_MAX_C = 80.0f;   // потолок температуры нагревателя

static void controlLoop() {
    float air    = s_link.telemetry.airTempC[0];   // SHT31
    float target = (float)menu.target_temp;        // из меню
    float hyst   = (float)menu.hysteresis;         // из меню
    if (air < target - hyst)  s_heating = true;    // остыли — греем
    else if (air >= target)   s_heating = false;   // дошли до цели — стоп
}

static void applyHeater() {
    float heaterTemp = s_link.telemetry.heaterTempC[0];   // термистор
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
    Wire.begin(8, 9);                 // SDA, SCL — выводы вашей платы
    s_climateOk = s_climate.begin();  // сам находит адрес 0x44 или 0x45
    myHeater.begin();
    myFan.begin();
    menu.initDefaults();              // дефолты меню в RAM
    s_link.begin();

    // Команды портала. Реальное API фасада — onCommand (не onRequest).
    s_link.onCommand("invoke", [](JsonObjectConst data) {
        const char* action = data["action"] | "";
        if (strcmp(action, "storage.start") == 0) {
            s_heating = true;
            s_link.status.mode[0]        = iDryer::UnitMode::Storage;
            s_link.status.targetTempC[0] = (float)menu.target_temp;
            s_link.publishStatusNow();
        } else if (strcmp(action, "storage.stop") == 0) {
            s_heating = false;
            myHeater.off();
            s_link.status.mode[0] = iDryer::UnitMode::Idle;
            s_link.publishStatusNow();
        }
    });
}

void loop() {
    s_link.loop();   // сеть + автопубликация телеметрии/статуса

    if (s_climateOk) {
        s_climate.tick(millis());
        SensorReading r = s_climate.get();
        if (r.ok) {
            s_link.telemetry.airTempC[0]       = r.temperature;
            s_link.telemetry.airHumidityPct[0] = r.humidity;
        }
    }
    s_link.telemetry.heaterTempC[0] = readHeaterTempC();

    controlLoop();
    applyHeater();
    applyFan();
}
