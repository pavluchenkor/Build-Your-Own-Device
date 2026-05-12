# Controller Mistakes

A controller is not a universal box where you can plug everything directly.

It reads sensors, outputs control signals, and communicates with the host. But power loads must be powered through appropriate outputs, MOSFETs, relays, SSRs, or drivers.

## Symptoms

Typical signs of controller or connection problems:

- board not detected via USB;
- firmware does not start;
- pins do not respond;
- controller reboots;
- controller heats up significantly;
- board stops working after module is connected;
- ESP32 loses Wi-Fi when load is turned on;
- sensor not visible though power is present;
- Klipper does not connect to MCU;
- commands work on wrong pin.

## Wrong Controller Chosen

Before choosing a board you must understand the task.

For a simple autonomous Wi-Fi device, ESP32 can be a good choice.

For an additional MCU in Klipper, it is often more practical to look at:

- RP2040;
- STM32;
- ready-made 3D printer board.

Arduino Uno/Nano are useful for learning and simple experiments, but for a new serious device around a printer you quickly run into limitations.

The mistake is to choose a board only because "it is popular", without checking:

- number of needed pins;
- logic levels;
- power supply;
- firmware support;
- USB/UART/CAN availability;
- support for needed libraries;
- output current;
- development environment.

## ESP32 as Klipper MCU

ESP32 is useful as a separate IoT/Wi-Fi device.

But do not automatically expect ESP32 to be the best choice as a Klipper MCU.

If the goal is integration with Klipper as an additional MCU, first look at official and proven options for Klipper. For new hardware extensions it is often simpler and more reliable to use RP2040 or STM32.

ESP32 is good if the device should:

- work autonomously;
- have Wi-Fi;
- provide data via MQTT or HTTP;
- have web interface;
- communicate with Home Assistant;
- work separately from Klipper.

## 3.3V and 5V Logic

Many modern controllers work with 3.3V logic.

For example:

- ESP32;
- RP2040;
- many STM32.

The mistake is to apply a 5V signal to an input designed only for 3.3V.

This can:

- immediately damage the pin;
- damage the controller later;
- cause unstable operation;
- break a module that seemed okay.

Before connecting verify:

- module power voltage;
- input/output logic level;
- is there a level converter;
- does input accept 5V;
- what is written in technical description.

## GPIO Does Not Power a Load

GPIO is a signal pin.

It must not power:

- fan;
- servo;
- heater;
- LED strip;
- relay without driver;
- solenoid;
- motor.

GPIO can send a command. Load current must go through a power output, MOSFET, driver, relay, or separate module.

If load is connected directly to GPIO, you can damage the pin or the entire board.

## No Common GND

A controller can drive an external module only if they have a common reference level.

Typical mistake:

- servo powered from separate 5V supply;
- signal comes from controller;
- `GND` not connected;
- servo jerks or does not respond.

Same with MOSFET modules, PWM fans, some sensors, and external boards.

## Incorrect Firmware

Board may be okay, but firmware does not fit.

Errors:

- firmware flashed for wrong microcontroller;
- chose wrong bootloader;
- mixed up USB and UART firmware;
- chose wrong serial port;
- Klipper specified wrong device path;
- pins in config do not match board;
- did not restart firmware/host after flashing.

Before flashing you must know exactly the board and microcontroller model.

## Pin Exists on Schematic But Not Suitable

Not every pin is the same.

Pins can have restrictions:

- input only;
- used by USB/UART/SPI;
- used during boot;
- related to boot mode;
- does not support needed PWM;
- pulled up or down;
- conflicts with another module.

If pin behaves strangely, check board documentation, not just GPIO number.

## What to Check

Mini-checklist:

1. Is the right board chosen for the task?
2. What power does the board need?
3. What logic: 3.3V or 5V?
4. Is there common `GND` with external modules?
5. Is load not powered from GPIO?
6. Does board support needed interface?
7. Is selected pin not used?
8. Is firmware correct?
9. Is board visible via USB?
10. Does configuration match board pinout?

## What Not to Do

You cannot:

- apply 5V to 3.3V input without checking;
- connect load directly to GPIO;
- flash random firmware of a "similar" board;
- change wiring under power;
- assume any GPIO fits any task;
- ignore controller heating;
- connect external modules without common ground when needed.

## Key Points

- Controller controls but does not directly power a load.
- 3.3V and 5V logic must be compatible.
- GPIO is a signal, not power supply.
- For Klipper MCU you often look at RP2040/STM32, ESP32 is more convenient as autonomous Wi-Fi device.
- Firmware and pinout must match the actual board.
- If board heats up or stops being detected, turn off power and find the connection error.

## References

- [Klipper: Installation](https://www.klipper3d.org/Installation.html) - general process of preparing and flashing MCU for Klipper.
- [Klipper: Config Reference, MCU](https://www.klipper3d.org/Config_Reference.html#mcu) - `[mcu]` section, serial/CAN connection, and additional MCUs.
- [Arduino: Digital Pins](https://docs.arduino.cc/learn/microcontrollers/digital-pins/) - basic explanation of digital pins as inputs/outputs, not power supply.
- [Espressif ESP32 Datasheet](https://www.espressif.com/sites/default/files/documentation/esp32_datasheet_en.pdf) - official electrical specifications of ESP32.
- [Raspberry Pi Pico Datasheet](https://datasheets.raspberrypi.com/pico/pico-datasheet.pdf) - official data on RP2040/Pico, power, and GPIO.
