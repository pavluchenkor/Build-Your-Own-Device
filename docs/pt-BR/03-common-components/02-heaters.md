---
title: "Aquecedores para secadores de filamento e câmaras aquecidas"
description: "Como escolher um aquecedor para secador de filamento ou câmara ativa de impressora 3D: 12V, 24V, rede elétrica, potência, controlo e segurança."
---

# Aquecedores para secadores de filamento e câmaras aquecidas

O aquecedor define a velocidade de aquecimento e os limites de segurança do secador ou da câmara. Esta página explica tipos de aquecedores, potência, controlo por MOSFET ou SSR e erros que podem causar sobreaquecimento.

A heater is a load that converts electrical energy into heat. In a simple DIY device, this is the most dangerous component: an error in a fan usually results in poor airflow, but a heater error can cause overheating, a melted enclosure, damaged wiring, or fire risk.

In 3D printers and iDryer-like devices, heaters are found in the hotend, bed, chamber, filament dryer, air duct, or separate heating module.

## Where It's Used

Typical tasks:

- heating the hotend;
- heating the bed;
- preheating the printer chamber;
- drying filament;
- preheating air before a filter or duct;
- maintaining temperature in a small process volume.

These are different tasks. A heater for a metal hotend, a silicone bed pad, and an air PTC module are not interchangeable without recalculating power, mounting, airflow and protection.

## Types of Heaters

Common options:

- cartridge heater;
- silicone pad;
- PTC heater;
- ceramic heating element;
- ready-made fan heater module;
- heating plate;
- mains heating bed;
- nichrome or resistive assembly in a finished enclosure.

A cartridge heater is usually inserted into a metal block. It needs good thermal contact with the metal and reliable temperature sensor mounting.

A silicone pad is usually glued or pressed to a flat surface. It needs a flat surface, good adhesion, a temperature sensor and protection from peeling.

A PTC heater partially limits temperature rise due to its properties, but this doesn't replace the controller, sensor, fuse, enclosure and airflow check. PTC doesn't automatically make a device safe.

A ready-made fan heater module combines heater and airflow, but it still needs to be checked for voltage, power, temperature, housing materials and emergency protection.

## Voltage, Power and Current

Before connecting, you need to find:

- operating voltage;
- power;
- current;
- current type: DC or AC;
- maximum temperature;
- wire operating temperature;
- mounting method;
- airflow requirements;
- allowed control method.

Current is calculated by the formula:

```text
current = power / voltage
```

Examples:

```text
24V 120W -> 5A
24V 240W -> 10A
24V 300W -> 12.5A
230V 300W -> about 1.3A
```

A low-voltage high-power heater is safer for voltage, but requires large currents. Large currents require a proper power supply, wires, terminals, MOSFET/SSR and fuse.

A mains heater on `110-230V AC` can deliver high power with lower current, but the shock risk is much higher. For the mains part you need electrical safety knowledge, enclosure, terminals, insulation, grounding where required, fuses and galvanic isolation of control.

## Heater Control

The controller should not power the heater directly from GPIO. GPIO only provides a control signal.

Typical power control options:

- MOSFET - for DC heaters `12V`/`24V`;
- DC SSR - for DC heaters if properly rated for DC;
- AC SSR - for mains AC heaters;
- mechanical relay - for rare on/off, but not for frequent PID/PWM;
- ready-made power output - only if rated for the needed current and voltage.

AC SSR and DC SSR are different devices. The wrong type may not switch off the heater or work unsafely.

A typical MOSFET module for Arduino/ESP32 cannot be used as a `110-230V AC` switch. If the module is not designed for mains load, it cannot be connected to mains.

## Layers of Safety

A heater cannot be designed as "controller turns it on - controller turns it off". You need multiple layers of protection.

![Layers of safe heater control](../../../img/03-common-components/02-heater-safety-stack.svg)

Minimum logic:

- power supply is rated for the current;
- fuse is selected for wiring and load;
- power switch matches the load type;
- temperature sensor is mounted in the right place;
- firmware has `min_temp`, `max_temp` and heating verification;
- there is independent hardware thermal protection: thermal fuse, thermostat or bimetallic switch;
- enclosure and materials withstand the actual temperature;
- first test is done under supervision.

Hardware thermal protection must work independently of the controller. In the simple case, it's placed in series in the heater power circuit to physically break the power. This is not just another sensor for the firmware.

If the controller hangs, the sensor falls off, a MOSFET shorts or an SSR sticks, the protection must break power to the heater.

## Temperature Sensor

A heater doesn't know its own temperature. The controller makes the decision based on the sensor.

