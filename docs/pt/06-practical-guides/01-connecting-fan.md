# Ligação de um Ventilador

A fan seems like a simple component: apply power and it spins.

In practice, problems arise from four things:

- selecting a fan with the wrong voltage;
- connecting it to a weak controller output;
- not understanding the difference between 2-pin, 3-pin, and 4-pin fans;
- placing the fan where it lacks pressure due to a filter, grill, or duct.

In iDryer-like devices, a fan is usually needed for air circulation, heater cooling, chamber exhaust, filtration, or electronics cooling.

## What to check before connecting

Before connecting, find the fan parameters:

- voltage: `5V`, `12V`, or `24V`;
- current or power;
- connector type: 2-pin, 3-pin, or 4-pin;
- PWM control capability;
- tachometric signal presence;
- airflow;
- static pressure;
- noise level;
- operating temperature.

This data is found on a label, product page, or in the technical datasheet.

For example, a fan datasheet usually contains not just voltage and current, but also airflow, static pressure, noise `SPL dB(A)`, operating temperature, and service life. These are more useful than selecting a fan by size alone.

## Do not power a fan from GPIO

GPIO of a controller is a control signal, not a power output.

Never power a fan directly from GPIO. This can damage the controller or cause resets when the fan starts.

The correct logic is:

- the fan receives power from a power supply or board power output;
- the controller only manages on/off or speed;
- if an external MOSFET module is used, the power supply `GND` and controller `GND` must be common.

![N-channel MOSFET in switching mode (low-side) for load control](../../../img/01-electronics-basics/02-nmos-switch-operation.png)

*Source: [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:NMOS_PWR_WHOLE.PNG), KjellElec, CC BY-SA 4.0*

## Simplest option: 2-pin fan

A 2-pin fan typically has only:

- `+` power;
- `-` power.

If it is a 24V fan, connect it to 24V. If it is a 12V fan, connect it to 12V.

For simple on/off control, you can use:

- a dedicated fan output on the board, if rated for the needed voltage and current;
- an external MOSFET module for DC loads;
- a separate fan controller.

If the fan should run continuously, it can be connected directly to an appropriate power supply through a fuse or protected power line. But in a device with a heater, it is often better for the fan to be controlled by the controller as part of safety logic.

## 3-pin fan

A 3-pin fan typically has:

- power;
- ground;
- tachometric signal.

The tachometric signal allows you to monitor fan RPM. It does not control speed by itself.

A 3-pin fan's speed is usually changed by reducing supply voltage or PWM on the power line, if the specific board and fan support this. But this method may work worse than proper 4-pin PWM: the fan may squeal, fail to start at low speed, or operate unstably.

If speed control is not needed, a 3-pin fan can be used as a regular 2-pin: power and ground are connected, the tachometric wire is unused.

## 4-pin PWM fan

A 4-pin PWM fan typically has:

- ground;
- power;
- tachometric signal;
- PWM control signal.

The key difference: power to the fan is applied continuously, and speed is set by a separate PWM signal.

This is the correct way to control computer PWM fans. Do not assume a 4-pin fan needs to be controlled by constantly switching power on and off. For a proper PWM fan, the control signal should go to a separate PWM pin.

Computer 4-pin PWM fans often have a control input designed for open-collector/open-drain signals with internal pull-up, not any voltage from GPIO. Do not apply `12V` or `24V` to the PWM pin. Check fan documentation; if open-drain/open-collector is required, use an appropriate transistor output or GPIO mode.

For many 4-pin PWM fans, typical PWM frequency is around `25 kHz`. Some fans operate in a nearby range, but at too low or too high frequency they may behave unpredictably: run at full speed, stop, or make noise.

If the PWM wire is not connected, many 4-pin fans run at full speed.

## Common GND / common negative

If the fan is powered by a separate power supply and the PWM signal comes from the controller, a common `GND` / common negative is needed.

Without a common `GND`, the controller and fan have no common reference level. As a result, PWM may not work or may work intermittently.

Simple rule:

- the fan's positive power comes from an appropriate power supply;
- the fan's negative power is connected to the power supply's negative;
- the controller's `GND` is connected to the same negative;
- the control signal only works with a common ground.

## Selecting a fan for the task

For open cooling, airflow matters.

For a filter, heatsink, tight grill, long duct, or narrow channel, static pressure is more important.

So for a printer chamber filter, an ordinary quiet case fan may be weak. It will blow well in free air but barely push air through a HEPA filter, charcoal layer, or narrow channel.

Guidelines:

- for free air circulation look at `CFM` or `m³/h`;
- for filters, heatsinks, and ducts, static pressure is essential;
- for quiet operation look not just at `dB(A)` but also at mounting, grill, and vibration;
- for a heated chamber look at the fan's operating temperature.

## Starting current and margin

When a fan starts, it may briefly draw more current than during normal operation.

