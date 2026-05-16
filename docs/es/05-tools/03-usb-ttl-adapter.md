# USB-TTL

Un adaptador USB-TTL, o adaptador USB-UART, le permite hablar a su computadora con un microcontrolador sobre UART a través de USB.

Lo necesita para:

- parpadear algunas placas;
- leer registros;
- depurar comunicación UART;
- configurar módulos;
- recuperar una placa cuando USB normal no funciona;
- conectarse a un dispositivo sin USB-UART incorporado.

Los adaptadores comunes usan chips como CH340, CP2102, FT232 y similares.

## USB-TTL o USB-UART

Las descripciones del consumidor a menudo dicen USB-TTL.

Técnicamente, generalmente significa un adaptador USB-UART con niveles lógicos TTL.

Lo principal a entender:

- el lado USB se conecta a la computadora;
- el lado UART se conecta al microcontrolador;
- el adaptador no es un programador para todas las placas;
- el adaptador no reemplaza ST-Link si necesita parpadear STM32 a través de SWD.

## Pines Principales

Típicamente hay:

- `GND`;
- `TX`;
- `RX`;
- `VCC` o `3V3`/`5V`;
- a veces `DTR`;
- a veces `CTS`, `RTS`.

Mínimo para comunicación:

- `GND`;
- `TX`;
- `RX`.

El poder solo está conectado si está seguro de que el adaptador debe alimentar la placa.

## TX y RX Están Conectados en Cruzado

UART se conecta de esta manera:

```text
adaptador TX -> placa RX
adaptador RX -> placa TX
adaptador GND -> placa GND
```

`TX` es transmitir.

`RX` es recibir.

El transmisor de un dispositivo debe conectarse al receptor del otro.

Si conecta `TX` a `TX`, la comunicación generalmente no funcionará.

![TX/RX conectado en cruzado en conexión UART](../../../img/02-controllers/06-uart-tx-rx-crossover.png)

*Fuente: [SparkFun Electronics](https://learn.sparkfun.com/tutorials/serial-communication/all), CC BY-SA 4.0*

## Tierra Común

El GND del adaptador y el GND de la placa deben estar conectados.

Sin una tierra común, UART puede no funcionar o funcionará de manera inestable.

Incluso si la placa está alimentada por una fuente de alimentación separada, la tierra sigue siendo necesaria como el nivel de señal común.

## Niveles Lógicos 3.3V y 5V

Este es uno de los puntos más importantes.

El adaptador puede funcionar con lógica en:

- `3.3V`;
- `5V`;
- `3.3V/5V` intercambiable.

Muchas placas y módulos modernos usan lógica 3.3V: ESP32, RP2040, muchos STM32.

Si aplica una señal UART de 5V a una entrada de 3.3V, puede dañar el pin o la placa completa.

Antes de conectar, verifique:

- qué nivel lógico usa la placa;
- qué nivel lógico usa el adaptador;
- qué hace el jumper 3.3V/5V;
- si el jumper cambia solo el poder `VCC` o también los niveles `TX/RX`.

Algunos adaptadores proporcionan potencia de 5V pero señales lógicas de 3.3V. Otros cambian tanto potencia como niveles. Consulte la documentación del adaptador específico.

## Poder del Adaptador

No siempre necesita conectar `VCC`.

A menudo es más seguro conectar solo:

- `GND`;
- `TX`;
- `RX`.

Alimente la placa desde su fuente normal.

Puede conectar `VCC` del adaptador si:

- la placa está clasificada para ese voltaje;
- la corriente de la placa está dentro de la capacidad del adaptador;
- no hay otra potencia al mismo tiempo;
- la documentación de la placa permite alimentar a través de este pin.

Un error peligroso es suministrar potencia tanto del adaptador USB-UART como de una fuente de alimentación separada al mismo tiempo, causando que las fuentes entren en conflicto.

## DTR y Reinicio Automático

Algunas placas usan `DTR` para reinicio automático durante el parpadeo.

Por ejemplo, Arduino Pro Mini y placas similares pueden usar DTR a través de un capacitor para reinicio automático.

Si el parpadeo no comienza automáticamente, puede ser porque:

- DTR no está conectado;
- se necesita reinicio manual;
- el adaptador incorrecto está seleccionado;
- el bootloader incorrecto está seleccionado;
- la velocidad o placa en el IDE está seleccionado incorrectamente.

Para la lectura simple de registro, DTR generalmente no es necesario.

## Cómo Verificar Si el Adaptador Es Visible para el Sistema

En macOS y Linux, el adaptador generalmente aparece como un dispositivo en `/dev`.

Ejemplos:

```bash
ls /dev/tty.*
ls /dev/cu.*
ls /dev/ttyUSB*
ls /dev/ttyACM*
```

En Windows aparece como un puerto `COM`.

Si el puerto no aparece:

- verifique el cable USB;
- intente un puerto USB diferente;
- verifique el controlador;
- verifique que no sea solo un cable de carga;
- vea qué chip está en el adaptador: CH340, CP2102, FT232.

Los adaptadores baratos a veces requieren un controlador separado, especialmente en Windows.

## Prueba de Bucle Invertido

Forma simple de verificar el adaptador:

1. Conecte el `TX` y `RX` del adaptador juntos.
2. Abra una terminal serie.
3. Seleccione el puerto y la velocidad.
4. Escriba texto.

Si los caracteres que escribe vuelven, el adaptador y el puerto probablemente funcionen.

Después de la prueba, retire el puente entre `TX` y `RX`.

## Errores Comunes

- `TX` conectado a `TX` y `RX` a `RX`;
- olvidó `GND` común;
- seleccionó nivel 5V para una placa 3.3V;
- conectó `VCC` aunque la placa ya está alimentada por separado;
- el cable USB resultó ser de solo carga;
- controlador CH340/CP210x/FTDI no instalado;
- puerto COM incorrecto seleccionado;
- velocidad UART no coincide;
- esperando que USB-UART parpadee STM32 a través de SWD;
- confundió modo de arranque o reinicio durante parpadeo.

## Lo Esencial

- El adaptador USB-UART es necesario para comunicación UART entre computadora y placa.
- Mínimo para comunicación: `GND`, `TX`, `RX`.
- El `TX` del adaptador va a `RX` de la placa, `RX` del adaptador va a `TX` de la placa.
- Verifique los niveles lógicos 3.3V/5V antes de conectar.
- `VCC` solo se conecta si definitivamente necesita potencia del adaptador.
- Si el adaptador no es visible, verifique el cable, el controlador y el puerto USB.

## Materiales de Referencia

- [SparkFun: Serial Basic Hookup Guide](https://learn.sparkfun.com/tutorials/serial-basic-hookup-guide) - adaptador USB a serie, TX/RX/GND, VCC, DTR e intercambio de 3.3V/5V.
- [SparkFun: Serial Basic CH340C Hookup Guide](https://learn.sparkfun.com/tutorials/sparkfun-serial-basic-ch340c-hookup-guide/serial-basic-overview) - adaptador USB-UART CH340C moderno, pines, LEDs y selección de voltaje.
- [SparkFun: Serial Communication](https://learn.sparkfun.com/tutorials/serial-communication) - conceptos básicos de UART, TX/RX y comunicación serie.
- [Silicon Labs: CP210x USB to UART Bridge VCP Drivers](https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers) - controladores oficiales de Puerto Virtual CP210x.
- [Adafruit FTDI TTL-232 USB Type C Cable](https://www.adafruit.com/product/4364) - cable de ejemplo con potencia de 5V y lógica de 3.3V, mostrando por qué la potencia y los niveles de señal necesitan leerse por separado.
