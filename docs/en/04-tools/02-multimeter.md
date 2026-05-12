# Multimeter

A multimeter is the main first-line diagnostic tool.

You can check with it:

- whether power is present;
- if voltage is correct;
- where plus and minus are;
- if a wire is broken;
- if a fuse is intact;
- if a thermistor appears to be functional;
- whether there is voltage sag under load.

But it is easy to make mistakes with a multimeter if you confuse the modes. The most dangerous errors involve measuring current and mains voltage.

## Probes and ports

A multimeter typically has:

- `COM` - common port, where you almost always insert the black probe;
- `V/Ohm/mA` or similar port - for voltage, resistance, continuity and small currents;
- `10A` or `A` - separate port for large current.

Before measuring, always check:

- which port the red probe is inserted into;
- what mode is selected;
- what exactly you are about to measure.

A very common mistake: after measuring current, you forget to move the probe from `A` back to `V/Ohm`, then try to measure voltage. This can cause a short circuit.

## Measuring DC voltage

DC is direct (constant) voltage. In our devices this is usually:

- `3.3V`;
- `5V`;
- `12V`;
- `24V`.

Procedure:

1. Black probe into `COM`.
2. Red probe into the `V` port.
3. Select DC voltage mode: usually `V` with a straight line.
4. Black probe on negative or `GND`.
5. Red probe on positive.
6. Read the display.

If a minus sign appears before the number on the display, the probes are swapped. This is useful: you can determine polarity this way.

![Digital multimeter with probes](../../../img/04-tools/02-digital-multimeter.jpg)

*Source: [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:Aneng_AN870_multimeter_02.jpg), Retired electrician, CC0 Public Domain*

## Where to measure voltage

Don't limit yourself to the power supply output.

Check:

- on the power supply terminals;
- on the board input;
- on the load terminals;
- on a DC-DC module;
- on the fan;
- on a servo;
- on an LED strip.

If the power supply shows 24V but the load shows noticeably less, look for sag on the wires, terminals or connectors.

For power supply diagnostics, it is important to measure under load, not just idle.

## Measuring AC voltage

AC is alternating voltage, such as 110-230V from the mains.

Mains voltage is dangerous.

If you don't understand what you are doing, don't measure open mains parts with a multimeter. Better to use ready-made safe modules, enclosed terminals and specialist help.

If you do measure, you need:

- a multimeter with safety category **CAT II** or **CAT III** — this is written on the device body next to the voltage, for example `CAT II 600V`. CAT I is not suitable for household mains. CAT III and CAT IV provide extra margin for more complex installations;
- properly functioning probes with a category not lower than the multimeter;
- dry hands;
- enclosed and stable assembly;
- understanding of where phase and neutral are;
- no accidental open contact points.

For most tasks involving low-voltage electronics, DC measurements are sufficient.

## Continuity check

Continuity shows whether two points are electrically connected.

It is useful to check:

- if a wire is intact;
- if `GND` is connected;
- if a cable is not broken;
- if a button works;
- if a fuse is intact;
- if neighboring contacts are shorted.

Procedure:

1. Turn off power.
2. Set the multimeter to continuity mode: usually a sound icon or diode symbol.
3. Touch the probes to each other - there should be a beep.
4. Touch the two points you want to check.
5. If it beeps, there is a conductive connection between the points.

Continuity check is done on a de-energized circuit.

## Resistance

Resistance is measured in ohms.

For our tasks this is needed to:

- check a thermistor;
- check for broken wire;
- check a fuse;
- determine if there is a short circuit;
- check a resistor.

Important: resistance is only measured on a de-energized circuit.

If you measure resistance on an energized board, you can get incorrect readings or damage the multimeter.

## Testing a thermistor

For a typical NTC `100K` at room temperature, expect tens or around `100 kOhm`.

If the multimeter shows:

- `OL` or infinity - likely open circuit;
- almost `0 Ohm` - likely short circuit;
- value fluctuating a lot when you move the wire - poor contact;
- resistance decreasing when heated by your fingers - looks like a live NTC.

Exact values depend on thermistor type and temperature.

## Measuring current

Measuring current is more dangerous than measuring voltage.

Voltage is measured in parallel: probes touch two points.

Current is measured in series: you must break the circuit and connect the multimeter in line so current flows through the device.

Mistake - put the multimeter in current mode and touch the probes to the plus and minus of the power supply. That is almost a short circuit through the multimeter.

For a beginner it is better to:

- first calculate current from power;
- use ready-made watt meters/USB power meter/DC power meter;
- measure current only if you understand how to connect the multimeter in series;
- start with the correct range and correct port.

## Checking a fuse

Check the fuse on a de-energized circuit.

Methods:

- continuity;
- resistance measurement.

A good fuse usually shows continuity and has very low resistance.

A blown fuse usually does not show continuity.

If a fuse blew, you cannot just install a higher-rated one. First find the cause.

## How not to burn out the multimeter

Minimum rules:

- check the mode before measuring;
- check the red probe port before measuring;
- don't measure resistance on an energized circuit;
- don't measure current like voltage;
- don't go into 110-230V AC without understanding safety;
- start with a higher range if the multimeter is not auto-ranging;
- use functioning probes;
- don't touch the metal tips with your fingers.

## Practical scenarios

Check a 24V power supply:

1. DC voltage mode.
2. Black probe on negative.
3. Red probe on positive.
4. Should read about 24V.

Check a fan:

1. Measure voltage on the fan connector.
2. Check polarity.
3. Check voltage during startup.

Check for broken wire:

1. Disconnect power.
2. Continuity mode.
3. Probes on both ends of the wire.
4. No beep - possible open circuit.

Check for short between `+` and `GND`:

1. Disconnect power.
2. Check continuity between `+` and `GND`.
3. If it beeps where it shouldn't, look for a short.

## The essentials

- For DC voltage use the `V` mode with a straight line.
- Resistance and continuity are only done on de-energized circuits.
- Current is measured in series, not in parallel.
- After measuring current, move the probe from `A` back to the normal `V/Ohm` port.
- Mains voltage is dangerous; don't measure open 110-230V parts without understanding safety.
- A multimeter under load often reveals problems invisible when idle.

## Reference materials

- [SparkFun: How to Use a Multimeter](https://learn.sparkfun.com/tutorials/how-to-use-a-multimeter/all) - practical guide to voltage, current, resistance, continuity and multimeter ports.
- [Fluke: How to Measure Resistance](https://www.fluke.com/en-us/learn/best-practices/test-tools-basics/digital-multimeters/how-to-measure-resistance) - safe resistance measurement.
- [Fluke: How to Measure AC Voltage](https://www.fluke.com/en-us/learn/best-practices/test-tools-basics/digital-multimeters/how-to-measure-ac-voltage) - measuring AC voltage and probe connection order.
- [Fluke: How to Test for Continuity](https://www.fluke.com/en-us/learn/best-practices/test-tools-basics/digital-multimeters/how-to-test-for-continuity) - continuity check and open-circuit search.
- [Fluke: Choosing the correct fuse for your tester](https://www.fluke.com/en-us/learn/blog/digital-multimeters/choosing-the-correct-fuse-for-your-tester) - why current input ports need proper fuses with correct voltage and interrupt rating.
