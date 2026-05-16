# Servomotory

A servo motor is a small drive with a motor, gearbox and internal electronics. You give it a position, and it tries to rotate the shaft to that position and hold it.

In simple devices, a servo is convenient where you need not just to turn a motor on, but to rotate a mechanism to an understandable angle: open a damper, shift a lock, press a button, switch airflow or rotate a small indicator flag.

## Where It's Used

In iDryer-like devices and 3D printer peripherals, a servo can be used for:

- air intake or exhaust damper;
- air duct switching;
- opening/closing a small cover;
- mechanical lock;
- pressing a physical button;
- moving an indicator flag;
- simple dosing or catch.

A servo is good for light mechanics with limited travel. For continuous rotation of a fan, screw or pump, it usually doesn't work: you need a different motor and driver.

## Three Wires

A typical hobby servo has three lines:

- power: usually `4.8-6V`, sometimes `7.4V` or other value on special models;
- ground: `GND`;
- signal: control pulses from the controller.

Common wire colors:

- red - power;
- black or brown - ground;
- yellow, orange or white - signal.

You can't blindly trust colors. Different manufacturers use different color schemes. Before connecting, check the markings, product page or technical description.

A detailed connection diagram with separate power is in the practical section: [Connecting a servo motor](../05-practical-guides/03-connecting-a-servo-motor.md).

## What "Servo Motor" Means

Inside a typical positional hobby servo, there's:

- DC motor;
- gearbox;
- position sensor, often a potentiometer;
- control board;
- output shaft with arm.

The external controller doesn't manage the motor directly. It sends a position signal, and the servo's internal electronics automatically turns the motor so the shaft reaches the desired angle.

So a servo differs from a regular DC motor:

- DC motor just rotates when powered;
- servo tries to reach a set position;
- servo draws current even while holding if there's load on the shaft;
- servo can rapidly increase current and get hot if jammed.

## Positional and Continuous Rotation

The most common type is a positional servo. You set an angle, for example `0`, `90` or `180` degrees.

Continuous rotation servo looks similar but works differently: the control signal sets not the angle, but the direction and speed of rotation. It doesn't know where the shaft is. For a damper or lock, such a servo is often inconvenient because without additional sensors you can't guarantee the position.

Before buying, check what the description says:

- `standard servo`, `positional servo`, `180°` - usually positional;
- `continuous rotation`, `360°` - usually rotates continuously, not positioned to an angle.

The phrase `360° servo` on a marketplace is risky: sometimes it's a continuous rotation servo, sometimes it's just an extended range. You need to check the technical description and reviews with real measurements.

## Control Signal

A typical hobby servo is controlled by repeating pulses.

Typical guidelines:

- period about `20 ms`;
- pulse about `1 ms` - one edge of the range;
- pulse about `1.5 ms` - middle;
- pulse about `2 ms` - other edge of range.

Different servos have different actual limits. Some work about `500-2500 us`, others safely only in a narrower range.

So extreme positions can't be set blindly. First check the middle, then small deviations, only then expand the range.

## Power and Current

The signal wire doesn't power the servo. It draws motor energy from the power line.

Even a small servo can briefly draw large current on startup, rapid movement or mechanical stop. Average current "in quiet demo" doesn't show the worst case.

Important parameters:

- operating voltage;
- no-load current;
- loaded current;
- stall current - current with blocked shaft;
- holding torque or stall torque;
- rotation speed;
- operating temperature.

If the technical description lists stall current, the power source must be chosen with this value and margin. If stall current is not listed, you can't consider the power "safe by eye": for a real device, it's better to use a source with margin and check voltage drop under load.

For one small servo, a board's 5V output sometimes works. But for a damper, lock or multiple servos, you usually need a separate 5V/6V DC-DC converter or power supply. The ground must be common with the controller.

## Torque and Mechanics

A servo is chosen not just by size. The main mechanical parameter is torque, often in `kg·cm` or `N·cm`.

Roughly:

- the longer the lever, the more torque needed;
- the heavier the damper or tighter the mechanism, the more torque needed;
- friction, misalignment and seal greatly increase load;
- when held at a stop, servo heats and draws current.

Example: a small light damper may work fine with a microservo. A damper on a tight seal or a cover with a spring may need a larger servo with metal gears.

For reliable mechanics:

- don't force the servo to constantly push against a physical stop;
- limit angles in firmware;
- leave a small margin of travel;
- make the linkage without misalignment;
- use a suitable arm length;
- test operation at real enclosure temperature.

If the servo hums at the end position, it usually signals load, stop or wrong geometry.

## Gearbox: Plastic or Metal

Plastic gears are cheaper, quieter and work for light tasks. But they break faster on impacts, jamming and heavy loads.

Metal gears are stronger, but the servo may be louder, heavier and more expensive. For dampers, locks and mechanisms a user might accidentally touch, a metal gearbox often makes sense.

But metal gears don't replace good mechanics. If the mechanism jams, it can damage the arm, case, mount or shaft itself.

## Analog and Digital Servo

In simple projects, analog hobby servos are more common. Digital servos usually hold position stiffer and respond faster, but may draw more current and be noisier when holding.

For a dryer damper or simple lock, what usually matters more is:

- enough torque;
- normal power;
- reliable mechanics;
- clear angle range;
- operating temperature;
- gearbox lifetime.

Being "digital" doesn't automatically make a servo good for the device.

## What to Check Before Buying

Before buying a servo, check:

- positional or continuous rotation;
- operating voltage;
- required current and stall current if listed;
- torque;
- rotation speed;
- angle range;
- gearbox material;
- case size;
- connector type;
- wire length;
- operating temperature;
- availability of technical description or reasonable specs.

For a small flag you can use a microservo. For a damper with a seal, lock or lever in a warm chamber, it's better not to choose the cheapest servo without specs.

## Typical Errors

- powering servo from GPIO;
- powering from a weak board 5V pin;
- forgot common ground with separate power;
- trusted wire colors without checking;
- mixed up positional servo and continuous rotation servo;
- didn't account for stall current;
- placed servo against a mechanical stop;
- used angle `0` or `180` when the mechanism safely moves only in a narrow range;
- chose servo by size only, not calculating torque;
- put plastic gears where impact or jamming is possible;
- placed servo next to heater without temperature check.

## Main Point

A servo is a convenient component for dampers, locks and small mechanisms, but it needs normal power and careful mechanics. A signal from the controller only sets the position, and all motor current goes through the power line.

Before using, check servo type, voltage, torque, current, angle range and mechanical behavior at end positions.

## Reference Materials

- [SparkFun: Hobby Servo Tutorial](https://learn.sparkfun.com/tutorials/hobby-servo-tutorial) - basic explanation of hobby servo structure, signal, power and typical problems.
- [SparkFun: Basic Servo Control for Beginners](https://learn.sparkfun.com/tutorials/basic-servo-control-for-beginners/servo-motor-basics) - table of typical wire colors, power, stall current and control signal range.
- [Pololu: Electrical characteristics of servos](https://www.pololu.com/blog/16/electrical-characteristics-of-servos-and-introduction-to-the-servo-control-interface) - useful explanation of servo currents and why stall current matters for power selection.
- [Adafruit: If the Servo Misbehaves](https://learn.adafruit.com/adafruit-arduino-lesson-14-servo-motors/if-the-servo-misbehaves) - practical description of power drop and capacitor next to servo.
- [Arduino Servo Library Reference](https://www.arduino.cc/reference/en/libraries/servo/) - official Servo library for Arduino approach and standard/continuous rotation servo description.
