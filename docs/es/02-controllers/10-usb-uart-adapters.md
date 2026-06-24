# Adaptadores USB-UART

Un adaptador USB-UART es necesario para que una computadora o host Linux pueda comunicarse con un dispositivo UART a través de USB. Convierte USB en líneas serie estándar `TX`, `RX` y `GND`.

Este tipo de adaptador suele ser necesario para flashear, leer logs, realizar diagnósticos y recuperar placas que no tienen un conector USB adecuado.

## Dónde se necesita

El adaptador USB-UART es útil para:

- flashear algunas placas de microcontroladores;
- leer logs serie;
- acceder a la consola del dispositivo;
- diagnósticos en modo bootloader;
- conectar Arduino Pro Mini y algunos clones de Nano;
- trabajar con placas sin USB integrado;
- recuperación tras un flasheo fallido;
- conexión temporal del MCU al host mediante serie.

Si una placa ya tiene USB adecuado y aparece como dispositivo serie, puede que no sea necesario un adaptador USB-UART adicional.

## Qué contiene

Contactos típicos:

- `TX` o `TXO` — transmisión desde el adaptador al dispositivo;
- `RX` o `RXI` — recepción desde el dispositivo;
- `GND` — masa común;
- `VCC`, `3V3` o `5V` — alimentación, si se necesita;
- `DTR` — usado habitualmente para auto-reset/flasheo;
- `RTS`, `CTS` — líneas de control de flujo o escenarios de arranque/reset.

Diagrama de conexión:

![Adaptador USB-UART con chip CH340T](../../img/02-controllers/10-usb-uart-ch340-adapter.jpg)

*Fuente: [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:15938_-_USBtoSerial_1.jpg), SparkFun Electronics, CC BY 2.0*

Para la lectura simple de logs, `TX`, `RX` y `GND` suelen ser suficientes. La alimentación solo se conecta si está claro que la placa debe recibir energía desde el adaptador.

## Cómo conectar TX y RX

La conexión es cruzada:

```text
TX adapter -> RX device
RX adapter <- TX device
GND adapter -> GND device
```

Si no hay conexión, lo primero que hay que comprobar es: si `TX` y `RX` están invertidos, si hay una `GND` común, si la velocidad coincide y si el puerto COM/tty correcto está seleccionado.

## 3.3V y 5V

Los adaptadores USB-UART existen en variantes:

- solo `3.3V`;
- solo `5V`;
- con selector `3.3V/5V`;
- con jumper o jumper de soldadura;
- con `VCC` de un voltaje pero señales en otro nivel.

Esto es importante: el nivel de `VCC` y el nivel de `TX/RX` no siempre son evidentes a partir de las etiquetas.

ESP32, RP2040 y STM32 suelen usar lógica de `3.3V`. Arduino Uno/Nano frecuentemente usa lógica de `5V`. Si se aplica una señal de `5V` a una entrada de `3.3V`, se puede dañar la placa.

Antes de conectar, consulta la documentación del adaptador y de la placa. No te fíes únicamente del color del jumper o de la etiqueta en la carcasa.

## TTL UART y RS-232

El adaptador USB-UART para microcontroladores generalmente entrega UART TTL/CMOS: `3.3V` o `5V`.

Esto no es lo mismo que el RS-232 real.

El RS-232 tiene niveles de voltaje diferentes y no puede conectarse directamente a un GPIO de microcontrolador. Si necesitas trabajar con un puerto RS-232 real, necesitas un adaptador USB-RS232 o un convertidor de niveles, no un USB-UART TTL convencional.

## Alimentación desde el adaptador

El pin `VCC` del adaptador puede ser útil, pero con frecuencia se usa de forma incorrecta.

Enfoque seguro:

- para logs y diagnósticos, conecta primero solo `TX`, `RX`, `GND`;
- no conectes `VCC` si la placa ya recibe alimentación por USB, fuente de alimentación u otro circuito;
- no alimentes motores, servos, relés, calentadores ni tiras LED a través del adaptador USB-UART;
- verifica cuánta corriente puede suministrar realmente el adaptador;
- ten en cuenta que `VCC` puede ser `3.3V` o `5V`.

Si conectas dos fuentes de alimentación sin entender el circuito, puedes provocar alimentación inversa, inestabilidad o daños en la placa.

## DTR y RTS

Algunas placas usan `DTR` y `RTS` para auto-reset o para entrar en modo bootloader.

Ejemplos:

- Arduino Pro Mini suele usar `DTR` a través de un condensador para el reset durante el flasheo;
- las placas ESP32 pueden usar `DTR`/`RTS` para controlar automáticamente `EN` y `BOOT`;
- algunos escenarios de bootloader requieren presionar un botón manualmente si estas líneas no están conectadas.

