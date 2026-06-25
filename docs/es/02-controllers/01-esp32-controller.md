# Controlador ESP32

ESP32 es una familia de microcontroladores Espressif con Wi-Fi, Bluetooth y un amplio conjunto de periféricos. En dispositivos DIY, se elige a menudo cuando necesitas construir un módulo independiente: se conecta a la red por sí solo, lee sensores, muestra una página en el navegador y controla salidas simples.

Para dispositivos alrededor de una impresora 3D, ESP32 es útil no como "otra placa de potencia", sino como un pequeño controlador conectado a la red: un sensor de temperatura/humedad, un módulo de ventilación, un filtro simple con interfaz web, monitoreo de cámara separada o una secadora independiente.

## Dónde es útil ESP32

Tareas típicas:

- sensor Wi-Fi de temperatura y humedad;
- controlador de ventilador separado a través de módulo MOSFET;
- control de relé o SSR con señal de bajo voltaje;
- pantalla OLED sobre I2C;
- lector RFID/NFC sobre SPI o UART;
- servo con potencia separada;
- página web simple para estado y configuración;
- integración con MQTT, Home Assistant o tu propia lógica local;
- prototipo autónomo que no necesita ser parte de Klipper.

ESP32 es bueno cuando el dispositivo debe vivir separadamente de la impresora e intercambiar datos a través de la red. Si la tarea es simplemente agregar pines a Klipper, generalmente es mejor mirar RP2040, STM32 o una placa de impresora lista.

## Arquitectura típica del dispositivo

ESP32 no alimenta cargas directamente. Emite señales de control, y módulos separados hacen el trabajo de potencia.

![Placa de desarrollo ESP32 con pines GPIO](../../img/02-controllers/01-esp32-dev-board.jpg)

*Fuente: [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:ESP32_Dev_Board.jpg), Edwiyanto, CC BY-SA 4.0*

En la práctica, se ve así:

- ESP32 se alimenta desde USB o desde un `5V` estable en la placa de desarrollo;
- la lógica del ESP32 misma funciona a `3.3V`;
- los sensores se conectan a GPIO, I2C, SPI, UART o ADC;
- los ventiladores, tiras LED, calentadores DC se conectan a través de MOSFET o controlador;
- los calentadores de red se conectan únicamente a través de un SSR/relé AC apropiado y una sección de potencia segura;
- el servo se alimenta desde una fuente `5V/6V` separada, y ESP32 proporciona solo la señal.

GPIO no es una fuente de potencia para una carga. Un pin puede cambiar la entrada del controlador, pero no debe alimentar directamente un ventilador, calentador, relé, servo o tira LED.

## Qué significa ESP32 en una placa

La etiqueta "ESP32" puede significar diferentes cosas:

- el chip ESP32 mismo;
- un módulo con el chip, memoria flash y antena, como ESP32-WROOM;
- una placa de desarrollo con USB, regulador de potencia, botones y pines expuestos;
- variantes más nuevas: ESP32-S3, ESP32-C3, ESP32-C6 y otros.

Para un primer proyecto, es más conveniente usar una placa de desarrollo que un módulo desnudo. Una placa de desarrollo ya tiene USB, un regulador de potencia, botones `BOOT`/`EN` y pines para protoboard.

Antes de comprar, verifica:

- el nombre exacto de la placa y el chip;
- si tiene USB-C o micro-USB;
- cuál USB-UART o USB integrado se usa;
- si hay esquemático y diagrama de pines;
- cuáles GPIO están realmente expuestos;
- qué regulador de potencia hay en la placa;
- si tiene una antena adecuada y espacio alrededor;
- si el tamaño de la placa cabe en tu carcasa.

## Lógica de 3.3V

ESP32 funciona con lógica `3.3V`. Esto significa que un nivel `HIGH` típico en GPIO es alrededor de `3.3V`, no `5V`.

Lo que importa:

