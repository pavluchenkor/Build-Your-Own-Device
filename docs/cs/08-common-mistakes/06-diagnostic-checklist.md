# Kontrolní seznam diagnostiky

This checklist is needed when the device does not work or behaves strangely.

The idea is simple: first remove the danger, then check power and wiring, and only after that move to firmware, sensors, and loads.

## 1. Stop and Turn Off Power

First, turn off the device.

Especially if there is:

- smell;
- wire heating;
- terminal heating;
- smoke;
- strange sound;
- sparking;
- heater will not turn off;
- breaker or fuse trips.

Do not change wires under power.

## 2. Disconnect Power Load

Before diagnostics it is better to temporarily disconnect:

- heater;
- powerful LED strip;
- servo;
- motor;
- external power load.

First verify controller and logic are alive without dangerous load.

If device has 110-230V AC, do not hold open mains part under power on the bench.

## 3. Check Power Supply

With multimeter check:

- is there voltage at power supply output;
- is voltage correct;
- is polarity correct;
- does voltage sag under load.

For example:

- 24V line should be about 24V;
- 12V line should be about 12V;
- 5V line should be about 5V;
- 3.3V line should be about 3.3V.

Acceptable deviation depends on power supply and device, but an obvious error like 24V instead of 12V should be found before connecting load.

## 4. Check Polarity

Check where plus and minus are.

Do not trust only wire color.

Check:

- board markings;
- power supply markings;
- module pinout;
- multimeter;
- connection diagram.

Reversed polarity often kills module instantly.

## 5. Check Common GND

If there is external module or separate power, check common `GND`.

This is important for:

- MOSFET module;
- servo;
- PWM fan;
- HX711;
- RFID;
- external sensors;
- separate DC-DC.

If signals go between devices, they must have a common reference level, unless the circuit uses special isolation.

## 6. Check Terminals and Connectors

Inspect:

- wire inserted all the way;
- conductor clamped, not insulation;
- no exposed strands;
- no darkening;
- no smell;
- terminal does not shake;
- connector does not hold "on faith";
- case cover does not pinch wire.

Move wires with power off. If contact clearly drops mechanically, fix wiring first.

## 7. Check Controller Without Load

Connect controller without power load.

Check:

- is it detected via USB;
- does firmware start;
- is there communication with host;
- does microcontroller not heat;
- does power not flicker;
- are logs visible.

If controller is not detected even without load, do not reconnect heater and power modules until you find the cause.

## 8. Check Firmware and Configuration

Check:

- firmware built for correct board;
- correct serial/CAN/USB path selected;
- pins in config match pinout;
- `sensor_type` correct;
- `min_temp` and `max_temp` reasonable;
- outputs not accidentally inverted;
- no pin conflicts.

If heater behaves opposite after configuration change, for example "off", but temperature rises, turn off power and check config and power circuit.

## 9. Check Sensors

Before heating check sensors.

For thermistor:

- temperature like room temperature;
- no `MINTEMP`;
- no `MAXTEMP`;
- readings do not jump;
- resistance like expected;
- when heated by hand readings change correctly.

For other sensors:

- power correct;
- interface selected correctly;
- address or pins match config;
- wires short and not hanging.

## 10. Check Output Without Load

If need to check MOSFET, relay, or board output, do it first without dangerous load.

Options:

- small test fan;
- LED with resistor;
- multimeter;
- weak safe load.

Do not start diagnostics with powerful heater.

For heater, before first turn-on, numerical check is useful: measure resistance and compare to expected `R = U^2 / P`. If there is metal case or `PE`, check no short to case. For `12V`/`24V` heater first run is better through lab power supply with current limit or temporary fuse.

## 11. Check Power Switch Separately

For MOSFET/SSR/relay check:

- correct load type: AC or DC;
- correct voltage;
- correct terminals;
- control input;
- common `GND` if needed;
- heatsink if needed;
- input and output not mixed up.

AC SSR and DC SSR cannot be swapped.

For SSR separately check "off" state: with control signal removed load must not heat. First better use safe small load, lamp, or multimeter, not main heater.

## 12. Connect Load with Brief Test

When basic checks passed, connect load briefly and under supervision.

Check:

- load turns on;
- load turns off;
- terminals do not heat;
- wires do not heat;
- MOSFET/SSR does not overheat;
- sensor shows realistic temperature;
- controller does not reboot;
- fuse does not trip.

First heater test should not be long and unattended.

## 13. Check After Few Minutes of Operation

After few minutes check:

- terminals;
- wires;
- power supply;
- MOSFET;
- SSR;
- case near heater;
- sensor readings;
- controller stability.

If something unexpectedly became hot, turn off power and return to checking power, wiring, and power switch.

## What Not to Do

You cannot:

- repeatedly turn on device if something heats or smells;
- hold 110-230V AC open on the bench;
- change wires under power;
- increase fuse "so it does not blow";
- disable thermal protection for testing;
- short emergency thermostat;
- test powerful heater without temperature sensor;
- leave first test unattended.

## Short Order

If you need very short order:

1. Turn off power.
2. Disconnect power load.
3. Check power supply voltage.
4. Check polarity.
5. Check common `GND`.
6. Check terminals and wires.
7. Check controller without load.
8. Check firmware and pinout.
9. Check sensors.
10. Check output without dangerous load.
11. Check MOSFET/SSR/relay.
12. Connect load with brief test.
13. Check heating of wires, terminals, and power parts.

## Key Points

- Diagnostics start with turning off power and reducing risk.
- Power load better disconnected for basic checks.
- Power, polarity, `GND`, and terminals checked before firmware.
- Heater cannot be used as first test indicator.
- If protection triggered, find the cause, not disable protection.

## References

- [SparkFun: Troubleshooting Tips](https://learn.sparkfun.com/tutorials/sparkfun-troubleshooting-tips/hardware-checks) - basic sequence of checking connections, power, and hardware problems.
- [SparkFun: How to Power a Project](https://learn.sparkfun.com/tutorials/how-to-power-a-project/voltagecurrent-considerations) - how to think about voltage, current, and project power.
- [Fluke: How to Measure Resistance with a Digital Multimeter](https://www.fluke.com/en-us/learn/best-practices/test-tools-basics/digital-multimeters/how-to-measure-resistance) - safe resistance measurement on de-energized circuit.
- [Tom's Hardware: How to Fix 3D Printer Thermal Runaway](https://www.tomshardware.com/3d-printing/how-to-fix-3d-printer-thermal-runaway) - practical checks of thermistor, heater, fan, power, and wiring.
- [Klipper Configuration Reference: min_temp, max_temp and verify_heater](https://www.klipper3d.org/Config_Reference.html#verify_heater) - software checks of temperature, sensor, and expected heater temperature rise.
