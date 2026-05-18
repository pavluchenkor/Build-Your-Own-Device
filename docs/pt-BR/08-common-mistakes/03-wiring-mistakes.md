# Erros de Fiação

Wiring often breaks the device more than the electronics themselves.

Poor contact, reversed polarity, or weak terminal can look like a firmware, sensor, or controller error.

## Symptoms

Typical signs of wiring problems:

- device works sometimes, then does not;
- board detected only when cable is moved;
- sensors show garbage;
- temperature jumps;
- fan starts intermittently;
- USB drops off;
- terminal heats up;
- wire darkens or smells;
- module works on the bench but does not work in the case;
- after closing the cover device stops working.

If a symptom changes when the wire is moved, first check the wiring.

## Reversed Plus and Minus

Polarity cannot be checked "by color".

Red wire is often plus, black wire often minus, but this is not a guarantee. In a DIY device, the previous builder or you yourself may have mixed up the colors.

Before connecting:

- check board markings;
- check module pinout;
- measure voltage with multimeter;
- verify where `+` and where `GND`;
- do not connect module if pinout is unclear.

Reversed polarity can instantly destroy a board, sensor, fan, or DC-DC.

## No Common Ground

Common ground is needed when one module is powered separately, and the signal comes from the controller.

Examples:

- servo with separate 5V power;
- MOSFET module for fan;
- 4-pin PWM fan;
- HX711;
- RFID module;
- external sensor.

Without common `GND` the signal may not make sense. Device may not respond, jerk, or work unstably.

## Poor Contact in Terminal

Terminal may look clamped, but hold the wire poorly.

Reasons:

- wire not inserted all the way;
- insulation clamped instead of conductor;
- stranded wire frayed;
- screw loosened;
- terminal not rated for current;
- wire too thin or too thick for terminal;
- no ferrule where needed.

Poor contact causes heating. Heating worsens the contact. This is a dangerous cycle.

After a brief test under load, check if terminals and connectors are heating.

## Dupont Not for Power Load

Dupont wires are convenient for breadboards and weak signals.

But they cannot be considered normal power wiring for:

- heaters;
- powerful fans;
- LED strips;
- servos with large current;
- device power;
- 110-230V AC.

Dupont may hold poorly, have small contact area, and heat up at currents it is not designed for.

For the power part you need proper terminals, connectors, wire cross-section, and strain relief.

## TX and RX

For UART often cross-wiring is needed:

- `TX` of one device to `RX` of another;
- `RX` of one device to `TX` of another;
- common `GND`.

Typical mistakes:

- connected `TX` to `TX`;
- connected `RX` to `RX`;
- forgot `GND`;
- chose wrong speed;
- logic levels do not match: 5V and 3.3V.

If UART does not work, first check `TX/RX/GND`, then speed and settings.

## I2C and SPI

For I2C:

- `SDA` must go to `SDA`;
- `SCL` must go to `SCL`;
- need common `GND`;
- device address must not conflict;
- wires must be short.

For SPI:

- `MOSI`, `MISO`, `SCK`, `CS` must match the pinout;
- each device has its own `CS`;
- need common `GND`;
- long wires can break the connection.

RFID RC522 often confuses people: pin `SDA` on the board may mean `SS/CS` for SPI, not I2C `SDA`.

## Mains and Signal Wires

110-230V AC wires, power DC load, and weak signals must not be laid randomly in one bundle.

Problems:

- interference;
- heating;
- insulation damage;
- risk of touching mains part;
- difficult diagnostics;
- user danger.

Mains part must be separated physically. Low-voltage sensors, UART/I2C/SPI, and thermistor wires are better run separately from heater power wires.

## Exposed Strands

An exposed wire outside a terminal is a bad sign.

It can:

- touch a neighboring terminal;
- short the case;
- get under the cover;
- hit the fan;
- create a danger during maintenance.

After clamping in the terminal no long bare strands should stick out.

## What to Check

Mini-checklist:

1. Power supply polarity.
2. Common `GND`.
3. Pinout correspondence.
4. Terminal quality.
5. No insulation clamped instead of conductor.
6. No exposed strands.
7. Wires not taut.
8. Cover does not pinch cable.
9. Power and signal wires separated.
10. Connector rated for current.
11. Device does not change behavior when wire is moved.

## What Not to Do

You cannot:

- change wires under power;
- hold open mains part on the bench;
- use Dupont for heater;
- clamp stranded wire so some strands stick out;
- twist power wires without proper connection;
- ignore a heating terminal;
- consider "sometimes works" normal.

## Key Points

- If device responds to wire movement, this is a wiring problem.
- Polarity is checked with multimeter, not by color.
- Common `GND` is needed for most external modules with separate power.
- Dupont is suitable for breadboards and signals, but not for power load.
- Mains and low-voltage wires must be separated.
- Heating terminal is reason to stop, not continue the test.

## References

- [SparkFun: Troubleshooting Tips](https://learn.sparkfun.com/tutorials/sparkfun-troubleshooting-tips/hardware-checks) - basic checking of connections, continuity, power cycle, and heating.
- [SparkFun: Serial Communication](https://learn.sparkfun.com/tutorials/serial-communication) - UART, TX/RX, and serial communication.
- [SparkFun: I2C](https://learn.sparkfun.com/tutorials/i2c) - `SDA`, `SCL` lines, addresses, and I2C typical mistakes.
- [SparkFun: Serial Peripheral Interface](https://learn.sparkfun.com/tutorials/serial-peripheral-interface-spi) - SPI lines, `MOSI`, `MISO`, `SCK`, `SS/CS`.
- [FRC Design: Design for 3D Printing](https://www.frcdesign.org/design-handbook/structure/design-for-3d-printing/) - practical advice on electronics cases: wire holes, ventilation, port access, and component service removal.
