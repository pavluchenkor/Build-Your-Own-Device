---
title: "Menú del dispositivo desde YAML: configuración en NVS y en el portal"
description: "Cómo describir el menú del dispositivo en idryer-core en menu.yaml: la temperatura objetivo y la histéresis se guardan en NVS y se muestran con widgets en el portal iDryer."
---

# Menú desde YAML

El menú es un conjunto de parámetros del dispositivo: temperatura objetivo, histéresis, umbrales de ventilador. En `idryer-core` el menú se describe en un único archivo `menu.yaml`, y todo lo demás — estructuras C++, almacenamiento en memoria no volátil (NVS) y publicación en el portal — se genera automáticamente.

Este es uno de los componentes clave del núcleo. No escribe código de almacenamiento de parámetros ni inventa un formato para el portal — solo enumera los parámetros en YAML.

## Por qué el menú

Después de los pasos anteriores, el dispositivo lee sensores, pero todos los umbrales están «codificados» en el código. El menú resuelve tres problemas a la vez:

- **almacenamiento**: los valores persisten después del reinicio (NVS);
- **gestión desde el portal**: cada parámetro se convierte en un widget (deslizador, conmutador);
- **única fuente de verdad**: un archivo describe tanto la memoria como la interfaz.

## Cómo funciona

Un archivo `menu.yaml` pasa por un generador durante la compilación:

```text
menu.yaml → (pio run build) → archivos C++ en src/menu/ + NVS + JSON para el portal
```

Un elemento con el campo `role:` es visible para el portal y se muestra como un widget. Un elemento sin `role:` es privado, solo para la lógica interna del dispositivo.

!!! warning "No edite los archivos generados"
    Los archivos `menu_state.*`, `menu_bindings.*`, `menu_ids.h` y otros los crea el generador. Edite solo `menu.yaml` y recompile — de lo contrario sus cambios se perderán.

## Paso 1. Copie la plantilla

La biblioteca contiene una plantilla de menú. Cópiela en su proyecto:

```bash
mkdir -p src/menu
cp path/to/idryer-core/menu/menu.template.yaml src/menu/menu.yaml
```

## Paso 2. Habilite la generación durante la compilación

Copie el gancho de ejemplo del proyecto `iDryer-Storage` (puede usarlo tal cual, no necesita cambios):

```bash
mkdir -p extra_scripts
cp path/to/iDryer-Storage/extra_scripts/pre_gen_menu.py extra_scripts/pre_gen_menu.py
```

Luego en `platformio.ini` agregue `-Isrc/menu` en la sección `[env:cabinet]` (para que el código vea `#include <menu_state.h>`) y conecte el gancho mediante `extra_scripts`:

```ini
[env:cabinet]
; ... platform / board / lib_deps del capítulo 4 — sin cambios ...

build_flags =
    -Isrc/menu                      ; ← agregado: ruta al menú generado
    -DIDRYER_API_BASE='"https://portal.idryer.org/api"'
    -DMQTT_BROKER='"mqtt.idryer.org"'
    -DMQTT_PORT=8883
    -DMQTT_USE_TLS=1

extra_scripts =                     ; ← agregado
    pre:extra_scripts/pre_gen_menu.py
```

El gancho encontrará automáticamente el generador en la ruta `lib/idryer-core/menu/menu_gen.py`, por lo que la biblioteca debe estar conectada mediante `lib/` (enlace simbólico o copia), como se describe en el capítulo 4.

## Paso 3. Describa los parámetros del gabinete

Abra `src/menu/menu.yaml`. La plantilla ya tiene un elemento raíz `root` con un arreglo `children` y parámetros de ejemplo. Elimine los ejemplos (`my_param`, `my_flag`, `my_mode_group`) y agregue los suyos dentro de `children`. Los dos últimos elementos — `units_count` e `language` — déjelos en su lugar: este es un contrato fijo con el portal.

Para un gabinete básico, basta con unos pocos parámetros.

Temperatura objetivo de almacenamiento:

```yaml
- id: target_temp
  type: value
  role: storage.target_temperature   # hace que el parámetro sea un widget en el portal
  title: { ru: "ТЕМПЕРАТУРА", en: "TARGET TEMP" }
  unit:  { ru: "°C", en: "°C" }
  vtype: uint16
  min: 30
  max: 50
  step: 1
  bind: target_temp            # clave NVS (≤ 15 caracteres)
  persist: true
  scope: global
  default: 45
```

Histéresis (cuántos grados puede bajar la temperatura por debajo del objetivo antes de que se encienda el calentador nuevamente):

