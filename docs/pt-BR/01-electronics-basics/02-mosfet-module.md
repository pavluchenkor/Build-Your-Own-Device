# Módulo MOSFET

A MOSFET module is a ready-made small board that works as a controlled power switch for DC loads. The controller supplies a weak control signal, and the MOSFET module turns the current from the power supply to the load on or off.

In iDryer-like devices and 3D printer peripherals, a MOSFET module is used for fans, LED strips, low-voltage heaters, and other `12V`/`24V` loads, when the board's standard output is weak, occupied, or inconvenient.

## MOSFET and MOSFET module

A MOSFET is a field-effect transistor. It has three main pins:

- `Gate` - control input;
- `Drain` - power output;
- `Source` - power output.

The gate does not power the load. It only controls. The main load current flows through the power part of the MOSFET between `Drain` and `Source`.

A MOSFET module is not just a single transistor. It is usually a board with a MOSFET, terminals, control input, and sometimes additional resistors, indicators, heatsink, or protection diode.

The board is convenient for a prototype, but its specifications must be checked as carefully as any power node.

## Why it is needed

GPIO of the controller should not power a heavy load.

GPIO can control:

- input of MOSFET module;
- input of relay;
- input of SSR;
- input of driver.

But GPIO should not directly power:

- fan;
- LED strip;
- heater;
- motor;
- solenoid;
- servo drive.

If you connect the load directly to GPIO, you can damage the controller, get reboots, overheat traces, or just get unstable operation.

## Low-side switching

The most common variant for N-channel MOSFET module is low-side switching, that is, switching via the negative line.

![N-channel MOSFET in low-side switching mode](../../../img/01-electronics-basics/02-nmos-switch-operation.png)

*Source: [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:NMOS_PWR_WHOLE.PNG), KjellElec, CC BY-SA 4.0*

Typical logic:

1. `+24V` from power supply goes directly to the load positive.
2. Load negative goes to the power output of MOSFET module.
3. MOSFET module connects or breaks the path from load negative to `GND`.
4. `GND` of power supply and `GND` of controller are connected together.
5. Controller control pin goes to the `Signal`, `IN`, `Gate` or similar input of the module.

Common `GND` / common negative is mandatory. Without it, the controller and MOSFET module do not have a common reference level for the control signal.

Low-side switching has a limitation: MOSFET breaks the load negative. While the switch is off, the load negative is not equal to common `GND`. For a simple 2-pin fan, strip, or heater this is usually fine. For a load with a tachometer, separate signal wire, sensor inside, or additional connection to another board, you need to check the schematic: sometimes it is better to control the standard input or use a different switching method.

## Where to use

MOSFET module is suitable for DC loads if it is rated for their voltage and current:

- `12V`/`24V` fan;
- single-color LED strip;
- channel of standard RGB strip;
- `12V`/`24V` heater;
- small DC motor, if protected from spikes;
- solenoid, if there is flyback diode or other protection.

For addressable LED strip, MOSFET usually does not control the data. It can disconnect power to the entire strip, but individual LEDs are controlled via the data line.

For a servo drive, a MOSFET module is usually not needed to control position: the servo needs a separate control PWM signal and normal power.

## What to check when choosing

Before purchasing or connecting, check:

- load voltage rating;
- maximum current rating;
- real current of your load;
- does the input work from `3.3V`;
- is `Rds(on)` in the technical specification at the needed gate voltage;
- does it need active logic `HIGH` or `LOW`;
- is there common `GND`;
- is there flyback diode for motors/solenoids;
- terminal size and maximum terminal current;
- board trace thickness and cooling;
- is heatsink needed;
- is there a schematic, technical specification, or normal documentation.

If the description only says "MOSFET module for Arduino" without voltage, current, schematic, and MOSFET type, you cannot choose such a module for a heater or long LED strip.

## 3.3V and logic-level MOSFET

Many modern controllers work with `3.3V` logic: ESP32, RP2040, many STM32.

Not every MOSFET fully opens from `3.3V`. If it does not open fully, its resistance remains high and it heats up.

Important terms:

- `Vgs(th)` - threshold where MOSFET starts to open;
- `Rds(on)` - resistance of the open channel;
- logic-level MOSFET - MOSFET rated for control from logic levels.

Common mistake: see in the technical specification `Vgs(th) = 2V` and decide that the MOSFET works fine from `3.3V`. That is not so. `Vgs(th)` does not mean "fully open". You need to check `Rds(on)` at `2.5V`, `3.3V`, `4.5V` or `5V`, depending on the controller.

For ESP32/RP2040 it is better to choose a module that explicitly states `3.3V` control compatibility, or where the input circuit provides this. If the table has `Rds(on)` only at `10V`, and there is no data at `2.5V`/`3.3V`/`4.5V`, such a module is suspicious for a `3.3V` controller.

