# Fundamentos de hardware

Esta sección cubre todo lo que necesitas para construir un secador de filamento desde cero — desde fundamentos de electrónica hasta guías prácticas de cableado.

No se requiere experiencia previa en electrónica. Cada artículo se enfoca en un tema específico y se vincula a material relacionado.

## Contenidos

### 00. Comienza aquí

| Archivo | Qué hay adentro |
|---|---|
| `00-start-here/01-introduction.md` | Para quién es esta sección, cómo leerla y por qué el camino va de simple a complejo. |

### 01. Fundamentos de electrónica

| Archivo | Qué hay adentro |
|---|---|
| `01-electronics-basics/01-load-calculation-24v.md` | Voltaje, corriente, potencia, ley de Ohm, cálculo de carga 24V, derating, lectura de hojas de datos. |
| `01-electronics-basics/02-mosfet-module.md` | MOSFET como interruptor electrónico, módulos listos, cargas DC, ventiladores, tiras LED, calentadores. |
| `01-electronics-basics/03-triac.md` | TRIAC para cargas AC, optoacoplador, aislamiento galvánico, circuito snubber, calor y disipador de calor. |
| `01-electronics-basics/04-solid-state-relay-ssr.md` | SSR, diferencias de relés mecánicos, variantes AC/DC, disipador de calor, selección de voltaje y corriente. |

### 02. Controladores

| Archivo | Qué hay adentro |
|---|---|
| `02-controllers/00-how-to-choose-controller.md` | Tabla de selección de controlador por tarea. Lee esto primero. |
| `02-controllers/01-esp32-controller.md` | ESP32, Wi-Fi/Bluetooth, por qué no es ideal como Klipper MCU. |
| `02-controllers/02-arduino-controller.md` | Arduino como plataforma de aprendizaje, limitaciones para dispositivos reales y Klipper. |
| `02-controllers/03-rp2040-controller.md` | RP2040/Pico, flasheo fácil vía BOOTSEL, uso como Klipper MCU. |
| `02-controllers/04-stm32-controllers.md` | Familia STM32, placas de impresora, DFU/SWD/ST-Link, complejidad de selección y flasheo. |
| `02-controllers/05-mcu-in-klipper.md` | Qué es un MCU, rol del host de Klipper, configuración de pin, programación de G-code. |
| `02-controllers/06-uart-interface.md` | Interfaz serial UART, cruce RX/TX, GND, niveles 3.3V/5V. |
| `02-controllers/07-i2c-interface.md` | Bus I2C, SDA/SCL, direcciones de dispositivo, pantallas, sensores, líneas cortas. |
| `02-controllers/08-spi-interface.md` | SPI, MOSI/MISO/SCK/CS, pantallas, RFID, intercambio de datos rápido, CS separado por dispositivo. |
| `02-controllers/09-can-interface.md` | Bus CAN, par diferencial, placas de cabezal de herramienta, terminadores, inmunidad al ruido. |
| `02-controllers/10-usb-uart-adapters.md` | Adaptadores USB-UART, flasheo, logs seriales, RX/TX, niveles de voltaje, errores comunes. |
| `02-controllers/11-flashing-controller.md` | Qué significa flasheo, métodos UF2/USB/DFU/ST-Link, proceso de compilación de Klipper. |

### 03. Componentes comunes

| Archivo | Qué hay adentro |
|---|---|
| `03-common-components/01-overview.md` | Qué son los componentes, lista de temas y su rol en el dispositivo. |
| `03-common-components/02-heaters.md` | Calentadores 12V/24V/110–230V AC, potencia, sensor de temperatura, seguridad. |
| `03-common-components/03-fans.md` | Flujo de aire, presión estática, ruido, tipos 2-pin/3-pin/4-pin. |
| `03-common-components/04-thermistors.md` | Termistores, contacto térmico, pasta térmica/funda, retroalimentación PID. |
| `03-common-components/05-led-strips.md` | Tiras LED 5V/12V/24V, corriente por metro, MOSFET, potencia, tiras direccionables. |
| `03-common-components/06-servo-motors.md` | Motores servo, potencia, señal, corriente pico, fuente de alimentación separada. |
| `03-common-components/07-load-cells.md` | Celdas de carga, amplificador HX711, mecánica de montaje, calibración. |
| `03-common-components/08-oled-display.md` | Pantallas OLED, I2C/SPI, dirección, potencia, cuándo usar pantalla. |
| `03-common-components/09-touchscreen.md` | Pantallas TFT/táctil, UART/SPI/HDMI, potencia, compatibilidad. |
| `03-common-components/10-rfid-and-nfc.md` | RFID/NFC, tarjetas, tags, frecuencias, cableado, casos de uso. |

### 04. Física térmica y materiales

