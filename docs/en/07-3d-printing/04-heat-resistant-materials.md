# Heat-resistant materials

For parts near heat, what matters is not the label "heat-resistant" but real material behavior in your specific design.

A part may not melt, but it can already:

- soften;
- bend;
- creep under a screw;
- change size;
- lose rigidity;
- loosen fasteners;
- shift a sensor;
- block airflow.

Therefore, "melting temperature" is almost never the main parameter for an enclosure, bracket, or air duct.

## What counts as a hot zone

A hot zone is not just where the heater sits.

In a homemade device, hot areas can include:

- airstream after the heater;
- wall near the heater;
- thermistor mounting point;
- air duct;
- area above the power supply;
- location near an SSR or MOSFET with heatsink;
- closed chamber that heats up entirely.

If a part is in such a zone, material is chosen with a margin and tested in real assembly.

## Working temperature, not melting

Melting is already a late stage of the problem.

For a printed part, what is more important:

- at what temperature it loses rigidity;
- whether there is a load;
- how many hours it will work;
- is there hot airflow;
- is there vibration;
- does it hold a screw or clip;
- what happens if it deforms.

A sensor holder can become dangerous even before visible failure. If the sensor moves away from the surface, the controller may continue heating because it reads the wrong temperature.

## Basic options

A rough material hierarchy:

- PLA - for cold prototypes and decorative parts away from heat.
- PETG - basic option for moderate temperatures and simple working parts.
- ABS/ASA - better for warmer and mechanically loaded parts, if you have print conditions.
- PA/nylon - tough technical material, but highly dependent on humidity and print conditions.
- PC/polycarbonate - more heat-resistant and strong material, but difficult to print.
- Composites with carbon or glass filler - can be stiffer and more stable, but require suitable nozzle and understanding of properties.
- Metal, fiberglass, ceramic, or ready-made heat-resistant parts - where plastic is no longer appropriate.

This is not a "better-worse" ranking. It is a list of options with different complexity, cost, and risks.

## PETG

PETG works for many parts in a moderate temperature zone:

- electronics covers;
- fan brackets;
- temperature sensor holders away from the heater;
- air ducts for moderate airflow;
- enclosure elements not bearing critical safety.

But PETG can soften and creep under load. If a part holds a heater, power terminal, or safety sensor, PETG must be used very carefully.

## ABS and ASA

ABS and ASA typically work better in hotter zones than PETG.

They are considered for:

- chamber enclosure;
- air ducts;
- brackets in warm environment;
- technical parts;
- parts that must retain shape longer.

But they have a price:

- harder to print;
- warping;
- smell;
- potentially harmful fumes;
- preferably printed in a closed chamber;
- requires ventilation.

ASA is often preferred for parts where UV resistance and durability matter. ABS can be cheaper and more available.

## PA / Nylon

PA, or nylon, is used for technical parts with mechanical load.

Advantages:

- high impact toughness;
- good wear resistance;
- low friction;
- good mechanical toughness;
- some variants have good temperature resistance.

Drawbacks:

- absorbs moisture strongly;
- requires drying;
- can warp;
- difficult to print;
- requires correct surface and conditions.

Wet nylon prints poorly: bubbles, hissing, bad surface, and weak strength result. For a simple enclosure cover, nylon is usually excessive.

## PC / Polycarbonate

Polycarbonate is considered when you need high strength and temperature resistance.

Advantages:

- high impact strength;
- high temperature resistance;
- good rigidity;
- suitable for functional parts.

Drawbacks:

- difficult to print;
- high nozzle and bed temperature;
- prone to warping;
- needs stable warm environment;
- not every printer is suitable.

PC is not a "beginner" material. If printing is unstable, a part can look normal but have poor interlayer strength.

## Composites

Composite filaments contain fillers: carbon fiber, fiberglass, Kevlar, or other material.

They can provide:

- greater rigidity;
- less deformation;
- better dimensional stability;
- nice technical surface.

But they do not make the base plastic magically non-flammable or fully heat-resistant.

Important:

- carbon filler wears brass nozzles;
- hardened or suitable nozzle is needed;
- composite can be more brittle;
- properties depend on specific material, not just the letters `CF` in the name.

## When plastic does not work

For some locations, the right material is not printed plastic.

Better to consider metal, fiberglass, ceramic, or ready-made industrial parts for:

- heater bracket;
- direct heat zone;
- contact with power terminal;
- mains wire mounting;
- mechanical barrier between 110-230V AC and user;
- place where part deformation could lead to fire or electric shock.

A printed part can hold enclosure shape, but should not be the only protection from a dangerous failure.

## How to choose material

Before choosing a material, answer:

1. What is the maximum temperature at the installation location?
2. How long will the part work at this temperature?
3. Is there mechanical load?
4. Are there screws, clips, or constant compression?
5. Is there a heater, SSR, MOSFET, power supply, or 110-230V AC nearby?
6. What will happen if the part deforms?
7. Can you replace plastic with metal or a ready-made bracket?

If the failure consequence is serious, you do not want "the most convenient plastic" but a design with margin and independent protection.

## Common mistakes

- looking only at melting temperature;
- thinking PETG is safe next to any heater;
- using PLA in a closed hot chamber;
- printing PC/nylon without a suitable printer and getting a weak part;
- choosing composite only for the cool `CF` marking;
- placing a plastic part right next to a power terminal;
- not checking the part after extended heating;
- forgetting about screw load and material creep;
- not accounting for the fact that a closed enclosure heats up entirely.

## Key takeaways

- Working temperature is more important than melting temperature.
- A part can become dangerous before visible melting.
- PETG is a basic option for a moderate zone, not universal heat protection.
- ABS/ASA better handle heat but require print conditions and ventilation.
- Nylon and PC are technical materials for experienced users and suitable equipment.
- In hot and load-bearing locations, metal or a ready-made heat-resistant bracket is often better.

## References

- [Prusa Knowledge Base: Material guide](https://help.prusa3d.com/category/material-guide_220) - comprehensive Prusa catalog of materials with PLA, PETG, ABS, ASA, PC, Nylon, and composites.
- [Prusa Knowledge Base: Polycarbonate](https://help.prusa3d.com/article/polycarbonate-pc_165812) - PC properties, high temperature resistance, and print difficulty.
- [Prusa Knowledge Base: Polyamide / Nylon](https://help.prusa3d.com/article/polyamide-nylon_167188) - nylon as a technical material, moisture absorption, drying, and print requirements.
- [Bambu Lab: 3D Printer Filament Comparison Guide](https://bambulab.com/en-us/filament-guide) - material comparison by heat resistance, strength, moisture absorption, and drying needs.
- [Prusa Knowledge Base: Enclosure guidepost](https://cdn.help.prusa3d.com/article/enclosure-guidepost_366332) - why a closed chamber is important for materials that warp during cooling.
