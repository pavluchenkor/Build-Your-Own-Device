# Pantallas Táctiles

Una pantalla táctil no es sólo una pantalla. Es una pantalla más entrada del usuario. No solo debe mostrar la temperatura o un botón, sino también indicarle al dispositivo dónde tocó.

Por este motivo, una pantalla táctil es casi siempre más compleja que una OLED. Debe elegir no sólo el tamaño y la resolución, sino también comprender quién dibuja la interfaz, quién procesa los toques, qué interfaz se utiliza y si el firmware elegido la admite.

## Cuándo es útil la pantalla táctil

Una pantalla táctil tiene sentido si el dispositivo necesita una interfaz local completa:

- choosing drying mode;
- ajuste de temperatura y tiempo;
- material profile list;
- confirming errors;
- manual fan, lighting or damper control;
- Wi-Fi setup;
- estado de visualización sin teléfono ni computadora.

Si solo necesita mostrar la temperatura, el error y el modo, generalmente OLED, un par de botones, un codificador o una interfaz web son suficientes. Una pantalla táctil agrega costo, energía, espacio en el gabinete, firmware, cables y otro punto de falla.

## Pregunta principal: ¿Quién dibuja la interfaz?

Antes de comprar, responda la pregunta principal: ¿dónde se encuentra la interfaz de usuario?

Hay varias clases de pantalla diferentes:

![Classes of touchscreens and who draws the interface](../../img/03-common-components/09-touchscreen-classes.svg)

Raw TFT es una pantalla simple con un controlador como `ST7789`, `XPT2046`, `FT5x06`, además de un controlador táctil independiente como `XPT2046` o `FT5x06`. Su microcontrolador o firmware dibuja la interfaz. Esto es flexible pero requiere código, memoria, controladores y calibración.

La pantalla Smart UART/HMI es una pantalla con su propio firmware y editor de interfaz, como Nextion. El microcontrolador envía comandos a través de UART y la pantalla muestra páginas y elementos. Esto reduce la carga de MCU pero vincula su proyecto a las herramientas y al protocolo de esa pantalla.

La impresora TFT, como BTT TFT35, a menudo tiene su propio modo de pantalla táctil a través de UART y una emulación LCD 12864 clásica a través de conectores EXP. Esta pantalla es conveniente para placas de impresora Marlin/3D, pero no es un panel universal para ningún dispositivo de bricolaje.

La pantalla HDMI/DSI/USB para host Linux funciona como un monitor normal y un dispositivo táctil para Raspberry Pi u otra computadora Linux. Esto se adapta a KlipperScreen pero no se conecta directamente al pequeño ESP32 como un módulo simple.

## Connection Interfaces

Las pantallas táctiles utilizan diferentes interfaces.

Opciones comunes:

- SPI: a menudo en un TFT pequeño para ESP32/Arduino;
- I2C: a menudo en controladores táctiles capacitivos, a veces en controladores táctiles;
- UART: en pantallas inteligentes y algunas impresoras TFT 3D;
- EXP1/EXP2/EXP3 - en pantallas compatibles con placas de impresora 3D;
- HDMI + USB: en pantallas Linux para Raspberry Pi;
- DSI: en algunas pantallas Raspberry Pi;
- RGB/8080 paralelo: en TFT más rápido, pero con más cables y requisitos.

No se puede elegir una pantalla sólo por la diagonal. Dos pantallas `3.5"` pueden ser completamente diferentes: un módulo SPI para ESP32, un segundo panel UART con firmware propio, una tercera pantalla HDMI para Raspberry Pi.

## Tacto resistivo y capacitivo

La parte táctil también varía.

Resistive touch:

- responde a la presión de los dedos, el lápiz óptico o las uñas;
- often requires calibration;
- generalmente peor para los gestos;
- can be cheaper;
- encontrado con controladores como `XPT2046`.

Capacitive touch:

