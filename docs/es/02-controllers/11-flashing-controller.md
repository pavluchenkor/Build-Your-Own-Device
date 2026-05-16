# Flasheo del Controlador

Firmware (`firmware`) es un programa escrito en la memoria flash de un microcontrolador. Sin firmware, la placa no sabe qué hacer con pines, sensores, ventiladores e interfaces.

Importante: no confundas firmware y configuración. El firmware se escribe en el controlador. La configuración de Klipper generalmente vive en el host en `printer.cfg` y le dice al MCU ya flasheado qué pines y parámetros usar.

## Firmware, bootloader, configuración

Tres conceptos diferentes:

- **firmware** - programa principal del microcontrolador;
- **bootloader** - pequeño programa que ayuda a escribir el firmware principal;
- **config** - configuración del dispositivo, por ejemplo `printer.cfg` en Klipper.

El bootloader se ejecuta primero y puede aceptar nuevo firmware a través de USB, UART, DFU, tarjeta SD, CAN u otro mecanismo. Si el bootloader se borra accidentalmente, flashear la placa puede volverse difícil: a veces se necesita ST-LINK/SWD, USB-UART u otro programador.

## Ruta general

Antes de flashear, el procedimiento normal es:

1. Aprende el modelo exacto de la placa.
2. Aprende el microcontrolador exacto.
3. Encuentra el diagrama de pines, esquemático e instrucciones del fabricante.
4. Entiende si se necesita firmware independiente o firmware MCU de Klipper.
5. Encuentra una configuración lista o ejemplo para esta placa.
6. Elige el método de flasheo correcto.
7. Construye o descarga el archivo correcto.
8. Pon la placa en modo de flasheo.
9. Escribe el firmware.
10. Verifica que la placa aparece en el sistema.
11. Verifica comunicación con host y pines básicos sin carga.

No puedes adivinar configuraciones de firmware. Para Klipper, el tipo de microcontrolador, offset del bootloader, referencia de reloj e interfaz de comunicación son especialmente importantes.

## Métodos de flasheo típicos

Las diferentes placas flashean de diferentes formas:

![Caminos principales para flashear el controlador](../../../img/02-controllers/11-controller-flashing-paths.svg)

Variantes comunes:

- **almacenamiento masa USB / UF2** - la placa aparece como disco, `.uf2` se copia a él;
- **DFU USB** - la placa entra en modo DFU, firmware se escribe a través de USB;
- **serie USB / bootloader UART** - firmware a través de puerto serie;
- **ST-LINK / SWD** - el programador se conecta a pines SWD;
- **tarjeta SD** - algunas placas de impresora 3D flashean con archivo en la tarjeta;
- **CAN/Katapult/CanBoot** - firmware a través de bootloader CAN;
- **bootloader Arduino** - flasheo de sketch a través de Arduino IDE o avrdude.

No hay un método universal para todas las placas. El método está determinado por la placa específica, bootloader y firmware.

## RP2040 y UF2

Para Raspberry Pi Pico y muchas placas RP2040, la forma más simple es `BOOTSEL` y UF2.

Usualmente:

1. Mantén presionado `BOOTSEL`.
2. Conecta USB.
3. La placa aparece como disco `RPI-RP2`.
4. Copia archivo `.uf2`.
5. El disco desaparece, la placa se reinicia.

El BOOTSEL de Pico está en la ROM del microcontrolador, así que no se puede borrar accidentalmente por flasheo normal. Esto hace que RP2040 sea conveniente para principiantes.

## STM32: DFU, ST-LINK, tarjeta SD

Las placas STM32 flashean de diferentes formas.

Opciones posibles:

- bootloader DFU USB integrado;
- bootloader UART;
- ST-LINK/SWD;
- tarjeta SD en placa de impresora;
- bootloader del fabricante de la placa;
- bootloader CAN.

Para STM32, el offset del bootloader es a menudo importante. Por ejemplo, si el bootloader ocupa los primeros `8 KiB`, Klipper debe construirse con el offset correcto. Si se elige mal, la placa puede no iniciar después del flasheo.

ST-LINK/SWD es útil como opción más de bajo nivel: a menudo puede recuperar una placa si el bootloader normal no funciona. Pero esto requiere pines SWD, programador y comprensión de la conexión.

## Klipper: make menuconfig

Para firmware de Klipper, usualmente haces:

```bash
cd ~/klipper
make menuconfig
make
```

En `make menuconfig`, seleccionas:

- arquitectura de microcontrolador;
- modelo de procesador;
- offset del bootloader;
- referencia de reloj;
- interfaz de comunicación: USB, serie, CAN, etc.;
- a veces parámetros adicionales para placa específica.

Los valores correctos a menudo se escriben en comentarios en la parte superior de un archivo de configuración listo para la placa. Si tal configuración existe, lee primero sus comentarios superiores.

Después de construir, el archivo firmware generalmente aparece en `~/klipper/out/`. Luego, se escribe usando el método adecuado para la placa específica.

## Verificación después del flasheo