| Archivo | Qué hay adentro |
|---|---|
| `04-thermal-physics-and-materials/01-overview.md` | Por qué una sección sobre calor, materiales, carcasas, aislamiento y seguridad. |
| `04-thermal-physics-and-materials/02-thermal-conductivity.md` | Conductividad térmica, aislamiento, puentes térmicos, clasificaciones de temperatura de material. |
| `04-thermal-physics-and-materials/03-material-safety.md` | Inflamabilidad, gases, toxicidad, PIR/XPS/EPS, hojas de datos de seguridad (SDS/MSDS). |
| `04-thermal-physics-and-materials/04-convection-and-airflow.md` | Convección, calentador 100W sin flujo de aire vs. débil vs. flujo apropiado, transferencia de calor. |

### 05. Herramientas (era 04 en estructura de carpeta EN — nota: carpeta es `04-tools/`)

| Archivo | Qué hay adentro |
|---|---|
| `04-tools/01-overview.md` | Lista de herramientas: multímetro, USB-TTL, soldadura, crimpado, ST-Link, osciloscopio. |
| `04-tools/02-multimeter.md` | Voltaje, continuidad, resistencia, seguridad de medición. |
| `04-tools/03-usb-ttl-adapter.md` | Adaptador USB-TTL/USB-UART, flasheo, logs seriales, RX/TX, niveles de voltaje. |
| `04-tools/04-soldering.md` | Soldadura de cables, conectores JST, termistores, errores comunes. |
| `04-tools/05-crimping-connectors.md` | Crimpado de terminales y conectores, calidad de contacto, uniones de crimpado malas. |
| `04-tools/06-st-link.md` | ST-Link, STM32, interfaz SWD, recuperación después flasheo fallido. |
| `04-tools/07-oscilloscope.md` | PWM, UART, ruido, caída de voltaje, seguridad de voltaje mains, medición de frecuencia. |

### 06. Guías prácticas (carpeta: `05-practical-guides/`)

| Archivo | Qué hay adentro |
|---|---|
| `05-practical-guides/01-connecting-fan.md` | Cableado de ventilador, voltaje, control lado controlador, ruido. |
| `05-practical-guides/02-checking-thermistor.md` | Verificación de termistor con multímetro, resistencia, cableado, lecturas de firmware. |
| `05-practical-guides/03-connecting-servo.md` | Potencia de servo, línea de señal, corriente pico, reinicios del controlador. |
| `05-practical-guides/04-connecting-load-cell.md` | Celda de carga, amplificador HX711, potencia, cables de señal, calibración. |
| `05-practical-guides/05-connecting-rfid-reader.md` | Lector RFID, potencia, SPI/UART/I2C, errores comunes. |

### 07. Impresión 3D (carpeta: `06-3d-printing/`)

| Archivo | Qué hay adentro |
|---|---|
| `06-3d-printing/01-overview.md` | Por qué una sección sobre partes impresas, carcasas, conductos y montajes. |
| `06-3d-printing/02-what-is-stl.md` | Formato STL, limitaciones, por qué un archivo STL no es suficiente para montaje. |
| `06-3d-printing/03-materials-petg-abs-asa.md` | PETG, ABS, ASA — dónde usar, límites cerca de fuentes de calor. |
| `06-3d-printing/04-heat-resistant-materials.md` | Materiales para partes cerca del calor, deformación, margen de temperatura. |
| `06-3d-printing/05-enclosure-design.md` | Diseño de carcasa, ventilación, montajes, distancia del calentador, acceso de servicio. |
| `06-3d-printing/06-why-pla-is-risky.md` | PLA cerca de fuentes de calor, ablandamiento, deformación, riesgo de falla de carcasa. |

### 08. Errores comunes (carpeta: `07-common-mistakes/`)

| Archivo | Qué hay adentro |
|---|---|
| `07-common-mistakes/01-overview.md` | Lista de errores típicos y la lógica detrás de la sección de diagnóstico. |
| `07-common-mistakes/02-power-mistakes.md` | Fuentes de alimentación débiles, caída de voltaje, margen de potencia, terminales malos. |
| `07-common-mistakes/03-wiring-mistakes.md` | Cables intercambiados, sin tierra, RX/TX, cables delgados, conexiones malas. |
| `07-common-mistakes/04-controller-mistakes.md` | Desajuste 3.3V/5V, placa incorrecta, firmware, niveles de señal. |
| `07-common-mistakes/05-heater-ssr-mistakes.md` | Calentadores, SSR, 110–230V AC, disipadores de calor, tipo de relé incorrecto. |
| `07-common-mistakes/06-diagnostic-checklist.md` | Secuencia de diagnóstico de dispositivo paso a paso rápida. |
