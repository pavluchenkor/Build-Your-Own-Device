# Controladores STM32

STM32 es una amplia familia de microcontroladores de 32 bits de STMicroelectronics basados en núcleos Arm Cortex-M. No es una placa ni un chip concreto: bajo el nombre STM32 existen docenas de series y cientos de modelos.

En el mundo de las impresoras 3D, STM32 es muy común. Muchas placas de impresora comerciales, placas de expansión, placas CAN y controladores utilizan STM32. Para Klipper y los periféricos de impresora, es una de las opciones más prácticas si estás dispuesto a trabajar con una placa específica.

## Dónde es útil STM32

STM32 es adecuado para:

- placa principal de impresora 3D;
- MCU adicional en Klipper;
- placa de control de ventiladores, sensores y salidas;
- placa CAN o placa de cabezal;
- placas personalizadas más serias;
- tareas que requieren temporizadores, PWM, ADC, UART, SPI, I2C, CAN o USB;
- proyectos que necesitan un ecosistema industrial ya establecido y documentación.

Si RP2040 es un inicio sencillo y claro, STM32 es un amplio mundo de controladores donde puedes seleccionar un chip para casi cualquier tarea. Pero la flexibilidad tiene el costo de la complejidad.

## STM32 es una familia

No puedes decir "tengo un STM32" y dejar de elegir. Necesitas conocer el modelo exacto.

Ejemplos de series:

- **STM32F0 / STM32C0 / STM32G0** — series económicas y de mercado masivo;
- **STM32F1** — serie antigua pero muy conocida, frecuente en Blue Pill y placas antiguas;
- **STM32F4** — serie más potente, popular en controladores;
- **STM32G4** — interesante para tareas de control, temporizadores y periféricos analógicos;
- **STM32H7** — controladores potentes de gama alta;
- **STM32L / STM32U** — series orientadas al bajo consumo energético.

Para un usuario típico, lo que importa no es el marketing de la serie, sino cosas concretas:

- si hay soporte en el firmware que necesitas;
- cuántos GPIO están realmente expuestos en la placa;
- si tiene USB, CAN, UART, I2C, SPI;
- cuánta flash y RAM tiene;
- cómo flashearla;
- si existe un pinout y esquema adecuados.

## La placa importa más que el nombre del chip

El mismo STM32 puede estar en placas muy diferentes.

Variantes comunes:

- **Blue Pill / Black Pill** — placas pequeñas y económicas, frecuentemente con STM32F103 o clase STM32F4, pero la calidad de los clones varía;
- **STM32 Nucleo** — placas de desarrollo oficiales de ST con ST-LINK integrado;
- **placa de impresora 3D comercial** — ya incluye drivers, conectores, salidas MOSFET, entradas para termistores, fusibles y conectores de alimentación;
- **placa de cabezal/CAN** — placa especializada para el cabezal de la impresora o un módulo remoto;
- **placa personalizada** — requiere diseño completo de alimentación, USB, SWD, protección y ruteo.

Para un primer proyecto práctico, suele ser más fácil conseguir una placa comercial con documentación que un STM32 desnudo o un clon genérico sin esquema.

## STM32 y Klipper

STM32 es uno de los caminos principales para un MCU en Klipper.

Arquitectura típica:

![Placas Nucleo para STM8 y STM32 de STMicroelectronics](../../../img/02-controllers/04-stm32-nucleo-boards.jpg)

*Fuente: [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:Nucleo-board.jpg), Avandalen, CC BY-SA 4.0*

El host de Klipper corre en un dispositivo Linux, y la placa STM32 controla físicamente los pines: conmuta salidas MOSFET, lee termistores, controla ventiladores, recibe señales de finales de carrera y se comunica con el host por USB, UART o CAN.

Para periféricos similares a iDryer, STM32 tiene sentido si:

- el dispositivo debe formar parte de la configuración de Klipper;
- necesitas una placa de impresora comercial con salidas de potencia;
- necesitas CAN;
- necesitas un enfoque de placa más industrial;
- ya tienes una placa STM32 y una configuración conocida.

Si necesitas añadir rápidamente algunos pines y sensores, RP2040 suele ser más sencillo. Si necesitas una placa potente y ya fabricada con conectores y drivers, una placa STM32 puede ser mejor.

## Flasheo: USB, DFU, UART, SWD, ST-LINK

STM32 no tiene un método de flasheo universal para todas las placas.

Opciones:

- **Bootloader USB / DFU** — flasheo mediante el bootloader USB integrado si la placa y el chip lo soportan;
- **Bootloader UART** — flasheo por pines serie en el modo BOOT correcto;
- **SWD mediante ST-LINK** — forma fiable de flashear y depurar mediante un programador;
- **ST-LINK integrado en Nucleo** — cómodo para el desarrollo;
- **bootloader en placa de impresora** — a veces el flasheo se realiza por tarjeta SD, USB o un bootloader especial del fabricante.

Por tanto, antes de comprar una placa hay que buscar no solo el datasheet del chip, sino las instrucciones de esa placa concreta. Para Klipper, es especialmente importante leer los comentarios en la configuración de la placa comercial y las instrucciones del fabricante.

## Nucleo, Blue Pill y placas de impresora

Las placas **STM32 Nucleo** son cómodas para aprender y prototipar. Normalmente incluyen ST-LINK integrado, conectores Arduino Uno V3 y pines ST morpho que dan acceso a más señales. Es una buena opción si quieres aprender STM32 y disponer de una herramienta de flasheo oficial.

