# Crimping connectors

Crimping is a method to connect a wire to a terminal or contact without soldering.

A good crimp provides:

- electrical contact;
- mechanical wire retention;
- insulation support;
- repeatability;
- convenient assembly and maintenance.

A poor crimp can get hot, fall apart, cause random errors and look almost normal.

## Why crimping is often better than soldering

For connectors and terminals, crimping is often better than soldering because:

- the wire stays flexible;
- the contact is designed by the manufacturer;
- insulation is retained;
- the joint better handles vibration;
- the connector can be disassembled and serviced;
- no risk of melting plastic connector body during soldering.

Soldering is good for pads and wires, but should not replace a proper contact in a connector if the manufacturer intended crimping.

## Types of terminals and connectors

In simple devices you often find:

- Dupont - weak signal connections for breadboards;
- JST-XH/JST-PH and similar - sensors, fans, small modules;
- ferrules - tips for multi-strand wire in screw terminals;
- Faston - flat terminals for some power connections;
- ring and spade terminals;
- screw terminals;
- board-mounted terminal blocks.

Each type requires its own contact, its own wire gauge and its own tool.

## You need the right tool

Pliers are not a crimping tool.

You can squeeze a contact so it seems to hold, but you won't get a proper crimp.

For good crimping, you need:

- a terminal for the correct wire gauge;
- correct strip length;
- correct tool matrix;
- correct contact position in the matrix;
- separate zones for strand and insulation crimp;
- no damaged strands.

Professional connector manufacturers provide crimp specifications, crimp height, strip length and pull force. For DIY assembly you don't always have full control, but the principle is the same: contact, wire and tool must match each other.

## Open barrel crimp

Many small contacts, like JST or Dupont, have two pairs of "wings":

- one pair crimps the bare conductor;
- the other pair holds the insulation.

Good result:

- the conductor is visible in the correct zone;
- insulation is held by the rear wings;
- the exposed length is not too long;
- conductor strands don't stick out;
- the contact is not skewed;
- the contact enters the connector body and locks in place.

If insulation entered the conductor crimp zone, electrical contact will be poor.

If only the conductor is crimped and insulation is not held, the wire may break when moved.

## Ferrules

For multi-strand wire in a screw terminal, ferrules are often useful.

They:

- gather all strands together;
- prevent strands from separating;
- improve seating in the terminal;
- reduce risk that some strands are left outside;
- make the joint neater.

This is especially useful for power wires, terminal blocks and assemblies that will be serviced.

But ferrules also must match the wire gauge and be crimped with the right matrix.

## How to check a crimp

After crimping, verify:

- the contact doesn't move on the wire;
- insulation is held;
- the conductor doesn't pull out;
- no strands are cut;
- the exposed length is not too long;
- the contact enters the connector body;
- the lock clicks in place;
- the wire withstands gentle pulling.

A gentle pull test is useful: carefully pull the wire. It should not come out of the contact.

No need to pull with all your strength. The goal is to find obviously bad crimps before installation.

## Why poor crimps get hot

A poor crimp creates high resistance.

Under current this becomes heat.

First the terminal might just be warm. Then plastic darkens, contact gets worse, heat increases.

This is especially dangerous for:

- heaters;
- fans with significant current;
- LED strips;
- power supplies;
- SSR/MOSFET circuits;
- mains connections.

If a terminal gets hot, turn off power and redo the connection.

## Dupont is not for power

Dupont is convenient for breadboards and weak signals.

But it cannot be used as a proper power connector for:

- a heater;
- device power;
- a powerful LED strip;
- mains parts;
- a motor or servo with large current.

Even if the connector physically fits the pins, that doesn't mean it is rated for the needed current, vibration and heat.

## Common errors

- crimped with pliers;
- chose the wrong gauge terminal;
- stripped too much insulation;
- stripped too little insulation;
- crimped insulation instead of the conductor;
- didn't crimp the insulation support;
- cut some strands;
- contact didn't lock in the body;
- power line held on Dupont;
- wrong ferrule gauge;
- didn't do a pull test;
- terminal gets hot but device keeps running.

## The essentials

- Crimping is both electrical contact and mechanical retention.
- Contact, wire and tool must match each other.
- Pliers don't replace a crimping tool.
- For multi-strand wire in a screw terminal, ferrules are often useful.
- Poor crimps can get hot and be dangerous.
- Power parts should not rely on weak breadboard connectors.

## Reference materials

- [Molex: Quality Crimp Handbook](https://www.molex.com/content/dam/molex/molex-dot-com/products/automated/en-us/commercialcrimpbookpdf/638/63800/TM-638000029-001.pdf?inline=) - detailed crimp quality reference, pull force, conductor and insulation crimp.
- [Molex: Industrial Crimp Quality Handbook](https://www.molex.com/content/dam/molex/molex-dot-com/products/automated/en-us/industrialcrimpbookpdf/640/64016/TM-640160065-001.pdf?inline=) - visual inspection of open and closed barrel crimp, strip length, wire brush and common defects.
- [JST: Application Tooling Guide, Crimp Style](https://www.jst.com/resources/application-tooling-guide/crimp-style/) - example of how specific JST contacts need specific tools, strip length and tensile specs.
- [American Electrical: Wire Ferrules](https://www.americanelectrical.com/wire-ferrules/) - why ferrules are useful for multi-strand wire in terminal blocks.
- [TE Connectivity: Wire Splices](https://www.te.com/en/products/terminals-splices/splices.html) - industrial crimp/splice connection types and why crimping is engineered separately, not random squeezing.
