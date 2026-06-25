# Pantalla OLED

Una pantalla OLED es una pantalla pequeña que muestra texto, números, iconos simples y el estado del dispositivo. A diferencia del LCD normal, el OLED se ilumina solo y no necesita retroiluminación separada. Por lo tanto, los módulos OLED pequeños son legibles, ocupan poco espacio y son convenientes para dispositivos simples de bricolaje.

En un dispositivo tipo iDryer, un OLED puede mostrar la temperatura, la humedad, el modo de trabajo, el error, el estado de Wi-Fi, el filamento restante o la fase de secado actual.

## Cuándo OLED Is Useful

Vale la pena agregar un OLED si los usuarios necesitan ver el estado del dispositivo directamente en el gabinete:

- current chamber temperature;
- humidity;
- target temperature;
- working mode;
- timer;
- sensor error;
- fan or heater status;
- connection status;
- Menú sencillo sin pantalla grande.

Si el dispositivo siempre se administra a través de Klipper, una interfaz web o una aplicación móvil, es posible que no sea necesario un OLED por separado. Agrega cableado, espacio en el gabinete, código y otro punto de falla.

## Tamaños y controladores típicos

Los pequeños módulos OLED más comunes:

- `128x32` pixels;
- `128x64` pixels;
- diagonal about `0.91"` or `0.96"`;
- monochrome: white, blue, yellow-blue;
- con controlador `SH1106` o similar `SH1106`.

`SH1106` y `SSD1306` tienen un aspecto similar pero no siempre son totalmente compatibles en código. Si se configura una biblioteca para `SH1106` pero el módulo es en realidad `SH1106`, la pantalla puede mostrar una imagen desplazada, basura o no funcionar.

Antes de comprar, es importante comprobar no sólo el tamaño de la pantalla sino también el controlador, la interfaz y el voltaje de suministro.

## I2C y SPI

Los módulos OLED pequeños suelen conectarse mediante I2C o SPI.

Un módulo I2C suele tener 4 contactos:

- `VCC`;
- `GND`;
- `SDA`;
- `SCL`.

Un módulo SPI normalmente necesita más líneas:

- `VCC`;
- `GND`;
- `SCK`/`CLK`;
- `MOSI`/`DIN`;
- `CS`;
- `DC`;
- sometimes `RST`.

I2C es más sencillo de cablear y suele ser suficiente para el estado, la temperatura y un menú sencillo. SPI es más rápido y mejor si la pantalla se vuelve a dibujar con frecuencia, pero para una visualización de estado pequeña esto rara vez es crítico.

![Connecting I2C OLED display to controller](../../img/03-common-components/08-oled-i2c-wiring.jpg)