**Blue Pill / Black Pill** son atractivas por precio y tamaño, pero los clones suelen tener problemas: chip incorrecto, regulador débil, USB deficiente, sin esquema correcto, bootloader extraño. Para experimentos son útiles; para un dispositivo fiable, solo tras verificación.

Las **placas de impresora 3D comerciales** suelen ser más prácticas para calentadores, ventiladores y sensores porque la sección de potencia ya está diseñada: hay terminales, salidas MOSFET, entradas para termistores, alimentación, fusibles o espacio para ellos. Pero incluso una placa comercial requiere verificar corrientes, conectores, refrigeración y seguridad.

## Lógica 3.3V y GPIO

La mayoría de los STM32 trabajan con lógica de `3.3V`.

Importante:

- no apliques `5V` a los pines a menos que el datasheet del chip indique específicamente que ese pin acepta `5V`;
- la compatibilidad con shields Arduino en Nucleo no significa que todas las señales sean seguras como en un Arduino Uno de `5V`;
- las resistencias de pull-up I2C suelen ir a `3.3V`;
- los GPIO no deben alimentar una carga directamente;
- ventiladores, tiras LED, calentadores, relés y servos se conectan mediante drivers y alimentación separada.

Aunque algunos pines STM32 acepten `5V`, eso no es permiso para conectar cualquier cosa. Hay que revisar la tabla de pinout y las características eléctricas del chip concreto.

## Por qué se elige STM32 frecuentemente para impresoras

STM32 es adecuado para placas de impresoras 3D porque dispone de muchos periféricos útiles:

- temporizadores y PWM para ventiladores, calentadores y señales;
- ADC para termistores y sensores;
- UART/SPI para drivers de motores paso a paso y módulos;
- I2C para pantallas y sensores;
- USB para comunicación con el host;
- CAN en algunas series y placas;
- rendimiento suficiente para tareas MCU en tiempo real.

Pero el microcontrolador por sí solo no hace que una placa sea segura. Los calentadores, MOSFET de potencia, SSR, fusibles, conectores y protección térmica siguen siendo una tarea de ingeniería aparte.

## Qué verificar antes de comprar

Antes de comprar una placa STM32, comprueba:

- modelo exacto del microcontrolador;
- si hay soporte en Klipper o en el firmware que necesitas;
- cuánta flash y RAM tiene;
- cómo se flashea la placa;
- si tiene USB, CAN, UART u otra interfaz necesaria;
- si existe pinout y esquema oficiales;
- qué pines están ocupados por LEDs, USB, oscilador, modo boot o SWD;
- qué pines son tolerantes a `5V` y cuáles no;
- qué salidas de potencia tiene la placa y para qué corriente están diseñadas;
- si hay fusibles, terminales y alimentación adecuada;
- qué tan comprensible es la documentación del fabricante.

Si una placa se vende solo con una foto bonita y sin esquema, no es una buena base para un dispositivo con calentador.

## Errores comunes

- pensar que STM32 es una placa concreta;
- comprar un clon de Blue Pill esperando el comportamiento de una placa oficial;
- no verificar el modelo exacto del chip;
- no entender cómo flashear la placa;
- confundir DFU, BOOT0, UART y ST-LINK;
- conectar un módulo de `5V` a un pin no tolerante a `5V`;
- usar los pines SWD como GPIO normales y perder la capacidad de flashear/depurar;
- pensar que GPIO es una salida de potencia;
- elegir una placa sin esquema para un calentador;
- no revisar la configuración de Klipper disponible antes de comprar.

## Puntos clave

STM32 es una familia de microcontroladores potente y práctica, especialmente para placas de impresoras 3D y MCU en Klipper. Pero hay que elegir no "STM32 en general", sino una placa concreta con un chip específico, pinout, método de flasheo y documentación.

Para un primer controlador sencillo, RP2040 suele ser más fácil. Para electrónica de impresora ya fabricada, placas CAN y periféricos más serios, STM32 suele ser la opción correcta.

## Materiales relacionados

- [STMicroelectronics: STM32 32-bit Arm Cortex MCUs](https://www.st.com/en/microcontrollers-microprocessors/stm32-32-bit-arm-cortex-mcus.html) — descripción general oficial de la familia STM32, series, rendimiento y herramientas.
- [STMicroelectronics: STM32 Mainstream MCUs](https://www.st.com/en/microcontrollers-microprocessors/stm32-mainstream-mcus.html) — descripción general de las series de mercado masivo STM32C0, G0, F0, F1, G4 y su posicionamiento.
- [STMicroelectronics: STM32CubeProgrammer](https://www.st.com/en/development-tools/stm32cubeprog.html) — herramienta oficial de flasheo de STM32 mediante ST-LINK/SWD, UART, USB DFU, I2C, SPI y bootloader CAN.
- [STMicroelectronics: NUCLEO-F103RB](https://www.st.com/en/product/nucleo-f103rb) — ejemplo de placa Nucleo oficial con ST-LINK integrado, conectores Arduino Uno V3 y pines ST morpho.
- [ST UM1724: STM32 Nucleo-64 boards user manual](https://www.st.com/resource/en/user_manual/dm00105823-stlink-v2-in-circuit-debugger-programmer-for-stm8-and-stm32-stmicroelectronics.pdf) — documentación de Nucleo-64, conectores, ST-LINK y advertencia sobre I/O de `3.3V`.
- [Klipper: Code overview](https://www.klipper3d.org/Code_Overview.html) — arquitectura de Klipper y contexto del backend MCU, incluyendo STM32 en el árbol de código fuente.
