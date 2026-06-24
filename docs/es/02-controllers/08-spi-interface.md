# Interfaz SPI

SPI es una interfaz de comunicación serie rápida entre un controlador y dispositivos periféricos. Expansión: `Serial Peripheral Interface`.

SPI se usa frecuentemente donde los datos necesitan transmitirse más rápido que con I2C, o donde el dispositivo está diseñado para SPI: pantalla, tarjeta SD, módulo RFID, sensor, driver o chip de memoria.

## Dónde se usa SPI

En impresoras 3D y dispositivos similares al iDryer, SPI puede aparecer en:

- Módulos RFID/NFC como el RC522;
- Pantallas OLED/TFT;
- Tarjetas SD;
- Acelerómetros para el compensador de resonancias;
- Drivers de motores paso a paso, por ejemplo TMC2130/TMC5160;
- Chips de memoria;
- Placas ADC/DAC y de expansión;
- Algunos sensores y módulos especializados.

SPI suele ser más rápido que I2C, pero requiere más cables y una selección de pines más cuidadosa.

## Líneas básicas

Un SPI típico utiliza:

- `SCK` o `CLK` - señal de reloj;
- `MOSI` - datos del controlador al dispositivo;
- `MISO` - datos del dispositivo al controlador;
- `CS`, `SS` o `NSS` - seleccionar dispositivo específico;
- `GND` - tierra común;
- alimentación del módulo.

Diagrama con dos dispositivos:

![SPI: operación básica de intercambio entre dispositivo maestro y esclavo](../../img/02-controllers/08-spi-basic-operation.png)

*Fuente: [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:SPI_basic_operation,_single_Main_%26_Sub.svg), Em3rgent0rdr, CC0 Public Domain*

`SCK`, `MOSI` y `MISO` pueden ser compartidos por varios dispositivos. Pero cada dispositivo generalmente necesita su propio `CS`.

## CS en lugar de direcciones

En I2C, los dispositivos se distinguen por direcciones. En SPI, generalmente no hay direcciones. El controlador selecciona el dispositivo con una línea `CS` separada.

Ejemplo:

```text
SCK  -> common to all SPI devices
MOSI -> common
MISO -> common
CS1  -> RFID module
CS2  -> display
CS3  -> SD card
```

Cuando el controlador quiere comunicarse con el módulo RFID, activa `CS1`. Cuando quiere comunicarse con la pantalla, activa `CS2`.

Más comúnmente, `CS` es activo en bajo: en reposo la línea es `HIGH`, para seleccionar un dispositivo - `LOW`. Pero esto debe verificarse en la hoja de datos técnica.

## MOSI/MISO y nuevos nombres

En esquemas antiguos y muy comunes, los nombres son:

- `MOSI` - Master Out Slave In;
- `MISO` - Master In Slave Out;
- `SS` - Slave Select.

En documentación más reciente, puede ver nombres neutros:

- `PICO` - Peripheral In Controller Out, equivalente a MOSI;
- `POCI` - Peripheral Out Controller In, equivalente a MISO;
- `CS` - Chip Select.

En la electrónica de impresoras 3D, `MOSI`, `MISO`, `SCK`, `CS` siguen siendo muy comunes. Lo más importante es entender la dirección de la señal y verificar el pinout del módulo específico.

## MISO puede no ser necesario

No todos los dispositivos SPI envían datos de vuelta.

Por ejemplo, una pantalla simple puede recibir solo comandos y píxeles. Entonces la línea `MISO` puede estar ausente o sin usar.

Pero para dispositivos que leen datos, `MISO` es necesario:

- Módulo RFID;
- Tarjeta SD;
- Sensor;
- Driver con diagnósticos;
- Chip de memoria.

Si el módulo debe responder y `MISO` no está conectado o está invertido, la inicialización puede fallar.

## Velocidad y modo SPI

SPI tiene una velocidad. Puede ser mucho mayor que I2C, pero eso no significa que deba configurarse al máximo de inmediato.

El funcionamiento se ve afectado por:

- longitud del cable;
- calidad de la tierra;
- el módulo y su hoja de datos;
- nivel de ruido;
- frecuencia del controlador;
- el modo SPI elegido.

El modo SPI se establece mediante los parámetros de polaridad de reloj y fase de reloj: `CPOL` y `CPHA`. El modo 0 se usa frecuentemente, pero no siempre. Si el modo es incorrecto, el dispositivo puede no responder o devolver datos incorrectos.

En la mayoría de las bibliotecas listas para usar, el modo ya está configurado. Pero si está conectando un módulo inusual o escribiendo una configuración de bajo nivel, debe verificar la hoja de datos.

## 3.3V y 5V

Al igual que otras interfaces, SPI no garantiza niveles de voltaje seguros.

ESP32, RP2040, STM32 y muchos módulos modernos operan con lógica de `3.3V`. Arduino Uno/Nano frecuentemente usa `5V`.

Antes de conectar, verifique:

- alimentación del módulo;
- nivel lógico de `SCK`, `MOSI`, `MISO`, `CS`;
- si hay adaptación de niveles;
- si el módulo tolera `5V` en las entradas de señal;
- si la entrada del controlador tolera `5V`.

