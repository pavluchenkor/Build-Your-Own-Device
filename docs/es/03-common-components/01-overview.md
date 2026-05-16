# Componentes Comunes

Los componentes comunes son las partes y módulos que encontrarás más a menudo al ensamblar un dispositivo tipo iDryer o periféricos de impresora 3D.

Propósito de esta sección:

Esta sección sirve como referencia para las piezas que realmente sostendrás en tus manos durante el montaje.

No necesitas conocimientos profundos de electrónica aquí. El objetivo principal es ayudarte a entender:

- qué es este componente;
- por qué lo necesitas;
- cómo se conecta típicamente;
- qué puedes sustituirlo;
- qué parámetros importan al comprar;
- qué más a menudo se rompe en la primera conexión.

Formato de cada página:

- qué es;
- dónde se usa en iDryer y periféricos de impresora 3D;
- qué parece una conexión típica;
- características importantes;
- errores típicos;
- una breve lista de verificación antes de comprar.

Archivos propuestos:

- `02-heaters.md` - calentadores: PTC, almohadillas de silicona, cartuchos, 12V/24V/110-230V AC.
- `03-fans.md` - ventiladores: 2 pines, 3 pines, 4 pines PWM, voltaje, corriente, ruido, flujo de aire.
- `04-thermistors.md` - termistores: NTC 100K, tablas de búsqueda, montaje, circuitos abiertos/cortos.
- `05-led-strips.md` - tiras LED: 5V/12V/24V, regular y direccionable, corriente por metro.
- `06-servo-motors.md` - servomotores: potencia, señal, ángulo, corriente máxima.
- `07-load-cells.md` - celdas de carga: HX711, calibración, montaje mecánico.
- `08-oled-display.md` - OLED: I2C/SPI, dirección, potencia, cuándo es necesario.
- `09-touchscreen.md` - TFT/táctil: UART/SPI/HDMI, potencia, compatibilidad.
- `10-rfid-and-nfc.md` - RFID/NFC: tarjetas, etiquetas, frecuencias, conexión.

## Materiales de Referencia

- [Klipper Configuration Reference](https://www.klipper3d.org/Config_Reference.html) - secciones oficiales de Klipper sobre calentadores, ventiladores, sensores de temperatura, servomotores y pantallas en la configuración.
- [DigiKey: Selecting A Fan](https://www.digikey.com/en/articles/selecting-a-fan) - selección práctica de ventiladores por flujo de aire, presión estática, resistencia de alojamiento y tarea térmica.
- [Adafruit: MOSFET Driver](https://learn.adafruit.com/adafruit-mosfet-driver) - por qué las cargas de alta potencia no se conectan directamente a GPIO y por qué necesitas un interruptor de potencia.
- [SparkFun: Load Cell Amplifier HX711 Breakout Hookup Guide](https://learn.sparkfun.com/tutorials/load-cell-amplifier-hx711-breakout-hookup-guide) - ejemplo de celda de carga, HX711, cables de potencia y señal, y calibración.
- [Adafruit: PN532 RFID/NFC Breakout Wiring](https://learn.adafruit.com/adafruit-pn532-rfid-nfc/breakout-wiring) - ejemplo de un componente donde necesitas verificar potencia, niveles lógicos e interfaz elegida de antemano.

## Ver También

- [Calentadores](02-heaters.md) - el tipo de carga más riesgoso: potencia, temperatura, SSR/MOSFET y protección independiente.
- [Ventiladores](03-fans.md) - flujo de aire, presión estática, 2 pines/3 pines/4 pines y potencia.
- [Termistores](04-thermistors.md) - sensor de temperatura como base para retroalimentación de calentador.
- [Conectar un ventilador](../05-practical-guides/01-connecting-a-fan.md) - ejemplo práctico de conexión de componentes a través de un interruptor de potencia.
- [Errores de calentador y SSR](../07-common-mistakes/05-heater-and-ssr-errors.md) - errores comunes con cargas de alta potencia y red.
