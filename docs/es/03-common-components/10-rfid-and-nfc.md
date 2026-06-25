# RFID y NFC

RFID es identificación por radiofrecuencia. NFC es una tecnología relacionada para un alcance muy corto, a menudo en la frecuencia `13.56 MHz`.

En un sencillo dispositivo de bricolaje, es una forma de leer una tarjeta, llavero, pegatina o etiqueta sin contacto por cable. Por ejemplo, un usuario trae una etiqueta de carrete de filamento y el dispositivo selecciona el perfil del material.

El principal error es pensar que "RFID" significa compatibilidad universal. En la práctica, es necesario alinear la frecuencia, el tipo de etiqueta, el microchip del lector, la biblioteca, la interfaz, la alimentación y la ubicación de la antena.

## Dónde se usa

En proyectos similares a iDryer, RFID/NFC se puede utilizar para:

- identifying a filament spool;
- selecting a material profile;
- vincular configuraciones a una etiqueta;
- service access;
- user action confirmation;
- consumable tracking;
- experimentos con etiquetas en contenedores, carretes o casetes.

Para la selección del perfil de material, a menudo basta con leer el UID de la etiqueta y almacenar una tabla `UID -> material`. Pero este enfoque debe tener un recurso manual: si la etiqueta no se lee, el usuario aún puede elegir manualmente el perfil.

## RFID y NFC en términos simples

RFID es un término amplio. Incluye diferentes frecuencias, estándares, rangos y tipos de etiquetas.

NFC suele significar comunicación de campo cercano en `13.56 MHz`, compatible con parte del ecosistema RFID. NFC se conoce por las tarjetas bancarias, los teléfonos, las pegatinas NTAG y las tarjetas MIFARE, pero esto no significa que ningún lector NFC lea ninguna tarjeta ni ningún dato.

Para pequeños dispositivos de bricolaje, los módulos `13.56 MHz` son los más comunes:

- RC522 / MFRC522;
- PN532;
- ready-made USB/UART RFID/NFC readers;
- Módulos NFC con SPI, I2C o UART.

Existen otros sistemas RFID, como las tarjetas de acceso `13.56 MHz` o UHF RFID. No son compatibles con los módulos NFC `13.56 MHz`.

## RC522

RC522 es un módulo `13.56 MHz` común y económico para tarjetas y etiquetas. Se usa frecuentemente con Arduino y ESP32.

Pros:

- cheap;
- many examples;
- adecuado para lectura UID sencilla;
- Generalmente se conecta a través de SPI.

Cons:

- a menudo funciona sólo con potencia y lógica `3.3V`;
- cheap module quality varies;
- el rango de lectura es pequeño;
- la compatibilidad con el tipo de tarjeta es limitada;
- El pin `SS` en la placa a menudo significa `CS`/`SDA` para SPI, no I2C `SDA`.

RC522 funciona si solo necesita leer UID de tarjetas o llaveros tipo MIFARE a corta distancia. Para tareas NFC más amplias, PN532 suele ser más conveniente.

## PN532

PN532 es un controlador NFC/RFID más flexible. Muchos módulos PN532 pueden funcionar a través de:

- SPI;
- I2C;
- UART.

Pero la interfaz elegida normalmente debe configurarse físicamente en la placa: puentes, interruptores DIP o soldadura. No puede conectar un módulo a través de I2C si está configurado en modo SPI.

A menudo se elige PN532 si necesita:

- more interface options;
- better NFC scenario support;
- trabajar con diferentes tipos de etiquetas;
- Python/CircuitPython/Raspberry Pi scenarios;
- better documented module.

Pero PN532 tampoco es un lector universal mágico. Debe verificar tipos de tarjetas específicos, biblioteca y modo de trabajo.

## Frecuencia y tipo de etiqueta

La etiqueta debe coincidir con el lector.

Antes de comprar etiquetas, verifique:

- frequency: `13.56 MHz`, `125 kHz` or other;
- type: MIFARE Classic, NTAG213/215/216, ISO14443A or other;
- si solo necesitas leer el UID;
- si necesita leer/escribir datos personalizados;
- si la biblioteca elegida admite las operaciones necesarias;
- si puede colocar físicamente la etiqueta en un carrete o caja.

Si la tarea es seleccionar un perfil de material, normalmente es más sencillo leer el UID y almacenar el perfil por separado. Escribir datos dentro de la etiqueta complica el proyecto: hay que pensar en el formato de los datos, la compatibilidad, la protección contra escritura y los errores de escritura.

## UID - Not Security

Es conveniente utilizar el UID de una tarjeta o etiqueta como identificador. Pero UID no es una protección confiable.

Para un perfil de spool, esto es normal: si conoce el UID, seleccione el perfil. Un error no es crítico porque el usuario puede comprobar el material manualmente.

Para acceder a funciones peligrosas, modos de servicio o desbloquear un calentador, el UID por sí solo es débil. Algunos UID se pueden copiar o falsificar y algunas tarjetas tienen límites de seguridad conocidos.

Practical rule:

- UID es bueno por conveniencia e identificación de consumibles;
- UID no debería ser la única protección para modos peligrosos;
- Para calentadores y piezas eléctricas, siempre es necesario realizar controles de seguridad por separado.

## Niveles de potencia y lógica

Muchos módulos RFID/NFC están clasificados para la lógica `3.3V`. Esto es especialmente importante para los módulos de conexión RC522 y PN532.

Comprobar:

- module power voltage;
- nivel lógico en SPI/I2C/UART;
- si la junta tiene un regulador;
- whether signal lines have level matching;
- si se necesitan resistencias pull-up I2C;
- si se necesita un terreno común con el controlador.

