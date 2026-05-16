# Errores del controlador

Un controlador no es una caja universal donde puedes enchufar todo directamente.

Lee sensores, emite señales de control y se comunica con el host. Pero las cargas de potencia deben ser alimentadas a través de salidas apropiadas, MOSFETs, relés, SSRs o drivers.

## Síntomas

Signos típicos de problemas del controlador o conexión:

- la placa no se detecta vía USB;
- el firmware no inicia;
- los pines no responden;
- el controlador se reinicia;
- el controlador se calienta significativamente;
- la placa deja de funcionar después de conectar módulo;
- ESP32 pierde Wi-Fi cuando la carga se activa;
- sensor no visible aunque hay potencia presente;
- Klipper no se conecta a MCU;
- los comandos funcionan en pin incorrecto.

## Controlador incorrecto elegido

Antes de elegir una placa debes entender la tarea.

Para un dispositivo Wi-Fi autónomo simple, ESP32 puede ser una buena opción.

Para un MCU adicional en Klipper, a menudo es más práctico mirar:

- RP2040;
- STM32;
- placa de impresora 3D lista.

Arduino Uno/Nano son útiles para aprender y experimentos simples, pero para un dispositivo nuevo serio alrededor de una impresora rápidamente encuentras limitaciones.

El error es elegir una placa solo porque "es popular", sin verificar:

- número de pines necesarios;
- niveles de lógica;
- fuente de alimentación;
- soporte de firmware;
- disponibilidad de USB/UART/CAN;
- soporte para librerías necesarias;
- corriente de salida;
- entorno de desarrollo.

## ESP32 como Klipper MCU

ESP32 es útil como dispositivo IoT/Wi-Fi separado.

Pero no esperes automáticamente que ESP32 sea la mejor opción como Klipper MCU.

Si el objetivo es integración con Klipper como MCU adicional, primero mira opciones oficiales y probadas para Klipper. Para nuevas extensiones de hardware a menudo es más simple y confiable usar RP2040 o STM32.

ESP32 es bueno si el dispositivo debe:

- funcionar autónomamente;
- tener Wi-Fi;
- proporcionar datos vía MQTT o HTTP;
- tener interfaz web;
- comunicarse con Home Assistant;
- funcionar separadamente de Klipper.

## Lógica 3.3V y 5V

Muchos controladores modernos funcionan con lógica 3.3V.

Por ejemplo:

- ESP32;
- RP2040;
- muchos STM32.

El error es aplicar una señal 5V a una entrada diseñada solo para 3.3V.

Esto puede:

- dañar inmediatamente el pin;
- dañar el controlador más tarde;
- causar operación inestable;
- romper un módulo que parecía estar bien.

Antes de conectar verifica:

- voltaje de potencia del módulo;
- nivel de lógica de entrada/salida;
- ¿hay convertidor de nivel?
- ¿acepta entrada 5V?
- qué está escrito en descripción técnica.

## GPIO no alimenta una carga

GPIO es un pin de señal.

No debe alimentar:

- ventilador;
- servo;
- calentador;
- tira LED;
- relé sin driver;
- solenoide;
- motor.

GPIO puede enviar un comando. La corriente de carga debe ir a través de una salida de potencia, MOSFET, driver, relé o módulo separado.

Si la carga se conecta directamente a GPIO, puedes dañar el pin o toda la placa.

## Sin GND común

Un controlador puede conducir un módulo externo solo si tienen un nivel de referencia común.

Error típico:

- servo alimentado de fuente 5V separada;
- la señal viene del controlador;
- `GND` no conectado;
- servo se sacude o no responde.

Igual con módulos MOSFET, ventiladores PWM, algunos sensores y placas externas.

## Firmware incorrecto

La placa podría estar bien, pero el firmware no encaja.

Errores:

- firmware flasheado para microcontrolador incorrecto;
- eligió bootloader incorrecto;
- mezclado firmware USB y UART;
- eligió puerto serial incorrecto;
- Klipper especificó ruta de dispositivo incorrecta;
- los pines en config no coinciden con la placa;
- no reiniciaste firmware/host después de flashear.

Antes de flashear debes conocer exactamente el modelo de placa y microcontrolador.

## El pin existe en esquemático pero no es adecuado

No todos los pines son iguales.

Los pines pueden tener restricciones:

- solo entrada;
- usado por USB/UART/SPI;
- usado durante el arranque;
- relacionado con modo de arranque;
- no soporta PWM necesario;
- pulled up o down;
- conflicto con otro módulo.

Si el pin se comporta extrañamente, verifica documentación de placa, no solo número GPIO.

## Qué verificar

Mini-checklist:

1. ¿Se elige la placa correcta para la tarea?
2. ¿Qué potencia necesita la placa?
3. ¿Qué lógica: 3.3V o 5V?
4. ¿Hay `GND` común con módulos externos?
5. ¿La carga no se alimenta de GPIO?
6. ¿La placa soporta interfaz necesaria?
7. ¿El pin seleccionado no se usa?
8. ¿El firmware es correcto?
9. ¿La placa es visible vía USB?
10. ¿La configuración coincide con pinout de placa?

## Qué no hacer

No puedes:

- aplicar 5V a entrada 3.3V sin verificar;
- conectar carga directamente a GPIO;
- flashear firmware aleatorio de una placa "similar";
- cambiar cableado bajo potencia;
- asumir que cualquier GPIO encaja en cualquier tarea;
- ignorar calentamiento del controlador;
- conectar módulos externos sin tierra común cuando sea necesario.

## Puntos clave

- El controlador controla pero no alimenta directamente una carga.
- La lógica 3.3V y 5V debe ser compatible.
- GPIO es una señal, no una fuente de alimentación.
- Para Klipper MCU a menudo miras RP2040/STM32, ESP32 es más conveniente como dispositivo Wi-Fi autónomo.
- El firmware y pinout deben coincidir con la placa real.
- Si la placa se calienta o deja de detectarse, apaga el poder y encuentra el error de conexión.

## Referencias

- [Klipper: Instalación](https://www.klipper3d.org/Installation.html) - proceso general de preparación y flasheo de MCU para Klipper.
- [Klipper: Referencia de configuración, MCU](https://www.klipper3d.org/Config_Reference.html#mcu) - sección `[mcu]`, conexión serial/CAN y MCUs adicionales.
- [Arduino: Pines digitales](https://docs.arduino.cc/learn/microcontrollers/digital-pins/) - explicación básica de pines digitales como entradas/salidas, no fuente de alimentación.
- [Hoja de datos ESP32 de Espressif](https://www.espressif.com/sites/default/files/documentation/esp32_datasheet_en.pdf) - especificaciones eléctricas oficiales de ESP32.
- [Hoja de datos Raspberry Pi Pico](https://datasheets.raspberrypi.com/pico/pico-datasheet.pdf) - datos oficiales sobre RP2040/Pico, potencia y GPIO.
