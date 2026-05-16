# RFID y NFC

RFID is radio-frequency identification. NFC is a related technology for very short range, often on frequency `13.56 MHz`.

In a simple DIY device, it's a way to read a card, keychain, sticker or tag without wired contact. For example, a user brings a filament spool tag, and the device selects the material profile.

The main mistake is thinking "RFID" means universal compatibility. In practice, you need frequency match, tag type, reader microchip, library, interface, power and antenna placement all to line up.

## Dónde It's Used

In iDryer-like projects, RFID/NFC can be used for:

- identifying a filament spool;
- selecting a material profile;
- linking settings to a tag;
- service access;
- user action confirmation;
- consumable tracking;
- experiments with tags on containers, spools or cassettes.

For material profile selection, often just reading the tag's UID and storing a `UID -> material` table is enough. But this approach must have a manual fallback: if the tag doesn't read, the user can still manually choose the profile.

## RFID and NFC in Simple Terms

RFID is a broad term. It includes different frequencies, standards, ranges and tag types.

NFC usually means near-field communication at `13.56 MHz`, compatible with part of the RFID ecosystem. NFC is known from bank cards, phones, NTAG stickers and MIFARE cards, but this doesn't mean any NFC reader reads any card and any data.

For small DIY devices, `13.56 MHz` modules are most common:

- RC522 / MFRC522;
- PN532;
- ready-made USB/UART RFID/NFC readers;
- NFC modules with SPI, I2C or UART.

There are other RFID systems, like `125 kHz` access cards or UHF RFID. They are not compatible with `13.56 MHz` NFC modules.

## RC522

RC522 is a cheap and common `13.56 MHz` module for cards and tags. It's often used with Arduino and ESP32.

Pros:

- cheap;
- many examples;
- suitable for simple UID reading;
- usually connects via SPI.

Cons:

- often works only with `3.3V` power and logic;
- cheap module quality varies;
- read range is small;
- card type support is limited;
- pin `SDA` on the board often means `SS`/`CS` for SPI, not I2C `SDA`.

RC522 works if you just need to read UID from MIFARE-like cards or keychains at short range. For broader NFC tasks, PN532 is usually more convenient.

## PN532

PN532 is a more flexible NFC/RFID controller. Many PN532 modules can work via:

- SPI;
- I2C;
- UART.

But the chosen interface usually needs to be set physically on the board: jumpers, DIP switches or soldering. You can't connect a module via I2C if it's set to SPI mode.

PN532 is often chosen if you need:

- more interface options;
- better NFC scenario support;
- work with different tag types;
- Python/CircuitPython/Raspberry Pi scenarios;
- better documented module.

But PN532 isn't a magic universal reader either. You need to check specific card types, library and working mode.

## Frequency and Tag Type

The tag must match the reader.

Before buying tags, check:

- frequency: `13.56 MHz`, `125 kHz` or other;
- type: MIFARE Classic, NTAG213/215/216, ISO14443A or other;
- whether you only need to read UID;
- whether you need to read/write custom data;
- whether your chosen library supports needed operations;
- whether you can physically place the tag on a spool or case.

If the task is to select a material profile, usually just reading UID and storing the profile separately is simpler. Writing data inside the tag complicates the project: you need to think about data format, compatibility, write protection and write errors.

## UID - Not Security

A card or tag's UID is convenient to use as an identifier. But UID is not reliable protection.

For a spool profile, this is normal: if UID is known, select the profile. An error isn't critical because the user can check the material by hand.

For access to dangerous functions, service modes or unlocking a heater, UID alone is weak. Some UIDs can be copied or faked, and some cards have known security limits.

Practical rule:

- UID is good for convenience and consumable identification;
- UID should not be the only protection for dangerous modes;
- for heaters and power parts, always need separate safety checks.

## Power and Logic Levels

Many RFID/NFC modules are rated for `3.3V` logic. This is especially important for RC522 and PN532 breakout modules.

Check:

- module power voltage;
- logic level on SPI/I2C/UART;
- whether the board has a regulator;
- whether signal lines have level matching;
- whether I2C pull-up resistors are needed;
- whether common ground with the controller is needed.

The presence of `5V` pin on a module board doesn't always mean signal lines tolerate `5V`. Some modules can be powered from `5V` through a regulator, but logic stays `3.3V`.

## Connection Interface

An RFID/NFC module can connect via SPI, I2C or UART.

SPI:

