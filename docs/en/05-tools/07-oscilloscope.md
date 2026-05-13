# Oscilloscope

An oscilloscope shows how a signal changes over time.

A multimeter can show "about 3.3V" or "there is frequency". An oscilloscope shows signal shape: pulses, edges, sag, noise, bounce, UART packets, PWM.

![Screen of a digital oscilloscope](../../../img/04-tools/07-digital-oscilloscope.jpg)

*Source: [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:Digital_oscilloscope.jpg), premek.v, Public Domain*

A PWM signal on the oscilloscope screen looks like this:

![Animation of PWM: duty cycle change and signal waveform](../../../img/04-tools/07-pwm-signal-waveform.gif)

*Source: [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:Pwm.gif), Mik81, CC0 Public Domain*

You don't need one for every simple build. But when a device behaves unstably, an oscilloscope can reveal in minutes what a multimeter cannot see.

## What you can see

In iDryer-like devices, an oscilloscope is useful for viewing:

- fan PWM;
- MOSFET module PWM;
- UART `TX/RX`;
- 5V or 3.3V sag at servo startup;
- power supply noise;
- button bounce;
- tachometric fan signal;
- brief glitches that a multimeter averages out.

An oscilloscope answers not just "is there voltage" but "what is happening to the signal over time".

## The most important warning

Most benchtop oscilloscopes have the probe ground connected to the mains protective earth.

This means: the ground clip of the probe is not "just another wire".

If you attach the ground clip to a point that is not `GND` of the low-voltage circuit, you can create a short circuit through the oscilloscope.

It is especially dangerous to go into the mains 110-230V AC part, SSR, power supply or high-voltage sections with a normal oscilloscope.

You cannot:

- disconnect the oscilloscope earth for "floating" measurement;
- connect the probe ground to phase or another voltage point;
- measure mains voltage with a normal probe without understanding the circuit;
- assume the two channels are completely independent: channel grounds are often connected together.

For floating measurements, high-side measurements and high-voltage measurements, you need proper methods: differential probe, isolated device or another safe approach.

## How to connect a probe

For low-voltage circuits:

1. Connect the probe to the oscilloscope.
2. Connect the probe ground to `GND` of the device.
3. Connect the probe tip to the signal.
4. Select the correct probe setting: `1x` or `10x`.
5. Make sure the oscilloscope is set to the same factor.

For most digital signals, use `10x`: the probe loads the circuit less and usually shows signal shape better.

## PWM

PWM is a pulse signal.

The oscilloscope shows:

- frequency;
- duty cycle;
- logic high level;
- logic low level;
- edges;
- jitter;
- noise.

For a fan or MOSFET this helps understand:

- whether the pin outputs a signal at all;
- whether 3.3V or 5V level is sufficient;
- whether frequency matches the setting;
- whether duty cycle changes on command;
- whether signal doesn't sag when load is connected.

## UART

UART on the oscilloscope looks like a sequence of pulses.

The oscilloscope helps see:

- whether there is activity on `TX`;
- whether logic levels are not swapped;
- what the idle level is;
- whether there is strong noise;
- whether baud rate roughly matches.

For decoding text, a logic analyzer or USB-UART adapter is more convenient. But an oscilloscope quickly shows whether the signal is physically alive.

## Power supply sag

A multimeter may not see a brief sag.

For example, when a servo starts, a 5V line might dip for a few milliseconds. The multimeter shows almost normal 5V, but the controller already rebooted.

An oscilloscope lets you see:

- how much voltage drops;
- how long the sag lasts;
- whether there are spikes;
- whether a capacitor helps;
- whether the situation changes with a different power supply or wires.

This is especially useful for ESP32, servos, fans and DC-DC.

## Noise and interference

Noise on power or signal lines can break sensors and communication.

An oscilloscope helps see:

- DC-DC ripple;
- motor spikes;
- noise near the heater;
- button bounce;
- interference on a long wire.

But understand the limits: poor probe ground connection can add noise to the display itself. A short probe ground spring or short ground wire often gives a more honest picture than a long clip.

## Multimeter with frequency measurement

Sometimes an oscilloscope is not needed for initial checks.

Some multimeters can measure signal frequency. In the specs this might be called `Hz`, `frequency` or `frequency counter`.

This is useful if you need to quickly understand:

- whether a PWM signal exists at all;
- whether frequency changes with adjustment;
- whether the controller output works;
- whether there is activity on a simple digital line.

For example, if a controller should output PWM to a fan or MOSFET module, a frequency-measuring multimeter can show that the signal exists and its frequency roughly matches the expected value.

But a multimeter doesn't show signal shape. It won't show:

- logic high level;
- pulse width;
- PWM duty cycle;
- signal edges;
- brief dips;
- noise and interference;
- line distortion.

So a frequency-measuring multimeter is a good tool for quick checks, but not a full oscilloscope replacement.

## What to check before measuring

Before connecting a probe:

1. What is `GND` in the circuit?
2. Is this point connected to mains protective earth?
3. Is there no mains voltage?
4. Is the probe rated for the voltage?
5. Is `10x` selected if needed?
6. Are the probe and channel set the same way?
7. Don't channel grounds connect different circuit points?
8. Can you first check the signal on the low-voltage side?

If you have doubts about 110-230V AC, don't connect the oscilloscope.

## Common errors

- ground clip attached to a voltage point, not `GND`;
- trying to "disconnect" oscilloscope earth from the mains;
- measuring mains voltage with a normal probe without a differential;
- forgetting that channel grounds are connected;
- probe set to `10x`, oscilloscope set to `1x`;
- using long probe ground and seeing extra noise;
- only looking with a multimeter and missing a brief sag;
- thinking a UART problem is software when there is no physical signal on the line.

## The essentials

- An oscilloscope shows signal shape over time.
- It is useful for PWM, UART, power sag, noise and brief glitches.
- A normal benchtop oscilloscope ground is connected to mains protective earth.
- You cannot connect the probe ground to an arbitrary circuit point.
- For mains and floating measurements, special safe methods are needed.
- A frequency-measuring multimeter is useful, but not an oscilloscope replacement.

## Reference materials

- [SparkFun: How to Use an Oscilloscope](https://learn.sparkfun.com/tutorials/how-to-use-an-oscilloscope/introduction) - basic practical introduction to oscilloscopes, signals and controls.
- [Tektronix: How to Use an Oscilloscope](https://www.tek.com.cn/documents/primer/how-to-use-an-oscilloscope) - grounding, setup, controls and basic oscilloscope use.
- [Tektronix: ABCs of Probes Primer](https://www.tek.com/en/documents/whitepaper/abcs-probes-primer) - warnings about probe ground, mains earth and danger of floating measurements with a normal oscilloscope.
- [Tektronix: Floating Oscilloscope Measurements and Operator Protection](https://www.tek.com/en/documents/technical-brief/floating-oscilloscope-measurements-and-operator-protection) - why disconnecting oscilloscope mains earth is dangerous and what safe alternatives exist.
- [Keysight: Floating an oscilloscope](https://docs.keysight.com/kkbopen/how-can-i-float-an-infiniium-or-infiniivision-x-oscilloscope-isolating-it-from-mains-power-607258715.html) - Keysight does not recommend bypassing grounding and suggests differential probes.
