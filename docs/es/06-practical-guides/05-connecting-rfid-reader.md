# Conectar un Lector RFID

Un lector RFID/NFC le permite leer una tarjeta, etiqueta o llavero sin contacto alambrado.

En dispositivos similares a iDryer, esto puede ser útil para identificación de carrete, selección de perfil de material, acceso de servicio o experimentos de seguimiento de consumibles.

Error principal: compre un "módulo RFID" y asuma que cualquier tarjeta se leerá desde cualquier distancia en cualquier controlador. En realidad, necesita verificar frecuencia, tipo de etiqueta, interfaz, potencia, niveles lógicos y colocación de antena.

## Módulos Populares

Los comunes incluyen:

- RC522 / MFRC522;
- PN532;
- lectores RFID/UART USB listos;
- módulos NFC con I2C, SPI o UART.

Para proyectos simples de impresoras 3D, los módulos de 13.56 MHz y etiquetas son más comunes: tarjetas, llaveros, etiquetas compatibles con NTAG/MIFARE.

## Qué Verificar Antes de Conectar

Antes de conectar, encuentre:

- frecuencia del módulo;
- tipos de tarjeta y etiqueta soportados;
- interfaz: SPI, I2C o UART;
- voltaje de suministro;
- niveles lógicos;
- pinout de la placa;
- selección de interfaz mediante jumpers o puentes de soldadura;
- distancia de lectura;
- antena y requisitos de colocación.

Si el módulo está clasificado para `3.3V`, no puede simplemente engancharlo a lógica de potencia o `5V` sin verificar. Algunas placas tienen reguladores de voltaje pero carecen de cambio de nivel en líneas de señal.

## RC522: Conexión SPI Típica

Los módulos RC522 baratos generalmente funcionan a `3.3V` y más comúnmente se conectan vía SPI.

Líneas típicas:

- `VCC` - potencia `3.3V`;
- `GND` - tierra;
- `SCK` - señal de reloj SPI;
- `MOSI` - datos del controlador al módulo;
- `MISO` - datos del módulo al controlador;
- `SDA`, `SS` o `CS` - selección de chip SPI;
- `RST` - reinicio;
- `IRQ` - interrupción, a menudo no usada en proyectos simples.

![Módulo RFID RC522 (MFRC522) para leer tarjetas de 13.56 MHz](../../../img/06-practical-guides/05-rfid-rc522-module.jpg)

*Fuente: [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:RFID-RC522_photo.jpg), Giacomo Alessandroni, CC BY-SA 4.0*

Los nombres de pin pueden diferir. Por ejemplo, en RC522, el pin `SDA` a menudo significa `SS`/`CS` para SPI, no la línea I2C `SDA`. Esta es una fuente común de confusión.

## PN532: SPI, I2C o UART

PN532 es un módulo más flexible. Dependiendo de la placa, puede funcionar vía:

- SPI;
- I2C;
- UART.

Pero no puede simplemente conectar cualquier pin. En muchas placas PN532, la interfaz se selecciona mediante jumpers, interruptores DIP o puentes de soldadura.

Antes de conectar, verifique:

- qué interfaz está físicamente seleccionada en la placa;
- qué pines coinciden con la interfaz seleccionada;
- si se necesitan resistencias pull-up para I2C;
- si se necesita pin pull-up o reinicio;
- si los niveles lógicos son compatibles con el controlador.

Si la placa dice "lógica 3.3V", no la conecte directamente a GPIO de 5V.

## Tierra Común

Como otros módulos, se necesita tierra común.

Si el módulo RFID se alimenta desde una fuente y el controlador desde otra, su `GND` debe estar conectado.

Sin tierra común, SPI/I2C/UART puede no funcionar o funcionar inestablemente.

## La Etiqueta Debe Coincidir con el Lector

RFID/NFC no es un estándar universal único.

Un módulo solo puede leer físicamente etiquetas soportadas por su chip y librería.

Verificar:

- frecuencia de etiqueta;
- tipo de tarjeta o llavero;
- el módulo soporta MIFARE, NTAG, ISO14443A o el tipo necesario;
- solo necesita leer UID o también leer/escribir datos;
- la librería elegida soporta la operación necesaria.

Para selección simple de perfil de material, a menudo es suficiente solo leer el UID de etiqueta y almacenar mapeo de UID -> material en firmware u host.

## Distancia de Lectura

La distancia de lectura para módulos RFID/NFC pequeños generalmente es corta.

Los resultados dependen de:

- tamaño de antena;
- tipo de etiqueta;
- orientación de etiqueta;
- distancia;
- plástico del alojamiento;
- metal cercano;
- interferencia;
- potencia del módulo.

El metal cerca de la antena puede empeorar drásticamente la lectura. Si el lector se monta en una secadora, cámara o soporte de carrete, pruebe la distancia en el ensamblaje real, no solo en el banco.