- no apliques `5V` a GPIO de ESP32;
- para sensores y módulos de `5V`, puedes necesitar un convertidor de nivel;
- las resistencias de pull-up de I2C deben ir a `3.3V` si el bus está conectado a ESP32;
- algunos módulos MOSFET/SSR listos pueden no funcionar de forma confiable desde `3.3V`;
- la potencia de carga no se puede tomar de GPIO.

Muchos sensores ya están disponibles en variantes de `3.3V`. Para ESP32, esta es la mejor opción.

## Potencia

Las placas de desarrollo generalmente tienen una entrada USB y un pin `5V`/`VIN`, y el ESP32 mismo se alimenta desde un regulador `3.3V`.

Errores comunes:

- alimentar ESP32 desde un cable USB débil;
- alimentar un servo, ventilador o relé desde el pin `3.3V` en la placa;
- conectar una carga pesada al pin `5V` sin entender de dónde viene esa corriente;
- no conectar GND común entre ESP32 y el controlador de bajo voltaje;
- ESP32 se reinicia cuando Wi-Fi comienza debido a caída de potencia.

Wi-Fi extrae corriente pulsada. Para un funcionamiento estable, un buen cable, regulador, condensadores en la placa y potencia separada para cargas son importantes.

## GPIO y pines especiales

ESP32 tiene muchos GPIO, pero no todos los pines son igualmente convenientes.

En ESP32 clásico:

- algunos pines están vinculados a la carga del chip, estos son pines strapping;
- `GPIO6-GPIO11` generalmente están ocupados por memoria flash y no se usan;
- `GPIO34-GPIO39` son solo entrada;
- `GPIO1` y `GPIO3` a menudo se usan como UART para firmware y registros;
- algunos pines pueden estar ocupados por LED, botón u otros circuitos en una placa de desarrollo específica.

Los pines strapping determinan el modo de arranque al inicio. Si la circuitería externa tira de tal pin de forma incorrecta, ESP32 puede no arrancar o puede entrar en modo de actualización de firmware.

Regla práctica: para la primera versión, usa pines del diagrama de pines de tu placa específica y evita pines marcados como `BOOT`, `FLASH`, `STRAP`, `TX0`, `RX0`, `GPIO6-GPIO11` a menos que entiendas su función.

## ADC en ESP32

ESP32 puede medir voltaje analógico a través de ADC, pero no es un multímetro de laboratorio.

Lo que importa:

- en ESP32 clásico hay ADC1 y ADC2;
- ADC2 entra en conflicto con Wi-Fi, así que para un dispositivo Wi-Fi es mejor usar pines ADC1;
- el rango de medición depende de la configuración de atenuación;
- la medición puede requerir calibración;
- no puedes aplicar voltaje por encima del nivel seguro de GPIO a ADC;
- un termistor generalmente necesita un divisor de voltaje y la tabla/modelo correcto en el firmware.

Si necesita un sensor de temperatura preciso, a menudo es más simple usar un sensor digital o un módulo listo con una biblioteca conocida. Para un termistor NTC, funciona ESP32, pero el circuito y las configuraciones de ADC deben verificarse.

## PWM, I2C, SPI y UART

ESP32 es conveniente para periféricos:

- PWM a través de LEDC es adecuado para ventiladores, retroiluminación y señales servo;
- I2C es adecuado para pantallas OLED y muchos sensores;
- SPI es adecuado para módulos RFID, pantallas y dispositivos rápidos;
- UART es adecuado para GPS, algunos sensores, otros controladores y depuración.

ESP32 tiene una matriz GPIO flexible: muchas señales se pueden asignar a pines diferentes. Pero esto no significa que cualquier pin sea siempre una buena opción. Las limitaciones específicas de la placa, memoria flash, pines de arranque y UART ocupado aún deben considerarse.

## ESP32 y Klipper

ESP32 se ve mejor como un dispositivo Wi-Fi/IoT separado cerca de la impresora, no como el camino principal para un MCU adicional en Klipper.

