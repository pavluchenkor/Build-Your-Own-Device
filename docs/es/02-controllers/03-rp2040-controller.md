# RP2040 Controller

RP2040 es un microcontrolador de Raspberry Pi. La placa más conocida basada en él es la Raspberry Pi Pico.

Para periféricos DIY alrededor de una impresora 3D, RP2040 es una de las opciones más prácticas: es económico, bien documentado, funciona con lógica de `3.3V`, es conveniente para flashear por USB y es adecuado como MCU adicional para Klipper.

## Dónde es útil RP2040

RP2040 es bueno para:

- placa de I/O adicional para Klipper;
- controlador de ventiladores vía MOSFET/drivers;
- lectura de termistores y sensores analógicos simples;
- conexión de OLED vía I2C;
- conexión de RFID/NFC vía SPI o UART;
- control de servos con señal PWM;
- placa autónoma sencilla sin Wi-Fi;
- banco de pruebas para sensores e interfaces.

Si necesitas conectividad de red desde el principio, es más fácil mirar ESP32 o Pico W. Si necesitas un MCU adicional cableado para Klipper, RP2040 suele ser más conveniente.

## Por qué Raspberry Pi Pico es conveniente

Raspberry Pi Pico es una placa de desarrollo lista basada en RP2040. Ya tiene USB, memoria flash, regulador de alimentación, un botón `BOOTSEL` y pines expuestos.

Ventajas de Pico:

- bajo costo;
- buena documentación y pinout;
- USB para flashear y comunicarse;
- muchos GPIO;
- lógica de `3.3V`;
- 2 UART, 2 SPI, 2 I2C;
- 16 canales PWM;
- 3 entradas ADC en pines expuestos de Pico;
- PIO para interfaces no estándar;
- flasheo UF2 conveniente vía almacenamiento masivo USB.

Para un primer proyecto, es mejor conseguir un Pico o Pico H con pines soldados que un chip RP2040 desnudo. Un chip desnudo requiere una placa personalizada, memoria flash, alimentación, USB, ruteo y pruebas.

## BOOTSEL y UF2

Una de las fortalezas de Pico es un proceso de flasheo simple:

1. Mantén presionado el botón `BOOTSEL`.
2. Conecta el USB a tu computadora.
3. La placa aparece como una unidad USB.
4. Copia el archivo de firmware `.uf2`.
5. La placa reinicia con el nuevo firmware.

Esto es conveniente para proyectos en MicroPython, CircuitPython, C/C++ y firmware de Klipper. Para un principiante, este método suele ser más comprensible que ST-Link, DFU o un USB-UART separado.

## RP2040 y Klipper

RP2040 es un buen candidato como MCU adicional en Klipper.

Esquema típico:

![Raspberry Pi Pico con chip RP2040](../../img/02-controllers/03-rp2040-pico-photo.jpg)

*Fuente: [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:Raspberry_Pi_Pico_oblique.jpg), Phiarc, CC BY-SA 4.0*

La idea es:

- el host Linux con Klipper sigue siendo el controlador principal;
- Pico/RP2040 se flashea con el firmware MCU de Klipper;
- se agrega una sección principal o adicional `[mcu]` a `printer.cfg`;
- los pines de RP2040 pueden usarse para ventiladores, sensores, PWM y otros periféricos;
- las cargas de potencia siguen conectadas vía MOSFET, driver, relé o SSR.

Esto es útil cuando necesitas separar parte del periférico en un bloque aparte: por ejemplo ventiladores, sensores de cámara, filtro, iluminación trasera, botón, fin de carrera o salidas de servicio.

## GPIO y lógica de 3.3V

RP2040 trabaja con lógica de `3.3V`. Esto significa:

- no apliques `5V` a GPIO;
- para módulos de `5V` puede que necesites un convertidor de nivel;
- las resistencias pull-up de I2C deben ir a `3.3V`;
- GPIO no debe alimentar una carga directamente;
- un ventilador, tira LED, relé o calefactor necesita un interruptor/driver externo.

Si un módulo es "compatible con Arduino", no significa que sea seguro para RP2040. Debes verificar los niveles de entrada y las resistencias pull-up.

## Alimentación

Pico generalmente se alimenta desde USB o vía el pin `VSYS`. La placa tiene un regulador para alimentar el microcontrolador.

Reglas prácticas:

- no alimentes motores, servos y relés desde el pin `3V3` de Pico;
- usa alimentación separada para las cargas;
- conecta GND común con los drivers de baja tensión;
- verifica de dónde viene la alimentación a `VSYS` y USB;
- considera la corriente de los módulos externos, no solo de Pico.

Si Pico se reinicia cuando arranca un servo o ventilador, el problema es casi siempre la alimentación, la tierra o el ruido.

## ADC en Pico

Pico tiene entradas ADC que puedes usar para tareas analógicas simples:

