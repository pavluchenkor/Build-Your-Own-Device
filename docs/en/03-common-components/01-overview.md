# Common Components

Common components are the parts and modules you'll most often encounter when assembling an iDryer-like device or 3D printer peripherals.

Purpose of this section:

This section serves as a reference for parts you'll actually hold in your hands during assembly.

You don't need deep electronics knowledge here. The main goal is to help you understand:

- what this component is;
- why you need it;
- how it's typically connected;
- what you can substitute it with;
- what parameters matter when buying;
- what most often breaks on first connection.

Format of each page:

- what it is;
- where it's used in iDryer and 3D printer peripherals;
- what a typical connection looks like;
- important characteristics;
- typical mistakes;
- a short checklist before buying.

Proposed files:

- `02-heaters.md` - heaters: PTC, silicone pads, cartridges, 12V/24V/110-230V AC.
- `03-fans.md` - fans: 2-pin, 3-pin, 4-pin PWM, voltage, current, noise, airflow.
- `04-thermistors.md` - thermistors: NTC 100K, lookup tables, mounting, open/short circuits.
- `05-led-strips.md` - LED strips: 5V/12V/24V, regular and addressable, current per meter.
- `06-servo-motors.md` - servo motors: power, signal, angle, peak current.
- `07-load-cells.md` - load cells: HX711, calibration, mechanical mounting.
- `08-oled-display.md` - OLED: I2C/SPI, address, power, when needed.
- `09-touchscreen.md` - TFT/touch: UART/SPI/HDMI, power, compatibility.
- `10-rfid-and-nfc.md` - RFID/NFC: cards, tags, frequencies, connection.

## Reference Materials

- [Klipper Configuration Reference](https://www.klipper3d.org/Config_Reference.html) - official Klipper sections on heaters, fans, temperature sensors, servo motors and displays in configuration.
- [DigiKey: Selecting A Fan](https://www.digikey.com/en/articles/selecting-a-fan) - practical fan selection by airflow, static pressure, housing resistance and thermal task.
- [Adafruit: MOSFET Driver](https://learn.adafruit.com/adafruit-mosfet-driver) - why high-power loads aren't connected directly to GPIO and why you need a power switch.
- [SparkFun: Load Cell Amplifier HX711 Breakout Hookup Guide](https://learn.sparkfun.com/tutorials/load-cell-amplifier-hx711-breakout-hookup-guide) - example of load cell, HX711, power, signal wires and calibration.
- [Adafruit: PN532 RFID/NFC Breakout Wiring](https://learn.adafruit.com/adafruit-pn532-rfid-nfc/breakout-wiring) - example of a component where you need to check power, logic levels and chosen interface beforehand.

## See Also

- [Heaters](02-heaters.md) - the riskiest type of load: power, temperature, SSR/MOSFET and independent protection.
- [Fans](03-fans.md) - airflow, static pressure, 2-pin/3-pin/4-pin and power.
- [Thermistors](04-thermistors.md) - temperature sensor as the basis for heater feedback.
- [Connecting a fan](../06-practical-guides/01-connecting-fan.md) - practical example of component connection through a power switch.
- [Heater and SSR errors](../08-common-mistakes/05-heater-ssr-mistakes.md) - common mistakes with high-power and mains loads.
