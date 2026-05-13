# PETG, ABS, and ASA

PETG, ABS, and ASA are often considered the next materials after PLA, when a part must be not just pretty but functional.

In devices around a dryer, printer chamber, or heater, material choice affects safety. A part can look normal after printing, but after an hour in a warm enclosure it can start to soften, warp the air duct, loosen fasteners, or shift a sensor.

## PETG

PETG is often a good first working material after PLA.

It typically:

- prints easier than ABS and ASA;
- smells less during printing;
- warps less;
- handles temperature better than PLA;
- works well for many brackets, covers, holders, and air ducts under moderate conditions.

For iDryer-like devices, PETG can work well for:

- fan bracket away from the heater;
- electronics cover;
- sensor holder in a moderate temperature zone;
- air duct for not-too-hot air;
- prototype enclosure.

But PETG does not automatically become heat-resistant for any hot zone.

If a part sits near a heater, in a hot airstream, or under constant load, PETG can gradually lose rigidity and deform.

## ABS

ABS is a more technical material than PLA and PETG.

It typically works better for:

- parts with mechanical load;
- enclosure in a warmer environment;
- brackets where PETG is already questionable;
- parts needing better temperature resistance.

Drawbacks of ABS:

- warps more;
- requires a closed chamber or stable warm environment during printing;
- noticeably smells;
- can emit harmful fumes during printing;
- not suitable for printing in a living space without ventilation.

Do not choose ABS just because "it is stronger". You need to know how to print it. Poorly printed ABS with delamination and internal stress can turn out worse than well-printed PETG.

## ASA

ASA is similar to ABS in purpose, but often better suited for outdoor and technical parts.

Advantages of ASA:

- good temperature resistance;
- UV resistance;
- less smell compared to ABS, but smell and fumes are still present;
- usually warps less than ABS;
- suitable for working technical parts.

Drawbacks:

- also requires good print conditions;
- for large parts, a closed print chamber is preferred;
- harmful fumes possible during printing;
- material is more expensive and demanding than PETG.

ASA is often more sensible than ABS for parts that will live long in a device or near windows/sunlight. But for a small internal electronics cover, ASA is not always necessary.

## Where to use which material

A rough guide:

| Task | PETG | ABS/ASA |
| --- | --- | --- |
| Cold prototype | works | works, but often excessive |
| Electronics cover away from heat | works | works |
| Fan holder in moderate zone | works | works |
| Air duct near warm airstream | sometimes works | often better |
| Part inside hot chamber | check temperature | often more sensible |
| Bracket near heater | risky | also requires checking, sometimes metal is needed |
| Part under constant load in heat | cautiously | better, but not automatically safe |
| Part near 110-230V AC | material is not the only answer | material is not the only answer |

This is not a permission table. This is just starter logic.

The real solution depends on temperature, distance to the heater, airflow, load, runtime, and consequences of failure.

## Melting temperature is not the main parameter

For enclosures and brackets, what matters is not the temperature at which material melts.

More important is when it will:

- soften;
- creep under load;
- lose shape;
- release a screw;
- warp;
- change size.

A part can become dangerous long before melting.

For example, a sensor holder can shift by just a few millimeters. Externally this seems minor, but the controller will already see the wrong temperature.

## Printing ABS/ASA requires conditions

ABS and ASA often require:

- a closed chamber;
- high bed temperature;
- stable temperature around the part;
- good bed adhesion;
- protection from drafts;
- room ventilation;
- careful filament drying if needed.

If you print ABS/ASA on an open printer, a large part can warp, crack, or delaminate.

For small parts, sometimes you can manage without a perfect closed chamber, but for an enclosure, air duct, or long part, plan for proper print conditions from the start.

## Do not choose material separately from design

Material is only part of the solution.

Even good material will not save poor geometry:

- thin walls;
- small posts for screws;
- sharp internal corners;
- load perpendicular to layers;
- poor mounting to enclosure;
- no gap to hot parts;
- blocked ventilation.

If a part holds a heater, power connector, or temperature sensor, you must think not just about plastic, but also about metal brackets, shielding, gaps, and fail-safe protection.

## Practical rule

For a simple device, you can think like this:

- PLA - prototype, template, cold decorative part.
- PETG - basic minimum for many working parts at moderate temperature.
- ABS/ASA - better for hotter and mechanically loaded parts, if you can print them.
- Metal, fiberglass, ceramic, or ready-made non-flammable parts - where plastic near heat is no longer appropriate.

If failure of a part can lead to overheating, short circuit, or contact between wire and hot part, material must be chosen with a large safety margin and tested in real assembly.

## Common mistakes

- thinking PETG is fully heat-resistant;
- printing ABS/ASA without a closed chamber and getting delamination;
- choosing material based on internet advice without knowing the temperature inside the enclosure;
- placing PETG air duct too close to the heater;
- using ABS/ASA in a living space without ventilation;
- thinking that swapping PLA for ASA automatically makes the design safe;
- not checking the part after an hour of operation at real temperature;
- forgetting that screws and load can deform plastic over time.

## Key takeaways

- PETG is often a good minimum for working parts, but not for any hot zone.
- ABS and ASA better handle temperature but are harder to print and require ventilation.
- ASA usually beats ABS in UV resistance and often smells less, but still requires care.
- Material is chosen based on actual temperature, load, and failure consequences.
- For parts near a heater, sometimes the right answer is not plastic but metal or a ready-made bracket.

## References

- [Prusa Knowledge Base: PETG](https://help.prusa3d.com/article/petg_2059) - PETG description, printing, strength, temperature resistance, and limits.
- [Prusa Knowledge Base: ABS](https://cdn.help.prusa3d.com/article/abs_2058) - ABS properties, print requirements, warping, and fume warning.
- [Prusa Knowledge Base: ASA](https://help.prusa3d.com/article/asa_5078) - ASA as a technical material with temperature and UV resistance, plus closed chamber requirements.
- [Bambu Lab: 3D Printer Filament Comparison Guide](https://bambulab.com/en-us/filament-guide) - comparative table of materials: PLA, PETG, ABS, ASA, PC, PA, and composites.
- [Bambu Lab: ASA Filament Guide](https://bambulab.com/en-us/filament/asa) - brief ASA description, its pros, cons, and use cases.
