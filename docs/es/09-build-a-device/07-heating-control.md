---
title: "Control de calefacción del gabinete: mantenimiento de temperatura y ventilador"
description: "Lógica del gabinete calefaccionado en idryer-core: mantenimiento de temperatura objetivo por histéresis, protección del calentador por termistor, ventilador y comandos del portal."
---

# Control de calefacción

En esta página conecta los sensores, configuraciones y la parte de potencia en una lógica operativa. El dispositivo mantiene una temperatura establecida dentro del gabinete, protege el calentador del sobrecalentamiento y responde a comandos desde el portal.

La lógica se ejecuta en `loop()` junto con el mantenimiento de la red. Todos los temporizadores y umbrales son no bloqueantes, sin `delay()`.

## Qué debe suceder

El comportamiento del gabinete se basa en tres reglas simples:

1. **Mantenimiento de temperatura.** Si el aire en el gabinete está más frío que el objetivo por la cantidad de histéresis, encienda la calefacción. Cuando alcance el objetivo, apague.
2. **Protección del calentador.** El termistor controla el calentador mismo. Si se sobrecalienta por encima del límite permitido, la calefacción se apaga independientemente de la temperatura del aire.
3. **Ventilador.** Se enciende para distribuir el calor en el gabinete y se apaga cuando la calefacción no es necesaria.

## Llaves del calentador y ventilador

El controlador enciende el calentador y el ventilador a través de una llave: módulo MOSFET (versión A) o SSR (versión B) — vea [Diagrama de conexión](03-wiring.md). Desde el punto de vista del código, es simplemente una salida GPIO: `HIGH` — encendido, `LOW` — apagado.

Describa tal llave con una pequeña estructura y cree dos instancias — para el calentador y el ventilador. Agregue esto a `src/main.cpp` (antes de `setup()`):

```cpp
struct GpioOutput {
    int pin;
    void begin() { pinMode(pin, OUTPUT); digitalWrite(pin, LOW); }
    void on()    { digitalWrite(pin, HIGH); }
    void off()   { digitalWrite(pin, LOW); }
};

static GpioOutput myHeater{4};   // GPIO4 — control del calentador
static GpioOutput myFan{5};      // GPIO5 — control del ventilador
```

Los números de pines son los mismos que en [Diagrama de conexión](03-wiring.md). En `setup()` ambas llaves deben inicializarse: `myHeater.begin();` y `myFan.begin();`.

!!! warning "Estado seguro al iniciar"
    `begin()` inmediatamente establece `LOW` — el calentador y el ventilador están apagados hasta que la lógica decida lo contrario. Esto es importante: al encender la alimentación, el calentador no debe encenderse accidentalmente.

## Mantenimiento de temperatura por histéresis

Para un gabinete a `40–45 °C` es suficiente una histéresis simple: la calefacción se enciende y apaga alrededor del objetivo. Esto es más simple que un PID completo y funciona de manera confiable para mantener el calor de manera suave.

Obtenga la temperatura objetivo e histéresis del menú (`menu.target_temp`, `menu.hysteresis`) — ya está conectado en [capítulo 6](06-menu.md). Agregue una bandera de estado y una función de decisión:

```cpp
static bool s_heating = false;

static void controlLoop() {
    float air    = s_link.telemetry.airTempC[0];     // SHT31
    float target = (float)menu.target_temp;          // del menú
    float hyst   = (float)menu.hysteresis;           // del menú

    if (air < target - hyst) {
        s_heating = true;     // se enfrió — calentar
    } else if (air >= target) {
        s_heating = false;    // alcanzó el objetivo — parar
    }
}
```

La temperatura objetivo e histéresis se toman del [menú](06-menu.md) — el usuario las cambia desde el portal.

## Protección del calentador por termistor

El aire se calienta lentamente, pero la bobina del calentador se calienta rápidamente. Sin un control separado, el calentador se sobrecalentará antes de que el aire alcance el objetivo. Por lo tanto, el termistor del calentador establece un límite máximo duro.

```cpp
static const float HEATER_MAX_C = 80.0f;   // límite de temperatura del calentador

static void applyHeater() {
    float heaterTemp = s_link.telemetry.heaterTempC[0];   // termistor

    bool allow = s_heating && heaterTemp < HEATER_MAX_C;

    if (allow) {
        myHeater.on();
        s_link.telemetry.heaterPower01[0] = 1.0f;   // reflejar en telemetría
    } else {
        myHeater.off();
        s_link.telemetry.heaterPower01[0] = 0.0f;
    }
}
```