La presencia del pin `5V` en una placa de módulo no siempre significa que las líneas de señal toleren `5V`. Algunos módulos pueden recibir alimentación desde `3.3V` a través de un regulador, pero la lógica sigue siendo `3.3V`.

## Connection Interface

An RFID/NFC module can connect via SPI, I2C or UART.

SPI:

- rápido y común;
- requires `SCK`, `MOSI`, `MISO`, `CS`;
- en RC522, el pin `CS` a menudo significa `CS`;
- Es importante no mezclar `MISO` y `MISO`.

I2C:

- utiliza `SCL` y `SCL`;
- puede compartir bus con otros dispositivos;
- needs correct pull-up resistors;
- Es importante comprobar la dirección y el modo del módulo seleccionado.

UART:

- utiliza `RX` y `RX`;
- El `RX` de un dispositivo va al `RX` de otro;
- conveniente para algunos lectores ya preparados;
- necesita velocidad y protocolo coincidentes.

La conexión SPI RC522 detallada se encuentra en la sección práctica: [Conectar un lector RFID](../06-practical-guides/05-connecting-rfid-reader.md).

## Antena y estuche

RFID/NFC funciona a través de una antena. En módulos pequeños, normalmente está impreso directamente en la placa.

La lectura se ve afectada por:

- antenna size;
- tag orientation;
- distance;
- case plastic;
- metal nearby;
- cables y líneas eléctricas cercanas;
- module power;
- tag type;
- donde el usuario trae la tarjeta.

El metal cerca de la antena puede empeorar drásticamente la lectura. Si el lector se monta cerca del marco metálico de la impresora, tornillos, pantalla, fuente de alimentación o panel de aluminio, el alcance puede ser mucho peor.

Para el caso, es mejor dejar una zona clara: "traer etiqueta aquí". No espere que la etiqueta de un carrete siempre lea automáticamente a través del plástico, el aire, el eje, el soporte y las piezas cercanas.

## Device Logic

La RFID debería mejorar la comodidad, no alterar el control.

Lógica normal para un carrete:

1. User brings a tag.
2. El dispositivo lee UID.
3. El UID se busca en la tabla de perfiles.
4. Si se encuentra UID, se sugiere el perfil del material.
5. User can confirm or change profile.
6. Si no se encuentra el UID o no se lee, la selección manual está disponible.

Bad logic:

- el dispositivo no puede iniciarse sin una etiqueta;
- unknown tag selects random profile;
- el error de lectura mantiene silenciosamente el perfil antiguo;
- cambios de perfil sin confirmación del usuario;
- UID es la única protección para un modo de servicio.

Para un calentador, es especialmente importante que la selección del perfil no pase por alto los límites de temperatura, los sensores y la protección de emergencia.

## Qué comprobar antes de comprar

Antes de comprar, consulte:

- module frequency;
- supported tag types;
- interface: SPI, I2C, UART, USB;
- power voltage;
- logic levels;
- disponibilidad de coincidencia de niveles;
- disponibilidad de documentación y pinout;
- cómo se selecciona la interfaz en el tablero;
- si hay una biblioteca para su controlador;
- antenna size;
- tipo y tamaño de etiqueta;
- rango esperado en un caso real;
- si es posible la selección de respaldo manual.

Para un primer proyecto, elija un módulo con buena documentación y ejemplos, no el más barato sin un esquema.

## Típicos Errors

- compré la tarjeta `13.56 MHz` para el lector `13.56 MHz`;
- conectado `5V` RC522 a la alimentación o lógica `5V`;
- tomó el pin `SDA` en RC522 para I2C `SDA`;
- mezclado `MISO` y `MISO`;
- forgot `CS`/`SS` in SPI;
- configuró una interfaz en PN532 con puentes pero conectó una diferente;
- no colocó pull-ups I2C donde era necesario;
- put antenna near metal;
- probé la lectura en el banco pero no probé por si acaso;
- hizo de RFID la única forma de seleccionar el perfil;
- utilice UID como protección de acceso confiable;
- no manejó la situación de "la etiqueta no se leyó".

## Principal Point

RFID/NFC es útil para la identificación de carretes, la selección de perfiles de materiales y la entrada de servicios simples. Pero no es un lector universal para ninguna tarjeta ni un sistema de seguridad confiable en sí mismo.

Primero elija la frecuencia y los tipos de etiquetas, luego el módulo, la interfaz, la alimentación y la ubicación de la antena. Luego pruebe la lectura en un caso real y definitivamente mantenga la selección de respaldo manual.

## Referencia Materials

- [Adafruit: PN532 RFID/NFC Breakout Wiring](https://learn.adafruit.com/adafruit-pn532-rfid-nfc/breakout-wiring) - PN532 connection, SPI/I2C/UART selection and warning about `3.3V` logic.
- [Adafruit: PN532 RFID/NFC guide, single page](https://learn.adafruit.com/adafruit-pn532-rfid-nfc?view=all) - complete PN532 guide, CircuitPython/Python, interfaces and SEL jumper setup.
- [Adafruit PN532 product page](https://www.adafruit.com/product/364) - description of PN532 module, supported interfaces and NFC/RFID capabilities.
- [NXP: MFRC522 Standard performance MIFARE and NTAG frontend](https://www.nxp.com/products/rfid-nfc/nfc-hf/nfc-readers/standard-performance-mifare-and-ntag-frontend:MFRC52202HN1) - MFRC522/RC522 microchip page and its purpose for `13.56 MHz` MIFARE/NTAG scenarios.
- [DigiKey: MFRC522 Datasheet by NXP](https://www.digikey.com/htmldatasheets/production/993456/0/0/1/mfrc522.html) - technical description of MFRC522: `13.56 MHz` reader/writer, ISO/IEC 14443 A/MIFARE/NTAG support and communication interfaces.
