# MCU en Klipper

Klipper consta de dos partes principales:

- **host** — una computadora Linux con Klipper, como Raspberry Pi, Orange Pi, mini-PC u otro dispositivo;
- **MCU** — una placa de microcontrolador que controla físicamente los pines.

El host toma decisiones de alto nivel, lee configuración, procesa código G y planifica acciones. El MCU ejecuta comandos precisos en hardware: cambia salidas, lee entradas, cuenta tiempo, genera PWM e informa el estado nuevamente al host.

## Qué es un MCU en Klipper

MCU significa unidad de microcontrolador.

En el contexto de Klipper, es una placa específica:

- placa principal de impresora 3D;
- placa RP2040 separada;
- placa STM32 separada;
- placa CAN/cabezal;
- placa I/O adicional.

Un MCU no "piensa como la impresora completa". Ejecuta comandos de bajo nivel enviados por el host. Esta separación hace que Klipper sea flexible: puedes agregar un segundo o tercer MCU y usar sus pines en una configuración compartida.

## Cómo se ve

Esquema simplificado:

![Host de Klipper y múltiples MCU](../../img/02-controllers/05-klipper-host-mcu-architecture.svg)

El host se comunica con el MCU a través de USB, UART o CAN. En la configuración de Klipper, cada MCU obtiene su propia sección, y los pines de ese MCU se usan en ventilador, sensor, calentador, salida y otras configuraciones de módulo.

## Qué hace el host

El host:

- almacena y lee `printer.cfg`;
- acepta código G y comandos del usuario;
- mantiene lógica de alto nivel;
- programa acciones en el tiempo;
- sincroniza comunicación con el MCU;
- decide cuándo cambiar un ventilador, calentador u otra salida;
- recibe lecturas y estado del MCU.

El host no aplica corriente a un ventilador ni lee un termistor directamente si estos pines están en una placa externa. Le dice al MCU qué hacer.

## Qué hace el MCU

El MCU:

- controla físicamente GPIO;
- lee entradas y sensores;
- genera PWM;
- ejecuta comandos en el momento correcto;
- informa resultados al host;
- entra en apagado por error si el firmware y la configuración están configurados de esa manera.

Por ejemplo, si la configuración tiene un ventilador en el pin `PA8`, es el MCU con ese pin el que cambia su estado. El host solo envía el comando.

## Qué significa `[mcu]`

En `printer.cfg`, la sección `[mcu]` describe el microcontrolador al que Klipper debe conectarse.

Ejemplo para USB/serie:

```ini
[mcu]
serial: /dev/serial/by-id/usb-Klipper_stm32f446xx_...
```

Para un MCU adicional, usas un nombre:

```ini
[mcu chamber]
serial: /dev/serial/by-id/usb-Klipper_rp2040_...
```

Después de esto, los pines del MCU adicional se pueden especificar con un prefijo:

```ini
[temperature_sensor chamber_air]
sensor_type: Generic 3950
sensor_pin: chamber:gpio26

[fan_generic chamber_fan]
pin: chamber:gpio15
```

La lógica es simple: `gpio15` significa "pin `chamber` en el MCU denominado `chamber`".

## Nombres de pines y prefijos

Klipper usa nombres de pines de hardware.

Ejemplos:

- para STM32: `PA4`, `PB0`, `PC13`;
- para RP2040: `gpio15`, `gpio26`;
- para Arduino/AVR puede haber sus propios alias.

Antes de un nombre de pin puede haber símbolos:

- `!` — invertir la lógica;
- `^` — habilitar pull-up si el MCU lo soporta;
- `~` — habilitar pull-down si el MCU lo soporta.

Ejemplo:

```ini
[gcode_button chamber_door]
pin: ^chamber:gpio12
```

Esto no es "magia de Klipper", sino una configuración específica de un pin de entrada en un MCU específico. Así que el diagrama de pines de la placa debe ser exacto.

## Por qué se necesita MCU adicional

El MCU adicional es útil cuando necesitas separar periféricos en un bloque separado.

Ejemplos para dispositivos tipo iDryer:

- sensores de temperatura y humedad de la cámara;
- ventilador de circulación;
- ventilador de filtro;
- retroiluminación;
- botón de puerta;
- sensor de tapa;
- servo amortiguador;
- módulo separado con celda de carga;
- OLED o RFID adicional;
- entrada de emergencia que es más conveniente de enrutar cerca del dispositivo.

Este enfoque es conveniente si el dispositivo debe ser parte de un sistema Klipper, no una caja Wi-Fi separada.

## Enfoque MCU o controlador independiente

Hay dos caminos diferentes.

**MCU en Klipper**:

- el dispositivo se controla desde `printer.cfg`;
- los pines son visibles para Klipper;
- puedes usar secciones existentes como `fan_generic`, `temperature_sensor`, `heater_generic`, `output_pin`;
- el estado es visible en la interfaz de Klipper;
- la comunicación con el host es necesaria.