```yaml
- id: hysteresis
  type: value
  title: { ru: "ГИСТЕРЕЗИС", en: "HYSTERESIS" }
  unit:  { ru: "°C", en: "°C" }
  vtype: uint8
  min: 1
  max: 5
  step: 1
  bind: hysteresis
  persist: true
  scope: global
  default: 2
```

!!! note "role: — es una lista cerrada"
    El valor `role:` no puede ser arbitrario — debe estar en la lista `canonical_roles` del contrato del núcleo. Si no hay un rol adecuado, la compilación se detiene y muestra la lista de roles permitidos. Para un gabinete de almacenamiento, los roles de la familia `storage.*` son apropiados: `storage.target_temperature`, `storage.target_humidity`, `storage.start`, `storage.stop`. La lista completa está en el encabezado de `menu.template.yaml`. Los parámetros sin `role:` (como la histéresis anterior) funcionan como configuración interna: se almacenan en NVS pero no se envían al portal.

Restricciones que no se pueden violar:

- `bind` — no más de 15 caracteres (límite de clave NVS);
- no agregue el campo `widget:` en `menu.yaml` — el tipo de widget lo determina el contrato según `role:`.

!!! warning "Verifique el elemento ignore_external_cmd de la plantilla"
    La plantilla contiene un elemento `ignore_external_cmd`, y su `bind` tiene 19 caracteres, lo que excede el límite de 15. Si lo deja así, la generación fallará: `bind 'ignore_external_cmd' ... tiene 19 caracteres, límite 15`. Elimine este elemento o acorte `bind` a `ign_ext_cmd` (como en los productos reales). Para un gabinete básico, puede simplemente eliminarlo.

## Paso 4. Compile el proyecto y verifique la generación

```bash
pio run -e cabinet
```

Durante la compilación, el pre-hook instalará automáticamente las dependencias (una sola vez) y generará los archivos C++ del menú. Si `menu.yaml` no cambió — la generación se omite (`up-to-date`).

Verifique que la generación se haya completado. En el registro de compilación aparece una línea sobre la generación del menú, y en la carpeta `src/menu/` — los archivos generados:

```text
src/menu/
├── menu.yaml          # su archivo (fuente)
├── menu_state.h/.cpp  # objeto menu con todos los parámetros
├── menu_bindings.*    # acceso por bind + escritura en NVS
├── menu_ids.h
└── menu_meta.h        # y otros
```

Si la compilación falla con un mensaje sobre un `role:` desconocido — significa que el rol no está en la lista `canonical_roles`. Corrija el rol y recompile. No edite manualmente los archivos marcados como autogen.

## Paso 5. Incluya el menú en main

Para usar el código del menú, incluya dos cosas en `src/main.cpp`:

1. El encabezado del menú generado:

    ```cpp
    #include <menu_state.h>      // objeto menu con todos los parámetros
    ```

2. La carga de valores por defecto en `setup()` — **antes** de `s_link.begin()`:

    ```cpp
    menu.initDefaults();         // establecer valores por defecto de YAML
    ```

Después de esto, los parámetros están disponibles a través del objeto global `menu`:

```cpp
uint16_t target = menu.target_temp;   // acceso directo al valor
```

Estos valores se usan en la lógica de calentamiento en el siguiente paso. Cuando el usuario cambia un parámetro en el portal, el núcleo aplica automáticamente el nuevo valor y lo guarda en NVS.

## `src/main.cpp` completo después de este capítulo

Comparado con el capítulo anterior, solo se agregaron dos líneas (marcadas con `// ← capítulo 6`): la inclusión del menú y `menu.initDefaults()`.

??? note "Versión anterior — `src/main.cpp` después del capítulo 5"

    ```cpp
    #include <iDryer.h>
    #include <Wire.h>
    #include <math.h>
    #include "Sht31ClimateSensor.h"

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
#include <iDryer.h>
#include <Wire.h>
#include <math.h>
#include "Sht31ClimateSensor.h"
#include <menu_state.h>           // ← capítulo 6

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
    menu.initDefaults();           // ← capítulo 6
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

## Verificación del resultado

Después de descargar el firmware:

- en el portal en la tarjeta del dispositivo aparece la configuración de temperatura objetivo;
- el cambio de valor en el portal se guarda y persiste después del reinicio;
- los parámetros internos (histéresis) están disponibles en el código a través de `menu`.

## Qué sigue

Los parámetros están descritos y almacenados. Ahora vamos a vincularlos al hardware en [Control de calentamiento](07-heating-control.md): el calentador mantiene la temperatura objetivo, el ventilador se enciende por umbral.