Por ejemplo, el RC522 generalmente requiere alimentación y lógica de `3.3V`. Conectarlo a un Arduino de `5V` sin adaptación de niveles es mala idea.

## SPI en Klipper

En Klipper, SPI se usa para varios dispositivos: drivers TMC, acelerómetros, algunas pantallas y sensores.

La configuración puede incluir:

- `cs_pin` - pin de selección del dispositivo;
- `spi_bus` - bus SPI de hardware;
- `spi_speed` - velocidad en Hz;
- `spi_software_sclk_pin`;
- `spi_software_mosi_pin`;
- `spi_software_miso_pin`.

Si el dispositivo está conectado a un MCU adicional, los pines deben pertenecer a ese MCU. Como con otras secciones de Klipper, el pinout específico de la placa es más importante que las suposiciones.

Idea aproximada:

```ini
[some_spi_device]
cs_pin: chamber:gpio9
spi_software_sclk_pin: chamber:gpio10
spi_software_mosi_pin: chamber:gpio11
spi_software_miso_pin: chamber:gpio12
```

Esto no es una configuración lista para un dispositivo específico, sino una ilustración: todos los pines SPI deben estar en el MCU al que el módulo está realmente conectado.

## Longitud del cable e interferencias

SPI puede funcionar rápido, pero no tolera cables largos y descuidados.

Reglas prácticas:

- mantenga `SCK`, `MOSI`, `MISO`, `CS` cortos;
- trace cerca de `GND`;
- no trace en paralelo con cables de calefactor y motor;
- reduzca `spi_speed` si hay errores;
- use conectores adecuados;
- no lleve SPI por toda la impresora sin motivo;
- para nodos remotos, elija con mayor frecuencia CAN, UART/RS-485 o un MCU separado cerca del módulo.

La línea `SCK` es especialmente sensible: es una señal de reloj. Si está contaminada, toda la comunicación puede volverse inestable.

## SPI y RC522

El RC522 es un buen ejemplo de módulo SPI con confusión de nombres.

En muchas placas RC522, el pin `SDA` se usa en realidad como `SS`/`CS` para SPI. No es el `SDA` de I2C.

Para el RC522, generalmente necesita:

- `3.3V`;
- `GND`;
- `SCK`;
- `MOSI`;
- `MISO`;
- `SDA`/`SS`/`CS`;
- `RST`;
- a veces `IRQ`, pero en proyectos simples frecuentemente no se usa.

Un diagrama detallado se encuentra en el artículo práctico: [Conexión de un lector RFID](../06-practical-guides/05-connecting-rfid-reader.md).

## Qué verificar antes de conectar

Antes de conectar un módulo SPI, verifique:

- alimentación del módulo;
- nivel lógico;
- pinout de la placa específica;
- dónde están `SCK`, `MOSI`, `MISO`, `CS`;
- si se necesitan `RST`, `DC`, `IRQ` u otros pines;
- qué `CS` está asignado al dispositivo;
- si `CS` no conflictúa con otro módulo;
- si se necesita SPI por hardware o SPI por software;
- qué velocidad recomienda la documentación;
- si el firmware soporta este módulo.

## Errores típicos

- confundidos `MOSI` y `MISO`;
- olvidó `CS`;
- conectó dos dispositivos a un mismo `CS`;
- no conectó `GND` común;
- aplicó `5V` a un módulo SPI de `3.3V`;
- confundió `SDA` en el RC522 con `SDA` de I2C;
- seleccionó velocidad demasiado alta;
- hizo los cables demasiado largos;
- conectó el módulo a un MCU pero especificó pines de otro;
- creer que SPI es una interfaz de potencia para alimentar cargas.

## Conclusión clave

SPI es una interfaz rápida para módulos cercanos al controlador. Generalmente se necesitan `SCK`, `MOSI`, `MISO`, `CS`, alimentación y `GND`.

La principal diferencia con I2C: SPI generalmente no tiene direcciones, y cada dispositivo se selecciona mediante un `CS` separado. Antes de conectar, verifique el pinout, los niveles lógicos, la velocidad, la longitud del cable y el soporte del firmware.

## Materiales relacionados

- [SparkFun: Serial Peripheral Interface](https://learn.sparkfun.com/tutorials/serial-peripheral-interface-spi) - explicación práctica de SPI, líneas de datos, nuevos nombres PICO/POCI y lógica de intercambio básica.
- [SparkFun: SPI Chip Select](https://learn.sparkfun.com/tutorials/serial-peripheral-interface-spi/chip-select-cs) - por qué se necesita `CS` y cómo conectar varios dispositivos SPI.
- [Adafruit: SPI Devices](https://learn.adafruit.com/circuitpython-basics-i2c-and-spi/spi-devices) - comparación SPI vs I2C, `CS` separado, velocidad, polaridad/fase y limitaciones.
- [DigiKey: SPI Simplifies Device Communication](https://www.digikey.com/en/articles/why-how-to-use-serial-peripheral-interface-simplify-connections-between-multiple-devices) - opciones para conectar varios dispositivos SPI y el papel de `CS`.
- [Klipper Configuration Reference: Common SPI settings](https://www.klipper3d.org/Config_Reference.html) - parámetros `spi_speed`, `spi_bus`, SPI por software y `cs_pin` en Klipper.
