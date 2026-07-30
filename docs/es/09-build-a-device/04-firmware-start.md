---
title: "Inicio de firmware en idryer-core: primer inicio y vinculación al portal"
description: "Creación de proyecto PlatformIO en librería idryer-core: platformio.ini, secrets.h, Config del dispositivo, primer firmware de ESP32 y vinculación al portal iDryer."
---

# Inicio de firmware en el núcleo

En esta página, crea un proyecto de firmware, lleva el ESP32 al estado Online en el portal y verifica que la parte de red funciona. Los sensores y la lógica de calefacción se agregarán en los siguientes pasos.

El enfoque se basa en la fachada `iDryer::Link`. Describe el dispositivo con una única estructura `iDryer::Config`, llama a `link.begin()` y `link.loop()` — el núcleo maneja toda la conexión de red por sí solo.

## 1. Prepare las herramientas

Necesitará:

- VS Code con la extensión PlatformIO;
- Cable USB;
- Red Wi-Fi `2.4 GHz` (ESP32 no funciona con redes solo `5 GHz`).

Qué es el firmware del controlador y cómo se carga en la placa — [Flasheo del controlador](../02-controllers/11-flashing-controller.md).

## 2. Cree el proyecto

En PlatformIO, un proyecto es una carpeta con estructura fija. Cree una carpeta de proyecto (por ejemplo `my-cabinet`) y ábrala en VS Code. Dentro deben estar estos archivos:

```text
my-cabinet/
├── platformio.ini        # configuración de compilación (completaremos en el paso 4)
├── include/
│   └── secrets.h         # usuario y contraseña de Wi-Fi (paso 3)
├── lib/
│   └── idryer-core/      # librería del núcleo (enlace simbólico o copia)
└── src/
    └── main.cpp          # código del dispositivo: Config + setup() + loop()
```

Todos los fragmentos de código a continuación van exactamente en estos archivos — cada paso indica en cuál. Cree manualmente las carpetas `include/`, `lib/` y `src/` si no existen.

Coloque la librería `idryer-core` en `lib/` — PlatformIO encuentra librerías allí automáticamente. La forma más fácil es hacer un enlace simbólico a la librería descargada:

```bash
ln -s /ruta/a/idryer-core lib/idryer-core
```

Esto también es necesario para la generación del menú (capítulo 6) — el hook busca el generador dentro de `lib/idryer-core/`.

## 3. Cree secrets.h

Copie el ejemplo `secrets.h.example` de la librería a `include/secrets.h` de su proyecto e indique los datos de su red:

```cpp
#define WIFI_SSID      "your-ssid"
#define WIFI_PASSWORD  "your-password"
```

Agregue `include/secrets.h` a `.gitignore` para que la contraseña no llegue al repositorio.

## 4. Configure platformio.ini

Complete `platformio.ini` en la raíz del proyecto:

```ini
[env:cabinet]
platform    = espressif32
framework   = arduino
board       = esp32-c3-devkitm-1

lib_deps =
    bblanchon/ArduinoJson @ ^6.21.0
    knolleary/PubSubClient
    densaugeo/base64 @ ^1.4.0
    links2004/WebSockets @ ^2.4.0
    https://github.com/jnthas/Improv-WiFi-Library.git

build_flags =
    -DIDRYER_API_BASE='"https://portal.idryer.org/api"'
    -DMQTT_BROKER='"mqtt.idryer.org"'
    -DMQTT_PORT=8883
    -DMQTT_USE_TLS=1
```

Reemplace `board` por su placa (por ejemplo, `esp32-s3-devkitc-1`). No es necesario indicar `idryer-core` en `lib_deps` — se encuentra en `lib/` (paso 2).

!!! note "Por qué todas estas dependencias"
    `ArduinoJson`, `PubSubClient`, `base64`, `WebSockets` e `Improv-WiFi-Library` las necesita la propia librería `idryer-core` (MQTT, acceso WebSocket por LAN, provisión de Wi-Fi). Sin ninguna de ellas, la compilación fallará con un error como `... .h: No such file`. Los flags `MQTT_BROKER` y `MQTT_PORT` también son obligatorios — sin ellos el núcleo no se compilará (`'MQTT_BROKER' was not declared`).

## 5. Describa el dispositivo en Config