## Current and heating

A MOSFET in the open state still has resistance. Heat is generated across it.

The greater the current, the more important:

- low `Rds(on)`;
- normal copper area on the board;
- appropriately sized terminals;
- heatsink, if needed;
- enclosure ventilation;
- current headroom;
- temperature check after real operation.

The "100A MOSFET" marking on the transistor package does not mean that a small module with thin traces and cheap terminals will withstand `100A`. The real limit is often the board, terminal block, wire, solder joint, and cooling.

If the MOSFET module is so hot that it is difficult to hold in your hand, that is a reason to stop and recalculate the current, cooling, and connection quality.

## Motors, fans, and solenoids

Inductive loads can produce voltage spikes when turned off.

Such loads include:

- DC motors;
- fans;
- solenoids;
- relays;
- electromagnets.

They often need protection:

- flyback diode;
- TVS diode;
- ready-made driver with protection;
- module where protection is already installed.

If the module is only rated for LED strip or resistive load, you cannot automatically assume it is safe for a motor or solenoid.

For a heater, flyback diode is usually not needed, because the heater is close to a resistive load. But for a heater, current, terminals, fuse, and independent thermal protection are more important.

## PWM control

A MOSFET module can be used not only for on/off, but also for PWM power regulation.

Typical examples:

- LED strip brightness;
- speed of simple DC fan;
- power of low-voltage heater.

But PWM is not always the same:

- 4-pin PWM fan is better controlled by a separate PWM pin of the fan, not by cutting power;
- heater usually does not require high PWM frequency;
- too high frequency can increase MOSFET heating;
- too low frequency can cause LED flicker or motor noise.

Choice of frequency depends on the load, module, and firmware.

## MOSFET module is not for 110-230V AC

Standard MOSFET modules for Arduino/ESP32 are designed for DC loads: `5V`, `12V`, `24V`, sometimes more if explicitly specified.

They cannot be used as a switch for mains voltage `110-230V AC`.

For mains load you need different solutions:

- relay or SSR rated specifically for AC load;
- normal terminals;
- fuse;
- enclosure;
- insulation;
- grounding where required;
- understanding of electrical safety.

If you are not sure that the module is intended for mains voltage, do not connect it to the mains.

## What to check after connecting

Before long-term operation, check:

- load gets correct voltage;
- controller and power supply have common `GND`;
- control signal actually turns the load on and off;
- MOSFET module does not heat excessively;
- terminals do not heat;
- wires are suitable for current;
- PWM works without strange noise, flicker, or reboots;
- load is actually off when command is off;
- for motor/solenoid there is spike protection;
- for heater there is a fuse and independent thermal protection.

Do the first test of heavy load briefly and under observation.

## Common mistakes

- powering load from GPIO;
- forgetting common ground;
- choosing module only by the pretty current number in the name;
- not checking operation from `3.3V` logic;
- using MOSFET that does not fully open;
- connecting motor or solenoid without flyback protection;
- connecting long LED strip through weak terminals;
- using DC MOSFET module for `110-230V AC`;
- not checking module heating in closed enclosure;
- thinking MOSFET module itself limits load current.

## The main point

A MOSFET module is a controlled power switch for DC loads. It does not create power and does not power the load from the controller. It only opens or closes the path for current from the power supply.

Check voltage, current, compatibility with `3.3V`/`5V` logic, common `GND`, heating, terminals, and protection for inductive loads. For mains voltage, standard Arduino/ESP32 MOSFET module is not suitable.

## Reference materials

- [SparkFun MOSFET Power Switch and Buck Regulator Hookup Guide](https://docs.sparkfun.com/SparkFun_MOSFET_Power_Switch_and_Buck_Regulator_Low-Side/single_page/) - example of ready-made low-side MOSFET module, load connection, thermal board limits and flyback diode.
- [SparkFun MOSFET Power Switch product page](https://www.sparkfun.com/products/23979) - example of how manufacturer specifies voltage, current, low-side circuit, MOSFET and board limitations.
- [Adafruit MOSFET Driver](https://learn.adafruit.com/adafruit-mosfet-driver) - practical explanation of why motors, solenoids, and powerful LEDs cannot be connected directly to GPIO and why spike protection is needed.
- [DigiKey: How to Select a MOSFET](https://www.digikey.com/en/blog/how-to-select-a-mosfet-for-logic-circuits-or-gate-design) - selecting MOSFET by `Vgs`, `Rds(on)` and logic control level.
- [Infineon: Logic level MOSFETs](https://www.infineon.com/products/power/mosfet/n-channel/optimos-strongirfet/optimos-ir-mosfet-logic-level) - explanation of logic-level MOSFET and control from microcontroller.
