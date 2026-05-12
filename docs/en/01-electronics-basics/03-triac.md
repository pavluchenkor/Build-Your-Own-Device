# TRIAC

A TRIAC, or thyristor, is a power semiconductor switch for alternating current. It is used where you need to turn on or control an AC load: for example a mains heater, incandescent lamp, or other simple device on `110-230V AC`.

For homemade devices this is a high-risk topic. TRIAC itself does not make mains voltage safe. It only provides a way to control an AC load without mechanical contacts.

## How TRIAC differs from MOSFET

The MOSFET module from the previous article is usually used for DC loads: `5V`, `12V`, `24V`.

TRIAC is used for AC loads. It is turned on by a control pulse and conducts current until the current through it falls below the holding value. In AC mains this usually happens around the zero crossing of the sine wave.

In practice:

- MOSFET - typical choice for `12V`/`24V` fan, LED strip, or DC heater;
- TRIAC - typical element inside AC power regulators and many AC SSRs;
- SSR - ready-made solid-state relay, which may contain an optocoupler, TRIAC/thyristor, enclosure, terminals, and sometimes heatsink.

For a beginner, for a mains load, it is often safer to consider a ready-made SSR or certified module than to assemble your own TRIAC circuit on a breadboard.

## Why it is used for AC loads

A powerful low-voltage load requires high current.

For example:

```text
24V 240W -> 10A
24V 300W -> 12.5A
230V 300W -> about 1.3A
```

At `24V` you need thick wires, powerful power supply, strong MOSFET, normal terminals, and cooling. At `230V AC` the current is lower, but there is dangerous mains voltage and all electrical safety requirements.

The TRIAC approach is not "better" and not "simpler". It is a different compromise: less current in the power circuit, but much higher requirements for insulation, enclosure, fuse, distances, and qualifications.

## Typical architecture

The controller is usually not connected to the TRIAC directly.

A typical safe architecture looks like this:

![AC dimmer circuit with TRIAC](../../../img/01-electronics-basics/03-triac-dimmer-circuit.svg)

*Source: [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:TRIAC_based_dimmer_circuit.svg), Osbertjoel, CC BY-SA 4.0*

It has:

- low-voltage side: controller and control resistor;
- optoisolator TRIAC: transmits command through optical isolation;
- mains side: power TRIAC, AC load, fuse, terminals, and enclosure;
- sometimes snubber circuit and varistor/TVS for noise and spikes.

The optoisolator TRIAC is needed for galvanic isolation. This means there is no direct electrical connection between the microcontroller and the mains section. Control is transmitted through light inside the optocoupler.

Galvanic isolation reduces the risk of mains voltage reaching the controller, USB, and computer. But it does not make the mains section safe to touch.

## Zero-cross and phase control

Optoisolator TRIACs come with zero-cross and without it.

A zero-cross optoisolator TRIAC turns on the load near the zero crossing of mains voltage. This is convenient for simple turn on/off of a heater or other resistive load: less noise and softer switching.

An optoisolator TRIAC without zero-cross is used where phase control of power is needed, for example a dimmer. Such a circuit is more complex: you need to detect zero crossing, count delay, and account for noise.

For a heater in a dryer or chamber, a dimmer level control is usually not needed. Often a slow on/off or burst control approach is enough, if it is supported by the chosen module and safe for the load.

## What loads are suitable

A TRIAC is easiest to use with resistive AC loads:

- heater;
- incandescent lamp;
- simple thermal load without electronics inside.

Use caution with:

- motors;
- AC fans;
- transformers;
- solenoids;
- power supplies;
- electronic drivers;
- loads with high inrush current.

Inductive load shifts the phase of current relative to voltage and can interfere with normal TRIAC turn-off. It may require other types of TRIACs, snubber circuit, varistor, or a different switching method.

A power supply or electronic driver should not be considered a normal resistive load. If it has its own electronics inside, TRIAC control may work poorly or dangerously.

## Snubber circuit

Snubber is an RC circuit (resistor + capacitor in parallel with TRIAC) that dampens sharp voltage changes and prevents false TRIAC triggering.

It can help:

- with inductive loads;
- with fast noise in the mains;
- with false TRIAC triggering;
- with turn-off problems.

A typical starting point for a resistive load of 200–400 W at 230 V: **100 nF + 100 Ω**. The capacitor must be of X2 type or equivalent, rated for mains circuit operation. This is not a universal solution, but a starting value. For another load, the ratings are recalculated according to the TRIAC datasheet and application notes from the manufacturer.

If you have no experience with AC circuits, it is better to use a ready-made module or SSR where the snubber is already calculated by the manufacturer.

## Heating and heatsink

A TRIAC heats up during operation. It is not a perfect switch: there is a voltage drop across it, which means heat is generated.