Después del flasheo, debes verificar más que solo "el flasher escribió éxito".

Verifica:

- ¿aparece el dispositivo en el sistema?
- ¿está presente `/dev/serial/by-id/...`, si usas USB/serie?
- ¿es visible `canbus_uuid`, si usas CAN?
- ¿coincide la ruta con `printer.cfg`?
- ¿no hay errores de comunicación en Klipper?
- ¿coinciden los pines con el diagrama de pines de esta placa específica?
- ¿funcionan entradas/salidas básicas sin carga de potencia?
- ¿están ventilador/MOSFET/SSR apagados en estado seguro?

Para la primera verificación, no conectes el calentador como la carga final. Primero verifica comunicación, sensores y lógica bajo condiciones seguras.

## Qué guardar antes del flasheo

Antes de cambiar firmware, es útil guardar:

- `printer.cfg` actual;
- versión antigua del firmware, si está disponible;
- modelo de placa y microcontrolador;
- ruta de serie o UUID de CAN encontrado;
- foto de conexiones;
- diagrama de pines;
- configuración de `make menuconfig`;
- enlace a instrucciones del fabricante.

Si algo sale mal, estos datos ayudarán a recuperarse rápidamente.

## Qué puede salir mal

Problemas comunes:

- el cable USB es solo de carga;
- la placa no entró en bootloader;
- se seleccionó el microcontrolador incorrecto;
- se seleccionó el offset del bootloader incorrecto;
- se seleccionó la interfaz de comunicación incorrecta;
- firmware escrito, pero la placa se busca en el lugar incorrecto;
- la ruta de serie cambió después de reconectar;
- la tarjeta SD no se lee por la placa;
- el archivo firmware tiene nombre incorrecto para el bootloader de la placa;
- controlador DFU/USB-UART no instalado;
- placa alimentada desde dos lados;
- después del flasheo, la configuración hace referencia a pines antiguos.

No cambies todo en respuesta al primer error. Es mejor ir paso a paso: cable, modo bootloader, modelo MCU, configuración de construcción, método de escritura, aparición del dispositivo del sistema, configuración.

## Flasheo y seguridad

El firmware puede encender y apagar salidas, pero no reemplaza la seguridad de hardware.

Para calentadores necesitas:

- interruptor de potencia correcto;
- fusible;
- protección térmica independiente;
- sensor de temperatura correcto;
- carcasa segura;
- verificación del comportamiento en error de firmware, MCU congelado o comunicación perdida.

Después de flashear el controlador, no conectes el calentador sin verificar que el pin está elegido correctamente, la lógica de encendido no está invertida y los límites de seguridad funcionan.

## Errores típicos

- confundir firmware y `printer.cfg`;
- flashear archivo de placa similar pero diferente;
- no leer comentarios en la parte superior de configuración Klipper lista;
- seleccionar offset de bootloader incorrecto;
- borrar bootloader sin entender las consecuencias;
- usar cable USB solo de carga;
- no poner la placa en modo de flasheo;
- buscar placa CAN en `/dev/serial/by-id`;
- buscar placa USB-serie a través de `canbus_uuid`;
- conectar carga de potencia antes de verificar pines;
- no guardar configuración antigua.

## Conclusión clave

El firmware es el programa dentro del controlador, la configuración son sus configuraciones operacionales. Para cada placa, debes conocer el modelo exacto, microcontrolador, bootloader, método de flasheo y parámetros de construcción.

Para RP2040, UF2/BOOTSEL es usualmente lo más simple. Para STM32, verifica la placa específica: DFU, ST-LINK, tarjeta SD, bootloader UART o CAN. Para Klipper, primero encuentra una configuración lista y comentarios para `make menuconfig`.

## Materiales relacionados

- [Klipper: Installation - Building and flashing the micro-controller](https://www.klipper3d.org/Installation.html#building-and-flashing-the-micro-controller) - ruta oficial para `make menuconfig`, `make` y verificación de ruta de serie.
- [Klipper: Bootloaders](https://www.klipper3d.org/Bootloaders.html) - por qué los bootloaders difieren entre placas, por qué se necesita offset del bootloader y cómo se flashean diferentes MCU.
- [Raspberry Pi Documentation: Pico-series microcontrollers](https://www.raspberrypi.com/documentation/microcontrollers/raspberry-pi-pico.html) - BOOTSEL, UF2 y especificidades de Pico/RP2040/RP2350.
- [Raspberry Pi Documentation: C/C++ SDK - Your First Binaries](https://www.raspberrypi.com/documentation/microcontrollers/c_sdk.html#your-first-binaries) - ejemplo oficial de BOOTSEL, almacenamiento masa USB `RPI-RP2` y flasheo de Pico vía UF2.
- [STMicroelectronics: STM32CubeProgrammer](https://www.st.com/en/development-tools/stm32cubeprog.html) - herramienta oficial de STM32 para flasheo a través de ST-LINK/SWD, UART, USB DFU, SPI, I2C y bootloader CAN.