- responds to a finger;
- normalmente es más agradable de usar;
- can support multiple touches;
- often has a separate controller like `FT5x06`, `GT911` families;
- Funciona peor con guantes gruesos y algunas fundas protectoras.

Para un dispositivo de taller, el toque resistivo a veces es más práctico porque se puede presionar con una uña o un lápiz. Para un buen panel en el gabinete, el capacitivo generalmente parece más moderno.

## Energía, retroiluminación y corriente

Una pantalla TFT atrae más que una pequeña OLED. El principal consumidor de energía es la luz de fondo.

Antes de conectar, verifique:

- screen power voltage;
- backlight current;
- whether you need a separate 5V source;
- si el brillo de la retroiluminación es ajustable;
- si los niveles lógicos son compatibles;
- si la pantalla sobrecarga el regulador de la placa;
- si la energía disminuye cuando se enciende la luz de fondo.

Si la pantalla se blanquea, parpadea, reinicia el controlador o pierde eventos táctiles, primero verifique la alimentación y la tierra, no el código de la interfaz.

Para un dispositivo con calentador, la pantalla no debería alimentarse desde un pin débil aleatorio. Debería ser parte de un esquema de poder adecuado y con un margen claro.

## Firmware y compatibilidad

Una pantalla hermosa es inútil si el firmware elegido no la admite.

Para el enfoque ESP32/Arduino, debe verificar:

- ¿Existe un controlador de pantalla?
- ¿Existe un controlador de controlador táctil?
- are there enough GPIO;
- ¿Hay suficiente RAM/PSRAM para el búfer?
- qué marco gráfico se utiliza;
- ¿Quién escribirá el menú?

Para ESPHome, verifique la compatibilidad con el controlador de pantalla específico y el componente de pantalla táctil. Por ejemplo, las pantallas ILI9xxx y la pantalla táctil XPT2046 necesitan SPI y una configuración separada, y la pantalla táctil resistiva necesita calibración.

Para Klipper, suelen existir dos mundos diferentes:

- pantallas pequeñas conectadas a MCU y descritas en la configuración de Klipper;
- KlipperScreen en un host Linux, donde la pantalla funciona como monitor y dispositivo táctil.

KlipperScreen normalmente necesita una pantalla donde Linux pueda mostrar un escritorio o una consola. Esto no es lo mismo que un pequeño UART TFT conectado a una placa de impresora.

Para placas Marlin/impresora, verifique si la pantalla específica admite el modo necesario: modo táctil UART, emulación 12864, EXP1/EXP2/EXP3, tipo de controlador específico en la configuración del firmware.

## Pantalla inteligente y pantallas tipo Nextion

La pantalla inteligente es conveniente porque la pantalla almacena páginas, botones, fuentes e imágenes. El controlador envía comandos a través de UART y recibe eventos táctiles.

Pros:

- menos carga en el microcontrolador;
- menos código de gráficos en el firmware principal;
- puedes dibujar la interfaz en el editor de pantalla;
- Solo se necesita UART y energía.

Cons:

- necesita aprender un editor y un protocolo separados;
- La interfaz a menudo se almacena en la pantalla;
- es más difícil mantener sincronizadas las versiones de la interfaz de usuario y del firmware del dispositivo;
- no todos los elementos se comportan como en una aplicación normal;
- reemplazar la pantalla puede requerir un rediseño.

Para un dispositivo simple, la pantalla inteligente puede ser una buena solución si necesita un buen panel sin un host Linux. Pero no es un "monitor normal": es un módulo independiente con su propia lógica.

## Estuche, cables y servicio

Una pantalla táctil es algo que los usuarios tocarán con las manos. Por eso, la mecánica es importante, no sólo los cables.

Comprueba de antemano:

