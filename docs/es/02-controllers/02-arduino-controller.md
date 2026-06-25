# Controlador Arduino

Arduino no es un microcontrolador específico, sino un ecosistema de placas, bibliotecas, ejemplos y entorno de desarrollo. Cuando un principiante dice "Arduino", generalmente se refiere a Arduino Uno, Nano, o una placa compatible basada en ATmega328P.

Para la educación, Arduino sigue siendo muy útil: es fácil comprender GPIO, botones, LEDs, PWM, entrada analógica, I2C, SPI y sensores simples. Pero para un nuevo dispositivo en torno a una impresora 3D, Arduino Uno/Nano no siempre es la mejor opción.

## Por qué Arduino es popular

Puntos fuertes de Arduino:

- gran cantidad de materiales educativos;
- IDE de Arduino sencillo;
- muchas bibliotecas listas para usar;
- ejemplos comprensibles como Blink;
- conveniente para probar rápidamente un sensor en el escritorio;
- fácil encontrar módulos compatibles;
- las placas antiguas están bien documentadas.

Si el objetivo es entender los fundamentos de los microcontroladores, Arduino es una buena opción. Reduce la barrera de entrada y permite ver resultados rápidamente.

## Arduino como placa educativa

Arduino es conveniente para:

- probar un botón, final de carrera o sensor;
- prueba simple de termistor mediante divisor de tensión;
- probar I2C OLED;
- probar módulo SPI RFID;
- generar PWM para una prueba pequeña;
- leer tensión analógica;
- experimentos rápidos en una protoboard.

En este modo, Arduino es una excelente herramienta de laboratorio. No es necesario construir el dispositivo final con él: primero se puede entender el circuito y el sensor, y luego transferir la solución a ESP32, RP2040, STM32 o una placa de impresora.

## Uno y Nano en pocas palabras

Los clásicos Arduino Uno y Nano generalmente están basados en ATmega328P.

Características típicas:

- lógica de `5V`;
- reloj de 16 MHz;
- 32 KB de memoria flash;
- 2 KB de SRAM;
- 14 pines digitales;
- 6 pines PWM en la clase Uno/Nano;
- 6 entradas analógicas en Uno, 8 en Nano;
- USB para programar y alimentar la placa.

Esto es suficiente para sketches educativos y tareas simples independientes, pero no para lógica compleja, redes, interfaz web, bibliotecas grandes e integración conveniente con sistemas modernos.

## Original, clon y compatible con Arduino

Es necesario distinguir entre:

- placas Arduino originales;
- clones económicos de Uno/Nano;
- placas compatibles con Arduino basadas en otros microcontroladores;
- placas Arduino modernas con Wi-Fi, USB-C, chips Arm y otra lógica.

Un clon de Nano por pocos dólares puede servir para experimentos, pero la calidad del USB-UART, el regulador, la soldadura y el bootloader puede variar. A veces, para un clon de Nano en el IDE de Arduino es necesario seleccionar un bootloader antiguo o un procesador diferente.

Si el dispositivo debe funcionar durante mucho tiempo sin supervisión, la calidad de la placa, el regulador, los conectores y la documentación son más importantes que el precio más bajo.

## Lógica de 5V

Los Arduino Uno/Nano antiguos usan lógica de `5V`.

Esto es conveniente con algunos módulos antiguos, pero peligroso para dispositivos de `3.3V`:

- ESP32 generalmente no tolera `5V` en GPIO;
- muchos OLED, RFID, sensores y módulos de radio están diseñados para `3.3V`;
- las resistencias de pull-up de I2C a `5V` pueden dañar un dispositivo de `3.3V`;
- algunas entradas de módulos son compatibles con `5V`, pero esto debe verificarse en la documentación.

Si Arduino se conecta a un módulo de `3.3V`, se necesita un convertidor de nivel o un circuito donde se sepa que los niveles son compatibles.

## GPIO no alimenta cargas

Un pin de Arduino puede encender un LED a través de una resistencia o proporcionar una señal de control. No debe alimentar directamente un ventilador, calentador, servo, relé o tira LED.

Circuito típico:

![Arduino Uno Rev3 con microcontrolador ATmega328P](../../img/02-controllers/02-arduino-uno-rev3.jpg)

*Fuente: [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:Arduino_Uno_Rev3_with_Atmega328P.jpg), HonCode, CC0 Public Domain*

Para cargas se necesita:

- MOSFET o driver para ventilador DC, tira LED o calentador DC;
- driver con transistor y diodo de protección para la bobina del relé;
- SSR o relé para carga de red AC;
- alimentación separada para el servo;
- GND común donde lo requiera el circuito de baja tensión.

GPIO es una señal de comando, no una salida de potencia.

## PWM y analogWrite

En Arduino, `analogWrite()` en Uno/Nano generalmente significa PWM, no una salida analógica real. La placa conmuta rápidamente el pin encendido y apagado, cambiando el ciclo de trabajo de la señal.

Esto es adecuado para:

- brillo de LED;
- entrada de control para un driver;
- PWM simple para un ventilador o módulo MOSFET;
- experimentos educativos.

Pero hay limitaciones:

- PWM no está disponible en todos los pines;
- la frecuencia PWM es fija o cambia de maneras no evidentes;
- `analogWrite()` y `analogRead()` son cosas diferentes;
- un ventilador PC de 4 pines puede requerir una frecuencia diferente y un enfoque adecuado de colector/drenador abierto;
- los calentadores y SSR no pueden usar simplemente cualquier PWM rápido sin entender la sección de potencia.

