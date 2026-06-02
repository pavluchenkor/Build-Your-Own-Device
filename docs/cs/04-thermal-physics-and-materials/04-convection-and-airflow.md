# Konvekce a proudění vzduchu

Convection is the transfer of heat by air stream. In a dryer, printer chamber, heated filter, or iHeater-like device, air often determines whether heat reaches where it is needed.

A heater by itself only converts electrical power into heat. The fan and air duct determine whether this heat is evenly distributed throughout the chamber or remains a small dangerous hot spot.

## Three Modes of One Heater

The same `100 W` heater can work completely differently.

![Convection cells: warm air rises, cold air falls](../../../img/04-thermal-physics-and-materials/04-convection-cells.svg)

*Source: [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:Convection_cells.svg), McSush, CC BY-SA 3.0*

Without airflow:

- heater heats up strongly in local zone;
- air nearby heats up, but mixes poorly;
- far part of chamber may stay cold;
- plastic, terminals, or insulation nearby may overheat;
- temperature sensor may not show what happens near heater.

With weak or improper airflow:

- some heat goes into chamber;
- mixing occurs;
- but flow may bypass heater;
- filter, screen, or narrow channel may greatly reduce airflow;
- hot spots still remain.

With normal flow:

- air passes through hot zone;
- heat escapes from heater into chamber;
- temperature becomes more even;
- PID control works more predictably;
- nearby parts overheat less locally.

Airflow does not create additional power. It helps remove already generated heat and transfer it to the right place.

## Natural and Forced Convection

There are two useful modes:

- natural convection - warm air rises on its own;
- forced convection - flow is created by a fan, blower, or centrifugal fan.

For small heated devices, natural convection is often insufficient. It is slow, depends on housing shape, and easily creates temperature zones.

Forced convection is usually better if you need to:

- quickly remove heat from heater;
- heat chamber evenly;
- pass air through a filter;
- dry filament;
- cool power electronics;
- keep temperature sensor in meaningful airstream.

## Fan Is Not Just Size

The phrase "I will put a 40 mm fan" tells you almost nothing about the result.

For a real device, important are:

- air flow;
- static pressure;
- operating point after installation in housing;
- flow direction;
- resistance of screens, filters, and air ducts;
- air temperature at fan;
- noise and vibration;
- resource under load;
- starting current;
- tachometer or rotation control.

Catalog often lists maximum flow and maximum static pressure. In a real device, the fan does not operate at these ideal points. Filter, screen, narrow channel, air duct turn, and dense heater create resistance, so actual flow may be much lower.

If air must pass through a filter, radiator, honeycomb, or narrow channel, often you need not just "more CFM" but a fan or centrifugal blower with appropriate static pressure.

## Air Path

Good design answers four questions:

1. Where is air drawn from?
2. What does it pass through?
3. Where does it release heat?
4. Where does it return?

For chamber or dryer, closed-loop circulation is useful:

```text
chamber -> fan -> heater -> hot stream -> chamber -> return
```

For a filter, different logic may apply:

```text
chamber -> filter -> fan -> exhaust or return
```

The main thing is that flow does not take the easiest useless path past heater or filter. Air always chooses the path with least resistance.

## Temperature Sensor Must See the Right Place

Bad options:

- sensor is right at heater and sees local overheat;
- sensor is in dead zone and sees cold corner;
- sensor touches metal wall and measures wall, not air;
- sensor is located before heater, though temperature after it matters;
- sensor is blown by a stream that does not reflect chamber temperature.

For chamber, it is usually useful to measure air where temperature should be controllable, but not directly at heater. For protection from overheat near heater, a separate sensor or independent thermostat/thermal cutoff is needed.

One sensor for control and one independent emergency element is much better than one sensor responsible for everything.

## Filters and Screens Can Kill Flow

A filter, screen, decorative grate, or narrow gap adds resistance.

Typical mistakes:

- putting dense filter on weak axial fan;
- half-blocking inlet with decorative screen;
- making sharp turn right after fan;
- positioning heater so air goes around it;
- forgetting that filter clogs with dust and resistance grows;
- not leaving access for filter maintenance.

If device depends on flow, check not only "fan is spinning" but also that air really passes through the right path.

## What Happens If Fan Fails

Most dangerous scenario for heater with airflow:

```text
fan stopped -> heater keeps working -> local temperature quickly rises
```

Therefore, heater that relies on air stream needs measures:

- independent overheat protection near hot zone;
- power limiting;
- material with temperature margin;
- distance from heater to plastic and insulation;
- fan tachometer control if fan is critical;
- firmware check for heating if using Klipper or similar;
- first test under observation.

Firmware helps but does not replace physical protection. MOSFET, SSR, or relay can fail in the on state.

## Minimum Check After Assembly

After building a heated device, check:

- flow direction;
- is there flow at outlet, not just fan rotation;
- temperature at heater;
- temperature after heater;
- temperature in far part of chamber;
- temperature of wires, terminals, and printed parts;
- temperature of fan;
- behavior with partially blocked filter;
- does heating shut off if sensor fails;
- does independent overheat protection trip in dangerous scenario.

Do first warm-up under observation. Measurements are better done after stabilization and after prolonged operation, because housing, fasteners, and insulation heat up slower than air.

## Connection to Klipper

In Klipper, several mechanisms are useful:

- `heater_fan` - fan turns on with heater or when temperature is reached;
- `temperature_fan` - fan is controlled by separate temperature sensor;
- `verify_heater` - checks that heater behaves as expected;
- `tachometer_pin` for fan - allows to see RPM if fan supports tachometer signal.

This is not a complete safety scheme, but a good level of control for device where temperature and flow are important.

## Main Takeaway

In a heated device, what matters is not only heater power but air path. Good flow removes heat from heater and transfers it to chamber. Poor flow leaves a hot spot, deceives sensor, and increases material overheating risk.

If heater depends on fan, fan failure must be a separate emergency scenario, not a surprise.

## Materials on the Topic

- [Engineering ToolBox: Convective Heat Transfer](https://www.engineeringtoolbox.com/amp/convective-heat-transfer-d_430.html) - explanation of natural and forced convection.
- [SANYO DENKI: Fan Airflow and Static Pressure](https://techcompass.sanyodenki.com/en/training/cooling/fan_basic/004/index.html) - why maximum flow and maximum pressure from catalog do not equal real device operation.
- [SANYO DENKI: Guideline in Selecting a Fan](https://products.sanyodenki.com/info/sanace/en/technical_material/select.html) - practical approach to choosing fan by thermal power, temperature rise, and actual tests.
- [DigiKey: Selecting a Fan](https://www.digikey.com/en/articles/selecting-a-fan) - difference between axial and centrifugal fans, impact of housing and flow resistance.
- [Klipper Documentation: Configuration Reference](https://www.klipper3d.org/Config_Reference.html) - parameters for `heater_fan`, `temperature_fan`, `verify_heater`, and fan tachometer.

## See Also

- [iDryer docs: Connecting a Fan](../06-practical-guides/01-connecting-fan.md) - local instruction on fan power, MOSFET, common GND, and Klipper examples.