- la pantalla no está en una zona caliente;
- there's a frame or protective mount;
- el cable no se dobla bruscamente al abrir la tapa;
- el cable se puede desconectar para realizar tareas de mantenimiento;
- el conector no puede entrar hacia atrás;
- el caso no presiona en la pantalla;
- hay acceso a una tarjeta SD o USB para actualizaciones si es necesario;
- el usuario no toca las partes eléctricas mientras usa la pantalla;
- El cableado de pantalla táctil/pantalla está separado de los cables del calentador.

Para dispositivos con calentador, es mejor mover la pantalla a la zona del usuario, lejos del aire caliente y las partes eléctricas.

## Qué comprobar antes de comprar

Antes de comprar una pantalla táctil, verifique:

- diagonal y resolución;
- display type: raw TFT, smart UART, printer TFT, HDMI/DSI;
- display interface;
- touch interface;
- controlador de pantalla: por ejemplo `ILI9488`, `ST7789`, `ST7789`;
- controlador táctil: por ejemplo `FT5x06`, `GT911`, `GT911`;
- corriente de alimentación y retroiluminación;
- logic levels;
- support in firmware;
- disponibilidad de documentación y ejemplos;
- disponibilidad de bibliotecas;
- RAM/PSRAM requirements;
- dimensiones del tablero, agujeros y cable;
- operating temperature;
- firmware/interface update method.

Si la descripción del producto carece de ejemplos de controlador de pantalla, interfaz, alimentación y conexión, es mejor no utilizar dicha pantalla para su primer proyecto.

## Típicos Errors

- compré una pantalla "para Arduino", pero el proyecto es KlipperScreen en Linux;
- compré una pantalla HDMI e intenté conectarme directamente a ESP32;
- compré una pantalla inteligente UART pero esperaba que funcionara como una TFT normal;
- eligió TFT sin formato pero no planeó tiempo para el código de menús y gráficos;
- no hay suficiente GPIO para la pantalla SPI y el controlador táctil;
- no hay suficiente RAM para el búfer de pantalla;
- didn't check touch controller;
- didn't calibrate resistive touch;
- la pantalla parpadea debido a la débil potencia de la luz de fondo;
- el cable pasa junto a los cables de alimentación del calentador;
- pantalla montada en zona caliente;
- La interfaz se ve bien pero el error principal es difícil de ver.

## Principal Point

Elija una pantalla táctil por arquitectura, no por diagonal. Primero decida quién dibuja la interfaz: el microcontrolador, la pantalla misma, el firmware de la impresora o el host Linux. Luego verifique la interfaz, la alimentación, el controlador táctil, el soporte de firmware y la mecánica del gabinete.

Para un calentador, secador o filtro simple, generalmente OLED, los botones o la interfaz web son suficientes. Utilice una pantalla táctil cuando los usuarios realmente necesiten una interfaz local.

## Referencia Materials

- [KlipperScreen: Hardware](https://klipperscreen.github.io/KlipperScreen/Hardware/) - requirements and screen examples for KlipperScreen, including HDMI/DSI/Raspberry Pi options.
- [BIGTREETECH TouchScreenFirmware](https://github.com/bigtreetech/BIGTREETECH-TouchScreenFirmware) - firmware and BTT TFT modes: touch mode, Marlin/12864 emulation, EXP connectors and settings.
- [BIGTREETECH TFT35 V3.0 repository](https://github.com/bigtreetech/BIGTREETECH-TFT35-V3.0) - documentation and files for popular 3D printer TFT35.
- [Adafruit 3.5 inch TFT Touchscreen Breakout](https://learn.adafruit.com/adafruit-3-5-color-320x480-tft-touchscreen-breakout) - example of raw TFT with SPI/8-bit modes, separate touch and libraries.
- [ESPHome: Touchscreen Components](https://esphome.io/components/touchscreen) - documentation on touch components, calibration and linking raw touch coordinates to display coordinates.
- [ESPHome: ILI9xxx TFT LCD Series](https://esphome.io/components/display/ili9xxx/) - example of raw TFT display support on ESPHome and important memory limitations.