- fast and common;
- requires `SCK`, `MOSI`, `MISO`, `CS`;
- on RC522, pin `SDA` often actually means `CS`;
- important not to mix up `MOSI` and `MISO`.

I2C:

- uses `SDA` and `SCL`;
- can share bus with other devices;
- needs correct pull-up resistors;
- important to check address and selected module mode.

UART:

- uses `TX` and `RX`;
- `TX` of one device goes to `RX` of another;
- convenient for some ready-made readers;
- needs matching speed and protocol.

Detailed RC522 SPI connection is in the practical section: [Connecting an RFID reader](../05-practical-guides/05-connecting-an-rfid-reader.md).

## Antenna and Case

RFID/NFC works through an antenna. On small modules, it's usually printed right on the board.

Reading is affected by:

- antenna size;
- tag orientation;
- distance;
- case plastic;
- metal nearby;
- wires and power lines nearby;
- module power;
- tag type;
- where the user brings the card.

Metal near the antenna can sharply worsen reading. If the reader is mounted near the printer's metal frame, screws, screen, power supply or aluminum panel, range can become much worse.

For the case, it's better to make a clear zone: "bring tag here". Don't expect the tag on a spool to always auto-read through plastic, air, shaft, holder and nearby parts.

## Device Logic

RFID should improve convenience, not break control.

Normal logic for a spool:

1. User brings a tag.
2. Device reads UID.
3. UID is looked up in profile table.
4. If UID is found, material profile is suggested.
5. User can confirm or change profile.
6. If UID is not found or didn't read, manual selection is available.

Bad logic:

- device can't start without a tag;
- unknown tag selects random profile;
- read error silently keeps old profile;
- profile changes without user confirmation;
- UID is the only protection for a service mode.

For a heater, it's especially important that profile selection doesn't bypass temperature limits, sensors and emergency protection.

## Qué to Check Before Buying

Before buying, check:

- module frequency;
- supported tag types;
- interface: SPI, I2C, UART, USB;
- power voltage;
- logic levels;
- availability of level matching;
- availability of documentation and pinout;
- how interface is selected on the board;
- whether there's a library for your controller;
- antenna size;
- tag type and size;
- expected range in a real case;
- whether manual fallback selection is possible.

For a first project, choose a module with good documentation and examples, not the cheapest without a schematic.

## Típicos Errors

- bought `125 kHz` card for `13.56 MHz` reader;
- connected `3.3V` RC522 to `5V` power or logic;
- took pin `SDA` on RC522 for I2C `SDA`;
- mixed up `MOSI` and `MISO`;
- forgot `CS`/`SS` in SPI;
- set one interface on PN532 with jumpers but connected a different one;
- didn't place I2C pull-ups where needed;
- put antenna near metal;
- tested reading on bench but didn't test in case;
- made RFID the only way to select profile;
- use UID as reliable access protection;
- didn't handle "tag didn't read" situation.

## Principal Point

RFID/NFC is useful for spool identification, material profile selection and simple service input. But it's not a universal reader for any cards and not a reliable security system by itself.

First choose the frequency and tag types, then the module, interface, power and antenna location. Then test reading in a real case and definitely keep manual fallback selection.

## Referencia Materials

- [Adafruit: PN532 RFID/NFC Breakout Wiring](https://learn.adafruit.com/adafruit-pn532-rfid-nfc/breakout-wiring) - PN532 connection, SPI/I2C/UART selection and warning about `3.3V` logic.
- [Adafruit: PN532 RFID/NFC guide, single page](https://learn.adafruit.com/adafruit-pn532-rfid-nfc?view=all) - complete PN532 guide, CircuitPython/Python, interfaces and SEL jumper setup.
- [Adafruit PN532 product page](https://www.adafruit.com/product/364) - description of PN532 module, supported interfaces and NFC/RFID capabilities.
- [NXP: MFRC522 Standard performance MIFARE and NTAG frontend](https://www.nxp.com/products/rfid-nfc/nfc-hf/nfc-readers/standard-performance-mifare-and-ntag-frontend:MFRC52202HN1) - MFRC522/RC522 microchip page and its purpose for `13.56 MHz` MIFARE/NTAG scenarios.
- [DigiKey: MFRC522 Datasheet by NXP](https://www.digikey.com/htmldatasheets/production/993456/0/0/1/mfrc522.html) - technical description of MFRC522: `13.56 MHz` reader/writer, ISO/IEC 14443 A/MIFARE/NTAG support and communication interfaces.
