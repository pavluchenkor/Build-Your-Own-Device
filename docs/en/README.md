# Hardware Basics

This section covers everything you need to build a filament dryer from scratch — from electronics fundamentals to practical wiring guides.

No prior electronics experience required. Each article focuses on a specific topic and links to related material.

## Contents

### 00. Start Here

| File | What's inside |
|---|---|
| `00-start-here/01-introduction.md` | Who this section is for, how to read it, and why the path goes from simple to complex. |

### 01. Electronics Basics

| File | What's inside |
|---|---|
| `01-electronics-basics/01-load-calculation-24v.md` | Voltage, current, power, Ohm's law, 24V load calculation, derating, reading datasheets. |
| `01-electronics-basics/02-mosfet-module.md` | MOSFET as an electronic switch, ready-made modules, DC loads, fans, LED strips, heaters. |
| `01-electronics-basics/03-triac.md` | TRIAC for AC loads, optocoupler, galvanic isolation, snubber circuit, heat and heatsink. |
| `01-electronics-basics/04-solid-state-relay-ssr.md` | SSR, differences from mechanical relays, AC/DC variants, heatsink, voltage and current selection. |

### 02. Controllers

| File | What's inside |
|---|---|
| `02-controllers/00-how-to-choose-controller.md` | Controller selection table by task. Read this first. |
| `02-controllers/01-esp32-controller.md` | ESP32, Wi-Fi/Bluetooth, why it's not ideal as a Klipper MCU. |
| `02-controllers/02-arduino-controller.md` | Arduino as a learning platform, limitations for real devices and Klipper. |
| `02-controllers/03-rp2040-controller.md` | RP2040/Pico, easy flashing via BOOTSEL, use as Klipper MCU. |
| `02-controllers/04-stm32-controllers.md` | STM32 family, printer boards, DFU/SWD/ST-Link, complexity of selection and flashing. |
| `02-controllers/05-mcu-in-klipper.md` | What an MCU is, Klipper host role, pin configuration, G-code scheduling. |
| `02-controllers/06-uart-interface.md` | UART serial interface, RX/TX crossover, GND, 3.3V/5V levels. |
| `02-controllers/07-i2c-interface.md` | I2C bus, SDA/SCL, device addresses, displays, sensors, short lines. |
| `02-controllers/08-spi-interface.md` | SPI, MOSI/MISO/SCK/CS, displays, RFID, fast data exchange, separate CS per device. |
| `02-controllers/09-can-interface.md` | CAN bus, differential pair, toolhead boards, terminators, noise immunity. |
| `02-controllers/10-usb-uart-adapters.md` | USB-UART adapters, flashing, serial logs, RX/TX, voltage levels, common mistakes. |
| `02-controllers/11-flashing-controller.md` | What flashing means, UF2/USB/DFU/ST-Link methods, Klipper build process. |

### 03. Common Components

| File | What's inside |
|---|---|
| `03-common-components/01-overview.md` | What components are, list of topics, and their role in the device. |
| `03-common-components/02-heaters.md` | Heaters 12V/24V/110–230V AC, power, temperature sensor, safety. |
| `03-common-components/03-fans.md` | Airflow, static pressure, noise, 2-pin/3-pin/4-pin types. |
| `03-common-components/04-thermistors.md` | Thermistors, thermal contact, thermal paste/sleeve, PID feedback. |
| `03-common-components/05-led-strips.md` | LED strips 5V/12V/24V, current per meter, MOSFET, power, addressable strips. |
| `03-common-components/06-servo-motors.md` | Servo motors, power, signal, peak current, separate power supply. |
| `03-common-components/07-load-cells.md` | Load cells, HX711 amplifier, mounting mechanics, calibration. |
| `03-common-components/08-oled-display.md` | OLED displays, I2C/SPI, address, power, when to use a display. |
| `03-common-components/09-touchscreen.md` | TFT/touch screens, UART/SPI/HDMI, power, compatibility. |
| `03-common-components/10-rfid-and-nfc.md` | RFID/NFC, cards, tags, frequencies, wiring, use cases. |

### 04. Thermal Physics and Materials