Desde aquí todo ocurre en un archivo — `src/main.cpp`. Ábralo e ingrese el código de este y los siguientes pasos.

`iDryer::Config` es el pasaporte del dispositivo. Los flags `has*` indican al portal qué tiene el dispositivo y determinan qué campos de telemetría se publican.

Para un gabinete calefaccionado, añada al inicio de `src/main.cpp`:

```cpp
#include <iDryer.h>

static const iDryer::Config CFG = {
    .deviceType        = iDryer::DeviceType::Dryer,
    .unitsCount        = 1,
    // Periféricos:
    .hasHeater         = true,    // calefactor controlado
    .hasFan            = true,    // ventilador
    .hasAirTemp        = true,    // temperatura del aire (SHT31)
    .hasAirHumidity    = true,    // humedad del aire (SHT31)
    .hasHeaterTemp     = true,    // temperatura del calefactor (termistor)
    // Períodos de autopublicación:
    .telemetryPeriodMs = 5000,
    .statusPeriodMs    = 10000,
    // Identificación en el portal:
    .hardwareVersion   = "1.0",
    .firmwareVersion   = "0.1.0",
    .model             = "DIY Storage Cabinet",
};

static iDryer::Link s_link(CFG);
```

!!! note "Los flags has* son un contrato con el portal"
    Un campo de telemetría cuyo flag correspondiente es `false` no se publica. Por ejemplo, sin `hasAirHumidity = true` la humedad no llegará a la nube, incluso si la escribe en el código. Active solo lo que físicamente existe en el dispositivo.

Lista de componentes y flags — [Composición del sistema](02-bom.md).

## 6. Main mínima

En el mismo archivo después del bloque `Config` agregue las funciones `setup()` y `loop()`. Para el primer inicio, es suficiente inicializar el enlace y ejecutarlo en `loop()`:

```cpp
void setup() {
    Serial.begin(115200);
    s_link.begin();
}

void loop() {
    s_link.loop();
}
```

Esto es suficiente para que el dispositivo se conecte a Wi-Fi y aparezca en el portal. Los sensores se agregarán en el paso [Sensores](05-sensors.md).

### Completo `src/main.cpp` después de este capítulo

Tome ambos bloques anteriores en un archivo — este es todo el `src/main.cpp` en este paso:

```cpp
#include <iDryer.h>

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

void setup() {
    Serial.begin(115200);
    s_link.begin();
}

void loop() {
    s_link.loop();
}
```

Cada capítulo muestra **qué agregar** y el **completo `src/main.cpp` después de los cambios**, para que siempre vea el cuadro completo, no fragmentos dispersos.

## 7. Flashee

```bash
pio run -e cabinet -t upload
```

## 8. Abra Serial Monitor

```bash
pio device monitor -b 115200
```

Secuencia esperada en el registro:

```text
[CLOUD] Connecting to WiFi...
[CLOUD] WiFi connected, IP: 192.168.1.42
[CLOUD] Provisioning device...
[CLOUD] PIN: 1234567 (expires in 600s)
```

Si el dispositivo se detiene en la línea `PIN: ...` — es normal. Proceda a la vinculación.

## 9. Vincule el dispositivo al portal

1. Abra [portal.idryer.org](https://portal.idryer.org/).
2. Vaya a la sección **Add device**.
3. Ingrese el PIN del Serial Monitor.

Después de la vinculación, el dispositivo cambiará al estado `Online`. En el registro aparecerá:

```text
[CLOUD] Device claimed!
[CLOUD] MQTT connected!
```

## Verificación del resultado

En este paso, el dispositivo debe estar Online en el portal. No hay datos de sensores aún — esto es esperado. Si el dispositivo no se conecta:

- verifique que la red sea `2.4 GHz` y que la contraseña en `secrets.h` sea correcta;
- verifique la alimentación del ESP32 (caídas de tensión al iniciar Wi-Fi son una causa frecuente de reinicios);
- vea [Errores de alimentación](../08-common-mistakes/02-power-mistakes.md) y [Errores de controladores](../08-common-mistakes/04-controller-mistakes.md).

## Qué sigue

La parte de red funciona. Proceda a [Sensores](05-sensors.md): conectaremos SHT31 y el termistor y veremos sus datos en el portal.
