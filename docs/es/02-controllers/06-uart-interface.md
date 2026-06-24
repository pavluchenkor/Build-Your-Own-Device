# Interfaz UART

UART es una interfaz simple de transmisión de datos serie entre dos dispositivos. Expansión: `Universal Asynchronous Receiver/Transmitter`.

En proyectos prácticos, típicamente escuchas "UART", "serie", "TX/RX" o "puerto UART". Para principiantes, el punto clave es: UART transmite datos en la línea `TX`, recibe en la línea `RX`, y ambos dispositivos necesitan un `GND` común para operación correcta.

## Dónde se usa UART

UART se encuentra casi en todas partes:

- registros de depuración de microcontroladores;
- flasheo de placas a través de adaptador USB-UART;
- comunicación host-a-MCU en algunos escenarios de Klipper;
- módulos GPS, RFID, huella dactilar y sensor;
- configuración del controlador de motor TMC;
- comunicación entre dos microcontroladores;
- puerto de servicio en la placa.

UART es conveniente porque requiere pocos cables y funciona bien para intercambio simple de texto, comando y diagnóstico.

## TX, RX y GND

Conexión mínima:

- `TX` - transmisión;
- `RX` - recepción;
- `GND` - tierra común.

TX de un dispositivo se conecta a RX del otro:

![TX/RX conectados cruzadamente y GND común en conexión UART](../../img/02-controllers/06-uart-tx-rx-crossover.png)

