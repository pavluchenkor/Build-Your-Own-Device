# ST-Link

ST-Link es un programador y depurador para microcontroladores STM32.

En el contexto de dispositivos simples, se usa para:

- parpadear una placa STM32;
- recuperar una placa después de un parpadeo fallido;
- conectarse al chip a través de SWD;
- borrar memoria;
- verificar que el microcontrolador es visible;
- a veces depurar el programa.

ST-Link no es necesario para todas las placas. ESP32, RP2040 y Arduino generalmente parpadean de manera diferente.

## ¿Qué es SWD?

SWD es `Serial Wire Debug`.

Es una interfaz de depuración y parpadeo para microcontroladores ARM, comúnmente usado con STM32.

Para conexión básica, generalmente necesita:

- `SWDIO`;
- `SWCLK`;
- `GND`;
- a veces `NRST`;
- a veces `3.3V` o `VTref` como voltaje de referencia de destino.

Importante: `3.3V` en ST-Link no siempre significa "alimentar la placa desde aquí". A menudo, ST-Link necesita ver el voltaje de la placa de destino para entender los niveles de señal.

## Conexión Mínima

Generalmente se conecta:

```text
ST-Link SWDIO -> placa SWDIO
ST-Link SWCLK -> placa SWCLK
ST-Link GND   -> placa GND
ST-Link NRST  -> placa NRST si se necesita reinicio
ST-Link 3.3V/VTref -> objetivo 3.3V si lo requiere ST-Link específico
```

La placa STM32 a menudo se alimenta desde su potencia normal o USB.

Antes de conectar, consulte la documentación de su ST-Link y placa específicos.

![Placas Nucleo para STM32 con depurador ST-Link incorporado](../../img/02-controllers/04-stm32-nucleo-boards.jpg)

*Fuente: [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:STM32_Nucleo_boards.jpg), Avandalen, CC BY-SA 4.0*

## Potencia de Placa

La confusión más común: ¿la placa está alimentada por ST-Link o por separado?

Opciones:

1. La placa se alimenta por separado, ST-Link solo se conecta a SWD y GND.
2. ST-Link proporciona 3.3V a una placa de destino pequeña, si está realmente diseñada para esto.
3. ST-Link solo lee `VTref` pero no debe alimentar la placa.

No puede conectar ciegamente múltiples fuentes de alimentación.

Si la placa ya está alimentada por USB o una fuente de alimentación, no conecte potencia de ST-Link hasta que esté seguro de que el esquema lo permite.

## Cómo ST-Link Difiere de DFU

DFU es un modo de parpadeo a través de un cargador de arranque USB, si está disponible.

ST-Link funciona a través de SWD directamente con el microcontrolador.

ST-Link es útil cuando:

- DFU no está disponible;
- el bootloader está corrupto o no se usa;
- parpadeo deshabilitado USB;
- la placa no entra en modo de parpadeo normal;
- necesita borrar memoria;
- necesita recuperar acceso STM32.

Pero si una placa parpadea normalmente a través de USB/DFU o tarjeta SD, ST-Link puede no ser necesario.

## Conectarse Bajo Reinicio

A veces el firmware rompe el acceso a SWD.

Por ejemplo:

- los pinos SWD se usan como GPIO normal;
- el firmware rápidamente duerme el chip;
- el código se cuelga justo después del arranque;
- los modos de reloj/potencia se configuran incorrectamente.

En tales casos, el modo `Connect under reset` ayuda.

La idea: ST-Link sostiene el reinicio e intenta conectarse antes de que se ejecute el firmware malo.

Esto a menudo requiere conectar `NRST`.

## Cómo Saber Si ST-Link Ve la Placa

En STM32CubeProgrammer o herramienta similar, generalmente ve:

- si ST-Link está conectado;
- si el objetivo es encontrado;
- qué chip se detecta;
- si puede leer memoria;
- si puede borrar flash.

Si ST-Link es visible como dispositivo USB pero el objetivo no es encontrado, el problema a menudo es la conexión de la placa:

- la placa de destino no tiene potencia;
- no hay `GND` común;
- `SWDIO` y `SWCLK` están intercambiados;
- `VTref` no está conectado si es necesario;
- la frecuencia de SWD es demasiado alta;
- el chip está bloqueado;
- el firmware evita conexión;
- `Connect under reset` es necesario.

## Frecuencia SWD

Si la comunicación es inestable, intente reducir la frecuencia de SWD.

En cables largos, puentes Dupont pobres o placas inestables, la frecuencia alta puede interferir con la conexión.

Para recuperación de placa, lento y confiable supera rápido.

## Errores Comunes

- olvidó `GND`;
- intercambió `SWDIO` y `SWCLK`;
- conectó potencia de ST-Link y USB al mismo tiempo sin entender el esquema;
- no alimentó la placa de destino;
- no conectó `NRST` cuando `Connect under reset` es necesario;
- estableció la frecuencia de SWD demasiado alta;
- intenta parpadear ESP32 o RP2040 con ST-Link;
- intenta conectarse a un chip bloqueado sin comprender la protección de lectura;
- usando cables de mala calidad largos;
- no actualizó el firmware de ST-Link o no instaló el controlador.

## Lo Que No Puede Hacer

No puede:

- aplicar 5V a una placa STM32 de 3.3V sin verificar;
- conectar múltiples fuentes de potencia ciegamente;
- conectar ST-Link a una placa bajo voltaje de corriente alterna sin aislamiento seguro y recinto;
- cambiar cables SWD con potencia activada si hay riesgo de cortocircuito;
- asumir que un ST-Link clon tiene el mismo pinout que el original.

Los pines de ST-Link clon pueden diferir. Siempre verifique las marcas en su adaptador específico.

## Lo Esencial

- ST-Link es necesario para STM32 a través de SWD.
- Mínimo: `SWDIO`, `SWCLK`, `GND`, a veces `NRST` y `VTref`.
- La placa debe estar alimentada correctamente, pero no necesariamente desde ST-Link.
- DFU y ST-Link son métodos de parpadeo diferentes.
- `Connect under reset` ayuda a recuperar el acceso después del mal firmware.
- Si el objetivo no es encontrado, primero verifique potencia, `GND`, `SWDIO/SWCLK`, `NRST` y frecuencia de SWD.

## Materiales de Referencia

- [STMicroelectronics: UM1075 ST-LINK/V2 User Manual](https://www.st.com/resource/en/user_manual/dm00026748-st-link-v2-in-circuit-debugger-programmer-for-stm8-and-stm32-stmicroelectronics.pdf) - manual oficial de ST-LINK/V2, pines SWD/JTAG, VCC de destino y GND.
- [STMicroelectronics: UM2237 STM32CubeProgrammer User Manual](https://www.st.com/resource/en/user_manual/um2237-stm32cubeprogrammer-software-description-stmicroelectronics.pdf) - modos de conexión ST-LINK, incluyendo Normal, Connect under reset y Hot plug.
- [ST Wiki: ST-LINK](https://wiki.st.com/stm32mpu/wiki/ST-LINK) - visión general de ST-LINK como sonda de hardware para STM32/STM8 y protocolos soportados.
- [Klipper: Installation](https://www.klipper3d.org/Installation.html) - proceso general de preparación de MCU para Klipper.
- [STMicroelectronics: STM32CubeProgrammer](https://www.st.com/en/development-tools/stm32cubeprog.html) - herramienta oficial de ST para parpadear STM32 a través de ST-LINK/SWD, UART, USB DFU, SPI, I2C y cargadores de arranque CAN.