If the sensor:

- is pressed poorly;
- is in the wrong location;
- falls off;
- is the wrong type in the firmware;
- has poor thermal contact;
- measures air instead of the critical part;

the controller may continue heating even though the actual temperature is already dangerous.

For a hotend, the temperature sensor contact with the metal block matters. For an air heater, it's important to understand what is being measured: the element temperature, air temperature after the element, chamber temperature, or temperature near the spool. These are different points, and they can differ significantly.

## Airflow and Heat Transfer

A heater releases power, but that power must safely go where intended.

For an air heater, airflow is critical:

- without flow, the element can locally overheat;
- weak ventilation doesn't remove heat;
- a clogged filter changes heating mode;
- plastic ducting can soften;
- a temperature sensor may not see what's happening at the element.

For a chamber heater, it's important to check not only the target air temperature, but also the temperature near the heater, wires, SSR/MOSFET, terminals and plastic parts.

## Wires, Terminals and Connectors

A heater often runs for long periods and consumes significant current. Poor contact becomes a heat source.

Check:

- wire gauge;
- insulation temperature class;
- terminal current rating;
- crimp quality;
- screw tightness;
- ferrules on stranded wires;
- strain relief;
- distance from hot parts;
- absence of exposed conductors.

If a terminal darkens, smells, softens plastic or becomes hot, power must be turned off and the cause found. Don't just increase the fuse or tighten it later.

## What to Check Before Buying

Before buying a heater, check:

- what medium it should heat: metal, air, bed, chamber;
- voltage and current type;
- power;
- current;
- operating temperature;
- maximum surface temperature;
- airflow requirements;
- mounting method;
- wire and insulation material;
- compatible power switch;
- place for temperature sensor;
- place for independent thermal protection;
- enclosure and surrounding materials;
- availability of technical description or clear documentation.

If the product page lacks voltage, power, temperature and application information, such a heater is not suitable for a safe first project.

## First Test

The first heating is done briefly and under supervision.

Procedure:

1. Check heater resistance and compare with `R = U^2 / P` calculation if voltage and power are known.
2. Check for short circuits where applicable.
3. If there's a metal enclosure or protective ground `PE`, check that the heater doesn't short to the enclosure.
4. Check supply voltage without the heater.
5. Check that the control switch turns off the load.
6. Check that the temperature sensor reads a reasonable value.
7. For `12V`/`24V` heater, if possible, start through a lab power supply with current limiting or temporary fuse.
8. Enable heating at low power or briefly.
9. Watch if temperature rises in the right place.
10. Check that power-off command actually stops heating.
11. Check heating of wires, terminals, MOSFET/SSR and enclosure.
12. Check emergency protection by a scenario you can safely simulate.

Don't leave a new heater unattended on first startup.

## Typical Errors

- connected heater to wrong voltage;
- didn't calculate current;
- powering heater through weak connector;
- using MOSFET for mains AC heater;
- mixed up AC SSR and DC SSR;
- installed SSR without heatsink when it was needed;
- forgot fuse;
- no independent thermal protection;
- poor temperature sensor mounting;
- made enclosure from PLA near heater;
- didn't account for airflow and clogged filter;
- tested on bench but not in enclosure;
- left mains part exposed;
- increased fuse instead of finding why it tripped.

## Main Point

A heater is chosen by the task, voltage, power, heat transfer method and safety. You can't treat it as a simple "two-wire load".

First calculate current, select power switch, wiring and fuse. Then ensure temperature sensor, firmware protection, independent hardware thermal protection, a proper enclosure and real-world testing.

## Reference Materials

- [Klipper Configuration Reference: heater_generic and verify_heater](https://www.klipper3d.org/Config_Reference.html#heater_generic) - heater settings, temperature sensors, `min_temp`, `max_temp` and heating verification in Klipper.
- [Marlin Configuration: Temperature Ranges and Thermal Protection](https://marlinfw.org/docs/configuration/configuration.html#temperature-ranges) - temperature limits, `MINTEMP`, `MAXTEMP` and thermal protection in Marlin.
- [Omron: Overview of Solid-state Relays](https://www.ia.omron.com/support/guide/18/introduction.html) - basic explanation of SSR, types, application and thermal measures.
- [Sensata/Crydom: SSR Heat Sink Reference](https://www.sensata.com/resources/brochure-solid-state-relays-heat-sink-reference) - why SSR needs a heatsink and how thermal regime relates to load current.
- [Omega: Cartridge Heaters](https://www.omega.nl/prodinfo/cartridge-heaters.html) - practical notes on cartridge heater application, thermal contact and power selection.