**Controlador independiente**:

- el dispositivo toma sus propias decisiones;
- puede tener Wi-Fi, interfaz web, MQTT;
- no necesita depender de la impresora;
- requiere su propio firmware y lógica de seguridad;
- no se conecta como un `[mcu]` regular en Klipper.

ESP32 es a menudo bueno para un dispositivo Wi-Fi independiente. RP2040 y STM32 a menudo son más convenientes como MCU cableado en Klipper.

## USB, UART y CAN

La comunicación entre host y MCU puede ser diferente.

**USB** — la opción más común y sencilla para una o dos placas cerca del host. Conveniente para Pico, placas STM32 y muchas placas de impresora.

**UART** — comunicación serie a través de pines TX/RX separados. Puede ser útil en algunas placas, pero requiere conexión cuidadosa de nivel, tierra y velocidad.

**CAN** — conveniente para módulos remotos, placas de cabezal y arquitectura cableada más estable. Pero CAN requiere un microcontrolador soportado, un transceptor CAN, un bus adecuado, terminadores e instalación de interfaz Linux.

Para un primer controlador adicional, USB es generalmente más simple. CAN tiene sentido cuando hay una razón real: cableado más largo, múltiples nodos, placa de cabezal o infraestructura CAN existente.

## MCU no protege la sección de potencia

Importante: agregar un MCU no hace que una carga sea segura.

Si un MCU controla un ventilador, calentador o SSR, aún necesitas:

- interruptor de potencia correcto;
- suministro de potencia adecuado;
- cables y terminales para la corriente;
- fusible;
- protección térmica independiente para el calentador;
- carcasa segura;
- verificación del comportamiento si se pierde la comunicación o el host se apaga.

Si el host pierde comunicación con el MCU, Klipper puede apagar el sistema, pero esto no reemplaza la protección de hardware. Un calentador debe diseñarse de modo que una falla individual de firmware, sensor, SSR o comunicación no conduzca a un modo inseguro.

## Qué verificar antes de elegir un MCU

Antes de comprar una placa para MCU de Klipper, verifica:

- si el microcontrolador es soportado por Klipper;
- si hay una configuración lista o instrucciones para la placa;
- qué método de comunicación se necesita: USB, UART o CAN;
- cómo se flashea la placa;
- si tienes suficiente GPIO, ADC, PWM, I2C, SPI, UART;
- qué pines están realmente expuestos;
- qué lógica GPIO: generalmente `3.3V`;
- si se necesitan controladores/MOSFET/SSR para cargas;
- si hay documentación para potencia y diagrama de pines;
- qué sucede si se pierde comunicación con el MCU.

Para un primer MCU adicional, generalmente es más fácil elegir RP2040/Pico o una placa STM32 bien conocida con instrucciones claras.

## Errores comunes

- pensar que el MCU contiene toda la lógica de Klipper;
- confundir host y MCU;
- agregar `[mcu chamber]` pero luego especificar pines sin el prefijo `chamber:`;
- tomar un pin del diagrama de pines de otra persona;
- flashear el tipo de microcontrolador incorrecto en `make menuconfig`;
- no verificar el offset del bootloader y el método de flasheo de la placa;
- usar un cable USB inestable;
- conectar `5V` a entrada `3.3V`;
- alimentar una carga desde GPIO;
- pensar que el apagado de software reemplaza un fusible y un fusible térmico.

## Puntos clave

En Klipper, un MCU es una placa que controla físicamente los pines, y el host planifica y coordina el trabajo. El MCU adicional te permite expandir el sistema y mover periféricos más cerca del dispositivo.

Para tareas tipo iDryer, esto es conveniente para ventiladores, sensores, filtros, retroiluminación, botones y algunos actuadores. Pero la sección de potencia y la seguridad del calentador siguen siendo una tarea de hardware separada.

## Materiales relacionados

- [Klipper: Code overview](https://www.klipper3d.org/Code_Overview.html) — arquitectura de Klipper, división de código de host y microcontrolador, modelo de tiempo y GPIO.
- [Klipper: Configuration reference - Micro-controller configuration](https://www.klipper3d.org/Config_Reference.html#micro-controller-configuration) — `[mcu]`, `[mcu name]` adicional, formato de nombre de pin y prefijos.
- [Klipper: Installation - Building and flashing the micro-controller](https://www.klipper3d.org/Installation.html#building-and-flashing-the-micro-controller) — proceso general de `make menuconfig`, construcción y flasheo del MCU.
- [Klipper: Bootloaders](https://www.klipper3d.org/Bootloaders.html) — por qué diferentes placas tienen diferentes métodos de flasheo y por qué el bootloader es importante.
- [Klipper: CANBUS](https://www.klipper3d.org/CANBUS.html) — comunicación CAN, `canbus_uuid`, puente USB a CAN y requisitos de hardware.
