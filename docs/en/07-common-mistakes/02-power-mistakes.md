# Power Supply Mistakes

Power supply is the first thing to check when the device behaves strangely.

A weak power supply, thin wire, or poor terminal can look like a firmware, Wi-Fi, sensor, or controller issue.

## Symptoms

Typical signs of power supply problems:

- controller reboots;
- screen flickers;
- Wi-Fi on ESP32 drops off;
- fan starts and stops;
- servo jerks;
- heater heats weakly;
- USB disappears when load is turned on;
- MOSFET, terminal, or wire heats up;
- sensors show unstable values;
- device works without load but breaks when heater or motor is connected.

If a symptom appears exactly when the load is turned on, almost always the power supply and wiring need to be checked.

## Power Supply Without Margin

You cannot select a power supply exactly matching the load power.

If the load consumes `100W`, a `100W` power supply will work at its limit. It can overheat, sag voltage, and poorly handle inrush currents.

Practical rule for this section:

**minimum power margin is 50%, unless the documentation of a specific component requires more.**

Example:

```text
heater: 24V 120W
current: 120W / 24V = 5A
minimum 50% margin: 7.5A
```

So the power supply is better to choose at least `24V 7.5A`, and in practice often larger, if there are fans, controller, lighting, and other loads.

## Total Current Not Calculated

You must calculate not one component, but the entire device.

For example:

- heater;
- fans;
- servo;
- LED strip;
- controller;
- display;
- sensors;
- DC-DC converter.

Currents add up. Inrush currents and brief peaks also need to be accounted for.

A servo or fan can briefly draw more than in normal mode. If the margin is small, exactly this moment will cause the controller to reboot.

## Confused 12V and 24V

The simplest and most dangerous mistake:

- 12V fan plugged into 24V;
- 5V module plugged into 12V;
- 24V heater expected to work normally from 12V;
- 3.3V module powered from 5V without checking.

Before connecting verify:

- load rating;
- power supply rating;
- voltage with multimeter;
- connection diagram;
- controller and module voltage ratings.

Do not rely only on wire color or similar connector type.

## Voltage Drop on Wires

Wire has resistance.

The longer the wire and the greater the current, the greater the voltage drop and heating.

Symptoms:

- power supply outputs 24V, but load gets less;
- heater heats weaker than expected;
- fan starts poorly;
- servo jerks;
- wire noticeably warm;
- terminal heats up.

Verify voltage not only at the power supply output, but also on the load itself during operation.

If voltage drops significantly under load, the problem may be in the wire, terminal, connector, power supply, or too large a load.

## No Common Ground

If a controller drives an external module or load, often a common ground is needed.

For example:

- controller drives a MOSFET module;
- controller sets PWM to a 4-pin fan;
- controller drives a servo with separate power;
- HX711, RFID, or other module is powered separately.

Without common `GND` the signal may not have the correct level. Device may not work or work randomly.

Common ground does not mean the entire load must be powered through the controller. It is only the common reference level for the signal.

## Controller Powered from Noisy Line

Motors, fans, servos, heaters, and LED strips can create voltage sags and noise.

If the controller is powered from the same line without proper DC-DC, filtering, and margin, it can reboot.

Common solutions:

- separate proper DC-DC for controller;
- short controller power wires;
- common `GND` at a clear point;
- capacitor near the load, if appropriate;
- separation of power and logic wiring;
- proper power supply with margin.

## What to Check with a Multimeter

At minimum:

1. Power supply voltage without load.
2. Power supply voltage under load.
3. Voltage at load terminals under load.
4. Polarity.
5. Presence of common ground.
6. Wire and terminal heating after a brief test.

If the device works only without load, measure it under load. Voltage without load may look normal.

## What Not to Do

You cannot:

- use a power supply "to the limit";
- increase fuse rating because it trips;
- use thin Dupont wires for power load;
- twist power wires without proper terminal;
- power heater through weak connector;
- connect load directly to GPIO;
- repeatedly turn on device if wire or terminal heats up.

If something is heating, first turn off power and find the cause.

## Typical Mistakes

- did not calculate load current;
- chose power supply without margin;
- forgot inrush current of fan or servo;
- confused 12V and 24V;
- power 5V controller from unstable line;
- no common `GND`;
- wire too thin;
- wire too long for the current;
- terminal not tightened well;
- load works but voltage drops significantly.

## Key Points

- Power supply is checked first.
- Calculate current for all loads, not just one part.
- Need at least 50% power margin.
- Voltage must be measured under load.
- Common `GND` is often mandatory for controlling external modules.
- Thin or long wire can cause voltage drop and heating.

## References

- [SparkFun: How to Power a Project](https://learn.sparkfun.com/tutorials/how-to-power-a-project/voltagecurrent-considerations) - basic considerations about voltage, current, and power for microcontroller projects.
- [SparkFun: Troubleshooting Tips](https://learn.sparkfun.com/tutorials/sparkfun-troubleshooting-tips/hardware-checks) - checking power supply, connections, and heating when troubleshooting.
- [ProdataKey: How does wire gauge affect line loss?](https://support.pdk.io/hc/en-us/articles/360047588514-How-does-wire-gauge-affect-line-loss) - why length, cross-section, and current affect voltage drop and losses.
- [WiringCalcs: Voltage Drop Explained](https://wiringcalcs.com/guides/voltage-drop-explained-guide/) - practical explanation of voltage drop, wire resistance, and the effect of current.
- [SparkFun Qwiic Power Meter guide](https://docs.sparkfun.com/SparkFun_Qwiic_Power_Meter_ACS37800/hardware_assembly/) - example of common `GND` when measuring/controlling external load.