If multiple fans are connected to one output, their currents add up.

Check:

- maximum output current of the board;
- current of one fan;
- total current of all fans;
- at least 50% margin;
- heating of terminals, wires, and MOSFET module during prolonged operation.

For example, if one fan draws `0.25A`, four such fans draw about `1A` without accounting for starting current.

## Example: connecting via MOSFET module

Typical circuit for a 12V or 24V fan:

1. The positive of the power supply goes to the positive of the fan.
2. The negative of the fan goes to the power output of the MOSFET module.
3. The negative of the power supply goes to the MOSFET module.
4. The controller's `GND` is connected to the power supply's negative.
5. The controller's control pin goes to the MOSFET module input.

This is called low-side switching: the MOSFET breaks the negative of the load.

For a simple 2-pin fan this is a standard and clear option if the MOSFET module is rated for the needed voltage and current. For a 3-pin/4-pin fan with a tachometer or separate PWM input, "cutting the negative" is not always good: monitoring RPM and native PWM control usually require a constant common `GND`.

## Example Klipper configuration

Pin names in examples are not universal. Before copying, check your board's pinout: a wrong `pin` may activate the wrong output.

If the fan is connected to a controlled output and should be controlled manually:

```ini
[fan_generic chamber_fan]
pin: PA8
max_power: 1.0
shutdown_speed: 0.0
kick_start_time: 0.5
off_below: 0.15
```

Control:

```gcode
SET_FAN_SPEED FAN=chamber_fan SPEED=1.0
SET_FAN_SPEED FAN=chamber_fan SPEED=0.4
SET_FAN_SPEED FAN=chamber_fan SPEED=0
```

If the fan should turn on based on chamber temperature:

```ini
[temperature_fan chamber_exhaust]
pin: PA8
max_power: 1.0
shutdown_speed: 0.0
kick_start_time: 2.0
off_below: 0.15
sensor_type: NTC 100K beta 3950
sensor_pin: PA0
min_temp: 0
max_temp: 80
target_temp: 45
control: watermark
```

Pin names here are typical. In a real device, check your board's pinout.

## What to check after connecting

Before prolonged operation, verify:

- the fan rotates in the correct direction;
- voltage matches the fan;
- the MOSFET module does not overheat;
- terminals do not overheat;
- wires are not too thin for the chosen current;
- the fan starts after a complete stop;
- no squealing or stalling at low speed;
- airflow passes through the needed area, not past it;
- the grill, filter, or housing does not choke the flow more than expected.

If the fan is near a heater, test it at real chamber temperature. A fan that works fine on the bench may degrade quickly in a hot enclosure.

## Common mistakes

- connecting a 12V fan to 24V;
- connecting a 24V fan to 12V and deciding it is broken;
- powering a fan from GPIO;
- forgetting common ground between controller and external power;
- expecting PWM control from a 3-pin fan;
- controlling a 4-pin PWM fan by cutting power instead of using the PWM pin;
- not accounting for total current of multiple fans;
- choosing a fan by size without checking static pressure;
- putting a quiet fan on a dense filter and getting near-zero flow;
- not checking flow direction after installation;
- leaving wires unsecured and getting fraying against the impeller or housing.

## Key points

- Fan voltage must match the power supply.
- GPIO does not power a fan, only controls it.
- For external power, a common ground with the controller is required.
- A 2-pin fan is easiest to control via a power output or MOSFET.
- 3-pin adds a tachometer but not a separate PWM input.
- 4-pin PWM is best controlled by a separate PWM signal, not power switching.
- For filters and ducts, static pressure matters more than a nice `CFM` number.
- After assembly, check not just rotation but actual flow through the construction.

## Related reading

- [Noctua: PWM setup and RPM monitoring of a fan with microcontrollers](https://www.noctua.at/en/support/faqs/microcontroller-guide-pwm-setup-and-rpm-monitoring) - practical explanation of 4-pin PWM, RPM signal, common ground, and typical PWM frequency.
- [Klipper Configuration Reference: Fans](https://www.klipper3d.org/Config_Reference.html#fans) - official sections `fan`, `heater_fan`, `controller_fan`, `temperature_fan`, and `fan_generic`.
- [Voron Documentation: Chamber Temperature & Exhaust Fan](https://docs.vorondesign.com/community/howto/alchemyEngine/chamber_temperature_exhaust_fan.html) - example of controlling chamber exhaust fan by temperature in Klipper.
- [DigiKey: Selecting A Fan](https://www.digikey.com/en/articles/selecting-a-fan) - fan selection accounting for airflow, static pressure, housing resistance, and filters.
- [SANYO DENKI: DC fan example datasheet](https://products.sanyodenki.com/en/sanace/dc/dc-fan/109P0405F601/) - example of real parameters: voltage, current, airflow, static pressure, noise, operating temperature, and service life.
