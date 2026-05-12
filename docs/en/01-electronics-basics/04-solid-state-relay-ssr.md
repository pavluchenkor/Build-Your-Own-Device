# Solid-State Relay

A solid-state relay, or SSR, is a relay without mechanical contacts. You apply a weak control signal from the controller to the SSR input, and the SSR output turns a load on or off.

In simple devices for 3D printers, SSR is most often used for a mains heater: chamber, dryer, table, or separate heating module. It is a convenient way to control `110-230V AC` load from low-voltage electronics, but not a way to make the mains safe.

If the project has `110-230V AC`, the power section must be assembled in an enclosure, with a fuse, normal terminals, insulation, cable strain relief, and understanding of electrical safety.

## How SSR differs from ordinary relay

An ordinary electromagnetic relay clicks because the contacts physically move inside. The relay coil needs power, often needs a transistor driver, protection diode, and the contacts can spark, chatter, and wear out.

SSR switches the load using semiconductors. Therefore, it has no click, no mechanical contact wear, and is better suited for frequent heater on/off cycling.

But SSR is not "relay without drawbacks".

SSR has its own limitations:

- it heats up;
- often requires heatsink;
- may have small leakage current in the off state;
- tolerates overloads and spikes worse than a properly chosen contactor;
- can fail in the "on" state;
- must be chosen for AC or DC load;
- does not replace fuse, enclosure, and emergency thermal protection.

For infrequent power cycling, an ordinary relay or contactor may be more appropriate. For frequent control of resistive heater, SSR is often more practical.

## What is inside AC SSR

An AC SSR usually contains:

- control signal input circuit;
- optical isolation;
- trigger circuit;
- power TRIAC or pair of thyristors;
- snubber circuit or other spike protection;
- power terminals for the load.

In simple terms, it is a ready-made TRIAC circuit in an enclosure. Therefore, SSR is convenient where you don't want to calculate optoisolator TRIAC, TRIAC, snubber, board spacing, and mains section yourself.

A ready-made enclosure does not eliminate the need to verify. Especially if the SSR is cheap, has no technical specification, or has a suspiciously high current rating on the enclosure.

## AC SSR and DC SSR

SSR must be chosen according to load type:

- **AC SSR** - for alternating current, for example mains heater `110-230V AC`;
- **DC SSR** - for direct current, for example `12V` or `24V` DC load.

These are different devices. AC SSR cannot automatically be put on a `24V` DC heater: it may not turn off. DC SSR cannot be considered suitable for `230V AC`: it can be dangerous and not rated for such a circuit.

You need to check not only the `AC` or `DC` label, but also the output voltage range.

Examples of markings:

```text
Input: 3-32V DC
Output: 24-380V AC
```

This means:

- input is controlled by low-voltage DC signal;
- output switches AC load in the specified range;
- you do not need to power the load from the input side through the SSR.

Before purchasing, check `Input`, `Output`, `Load voltage`, `Load current` lines and the manufacturer's connection diagram.

## Typical connection diagram

SSR is usually placed in the break of the load power line. The controller connects only to the SSR input, while the mains circuit goes through the SSR output.

![Internal structure of solid-state relay SSR](../../../img/01-electronics-basics/04-ssr-internal-structure.png)

*Source: [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:SSR.png), Thomas Verdyck, CC BY-SA 3.0*

Important points:

- SSR input and SSR output are different sides of the device;
- low-voltage side should not be connected to mains side;
- SSR is placed in the break of the load power line, usually `Line`;
- protective grounding `PE` is not broken through the SSR;
- fuse must protect the wiring and load;
- heater needs independent thermal protection;
- entire mains section must be closed from touch.

SSR is not considered service disconnect. For maintenance, you need a physical way to cut power: switch, breaker, connector, or other standard circuit break. In practice, there may be different schemes according to local rules, power type, protective grounding, and enclosure. If you are not sure, a qualified person should verify the circuit.

## Zero-cross, random turn-on, and control

AC SSR comes with different turn-on methods.

**Zero-cross SSR** turns on the load near the zero crossing of mains voltage. This is a good option for simple on/off of a resistive heater: less noise and softer switching.

**Random turn-on SSR** turns on the output almost immediately after the control signal is applied. This type is used where different logic is needed, phase control, or specific load requirements.

For a chamber, dryer, or simple heater, fast dimmer control is usually not needed. Often slow control is enough: for example, turn the heater on for seconds, not jerk it hundreds of times a second.

Not all SSRs are suitable for phase control. If you specifically need a phase power regulator, that is a separate device type and a separate topic with noise, heating, and load requirements.

## Leakage current

SSR can pass a small current even when it is "off". This is called leakage current.