*Fuente: [SparkFun Electronics](https://learn.sparkfun.com/tutorials/serial-communication/all), CC BY-SA 4.0*

Regla:

```text
TX del dispositivo A -> RX del dispositivo B
RX del dispositivo A <- TX del dispositivo B
GND del dispositivo A -> GND del dispositivo B
```

El error más común es conectar `TX` con `TX` y `RX` con `RX`. A veces el etiquetado del módulo es confuso, así que si no hay conexión, primero verifica doble el diagrama de pines y documentación en lugar de cambiar aleatoriamente todos los cables.

## UART, USB y USB-UART

UART no es USB.

Una computadora típicamente no tiene pines UART desnudos. Por eso se necesita un adaptador USB-UART: se conecta al USB de la computadora por un lado y proporciona líneas `TX`, `RX`, `GND` y a veces `VCC`, `DTR`, `CTS` del otro lado.

Ejemplos:

- computadora leyendo registros de una placa a través de USB-UART;
- flasheo USB-UART de una placa sin USB integrado;
- host conectándose a MCU sobre serie;
- adaptador ayudando a recuperar una placa después de flasheo fallido.

No confundas un conector USB en una placa con pines UART en el encabezado. En algunas placas USB ya está conectado a un chip USB-UART integrado, mientras que en otras USB va directamente al microcontrolador.

## Niveles de lógica: 3.3V, 5V, RS-232

UART describe el método de transmisión de datos, pero no garantiza niveles de voltaje seguros.

En electrónica DIY, TTL/CMOS UART es más común:

- `3.3V` UART - ESP32, RP2040, STM32 y muchas placas modernas;
- `5V` UART - Arduino Uno/Nano y algunos módulos más antiguos.

Aplicar una señal `5V` a una entrada de microcontrolador `3.3V` puede dañar la placa. Para niveles incompatibles, se necesita un convertidor de nivel u otro circuito de coincidencia.

También hay RS-232, que es separado. Esto no es "solo UART en un conector DB9". RS-232 tiene diferentes niveles de voltaje y lógica eléctrica diferente. No puedes conectar un puerto RS-232 verdadero directamente a GPIO de microcontrolador. Se necesita un convertidor de nivel, como un circuito tipo MAX232 o adaptador listo.

## Velocidad y formato

La velocidad de UART debe coincidir. Valores comunes:

```text
9600
57600
115200
250000
1000000
```

Si la velocidad no coincide, la terminal mostrará basura o silencio.

También hay formato de transmisión. `8N1` se usa a menudo:

- `8` - 8 bits de datos;
- `N` - sin paridad;
- `1` - un bit de parada.

Para la mayoría de tareas simples, configurar la misma velocidad y `8N1` estándar es suficiente, a menos que la documentación del módulo requiera lo contrario.

## UART en impresoras 3D

En impresoras 3D, UART a menudo sirve tres roles diferentes.

**Comunicación entre host y placa**

Algunas placas pueden comunicarse con el host a través de serie/UART. En Klipper, esto se describe en la sección `[mcu]` a través de `serial`.

**Configuración del controlador TMC**

Algunos controladores de motor usan UART para configurar corriente, stealthChop/spreadCycle, diagnósticos y lectura de estado. El motor en sí generalmente se controla no por UART, sino por señales `STEP` y `DIR`.

**Depuración y flasheo**

UART se puede usar para registros, modo bootloader y recuperación de placa a través de adaptador USB-UART.

## Un UART - usualmente dos dispositivos activos

UART clásico es una conexión entre dos dispositivos. No puedes conectar ciegamente múltiples transmisores a una línea `RX`.

Problemas:

- dos dispositivos tiran simultáneamente de la línea `TX`;
- los datos se mezclan;
- un módulo recibe comandos destinados a otro;
- posible conflicto eléctrico.

A veces un `TX` puede ser escuchado por múltiples receptores, pero esto es una decisión consciente y no es adecuado como regla universal. Para principiantes, es más seguro asumir: un puerto UART - un par de dispositivos.

## Qué verificar antes de conectar

Antes de conectar UART, verifica:

- dónde están `TX` y `RX`;
- si se necesita un `GND` común;
- nivel de lógica: `3.3V` o `5V`;
- si esto es TTL UART o RS-232;
- velocidad de transmisión;
- formato, si se especifica;
- si este UART no está ocupado por registros USB o flasheo;
- si hay otro transmisor conectado a esta línea;
- si se necesita potencia u solo `TX`/`RX`/`GND`.

La potencia del adaptador USB-UART solo se conecta si está claro que la placa debe alimentarse desde él. A menudo para diagnósticos, solo `TX`, `RX` y `GND` se necesitan.

## Errores típicos

- conectar `TX` con `TX`, `RX` con `RX`;
- olvidar el `GND` común;
- aplicar `5V` UART a entrada `3.3V`;
- confundir TTL UART y RS-232;
- seleccionar la velocidad de baudios incorrecta;
- conectar potencia del adaptador USB-UART a una placa ya alimentada;
- usar pines UART ocupados por registros USB o bootloader;
- conectar múltiples transmisores a una línea;
- pensar que UART puede conducir directamente una carga potente.

## Conclusión clave

UART es una interfaz simple para intercambio de datos entre dos dispositivos. Necesitas `TX`/`RX` conectados cruzadamente, `GND` común, velocidad coincidente y niveles de lógica compatibles.

UART no es una fuente de potencia y no funciona como salida de potencia. Transmite datos, no gira motores o activa calentadores directamente.

## Materiales relacionados

- [SparkFun: Serial Communication](https://learn.sparkfun.com/tutorials/serial-communication/all) - explicación práctica buena de UART, TX/RX, baudios, TTL serie, RS-232 y errores comunes.
- [SparkFun: Serial Communication - UARTs](https://learn.sparkfun.com/tutorials/serial-communication/uarts) - qué UART hace dentro de un microcontrolador y por qué se necesitan TX/RX.
- [Adafruit: Serial UART on FT232H](https://learn.adafruit.com/adafruit-ft232h-breakout/serial-uart) - ejemplo de adaptador USB-UART y conectar TX/RX/GND a dispositivo serie.
- [SparkFun: Serial Basic CH340C Hookup Guide](https://learn.sparkfun.com/tutorials/sparkfun-serial-basic-ch340c-hookup-guide) - ejemplo de adaptador USB-UART, pines RX/TX/VCC/GND y prueba de bucle invertido.
- [Klipper: Configuration reference - `[mcu]`](https://www.klipper3d.org/Config_Reference.html#mcu) - cómo se describe la conexión MCU en serie en la configuración de Klipper.