!!! warning "El límite del calentador es protección, no ajuste climático"
    `HEATER_MAX_C` limita la temperatura del calentador mismo, no del aire. El valor depende de la construcción del calentador y los materiales de la carcasa. Elíjalo con un margen por debajo de la temperatura a la cual se deforman las piezas impresas — vea [Materiales resistentes al calor](../07-3d-printing/04-heat-resistant-materials.md).

Para un calentamiento más suave en lugar de encendido/apagado "todo o nada", puede controlar la potencia a través de PWM y el campo `heaterPower01[0]` acepta valores de `0.0` a `1.0`. Para un gabinete con mantenimiento suave del calor, la lógica simple anterior generalmente es suficiente.

## Ventilador

El ventilador distribuye el calor en el gabinete. La lógica más simple es encenderlo junto con la calefacción:

```cpp
static void applyFan() {
    bool fanOn = s_heating;          // giramos mientras calentamos
    if (fanOn) myFan.on(); else myFan.off();
    s_link.telemetry.fanOn[0] = fanOn;   // reflejar en telemetría
}
```

En el controlador de serie, el ventilador se controla por temperatura con umbrales separados de encendido y apagado (por ejemplo, encendido a `55 °C`, apagado a `35 °C`), para que no fluctúe en el límite. Para el gabinete puede aplicar el mismo enfoque, vinculando los umbrales a parámetros del menú.

## Ensamblando en loop()

```cpp
void loop() {
    s_link.loop();          // red y auto-publicación

    // sensores (vea el paso "Sensores"):
    s_climate.tick(millis());
    SensorReading c = s_climate.get();
    if (c.ok) {
        s_link.telemetry.airTempC[0]       = c.temperature;
        s_link.telemetry.airHumidityPct[0] = c.humidity;
    }
    s_link.telemetry.heaterTempC[0] = readHeaterTempC();

    controlLoop();   // decidimos si calentar o no
    applyHeater();   // aplicamos al calentador + protección
    applyFan();      // aplicamos al ventilador
}
```

Los campos de telemetría (`heaterPower01`, `fanOn`) se publican automáticamente por la fachada — en el portal se ve si el dispositivo está calentando ahora y si funciona el ventilador.

## Comandos desde el portal

El inicio y parada del mantenimiento del calor se envían desde el portal como comandos. El controlador se registra con el método `s_link.onCommand(nombre, callback)` — **después** de `s_link.begin()`. Los comandos de acción llegan con el nombre `invoke` y el campo `action` (rol del menú, por ejemplo `storage.start` / `storage.stop`).

Para analizar JSON, necesita los encabezados `<ArduinoJson.h>` y `<string.h>` (para `strcmp`) — agréguelos al resto de `#include` al principio del archivo. El controlador en sí se coloca en `setup()`:

```cpp
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
```

- `storage.start` / `storage.stop` — los mismos roles que estableció en [menú](06-menu.md); el portal dibuja botones basados en ellos.
- `iDryer::UnitMode::Storage` — modo de mantenimiento suave de calor. Este es el modo principal del gabinete.
- `s_link.status.mode[0]` y `targetTempC[0]` muestran en el portal el estado actual de la cámara.
- Llame a `publishStatusNow()` después de cada cambio de estado para que el portal lo vea inmediatamente, sin esperar al temporizador.

!!! warning "Sin delay() en el controlador"
    El controlador `onCommand` se llama desde el callback de red. Cualquier bloqueo dentro de él rompe la sesión MQTT. Cambie las banderas y el estado, pero haga el trabajo real en `loop()`.

## `src/main.cpp` completo después de este capítulo

Este es el archivo final y completo del dispositivo. Las nuevas líneas respecto al capítulo anterior se marcan con `// ← capítulo 7`. Este mismo archivo se encuentra como ejemplo listo en la carpeta `example/09-cabinet/` del repositorio y se compila con el comando `pio run -e cabinet`.