For a powerful heater, such current usually does not create noticeable heating, but for a small lamp, LED driver, power supply, or very small load, it can be noticeable: indicator can glow weakly, power supply input can behave strangely.

Therefore, SSR should not be considered an ideal circuit break. Before the first heater turn on, verify that the load does not heat when the control signal is removed. It is better to first test the SSR output with a safe small load, a lamp, or multimeter, not immediately with the main heater.

For maintenance, emergency shutdown, and complete isolation, you need a switch, breaker, fuse, connector, or other physical way to cut power.

## Heating and heatsink

SSR heats up during operation. In the on state, there is a voltage drop across the power element, which means heat is generated.

You need to check:

- load current;
- maximum SSR current at real temperature;
- voltage drop at output;
- heatsink requirements;
- temperature inside enclosure;
- heatsink orientation and air flow;
- quality of thermal contact between SSR and heatsink;
- temperature of terminals and wires after test.

The label `25A` or `40A` does not mean that the SSR will withstand such current without heatsink in a closed enclosure next to a heater. Manufacturers usually specify current under specific cooling conditions.

Practical rule for a simple project: don't choose SSR exactly for load current. Plan headroom, use heatsink, read the technical specification, and verify temperature in the real enclosure. `50%` headroom is the lower bound for initial estimate, not a guarantee for any installation.

## SSR does not protect the heater

SSR is a power switch, not a safety system.

A heater needs independent layers:

- fuse or breaker for wiring and load;
- correct temperature sensor;
- software temperature limits;
- heating check in firmware;
- independent thermostat, thermal fuse, or bimetal switch;
- enclosure made from material that withstands real temperatures;
- first test under observation.

Important failure mode: SSR can break down and stay on. Therefore, emergency thermal protection must be able to cut heater power independently of the controller and SSR.

## What loads are suitable

SSR is easiest to use with resistive AC loads:

- heater;
- silicone heating pad;
- incandescent lamp;
- simple thermal load without built-in electronics.

Use caution with:

- motors;
- AC fans;
- transformers;
- solenoids;
- power supplies;
- electronic drivers;
- loads with high inrush current.

Inductive and electronic loads may require a different type of SSR, snubber, varistor, contactor, or separate circuit. You cannot choose SSR by the "40A" label alone.

## What to check before buying

Before buying SSR, check:

- load AC or DC;
- load voltage;
- load current and power;
- control input voltage;
- input compatibility with controller: `3.3V`, `5V`, `12V`, or other level;
- turn-on type: zero-cross or random;
- maximum current at needed cooling;
- is heatsink needed;
- is there technical specification;
- is there normal connection diagram;
- terminals and isolation distances;
- manufacturer quality;
- where fuse is placed;
- where independent thermal protection will be.

If there is no documentation, and the SSR must control a mains heater, that is a poor choice.

## Common mistakes

- confused SSR input and output;
- bought DC SSR instead of AC SSR or vice versa;
- did not check output voltage range;
- connected AC SSR to DC heater and were surprised it does not turn off;
- chose SSR exactly for load current;
- installed SSR without heatsink;
- installed SSR in a closed, hot enclosure;
- did not account for leakage current;
- use SSR as the only way for emergency shutdown;
- forgot fuse;
- did not install independent thermal protection;
- left mains terminals accessible;
- control SSR with too fast PWM without understanding SSR type and load.

## The main point

SSR is convenient for frequent quiet load control, especially mains resistive heater. But SSR must be chosen for load type, voltage, current, turn-on method, and thermal operating point.

For `110-230V AC` load, SSR does not eliminate electrical safety. You need enclosure, fuse, normal wiring, heatsink if needed, and independent heater thermal protection.

## Reference materials

- [Omron: Overview of Solid-state Relays](https://www.ia.omron.com/support/guide/18/introduction.html) - SSR design, optical isolation, types, and general application principles.
- [Omron: SSR glossary and installation notes](https://www.ia.omron.com/support/guide/18/further_information.html) - definitions of `load voltage`, `leakage current`, `output ON voltage drop`, zero-cross, snubber, and notes on heat dissipation.
- [Panasonic: SSR Principle of Operation](https://industry.panasonic.com/global/en/products/control/relay/solid-state/principle_operation) - difference between zero-cross and random SSR, behavior with resistive and inductive AC loads.
- [Sensata/Crydom: HS Series Heat Sinks](https://www.sensata.com/products/relays/solid-state-relays/ssr-accessories/hs-series-heat-sinks) - why SSR generates heat and why heatsink should match current and temperature.
- [DigiKey: Solid State Relays - A Basic Overview](https://www.digikey.com/en/blog/solid-state-relays-a-basic-overview) - brief overview of SSR output types, zero-cross, random turn-on, and limitations compared to mechanical relays.
