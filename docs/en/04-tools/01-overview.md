# Tools

This section is not about tool collecting.

It is about the minimal set that helps you safely assemble a device, verify connections, and find simple errors without guessing.

In homemade devices around iDryer and 3D printers, tools are needed for practical tasks:

- check if 24V is present on the power supply;
- understand if plus and minus are swapped;
- check continuity on a wire;
- test a thermistor;
- see if UART signal arrives;
- flash a controller;
- make a proper connector;
- find power supply sag;
- understand why a fan or heater doesn't turn on.

## Minimal set

For most simple builds, useful tools include:

- multimeter;
- USB-UART or USB-TTL adapter;
- soldering iron;
- crimping tool;
- wire cutters and stripper;
- heat shrink tubing;
- proper terminals and connectors;
- ST-Link if you work with STM32;
- oscilloscope or at least a multimeter with frequency counter for more complex diagnostics.

Not everything needs to be purchased at once. But a multimeter and proper wire tools usually pay for themselves quickly.

## Tools don't replace understanding

A multimeter does not make the mains part safe.

A soldering iron does not fix a bad schematic.

An oscilloscope is not needed if plus and minus are swapped.

So the order is:

1. Understand what should be connected.
2. Check power supply.
3. Check wiring.
4. Check sensors and signals.
5. Only then look for complex problems.

## What will be in this section

- `02-multimeter.md` - measuring DC voltage, continuity, resistance, fuses and why current measurement is more dangerous.
- `03-usb-ttl-adapter.md` - USB-UART adapters, TX/RX/GND, 3.3V/5V logic levels, flashing and logs.
- `04-soldering.md` - soldering wires, pads, modules, cold solder joints, heat shrink and strain relief.
- `05-crimping-connectors.md` - Dupont, JST, ferrules, Faston, terminals and crimp quality checks.
- `06-st-link.md` - ST-Link, STM32, SWD, board recovery after failed flashing.
- `07-oscilloscope.md` - PWM, UART, power sag, noise and critical safety warning about mains voltage.

## What's worth buying properly

There are things you should not economize on:

- a multimeter with proper probes and continuity mode;
- a soldering iron with temperature control;
- quality solder and flux;
- a crimping tool for specific terminals;
- connectors and terminals rated for the needed current;
- heat shrink tubing;
- wires of correct gauge.

Poor crimping or weak terminals can cause more problems than bad firmware.

## What you cannot do

You cannot:

- measure resistance on an energized circuit;
- measure current the same way you measure voltage;
- poke a multimeter into 110-230V AC without understanding safety;
- solder the power part "somehow";
- use Dupont for a heater;
- change wires while power is on;
- keep open mains parts on the table;
- think that if a wire "holds", the contact is good.

## The essentials

- Multimeter is the first diagnostic tool.
- USB-UART is needed for logs, flashing and communication with UART devices.
- Soldering and crimping are different tasks, and for connectors, crimping is often better.
- ST-Link is needed when you work with STM32 and SWD.
- Oscilloscope is not needed by everyone, but it quickly shows signals, sag and noise.
- For the power part, contact quality, wire gauge and safety matter more than assembly looks.

## Reference materials

- [SparkFun: How to Use a Multimeter](https://learn.sparkfun.com/tutorials/how-to-use-a-multimeter/all) - multimeter basics: voltage, current, resistance, continuity.
- [SparkFun: Troubleshooting Tips](https://learn.sparkfun.com/tutorials/sparkfun-troubleshooting-tips/hardware-checks) - hardware checks for power, connections and heat.
- [SparkFun: Serial Communication](https://learn.sparkfun.com/tutorials/serial-communication) - UART and basic serial communication logic.
- [Adafruit: Guide to Excellent Soldering](https://learn.adafruit.com/adafruit-guide-excellent-soldering) - practical soldering guide and connection quality.
- [STMicroelectronics: ST-LINK/V2 User Manual](https://www.st.com/resource/en/user_manual/um1075-stlinkv2-incircuit-debuggerprogrammer-for-stm8-and-stm32-stmicroelectronics.pdf) - official ST-Link documentation and SWD/SWIM.