- termistor vía divisor de tensión;
- potenciómetro;
- sensor de luz;
- medición de baja tensión vía divisor de tensión.

Limitaciones:

- la entrada ADC no debe superar el voltaje GPIO seguro;
- para medir `12V` o `24V` necesitas un divisor y protección;
- un termistor requiere una resistencia correcta, tabla/modelo y contacto mecánico;
- el ADC no reemplaza un multímetro o medidor industrial.

Para calefactores, recuerda: el ADC solo lee el sensor. La seguridad del calentamiento la proveen el interruptor de potencia, los límites del firmware, el fusible y la protección térmica independiente.

## PIO en términos simples

PIO es E/S Programable. RP2040 tiene pequeños bloques programables que pueden generar o leer señales no estándar sin carga constante en el código principal.

Un principiante no necesita comenzar con PIO. Pero esta es una de las razones por las que RP2040 es popular para interfaces, temporización y periféricos no estándar.

Para un dispositivo simple tipo iDryer, GPIO regular, PWM, I2C, SPI, UART y ADC suelen ser suficientes.

## Pico, Pico W y Pico 2

Es importante no confundir las placas:

- **Pico / Pico H** — placa RP2040 clásica sin Wi-Fi;
- **Pico W / Pico WH** — RP2040 con módulo Wi-Fi/Bluetooth a bordo;
- **Pico 2 / Pico 2 W** — nueva generación basada en RP2350, esto no es RP2040.

Si un artículo o proyecto menciona RP2040, generalmente se refiere al Pico de primera generación o una placa compatible. Pico 2 es similar en concepto, pero es un microcontrolador diferente, y la compatibilidad de firmware/pines debe verificarse por separado.

## Qué verificar antes de comprar

Antes de comprar una placa basada en RP2040, verifica:

- si es un Pico original, Pico W o clon;
- si los pines están soldados;
- si tiene el conector USB que necesitas;
- si tiene un pinout adecuado;
- qué GPIO están disponibles;
- si necesitas Wi-Fi;
- si la placa es adecuada para el firmware de Klipper;
- cómo se alimentarán la placa y las cargas;
- si tienes suficientes ADC/PWM/I2C/SPI/UART para la tarea;
- si hay espacio en la carcasa para el montaje.

Si planeas un MCU para Klipper, verifica de antemano las instrucciones existentes para tu placa específica y el método de flasheo.

## Errores comunes

- aplicar `5V` a GPIO de RP2040;
- alimentar un servo o relé desde `3V3`;
- olvidar el GND común con el MOSFET/driver;
- pensar que Pico W es un Pico normal y no considerar los recursos usados/potencia Wi-Fi;
- comprar Pico 2 esperando el comportamiento exacto de RP2040;
- medir `12V`/`24V` en ADC sin divisor;
- conectar un calefactor directamente a un pin;
- elija RP2040 para una tarea Wi-Fi cuando un Pico normal no tiene Wi-Fi;
- no verificar el pinout de un clon específico.

## Puntos clave

RP2040 y Raspberry Pi Pico son una opción sólida para periféricos DIY cableados y MCU adicional en Klipper. La placa es económica, comprensible, bien documentada y conveniente para flashear.

Pero RP2040 es un microcontrolador de `3.3V`, no un controlador de potencia. Las cargas se conectan vía drivers, MOSFET, relés o SSR. Para tareas Wi-Fi, necesitas Pico W u otro controlador con red.

## Materiales relacionados

- [Raspberry Pi: especificaciones de RP2040](https://www.raspberrypi.com/products/rp2040/specifications/) — especificaciones oficiales de RP2040: CPU, SRAM, UART/SPI/I2C, PWM, USB y PIO.
- [Documentación de Raspberry Pi: microcontroladores de la serie Pico](https://www.raspberrypi.com/documentation/microcontrollers/raspberry-pi-pico.html) — diferencias entre Pico, Pico W, Pico 2, GPIO, ADC, PWM y variantes de placa.
- [Hoja de datos de RP2040](https://datasheets.raspberrypi.com/rp2040/rp2040-datasheet.pdf) — descripción técnica detallada del microcontrolador, periféricos, PIO, GPIO y ADC.
- [Hoja de datos de Raspberry Pi Pico](https://datasheets.raspberrypi.com/pico/pico-datasheet.pdf) — documentación de la propia placa Pico: alimentación, USB, GPIO expuestos y limitaciones de la placa.
- [Documentación de Raspberry Pi: SDK de C/C++ - Tus primeros binarios](https://www.raspberrypi.com/documentation/microcontrollers/c_sdk.html#your-first-binaries) — ejemplo oficial de BOOTSEL, almacenamiento masivo USB `RPI-RP2` y copia de UF2 a Pico.
- [Referencia de configuración de Klipper](https://www.klipper3d.org/Config_Reference.html) — contexto del soporte de RP2040 en Klipper y configuración para periféricos como I2C.
