---
title: "Filtro inteligente: inicio del firmware y vinculación al portal"
description: "Estructura del firmware del filtro en idryer-core: Config de dispositivo de tipo no estándar, primer inicio, vinculación a la cuenta por PIN."
---

# Inicio del firmware

La estructura del proyecto repite completamente el [capítulo del ejemplo del gabinete](../09-build-a-device/04-firmware-start.md): PlatformIO, `secrets.h`, `idryer-core` en `lib/`, el mismo `platformio.ini` (solo reemplaza el nombre del entorno por `filter`). Aquí — solo lo que difiere.

## Config: dispositivo de tipo no estándar

El filtro no tiene ni calefactor ni sensor climático del diccionario del ecosistema. De las habilidades "del diccionario" solo tiene ventilador. En `src/main.cpp`:

```cpp
#include <iDryer.h>

static const iDryer::Config CFG = {
    .deviceType        = iDryer::DeviceType::Unknown, // dispositivo no estándar
    .unitsCount        = 1,
    // Periféricos: del diccionario del ecosistema solo tenemos ventilador.
    .hasFan            = true,
    // Períodos de publicación automática:
    .telemetryPeriodMs = 5000,
    .statusPeriodMs    = 10000,
    // Identificación en el portal:
    .hardwareVersion   = "1.0",
    .firmwareVersion   = "0.1.0",
    .model             = "DIY Air Filter",
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

!!! note "DeviceType::Unknown — está bien"
    El tipo `Unknown` significa "el portal no conoce este producto". Antes esto era un problema: el portal no tenía tarjeta para un tipo desconocido. Ahora es el camino estándar: el interface del dispositivo lo describir completamente el card manifest ([capítulo 6](06-card.md)), y el portal construirá la tarjeta según él. El tipo es necesario solo para los "propios" productos de iDryer, que tienen tarjetas de marca.

La bandera `hasFan = true` nos da de forma gratuita: el campo `fanStatus` en telemetría, la celda "Ventilador" en la tarjeta y una entidad en el manifest — todo del diccionario del ecosistema.

## No hay un sensor VOC en Config — y no debería haberlo

Fíjate: no hay una bandera "hasVoc" en `Config`. El diccionario `has*` describe la periféria que conoce el ecosistema. Tu sensor propio lo agregarás no a través del diccionario, sino a través de dos mecanismos diferentes: escribirás tus lecturas en la telemetría con tu propio campo y lo declararás en el card manifest — estos son los dos capítulos siguientes. En eso está la esencia del enfoque: el diccionario no necesita expandirse para cada dispositivo nuevo.

## Primer inicio y vinculación

El procedimiento no difiere del ejemplo del gabinete:

1. Carga el firmware en la placa, abre Serial Monitor.
2. El dispositivo levantará Wi-Fi (datos de `secrets.h`), se registrará e imprimirá el PIN:
   ```text
   [CLOUD] PIN: 1234567 (expires in 600s)
   ```
3. En el [portal](https://portal.idryer.org/) — "Agregar dispositivo" → ingresa el PIN.
4. Después de la vinculación aparecerá `Device claimed!` en el registro, el dispositivo pasará a `En línea`.

Análisis detallado de la vinculación, errores Wi-Fi y re-vinculación — en el [capítulo del ejemplo del gabinete](../09-build-a-device/04-firmware-start.md).

El dispositivo ya es visible en el portal, pero la tarjeta sigue casi vacía — aún no hay datos. Vamos a conectar el sensor.