Si el flasheo no arranca automáticamente, no siempre es un problema de `TX/RX`. Puede ser que `DTR`/`RTS` no estén conectados, que se haya seleccionado el bootloader incorrecto, o que sea necesario presionar manualmente `BOOT`/`RESET`.

## CH340, CP2102, FTDI

Chips USB-UART populares:

- **CH340/CH341** — adaptadores económicos y muy extendidos;
- **CP2102/CP210x** — USB-UART de Silicon Labs, muy común;
- **FT232/FTDI** — opción clásica, generalmente más cara;
- **PL2303** — presente en adaptadores y cables antiguos.

En sistemas modernos, el driver suele instalarse automáticamente, pero no siempre. Si el puerto no aparece, comprueba:

- que el cable USB no sea solo de carga;
- que el sistema detecte el dispositivo;
- si se necesita un driver;
- si un driver antiguo no está causando conflictos;
- si el puerto no está siendo usado por otro programa.

## Cómo probar el adaptador

Prueba de loopback simple:

1. Conecta el adaptador a la computadora.
2. Conecta `TX` del adaptador a `RX` del adaptador.
3. Abre un terminal serie.
4. Selecciona el puerto y la velocidad, por ejemplo `115200`.
5. Escribe caracteres.
6. Si funciona, los caracteres se devuelven como eco.

Esto prueba el adaptador en sí, el driver, el cable y el programa terminal sin ninguna placa externa.

## Qué verificar antes de comprar

Antes de adquirir un adaptador USB-UART, verifica:

- qué niveles tienen `TX/RX`: `3.3V`, `5V` o seleccionable;
- cómo se selecciona el nivel;
- qué chip se usa: CH340, CP2102, FTDI u otro;
- si hay drivers disponibles para tu sistema;
- si están presentes `DTR` y `RTS`, en caso de necesitar auto-flasheo;
- qué conector USB tiene;
- si los pines `GND`, `TX`, `RX`, `VCC` están en un orden conveniente;
- si existe un esquema o documentación clara;
- cuánta corriente se puede extraer de `VCC`, si fuera necesario.

Para diagnósticos con ESP32/RP2040/STM32, un adaptador con señales de `3.3V` y marcado claro es más conveniente.

## Errores típicos

- conectar `TX` con `TX`, `RX` con `RX`;
- olvidar la `GND` común;
- seleccionar nivel `5V` para una placa de `3.3V`;
- conectar `VCC` a una placa que ya tiene alimentación;
- alimentar cargas a través del adaptador USB-UART;
- confundir USB-UART TTL con USB-RS232;
- usar un cable USB solo de carga;
- no instalar el driver CH340/CP2102/FTDI;
- seleccionar un puerto COM/tty incorrecto;
- no conectar `DTR`/`RTS` cuando son necesarios para el auto-flasheo;
- dejar el terminal serie abierto y luego preguntarse por qué el flasheador no puede abrir el puerto.

## Conclusión clave

El adaptador USB-UART es un puente entre el USB de la computadora y los pines UART de un dispositivo. Para una conexión mínima, se necesita `TX/RX` cruzado y una `GND` común.

Principales riesgos: nivel incorrecto de `3.3V/5V`, conexión innecesaria de alimentación, confundir TTL UART con RS-232, y ausencia de las líneas `DTR`/`RTS` para el flasheo.

## Materiales relacionados

- [SparkFun: Serial Basic CH340C Hookup Guide](https://learn.sparkfun.com/tutorials/sparkfun-serial-basic-ch340c-hookup-guide) — guía práctica del USB-UART CH340C, pines `DTR/RX/TX/VCC/CTS/GND`, selección de voltaje y prueba de loopback.
- [SparkFun: Serial Basic Overview](https://learn.sparkfun.com/tutorials/sparkfun-serial-basic-ch340c-hookup-guide/serial-basic-overview) — descripción del pinout y el cambio `3.3V/5V` en el adaptador.
- [Adafruit: FT232H Serial UART](https://learn.adafruit.com/adafruit-ft232h-breakout/serial-uart) — ejemplo de adaptador USB-serie, líneas `TX`/`RX`, control de flujo y conexión al dispositivo.
- [Silicon Labs: CP2102 USB to UART Bridge](https://www.silabs.com/interface/usb-bridges/classic/device.cp2102) — ejemplo oficial del chip puente USB-UART y drivers de puerto COM virtual.
- [Klipper Configuration Reference: `[mcu]`](https://www.klipper3d.org/Config_Reference.html#mcu) — cómo se describe la conexión serie del MCU en Klipper mediante `serial`.
