# Časté chyby

This section is not here to criticize you.

It is here to help you quickly identify common errors in a DIY device: sagging power supply, loose wire, sensor showing garbage, controller restarting, heater behaving strangely.

The section format is straightforward:

- symptom;
- probable cause;
- what to check;
- what not to do;
- how to fix safely.

## The Main Rule of Diagnostics

If the device behaves strangely, you do not immediately change firmware, resolder everything, or increase power.

First, verify the basics:

1. power supply;
2. polarity;
3. common `GND`;
4. terminals and connectors;
5. sensors;
6. power switches;
7. firmware and configuration.

Most problems in simple devices turn out to be not "complex electronics", but power supply, wiring, or incorrect connections.

## When to Stop

Immediately turn off power if:

- burning smell appears;
- wire is heating up;
- terminal is heating up;
- connector is darkening;
- case has become hot in an unexpected place;
- heater will not turn off;
- breaker or fuse trips;
- temperature sensor shows garbage;
- device works only when you move the wire.

Do not "turn it on one more time to look". If something is heating, smelling, or sparking, find the cause first without power.

## Main Groups of Errors

In this section, errors are divided into groups:

- `02-power-mistakes.md` - weak power supply, incorrect voltage, sagging, thin wires, no margin.
- `03-wiring-mistakes.md` - reversed polarity, poor terminals, no common ground, bad connectors.
- `04-controller-mistakes.md` - unsuitable board, 3.3V/5V logic, GPIO instead of power output, incorrect firmware.
- `05-heater-ssr-mistakes.md` - heaters, SSR, MOSFET, 110-230V AC, temperature sensor, heatsinks and protection.
- `06-diagnostic-checklist.md` - general verification order when device does not work.

## Why Power Supply is Checked First

Power supply affects almost everything.

If the power supply is weak or the wires are thin, symptoms may look like a firmware issue:

- controller reboots;
- Wi-Fi drops off;
- screen flickers;
- servo jerks;
- fan does not start;
- sensors show random values;
- heater heats poorly.

Until the power supply is checked with a multimeter under load, it is difficult to confidently diagnose everything else.

## Why Wiring is More Important Than It Seems

A poor connection can work "almost normally".

This is exactly what is dangerous:

- today it works;
- when vibrated it disconnects;
- when heated, the contact gets worse;
- terminal gradually darkens;
- wire begins to heat up;
- sensor appears and disappears.

If the device changes behavior when you move the wire, this is not a software error. This is a connection problem.

## Why Protection Must Not Be Disabled

Thermal runaway, `MINTEMP`, `MAXTEMP`, `heater not heating` and similar errors exist not to annoy the user.

These are signs that the controller no longer trusts the temperature reading or sees dangerous heating behavior.

Bad idea:

- disable thermal protection;
- expand temperature limits without understanding the reason;
- replace the fuse with a larger one;
- short the thermostat directly;
- short the protection "for testing".

Right idea: find the reason for the protection to trigger.

## How to Read This Section

If the device does not work at all, start with the diagnostic checklist.

If the symptom is clear, go to the relevant article:

- reboots, flickering, weak heat - power supply;
- works when you move the wire - wiring;
- board not detected or pins not responding - controller;
- heater will not turn off or SSR is heating - heater and SSR;
- everything is unclear - general checklist.

## Key Points

- Most errors start with power, wiring, and incorrect connections.
- If something is heating, smelling, or darkening, turn off power.
- Diagnostics proceed from simple to complex.
- Firmware protection and hardware protection must not be disabled for convenience.
- The AC mains 110-230V cannot be diagnosed "on the bench" without understanding electrical safety.

## References

- [SparkFun: Troubleshooting Tips](https://learn.sparkfun.com/tutorials/sparkfun-troubleshooting-tips/hardware-checks) - basic approach to checking connections, power supply, heating, and hardware problems.
- [SparkFun: How to Power a Project](https://learn.sparkfun.com/tutorials/how-to-power-a-project/voltagecurrent-considerations) - voltage, current, and selecting power for an electronic project.
- [Tom's Hardware: How to Fix 3D Printer Thermal Runaway](https://www.tomshardware.com/3d-printing/how-to-fix-3d-printer-thermal-runaway) - practical analysis of temperature sensor, heater, fan, power supply, and wiring during thermal runaway.
- [Klipper Configuration Reference: verify_heater](https://www.klipper3d.org/Config_Reference.html#verify_heater) - official heater verification and temperature sensor checking by expected temperature rise and accumulated error.
- [SparkFun Qwiic Power Meter guide](https://docs.sparkfun.com/SparkFun_Qwiic_Power_Meter_ACS37800/hardware_assembly/) - example of the need for common `GND` when measuring/controlling external load.