*Source: [Adafruit Learning System](https://learn.adafruit.com/adafruit-128x64-oled-featherwing/), CC BY-SA 3.0*

## Niveles de potencia y lógica

Un módulo OLED puede tener clasificación para `5V`, `5V` o tener un regulador y cambio de nivel en la placa. Externamente, estos módulos pueden parecer casi idénticos.

Antes de conectar, verifique:

- qué potencia figura en el módulo o en la página del producto;
- si las líneas `SCL`/`SCL` son compatibles con la lógica del controlador;
- si el módulo tiene pull-ups I2C;
- si las dominadas no entran en conflicto con el voltaje del controlador.

Para ESP32 y la mayoría de los microcontroladores modernos, es más seguro asumir la lógica `5V`. Si un módulo OLED lleva I2C a `5V`, puede ser problemático para un controlador de 3,3 V.

Muchos módulos OLED I2C populares funcionan desde `3.3V` y se conectan bien a ESP32 directamente, pero es necesario verificar el módulo específico.

## I2C Address

I2C OLED often has addresses:

- `0x3C`;
- `0x3D`.

Si la pantalla no responde, la dirección es lo primero que se debe verificar después de la alimentación y los cables. Algunos módulos le permiten cambiar la dirección mediante un puente o soldando un pequeño puente en la placa.

Señales de dirección incorrecta:

- se inicia el boceto o el firmware pero la pantalla está en blanco;
- El escáner I2C ve el dispositivo en una dirección diferente;
- la biblioteca inicializa la visualización sin resultados visibles;
- cambiar `0x3D` a `0x3D` hace que funcione.

## Qué mostrar en una pantalla pequeña

Un OLED `128x64` o `128x64` tiene muy poco espacio. No intente crear una interfaz completa para teléfono inteligente.

Buen juego para secadora o calentador:

- large current temperature;
- target temperature;
- humedad si hay sensor;
- mode: `HEAT`, `DRY`, `IDLE`, `ERROR`;
- small fan/heat icon;
- error code or short message.

Bad set:

- long sentences;
- tiny tables;
- muchos elementos de menú en una pantalla;
- constantly scrolling text;
- animación decorativa en lugar de estado útil.

Para un dispositivo con calentador, es más importante ver rápidamente un error que una bonita pantalla de presentación.

## Quemado y brillo

Los píxeles OLED envejecen debido al brillo. Si muestra el mismo texto brillante en un lugar durante muchas horas, eventualmente puede aparecer un rastro.

Para un dispositivo de bricolaje, esto no siempre es fundamental, pero es mejor:

- no mantener el brillo al máximo sin necesidad;
- apagar la pantalla después del tiempo de inactividad;
- occasionally move static elements;
- no mostrar relleno blanco constantemente;
- Utilice actualizaciones breves en lugar de animaciones adicionales.

En una cámara cálida o cerca de un calentador, OLED también vive peor. Es mejor mantener los componentes electrónicos en una zona con temperatura controlada que no exceda el rango del módulo.

## Longitud del cable e interferencia

A I2C no le gustan los cables largos, especialmente cerca de motores, calentadores y líneas eléctricas. Si OLED está en una puerta o en un panel extraíble, un cable largo y flexible puede convertirse en una fuente de ruido.

Practical rules:

- mantenga cortos `SCL` y `SCL`;
- aléjelos de los cables de alimentación del calentador;
- utilice `GND` común;
- no hagas un conector que entre al revés;
- para una cubierta removible, use un conector y un protector contra tirones adecuados;
- Si I2C es inestable, primero acorte los cables y verifique los pull-ups.

SPI suele tolerar mejor una mayor velocidad de actualización, pero tiene más cables y los errores de conexión son más comunes.

## OLED or Touchscreen

OLED es bueno para mostrar el estado. No resuelve el problema de entrada sin botones, codificadores u otros controles.

Si los usuarios necesitan con frecuencia cambiar la configuración directamente en el dispositivo, es posible que necesite:

- encoder + OLED;
- several buttons + OLED;
- TFT display;
- touchscreen;
- web interface or app.

No instales una pantalla táctil sólo porque OLED parece pequeño. Para dispositivos simples, un OLED pequeño con un botón a veces es más confiable y claro.

## Qué comprobar antes de comprar

Antes de comprar un módulo OLED, verifique:

- size: `128x32`, `128x64` or other;
- controller: `SSD1306`, `SH1106`, `SH1107`;
- interface: I2C or SPI;
- power: `3.3V`, `5V` or range;
- logic level;
- Dirección I2C si aparece en la lista;
- reset pin support;
- soporte en firmware o biblioteca elegida;
- dimensiones físicas del tablero y orificios de montaje;
- connector location;
- operating temperature;
- color y legibilidad en el ángulo que necesita.

Para un dispositivo ESP32, I2C OLED `SSD1306` en `0x3C` con dirección `0x3C` suele ser lo más conveniente. Para una placa Klipper, verifique si la placa específica es compatible con el bus elegido y cómo se describe la pantalla en la configuración.

## Típicos Errors

- mezclado `SCL` y `SCL`;
- alimentación conectada a voltaje incorrecto;
- didn't check I2C address;
- seleccionó `SH1106` en el código pero el módulo es `SH1106`;
- made I2C wires too long;
- forgot common `GND`;
- conectó el módulo pull-up de 5 V al controlador de 3,3 V sin comprobarlo;
- selected SPI module expecting 4 pins like I2C;
- put screen in hot zone;
- visualización agregada sin comprender qué problema resuelve para los usuarios.

## Principal Point

Una pantalla OLED es buena para estados breves y una interfaz local sencilla. Para la mayoría de los dispositivos de bricolaje, un I2C OLED `128x64` es suficiente si es compatible con la alimentación y el firmware elegido.

Antes de realizar la conexión, verifique el controlador de pantalla, la interfaz, la alimentación, la dirección I2C y la longitud del cable. Si el dispositivo ya es conveniente a través de la interfaz web, es posible que OLED no sea necesario.

## Referencia Materials

- [Adafruit: Monochrome OLED Breakouts](https://learn.adafruit.com/monochrome-oled-breakouts) - practical guide to small SSD1306 OLED, I2C/SPI connection, sizes and examples.
- [SparkFun: Qwiic Micro OLED Hookup Guide](https://learn.sparkfun.com/tutorials/qwiic-micro-oled-hookup-guide) - example of I2C OLED module, library and text/graphics output.
- [ESPHome: SSD1306 OLED Display](https://esphome.io/components/display/ssd1306) - documentation on `ssd1306_i2c`, `ssd1306_spi`, addresses, SSD1306/SH1106 models and configuration.
- [Klipper Configuration Reference: display](https://www.klipper3d.org/Config_Reference.html#display) - display support in Klipper, including `ssd1306` and `sh1106`.
- [SSD1306 Datasheet: Solomon Systech](https://www.radiolocman.com/datasheet/pdf.html?di=168297) - technical description of SSD1306 controller: resolution, I2C/SPI/parallel interfaces and commands.
