# Thermal Physics and Materials

This section is needed for devices with a heater, chamber, filament dryer, filter with warm air, air ducts, fans, insulation, or printed parts near high temperatures.

You will not find an academic physics course here. The goal is practical: understand where heat goes, why the housing heats unevenly, why one material suits a chamber wall while another can soften, smoke, or become a fire risk.

## Why This Matters

In a simple heated device, you cannot think only this way:

```text
placed a heater -> it got hot
```

In practice, you need to answer other questions:

- where does heat from the heater go;
- where will hot spots appear;
- what does the temperature sensor see;
- will the material withstand prolonged heating;
- what happens if the fan fails;
- what happens if a MOSFET/SSR sticks;
- will wire, terminal, or plastic end up in the overheating zone;
- is there independent overheat protection.

A device may show `45°C` on the screen, but next to the heater, terminal, or inside the air duct it may be much hotter. Therefore, not only the target chamber temperature matters, but also the local temperatures of the parts.

## Three Ways Heat Spreads

Heat transfers in three main ways:

![Three mechanisms of heat transfer: conduction, convection, and radiation](../../../img/04-thermal-physics-and-materials/01-heat-transfer-kettle.png)

*Source: [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:Kettle-convection-conduction-radiation.png), P.wormer, CC BY-SA 3.0*

**Thermal conduction** - heat passes through a material. For example, a metal bracket quickly transfers heat from a hot zone to the housing.

**Convection** - heat is carried by an air stream. For example, a fan takes heat from the heater and spreads it throughout the chamber.

**Radiation** - a hot surface transfers heat via infrared radiation. For example, a strongly heated element can heat nearby plastic even without direct contact.

In a real device, all three mechanisms almost always work simultaneously.

## Material Is Part of the Thermal System

The material of the housing, wall, air duct, or mount affects the thermal regime.

Metal:

- conducts heat well;
- can dissipate heat from the hot zone;
- can make the outer surface hot;
- does not solve the insulation and electrical safety issue by itself.

Plastic:

- conducts heat poorly;
- can be convenient for a housing;
- can soften and lose strength;
- can be flammable or smoke when overheated.

Insulation:

- reduces heat loss;
- helps maintain chamber temperature;
- can amplify local overheating;
- requires protective layer and fire safety verification.

There is no universal "best material". There is a material suitable for a specific location, temperature, load, and failure scenario.

## Working Temperature Is Not Melting Temperature

Beginners often look only at melting temperature. This is a mistake.

Material can become unsuitable earlier:

- soften;
- lose shape;
- shrink;
- lose strength;
- start to smell;
- release decomposition products;
- become more flammable.

For housing, mounting, or air duct, the permissible working temperature, softening temperature, fire properties, and manufacturer recommendations matter more.

## Air Must Move Correctly

A fan in a heated device is not there "for show". It determines how heat will escape from the heater.

Without proper flow:

- heater can locally overheat;
- chamber will heat unevenly;
- sensor may not show the right temperature;
- nearby parts may become hotter than expected;
- PID control will behave worse.

But the fan must also be selected and installed correctly: flow, static pressure, direction, filter, screen, and air duct can completely change the result.

## What to Check in Any Heated Device

Before assembly and first test, check:

- heater power;
- temperature next to the heater;
- air temperature after the heater;
- temperature of terminals and wires;
- temperature of housing and printed parts;
- whether the material withstands working temperature with margin;
- whether flammable material is near the hot zone;
- is there a fuse;
- is there independent overheat protection;
- what happens if the fan fails;
- what happens if the temperature sensor fails.

The first test is done under observation and with the ability to quickly cut power.

## How to Read This Section

The section consists of three practical topics:

- [Thermal Conductivity](02-thermal-conductivity.md) - why metal, plastic, glass, and insulation behave differently.
- [Materials, Flammability and Harmful Emissions](03-material-safety.md) - how to choose material near heat and what to read in the datasheet.
- [Convection and Airflow](04-convection-and-airflow.md) - why the same heater works differently with different airflow.

## Main Takeaway

A heated device is not just a heater and sensor. It is a thermal system: heater, air, housing, materials, wires, terminals, fan, sensors, and emergency protection.

If a material is convenient, cheap, and easy to cut, that does not mean it can be placed next to a heater. First check the temperature, heat transfer, fire properties, documentation, and failure scenarios.

## Materials on the Topic

- [U.S. Department of Energy: Principles of Heating and Cooling](https://www.energy.gov/energysaver/principles-heating-and-cooling) - simple explanation of thermal conduction, convection, and radiation.
- [NASA Glenn Research Center: Heat Transfer](https://www1.grc.nasa.gov/beginners-guide-to-aeronautics/heat-transfer-3/) - basic explanation of heat transfer from a hotter body to a colder one.
- [Engineering ToolBox: Conductive Heat Transfer](https://www.engineeringtoolbox.com/conductive-heat-transfer-d_428.html) - thermal conduction, temperature gradient, material thickness, and multilayer walls.
- [UL Solutions: Combustion Fire Tests for Plastics](https://www.ul.com/services/combustion-fire-tests-plastics) - why plastic materials are compared by behavior when burning, not just by melting temperature.

## See Also

- [iDryer docs: Heaters](../03-common-components/02-heaters.md) - local article about heater selection, power switch, sensor, and independent overheat protection.