## Entradas analógicas

Arduino Uno/Nano es conveniente para mediciones analógicas simples:

- potenciómetro;
- termistor mediante divisor de tensión;
- sensor de luz;
- sensor de tensión simple mediante divisor de tensión.

Pero una entrada analógica no debe ver tensión por encima de su rango seguro. Para Uno/Nano este es generalmente el rango relativo a la alimentación de `5V` o el `AREF` seleccionado. Si se mide una tensión mayor, se necesita un divisor y protección.

Para mediciones de temperatura precisas, se necesita no solo `analogRead()`, sino también:

- circuito correcto de divisor de tensión;
- valor de la resistencia;
- tabla del termistor o parámetro Beta;
- tensión de alimentación/referencia estable;
- filtrado de ruido;
- contacto mecánico del sensor con el objeto.

## Arduino y Klipper

Algunas placas AVR antiguas pueden encontrarse históricamente cerca de impresoras 3D, pero para un nuevo dispositivo en torno a Klipper es mejor no comenzar con Uno/Nano.

Razones:

- memoria limitada;
- rendimiento débil;
- la lógica de 5V puede interferir con los módulos modernos de `3.3V`;
- sin red sin módulos adicionales;
- no es el camino más práctico para un nuevo MCU de Klipper.

Si se necesita un MCU adicional para Klipper, generalmente es más práctico considerar RP2040, STM32 o una placa lista para impresora 3D. Arduino puede mantenerse para educación, protoboard y prueba de sensores individuales.

## Cuándo Arduino sigue siendo apropiado

Arduino es apropiado si:

- necesitas probar rápidamente una idea;
- necesitas explicar cómo funciona algo;
- el dispositivo es muy simple y no necesita rojo;
- ya tienes un sketch funcional;
- la claridad es más importante que la compacidad y el rendimiento;
- es un banco educativo, no electrónica de potencia final.

Arduino no es una buena opción si:

- necesitas Wi-Fi de fábrica;
- necesitas integración estrecha con Klipper;
- necesitas mucha memoria;
- necesitas muchos sensores modernos de `3.3V`;
- el dispositivo debe ser compacto, duradero e industrialmente ordenado;
- hay una sección de potencia con calentador donde las protecciones independientes son importantes.

## Qué verificar antes de comprar

Antes de comprar una placa compatible con Arduino, verifica:

- si es una placa original, clon o compatible;
- qué microcontrolador está instalado;
- lógica de `5V` o `3.3V`;
- qué chip USB-UART se utiliza;
- si existe un driver para tu computadora;
- qué bootloader se necesita;
- cuánto flash y SRAM tiene;
- cuántos pines PWM y entradas analógicas tiene;
- si hay esquema y pinout;
- calidad del regulador de alimentación y conectores;
- si la placa es adecuada para la tarea final.

## Errores comunes

- pensar que Arduino es una placa específica;
- conectar Arduino de `5V` directamente a un módulo de `3.3V`;
- alimentar una carga desde GPIO;
- alimentar un servo desde el pin de `5V` y obtener reinicios;
- usar `analogWrite()` como una salida analógica real;
- seleccionar el bootloader incorrecto para un clon de Nano;
- no instalar el driver para el USB-UART;
- intentar construir un dispositivo moderno en red con Uno sin razón;
- transferir una protoboard educativa a un dispositivo de potencia cerrado sin rediseñar la alimentación, el cableado y la protección.

## Puntos clave

Arduino es un buen ecosistema educativo y una herramienta conveniente para pruebas rápidas. Es excelente para entender GPIO, PWM, ADC y sensores.

Pero los clásicos Uno/Nano son placas antiguas de `5V` con memoria limitada y sin red. Para un nuevo dispositivo en torno a una impresora 3D, ESP32, RP2040, STM32 o una placa lista para impresora suele ser más práctico, dejando Arduino como herramienta educativa y de diagnóstico.

## Materiales relacionados

- [Arduino Docs: UNO R3](https://docs.arduino.cc/hardware/uno-rev3) — especificaciones oficiales de Uno R3: ATmega328P, `5V`, pines, PWM, entradas analógicas y recursos de la placa.
- [Arduino Store: UNO Rev3 Tech Specs](https://store.arduino.cc/collections/arduino/products/arduino-uno-rev3) — tabla con tensión, corriente GPIO, memoria, frecuencia y dimensiones de la placa.
- [Arduino Store: Arduino Nano](https://store-usa.arduino.cc/products/arduino-nano) — especificaciones de Nano, alimentación, memoria, pines digitales y analógicos.
- [Arduino Help Center: Select the right processor for Arduino Nano](https://support.arduino.cc/hc/en-us/articles/4401874304274-Select-the-right-processor-for-Arduino-Nano) — por qué Nano y los clones de Nano pueden tener diferentes bootloaders.
- [Arduino Language Reference](https://docs.arduino.cc/language-reference/) — referencia oficial para `pinMode`, `digitalWrite`, `analogRead`, `analogWrite`, PWM y funciones básicas.
- [Arduino Help Center: Use PWM output with Arduino](https://support.arduino.cc/hc/en-us/articles/9350537961500-Use-PWM-output-with-Arduino) — lista de pines PWM para placas populares y limitaciones de `analogWrite()`.