## Dónde Colocar el Lector

Para un carrete de filamento, es mejor colocar el lector RFID/NFC donde el usuario intencionalmente trae la etiqueta.

No diseñe la lógica asumiendo que la etiqueta siempre se leerá automáticamente.

Opciones prácticas:

- zona "traiga etiqueta aquí" en el alojamiento;
- ubicación cerca del soporte de carrete;
- zona de servicio para tarjeta de acceso;
- panel separado con distancia de lectura corta.

Si la etiqueta está en el carrete, pruebe con diferentes carretes, orientación de etiqueta diferente, plástico diferente y proximidad de metal.

## Primer Inicio

Antes de integración:

1. Conecte módulo en el banco.
2. Ejecute un ejemplo de la librería para su módulo.
3. Verifique que la tarjeta o etiqueta se lee establemente.
4. Registre UID de varias etiquetas.
5. Verifique que tarjetas no soportadas no rompan la lógica.
6. Monte módulo en alojamiento y pruebe nuevamente.

En esta etapa, no construya sistemas de perfil complejos de inmediato. Primero, logre lectura estable de UID.

## Lógica de Dispositivo de Ejemplo

Para perfil de material, la lógica simple puede ser:

1. El usuario trae etiqueta.
2. El dispositivo lee UID.
3. UID se busca en una tabla.
4. Si UID es conocido, se selecciona perfil de material.
5. Si UID es desconocido, el dispositivo pide selección manual de perfil.

RFID no debe ser el único método de control. Necesita una copia de seguridad manual: perfil en menú, botón, pantalla o configuración de interfaz.

## Qué Verificar Después del Ensamblaje

Verificar:

- el módulo recibe voltaje correcto;
- los niveles lógicos son compatibles con controlador;
- la interfaz correcta está seleccionada;
- `MOSI`, `MISO`, `SCK`, `CS` no están intercambiados para SPI;
- `SDA`, `SCL` no están intercambiados para I2C;
- `TX` y `RX` están correctamente cruzados para UART;
- existe tierra común;
- reinicio/IRQ están conectados como la librería requiere;
- etiquetas del tipo correcto se leen;
- la distancia de lectura es normal en el alojamiento;
- metal y cables no bloquean la antena;
- el dispositivo funciona normalmente si la etiqueta no se lee.

## Errores Comunes

- conectando RC522 3.3V a potencia 5V o lógica 5V;
- confundiendo RC522 `SDA` con I2C `SDA`;
- olvidando `CS`/`SS` en SPI;
- intercambiando `MOSI` y `MISO`;
- seleccionando una interfaz en PN532 con jumpers pero cableando otra;
- usando tipo de tarjeta no soportado;
- colocando antena justo junto a metal;
- probando distancia de lectura en banco pero no en alojamiento;
- hacer RFID el único método de selección de perfil;
- almacenando lógica importante solo en UID sin verificación de error de lectura.

## Puntos Clave

- El módulo RFID/NFC debe elegirse para etiquetas e interfaz específicas.
- RC522 generalmente necesita `3.3V` y SPI.
- PN532 puede funcionar vía SPI, I2C o UART, pero la interfaz debe seleccionarse en la placa.
- Se requiere tierra común.
- El metal cerca de la antena puede empeoran mucho la lectura.
- Para perfiles de material, el UID de etiqueta a menudo es suficiente, pero se necesita selección manual de copia de seguridad.
- Pruebe en el alojamiento real, no solo en el banco.

## Lecturas Relacionadas

- [Adafruit: PN532 RFID/NFC Breakout Wiring](https://learn.adafruit.com/adafruit-pn532-rfid-nfc/breakout-wiring) - conexión PN532, selección de SPI/I2C/UART y advertencias de lógica 3.3V.
- [Adafruit: PN532 RFID/NFC guide, single page](https://learn.adafruit.com/adafruit-pn532-rfid-nfc?view=all) - guía completa PN532, cableado, CircuitPython, Raspberry Pi y selección de interfaz.
- [Adafruit PN532 product page](https://www.adafruit.com/product/364) - capacidades PN532, soporte de etiqueta NFC/RFID e interfaces UART/I2C/SPI de 3.3V.
- [NXP: MFRC522 Standard performance MIFARE and NTAG frontend](https://www.nxp.com/products/rfid-nfc/nfc-hf/nfc-readers/standard-performance-mifare-and-ntag-frontend:MFRC52202HN1) - página oficial MFRC522/RC522 para escenarios MIFARE/NTAG de 13.56 MHz.
- [DigiKey: MFRC522 Datasheet by NXP](https://www.digikey.com/htmldatasheets/production/993456/0/0/1/mfrc522.html) - hoja de datos técnica MFRC522: tarjetas soportadas, potencia, interfaces de comunicación con controlador y efectos de antena/potencia en distancia.