You need to check:

- load current;
- TRIAC package;
- on-state voltage drop;
- heatsink requirements;
- ambient temperature;
- temperature inside the enclosure;
- distance from plastic and wires;
- parameter headroom.

In the technical specification there are many parameters. For the first choice, three are enough:

- `IT(RMS)` — maximum RMS current through TRIAC. Should be higher than load current with headroom, at actual cooling.
- `VDRM`/`VRRM` — maximum voltage in the off state. For 230 V mains, choose TRIAC rated 600 V and higher.
- `IGT` — gate current. Should match the capabilities of the optoisolator TRIAC.

Other parameters (`IH`, `dV/dt`, `Tj`, `Rth`) are important for precise calculation or when there are problems in the real circuit.

The current rating in the technical specification is given under certain cooling conditions. In a closed, warm enclosure without a heatsink, the real maximum current is lower.

## TRIAC and SSR

An SSR for an AC load often uses an optocoupler and TRIAC or thyristor power stage inside.

Advantages of a ready-made SSR:

- convenient terminals;
- clear control input;
- enclosure;
- stated parameters;
- often easier to mount and cool mechanically.

Disadvantages:

- SSR also heats up;
- correct type is needed: AC-output SSR for AC load;
- many SSRs require heatsink;
- market has many counterfeits and modules with overstated specifications;
- SSR does not replace fuse, enclosure, and electrical safety.

If the task is to control a mains heater in a real device, a ready-made quality SSR is often more practical than a homemade circuit on a separate TRIAC.

## What you cannot do

You cannot:

- assemble a mains TRIAC circuit on a solderless breadboard;
- leave the open mains section under power;
- connect the controller directly to the mains section without isolation;
- use low-voltage MOSFET module instead of TRIAC/SSR for `230V AC`;
- put a random capacitor in the mains snubber circuit;
- consider the "40A" label on a cheap module sufficient verification;
- do without a fuse;
- place mains terminals next to USB, buttons, and open low-voltage contacts;
- test such a circuit without understanding electrical safety.

Working with `110-230V AC` requires knowledge, proper tools, enclosure, insulation check, and understanding of local rules. If in doubt, a qualified person should assemble or inspect the power section.

## What to check before buying

Before buying a TRIAC, module, or SSR, check:

- is this AC or DC load;
- mains voltage;
- load current and power;
- is it resistive or inductive load;
- is zero-cross needed;
- is snubber needed;
- maximum current at actual cooling;
- is heatsink needed;
- is there optoisolation;
- terminals and spacing for mains;
- fuse and enclosure;
- is there technical specification or manufacturer documentation.

If there is no documentation, and the module must control a mains heater, that is a poor choice.

## Common mistakes

- using TRIAC for DC load;
- confusing MOSFET, TRIAC, and SSR;
- connecting mains load without optoisolation;
- using zero-cross optoisolator TRIAC and expecting smooth dimming;
- using TRIAC with motor without snubber and load type check;
- not installing heatsink;
- not accounting for temperature inside enclosure;
- using random terminals and thin wires;
- thinking SSR or TRIAC replaces the fuse;
- leaving the mains section open next to the controller and USB.

## The main point

TRIAC is a power switch for AC loads. It is useful for mains resistive loads, such as heaters, but requires correct mains section design.

For a microcontroller, optoisolation is needed. For the load, the right TRIAC/SSR, fuse, terminals, enclosure, heatsink if needed, and safety verification are needed. If you have no experience with `110-230V AC`, do not assemble the power section yourself.

## Reference materials

- [STMicroelectronics: Standard and snubberless triacs documentation](https://www.st.com/en/thyristors-scr-and-ac-switches/standard-and-snubberless-triacs/documentation.html) - TRIAC selection, parameters and application notes on snubberless/standard TRIAC.
- [ST AN437: RC snubber circuit design for TRIACs](https://www.alldatasheet.com/datasheet-pdf/pdf/696239/STMICROELECTRONICS/AN437.html) - detailed explanation of why damping RC circuit is needed and how it affects TRIAC turn-off.
- [MOC3063 datasheet: zero-cross optoisolator TRIAC driver](https://www.alldatasheet.com/html-pdf/5043/MOTOROLA/MOC3063/258/1/MOC3063.html) - example of optoisolator TRIAC for interfacing logic with `115/240 VAC` loads.
- [Omron: Overview of Solid-state Relays](https://www.ia.omron.com/support/guide/18/introduction.html) - basic explanation of SSR as a solid-state relay without mechanical contacts.
- [Omron SSR glossary: phototriac, zero-cross, snubber](https://www.ia.omron.com/support/guide/31/further_information.html) - brief definitions of phototriac, zero-cross, and snubber circuit.