| File | What's inside |
|---|---|
| `04-thermal-physics-and-materials/01-overview.md` | Why a section on heat, materials, enclosures, insulation, and safety. |
| `04-thermal-physics-and-materials/02-thermal-conductivity.md` | Thermal conductivity, insulation, thermal bridges, material temperature ratings. |
| `04-thermal-physics-and-materials/03-material-safety.md` | Flammability, fumes, toxicity, PIR/XPS/EPS, safety data sheets (SDS/MSDS). |
| `04-thermal-physics-and-materials/04-convection-and-airflow.md` | Convection, 100W heater with no airflow vs. weak vs. proper airflow, heat transfer. |

### 05. Tools (was 04 in EN folder structure — note: folder is `04-tools/`)

| File | What's inside |
|---|---|
| `04-tools/01-overview.md` | Tool list: multimeter, USB-TTL, soldering, crimping, ST-Link, oscilloscope. |
| `04-tools/02-multimeter.md` | Voltage, continuity, resistance, measurement safety. |
| `04-tools/03-usb-ttl-adapter.md` | USB-TTL/USB-UART, flashing, serial logs, RX/TX, voltage levels. |
| `04-tools/04-soldering.md` | Soldering wires, JST connectors, thermistors, common mistakes. |
| `04-tools/05-crimping-connectors.md` | Crimping terminals and connectors, contact quality, bad crimp joints. |
| `04-tools/06-st-link.md` | ST-Link, STM32, SWD interface, recovery after a failed flash. |
| `04-tools/07-oscilloscope.md` | PWM, UART, noise, voltage sag, mains voltage safety, frequency measurement. |

### 06. Practical Guides (folder: `05-practical-guides/`)

| File | What's inside |
|---|---|
| `05-practical-guides/01-connecting-fan.md` | Fan wiring, voltage, controller-side control, noise. |
| `05-practical-guides/02-checking-thermistor.md` | Thermistor check with a multimeter, resistance, wiring, firmware readings. |
| `05-practical-guides/03-connecting-servo.md` | Servo power supply, signal line, peak current, controller resets. |
| `05-practical-guides/04-connecting-load-cell.md` | Load cell, HX711 amplifier, power, signal wires, calibration. |
| `05-practical-guides/05-connecting-rfid-reader.md` | RFID reader, power, SPI/UART/I2C, common mistakes. |

### 07. 3D Printing (folder: `06-3d-printing/`)

| File | What's inside |
|---|---|
| `06-3d-printing/01-overview.md` | Why a section on printed parts, enclosures, ducts, and mounts. |
| `06-3d-printing/02-what-is-stl.md` | STL format, limitations, why one STL file isn't enough for assembly. |
| `06-3d-printing/03-materials-petg-abs-asa.md` | PETG, ABS, ASA — where to use, limits near heat sources. |
| `06-3d-printing/04-heat-resistant-materials.md` | Materials for parts near heat, deformation, temperature margin. |
| `06-3d-printing/05-enclosure-design.md` | Enclosure design, ventilation, mounts, clearance from heater, service access. |
| `06-3d-printing/06-why-pla-is-risky.md` | PLA near heat sources, softening, deformation, enclosure failure risk. |

### 08. Common Mistakes (folder: `07-common-mistakes/`)

| File | What's inside |
|---|---|
| `07-common-mistakes/01-overview.md` | List of typical mistakes and the logic behind the diagnostics section. |
| `07-common-mistakes/02-power-mistakes.md` | Weak power supplies, voltage sag, power headroom, bad terminals. |
| `07-common-mistakes/03-wiring-mistakes.md` | Swapped wires, missing ground, RX/TX, thin wires, bad connections. |
| `07-common-mistakes/04-controller-mistakes.md` | 3.3V/5V mismatch, wrong board, firmware, signal levels. |
| `07-common-mistakes/05-heater-ssr-mistakes.md` | Heaters, SSR, 110–230V AC, heatsinks, wrong relay type. |
| `07-common-mistakes/06-diagnostic-checklist.md` | Quick step-by-step device diagnostic sequence. |
