---
title: "Where to start building a filament dryer"
description: "A clear path for a first project: how to approach a filament dryer build, choose electronics, heating, airflow, enclosure parts, and avoid safety gaps."
---

# Where to start building a filament dryer

If you want to build your own filament dryer, printer heated chamber, or separate heating module, start here. This page explains how to read the documentation and which decisions should be made before buying components.

You already print on a 3D printer and want to build a filament dryer. But when you open the schematic, questions appear immediately: which power supply, where does ground go, MOSFET or SSR, why do you need a heatsink. This section answers these questions step by step — from the first current calculation to a working device.

After this section, you will understand what you are building, why exactly this way, where danger might be, and how to check the device before powering it on.

The section gradually leads from simple concepts to real results.

The path here goes from simple to complex:

1. First understand power, current, load, and basic safety.
2. Then figure out what controllers exist and which to choose.
3. Then understand basic components: heater, fan, sensors, displays, RFID and load cells.
4. Then learn to use minimal tools: multimeter, USB-UART, soldering iron, crimper.
5. Then move to practical connections.
6. Then think about the enclosure and 3D-printed parts.
7. In the end, have a list of common mistakes and a diagnostic checklist on hand.

The main idea:

You don't have to understand all electronics at once. It is enough to go step by step and each time understand the next small step.

What this section should give:

- understanding how low-voltage `12V`/`24V DC` circuits differ from mains `110-230V AC`;
- ability to roughly calculate load current;
- understanding when you need MOSFET, SSR or relay;
- understanding how ESP32, Arduino, RP2040 and STM32 differ in practice;
- understanding why for Klipper MCU it's better to look at RP2040 or STM32;
- basic understanding of sensors, fans, heaters and displays;
- minimum multimeter diagnostic skills;
- understanding which printed parts can be placed near heat;
- list of mistakes that are better not to repeat.

What this section does not do:

- does not replace an electrician when working with `110-230V AC`;
- does not teach deep circuit design;
- does not try to explain all physics;
- does not give permission to assemble dangerous devices without understanding safety.

How to read:

- if the topic is new — go in order;
- if you have already built devices — open the needed section as a reference;
- if the device does not work — first look at `07-common-mistakes`;
- if you work with `110-230V AC` — first read everything related to safety, SSR, wires, terminals and protective grounding.

## Reference materials

- [SparkFun: Voltage, Current, Resistance, and Ohm's Law](https://learn.sparkfun.com/tutorials/voltage-current-resistance-and-ohms-law) - basic concepts of voltage, current, resistance, closed circuit and Ohm's law.
- [SparkFun: Troubleshooting Tips](https://learn.sparkfun.com/tutorials/sparkfun-troubleshooting-tips/all) - practical order of initial diagnosis: power, connections, polarity, solder joints, cables and voltage drops.
- [Fluke: How to Measure Resistance with a Digital Multimeter](https://www.fluke.com/en-us/learn/best-practices/test-tools-basics/digital-multimeters/how-to-measure-resistance) - why resistance measurements are made with power removed and why a multimeter is needed to check components.
- [OSHA: Electrical Incidents - Grounding](https://www.osha.gov/etools/construction/electrical-incidents/grounding) - why protective grounding is needed and why working with mains voltage requires separate safety discipline.

## See also

- [Load calculation 24V](../01-electronics-basics/01-load-calculation-24v.md) - first practical topic about voltage, current, power and power supply headroom.
- [Common components](../03-common-components/01-overview.md) - map of parts that are most often found in simple devices.
- [Tools](../04-tools/01-overview.md) - what you need to check, flash, solder and diagnose.
- [Practical guides](../05-practical-guides/01-connecting-a-fan.md) - example of first safe load connection through controller.
- [Common mistakes](../07-common-mistakes/01-overview.md) - what to look for if the device does not turn on, heats up, makes noise or behaves unstably.
