# Why PLA is risky

PLA is a great material to start with.

It prints easily, is inexpensive, produces neat parts, and is well-suited for prototypes. Many first enclosures, covers, and brackets are printed from PLA.

The problem starts when PLA is placed near heat and treated as a full working material.

## PLA does not have to melt to become dangerous

The main mistake is looking at melting temperature.

PLA can start losing rigidity long before it melts.

For a working part, dangerous is not just "it melted". Dangerous is when the part:

- softens;
- creeps under a screw;
- loses shape;
- releases a clip;
- shifts a sensor;
- blocks an air duct;
- reduces gap to a hot part;
- allows a wire to touch a heated zone.

Externally this can look like minor deformation. But for a heated device such a small change can cause wrong temperature reading or poor airflow.

## Where PLA is especially risky

PLA is better not used for:

- heater bracket;
- temperature sensor holder on a hot part;
- air duct right after the heater;
- part inside a hot chamber;
- power terminal bracket;
- part near an SSR, MOSFET, or heatsink;
- part under constant load in heat;
- enclosure where 110-230V AC runs nearby.

Even if the part does not touch the heater, it can sit in warm air for long periods. In a closed enclosure, temperature rises not just near the heater but throughout.

## Dangerous scenarios

Typical problems:

- heater bracket softened;
- sensor holder shifted and temperature reads wrong;
- air duct deformed and flow through heater decreased;
- electronics cover warped and blocked ventilation;
- screw crushed plastic after several hours of heating;
- wire started touching a hot part;
- gap between plastic and terminal became smaller;
- enclosure lost shape but device kept heating.

That is why "it printed nicely" does not mean "will work safely".

## Where PLA can be used

PLA is not a bad material. It just needs to be used where it belongs.

PLA is suitable for:

- cold prototypes;
- test-fit parts;
- templates;
- decorative covers away from heat;
- handles and pads in cool zones;
- temporary parts for shape checking;
- models that do not bear device safety.

PLA is useful early on: quickly check dimensions, board fit, cover shape, button placement, or air duct direction. But after checking, a working part near heat often needs to be reprinted from another material or replaced with a non-printed part.

## Closed enclosure makes it worse

In an open room, a PLA part might look stable.

In a closed dryer or printer chamber, conditions are different:

- air heats up;
- plastic stays in warmth for a long time;
- a heater operates nearby;
- airflow might not cool the part;
- there might be a power supply or power module inside;
- load acts for hours.

Therefore, checking "I touched the part with my hand, seems fine" is not enough.

You need to verify the device in real operation: with heating, fan, enclosure, and runtime similar to actual use.

## PLA under load

PLA is stiff, but that does not mean it holds constant load well in heat.

Bad places for PLA:

- standoffs under screws;
- clips;
- hinges;
- spool holders;
- thin brackets;
- parts compressed by a screw;
- parts holding a spring or lever.

If a PLA part is heated and loaded constantly, it can gradually change shape. This is called material creep.

For an enclosure this is especially unpleasant: today everything is assembled fine, but after several heating cycles the gap is different.

## What to use instead of PLA

Depending on the task, consider:

- PETG - for moderately warm zones and simple working parts;
- ABS or ASA - for warmer and technical parts;
- PC or PA/nylon - for experienced users and more demanding conditions;
- metal, fiberglass, ceramic, or ready-made brackets - near the heater and power section.

If the question is heater bracket, thermal protection, mains terminals, or critical sensor, do not choose material from a filament list alone. Sometimes the right answer is not to print this part from plastic at all.

## How to use PLA more safely

If PLA is used anyway:

- keep it in the cool zone;
- do not place near the heater;
- do not use as power part bracket;
- do not load with screw without margin;
- do not make PLA the only safety element;
- verify after extended heating;
- keep gap to hot parts;
- make a prototype, not the final hot part.

For early tests, you can print a PLA part, assemble the device without heating or at reduced power, verify shape, fit, and access. After that, the working part should be reprinted from suitable material.

## Common mistakes

- ignoring PLA softening and looking only at melting temperature;
- printing heater bracket from PLA;
- placing PLA air duct right after the heater;
- mounting thermistor with PLA in a hot zone;
- using PLA inside a closed warm chamber;
- thinking "if it does not melt in 5 minutes, it is safe";
- not checking deformation after several hours of operation;
- leaving PLA under a screw and load in heat;
- not reprinting the prototype in a working material.

## Key takeaways

- PLA is convenient for prototypes but poor for hot zones.
- A part can become dangerous long before melting.
- Main risk is loss of shape, rigidity, and gaps.
- PLA can be used away from heat and power section.
- For working parts near heat, consider PETG, ABS/ASA, or non-plastic solution.
- If failure of a PLA part can affect safety, the material is chosen wrong.

## References

- [Prusa Knowledge Base: PLA](https://help.prusa3d.com/article/pla_2062) - PLA as a simple material for prototypes and parts without high mechanical, chemical, or temperature load.
- [Prusa PLA product page](https://www.prusa3d.com/en/product/pla-filament/) - practical warning about low temperature resistance and strength loss at temperatures above roughly 60°C.
- [Bambu Lab: PLA Filament Guide](https://bambulab.com/en-us/filament/pla) - PLA as a beginner material for decorative parts and models, but not for high temperatures and demanding applications.
- [Bambu Lab: 3D Printer Filament Comparison Guide](https://bambulab.com/en-us/filament-guide) - comparison of heat resistance and other properties of PLA, PETG, ABS, ASA, PC, and engineering materials.
- [Filwiz: PLA Heat Resistance Explained](https://filwiz.com/guides/pla-heat-resistance-glass-transition-vs-melting-point) - explanation of the difference between melting temperature, glass transition, and practical heat tolerance of PLA.