Klipper se organiza como un host más uno o más MCU. Para nuevos MCU adicionales, generalmente es más práctico usar:

- RP2040;
- STM32;
- placas de impresoras 3D listas.

ESP32 puede intercambiar datos con el sistema de impresora por separado: a través de MQTT, API HTTP, Home Assistant, tu propio servidor u otra integración. Pero esto ya no es lo mismo que agregar `[mcu]` a la configuración de Klipper y usar pines directamente.

## Qué verificar antes de comprar

Antes de comprar una placa ESP32, verifica:

- modelo exacto: ESP32, S3, C3, C6, etc.;
- voltaje de lógica;
- si tiene USB y cómo se flashea la placa;
- si hay un diagrama de pines oficial o esquemático;
- qué pines son seguros para GPIO;
- qué pines son solo entrada;
- qué pines están ocupados por flash/PSRAM, USB, UART o LED;
- si tienes suficiente ADC/I2C/SPI/UART para la tarea;
- cómo se alimenta la placa;
- si cabe en la carcasa;
- si hay una biblioteca o firmware para tu escenario.

Si una placa de un mercado no tiene esquemático y un diagrama de pines adecuado, se puede usar para experimentos, pero no es adecuada para un dispositivo que debe funcionar desatendido durante un largo período.

## Errores comunes

- aplicar `5V` a GPIO de ESP32;
- alimentar una carga desde GPIO;
- alimentar un servo o relé desde un pin `3.3V` débil;
- olvidar GND común con MOSFET/controlador;
- elegir un pin ADC2 para un sensor y luego habilitar Wi-Fi;
- usar un pin de strapping de arranque para que ESP32 no inicie;
- usar `GPIO34-GPIO39` como salidas;
- comprar un módulo sin diagrama de pines y esquemático;
- pensar que "ESP32 con Wi-Fi" automáticamente significa control de calentador de red seguro;
- intentar reemplazar la electrónica de potencia con firmware.

## Puntos clave

ESP32 es una buena opción para dispositivos Wi-Fi autónomos: sensores, interfaces web, control de ventilación simple, filtros, pantallas y periféricos.

Pero ESP32 funciona con lógica `3.3V`, tiene pines especiales y no debe alimentar directamente cargas. Para circuitos de potencia, se necesitan MOSFET, controladores, relés o SSR, y para un calentador de red, se necesita una sección de potencia completamente segura.

## Materiales relacionados

- [Espressif: ESP32 Wi-Fi & Bluetooth SoC](https://www.espressif.com/en/products/socs/esp32/datasheet) — descripción oficial de la familia ESP32, módulos, placas de desarrollo y enlaces a documentación.
- [Espressif: ESP32 Series Datasheet](https://documentation.espressif.com/esp32_datasheet_en.html) — características del chip, periféricos, ADC, PWM, UART, I2C, SPI y limitaciones de pines.
- [ESP-IDF Programming Guide: GPIO & RTC GPIO](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/gpio.html) — tabla de GPIO, pines strapping, pines solo entrada, pines flash/PSRAM y limitación ADC2 con Wi-Fi.
- [Espressif: ESP32 Hardware Design Guidelines](https://docs.espressif.com/projects/esp-hardware-design-guidelines/en/latest/esp32/esp-hardware-design-guidelines-en-master-esp32.pdf) — recomendaciones para potencia, pines strapping, GPIO, ADC y diseño de placa.
- [Arduino-ESP32: LED Control API](https://docs.espressif.com/projects/arduino-esp32/en/latest/api/ledc.html) — PWM/LEDC en Arduino-ESP32 para ventiladores, retroiluminación y otras señales PWM.
- [Klipper: Code overview](https://www.klipper3d.org/Code_Overview.html) — contexto arquitectónico de Klipper para MCU y lista de backends de microcontrolador soportados en el árbol de código fuente.