??? note "Cómo quedó — `src/main.cpp` tras el capítulo 6"

    ```cpp
    #include <iDryer.h>
    #include <Wire.h>
    #include <math.h>
    #include "Sht31ClimateSensor.h"
    #include <menu_state.h>

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

    static Sht31ClimateSensor s_climate(&Wire);
    static bool               s_climateOk = false;

    static const int   THERM_PIN  = 2;
    static const float SERIES_R   = 4700.0f;
    static const float NOMINAL_R  = 100000.0f;
    static const float NOMINAL_T  = 25.0f;
    static const float BETA       = 3950.0f;

    static float readHeaterTempC() {
        int   raw = analogRead(THERM_PIN);
        float v   = (float)raw / 4095.0f;
        float r   = SERIES_R * (1.0f - v) / v;
        float tK  = 1.0f / (1.0f / (NOMINAL_T + 273.15f) + logf(r / NOMINAL_R) / BETA);
        return tK - 273.15f;
    }

    void setup() {
        Serial.begin(115200);
        Wire.begin(8, 9);
        s_climateOk = s_climate.begin();
        menu.initDefaults();
        s_link.begin();
    }

    void loop() {
        s_link.loop();

        if (s_climateOk) {
            s_climate.tick(millis());
            SensorReading r = s_climate.get();
            if (r.ok) {
                s_link.telemetry.airTempC[0]       = r.temperature;
                s_link.telemetry.airHumidityPct[0] = r.humidity;
            }
        }
        s_link.telemetry.heaterTempC[0] = readHeaterTempC();
    }
    ```

```cpp
#include <Wire.h>
#include <ArduinoJson.h>          // ← capítulo 7 (onCommand: JsonObjectConst)
#include <string.h>              // ← capítulo 7 (strcmp)
#include <math.h>
#include <iDryer.h>
#include "Sht31ClimateSensor.h"
#include <menu_state.h>

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

static Sht31ClimateSensor s_climate(&Wire);
static bool               s_climateOk = false;

static const int   THERM_PIN  = 2;
static const float SERIES_R   = 4700.0f;
static const float NOMINAL_R  = 100000.0f;
static const float NOMINAL_T  = 25.0f;
static const float BETA       = 3950.0f;

static float readHeaterTempC() {
    int   raw = analogRead(THERM_PIN);
    float v   = (float)raw / 4095.0f;
    float r   = SERIES_R * (1.0f - v) / v;
    float tK  = 1.0f / (1.0f / (NOMINAL_T + 273.15f) + logf(r / NOMINAL_R) / BETA);
    return tK - 273.15f;
}

// ← capítulo 7: llaves del calentador y ventilador
struct GpioOutput {
    int pin;
    void begin() { pinMode(pin, OUTPUT); digitalWrite(pin, LOW); }
    void on()    { digitalWrite(pin, HIGH); }
    void off()   { digitalWrite(pin, LOW); }
};
static GpioOutput myHeater{4};
static GpioOutput myFan{5};

// ← capítulo 7: lógica de mantenimiento de temperatura
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
    Wire.begin(8, 9);
    s_climateOk = s_climate.begin();
    myHeater.begin();              // ← capítulo 7
    myFan.begin();                 // ← capítulo 7
    menu.initDefaults();
    s_link.begin();

    s_link.onCommand("invoke", [](JsonObjectConst data) {   // ← capítulo 7
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
    s_link.loop();

    if (s_climateOk) {
        s_climate.tick(millis());
        SensorReading r = s_climate.get();
        if (r.ok) {
            s_link.telemetry.airTempC[0]       = r.temperature;
            s_link.telemetry.airHumidityPct[0] = r.humidity;
        }
    }
    s_link.telemetry.heaterTempC[0] = readHeaterTempC();

    controlLoop();   // ← capítulo 7
    applyHeater();   // ← capítulo 7
    applyFan();      // ← capítulo 7
}
```

## Verificación del resultado

Después de este paso:

- el inicio desde el portal pone el gabinete en modo Storage, el dispositivo comienza a calentar;
- la temperatura del aire se ajusta al objetivo y se mantiene dentro de los límites de la histéresis;
- el calentador no sobrepasa `HEATER_MAX_C`;
- el ventilador y la potencia de calefacción se ven en la telemetría;
- la parada desde el portal apaga la calefacción y pasa a Idle.

## Qué sigue

La lógica está lista. Queda ensamblar el dispositivo en la carcasa y verificar bajo carga — [Ensamblaje y verificación](08-assembly-and-check.md).
