# Chyby topidla a SSR

The heater is the most dangerous load in a simple DIY device.

A fan may not start. A sensor may give wrong readings. But a heater with an error can overheat the case, melt plastic, damage wiring, or create a fire risk.

If the device has 110-230V AC and you do not understand electrical safety, the right action is to stop and ask a specialist for help.

## Symptoms

Dangerous signs:

- SSR heats up significantly;
- heater will not turn off;
- temperature rises though command is off;
- temperature rises too fast or unreasonably;
- temperature sensor shows wrong value;
- terminal darkened;
- wire or connector heats up;
- breaker or fuse trips;
- case smells of plastic or burning;
- device is dangerous to touch;
- heating continues after controller error.

If heater behaves not as expected, turn off the power.

## AC SSR and DC SSR Mixed Up

SSRs come for different load types.

AC SSR is for alternating current. DC SSR is for direct current.

Mistake:

- AC SSR put on DC heater;
- DC SSR put on 230V AC;
- bought "SSR 40A" without understanding what is written on the case.

Wrong SSR type may not turn off the load or work dangerously.

Before connecting verify:

- output type: AC or DC;
- allowed load voltage;
- allowed current;
- control input voltage;
- manufacturer connection diagram;
- is heatsink needed.

## SSR Without Heatsink

SSR heats up during operation.

Even if the case says large current, it does not mean the relay will handle it without a heatsink in a closed case.

Check:

- load current;
- voltage drop across SSR;
- dissipated power;
- heatsink requirements;
- SSR case temperature after operation;
- is there airflow.

If SSR is so hot it is hard to hold by hand, this is reason to stop and figure out.

## MOSFET for 110-230V AC

Regular MOSFET modules for Arduino/ESP32 are usually for DC loads: 12V or 24V.

They cannot be used as a simple switch for AC mains 110-230V.

For mains load you need different components, different isolation, different terminals, grounding, fuses, and understanding of electrical safety.

If unsure the selected module is designed for mains load, do not connect it to mains.

## No Fuse

A fuse does not make the device completely safe, but it limits the consequences of some failures.

Bad ideas:

- "I will add it later";
- "power supply will protect itself";
- "my heater is small";
- "if fuse blows I will put a larger one".

Fuse is selected for the circuit, wiring, and load. It cannot be increased just because it trips.

If fuse trips, find the cause.

## No Independent Thermal Protection

Firmware and temperature sensor are not the only protection.

For heater, independent hardware protection is useful:

- thermostat;
- thermal fuse;
- bimetallic switch;
- separate emergency heater power cutoff.

Such protection must work independently of the controller and firmware.

If controller hangs, pin hangs in on state, SSR failed, or sensor disconnected, hardware protection can be the last line of defense.

## Temperature Sensor Poorly Mounted

Heater is controlled by feedback from the sensor.

If sensor:

- disconnected;
- poorly pressed;
- in wrong place;
- has no thermal contact;
- shows air temperature instead of heater;
- wrong type selected in firmware;

controller may continue heating because it sees wrong temperature.

Poor thermal contact is one of the most dangerous mistakes in heating systems.

## Wrong Heater Power

Heater power must be calculated before connecting.

Example:

```text
24V 120W -> 5A
24V 240W -> 10A
230V 300W -> about 1.3A
```

For low-voltage powerful heaters current quickly becomes large. This requires proper wires, terminals, MOSFET/SSR, and power supply.

For mains heaters current is less but shock hazard is much higher.

## Weak Terminals and Wires

A terminal that "sort of holds" can heat under current.

Reasons:

- poor contact;
- insulation clamped;
- wire too thin;
- terminal not rated for current;
- stranded wire without ferrule frayed;
- screw loosened by heat and vibration.

Darkened terminal, smell, heating, or plastic softening around is reason to turn off device.

## What Not to Do

You cannot:

- hold open mains part under power;
- change wires under power;
- use Arduino MOSFET module for 230V AC;
- use SSR without heatsink if required;
- disable thermal protection;
- short the emergency thermostat;
- increase fuse "so it does not blow";
- leave heater unattended on first test;
- use PLA mounting near heater.

## What to Check

Before first heating:

1. Heater voltage.
2. Power and current.
3. Power switch type: MOSFET, AC SSR, DC SSR, relay.
4. Current margin.
5. SSR or MOSFET heatsink, if needed.
6. Fuse.
7. Grounding, if required.
8. Terminals and wires.
9. Temperature sensor mounting.
10. Correct `sensor_type` in firmware.
11. `min_temp` and `max_temp`.
12. Independent thermal protection.
13. Behavior when controller is off.
14. Terminal and SSR temperature after brief test.

## Key Points

- Heater cannot be tested like an ordinary small load.
- AC SSR and DC SSR are different devices.
- SSR often requires heatsink.
- MOSFET module for DC loads does not work for 110-230V AC.
- Temperature sensor must be mounted firmly in correct place.
- Hardware thermal protection must be independent of firmware.
- If there is smell, terminal heating, or unusual heater behavior, turn off power.

## References

- [Klipper Configuration Reference: verify_heater](https://www.klipper3d.org/Config_Reference.html#verify_heater) - official heater verification and temperature sensor checking by rise rate and accumulated error.
- [Tom's Hardware: How to Fix 3D Printer Thermal Runaway](https://www.tomshardware.com/3d-printing/how-to-fix-3d-printer-thermal-runaway) - checking thermistor, heating cartridge, fan, power, and wiring during thermal runaway.
- [Marlin Configuration: Temperature Ranges and Thermal Protection](https://marlinfw.org/docs/configuration/configuration.html#temperature-ranges) - `MINTEMP`, `MAXTEMP`, and thermal protection as part of safety.
- [Sensata/Crydom SSR Heat Sink Selection](https://www.sensata.com/sites/default/files/a/sensata-ssr-heat-sink-selection-white-paper.pdf) - why SSR requires thermal calculation and heatsink at significant currents.
- [Omron: Solid State Relay Basics](https://components.omron.com/us-en/products/basic-knowledge/relays/solid-state-relays) - basic information about SSR, application, heating, and differences from mechanical relays.
