# 焊接

焊接用于当你需要可靠地连接电线到焊盘、焊接连接器、修复断开的连接或组装小模块时。

但焊接不应该替代电线会拉动、振动或发热的地方的适当的连接器、端子或机械紧固。

## When soldering is appropriate

Soldering is good for:

- soldering wires to a board;
- installing a pin header;
- repairing a broken wire;
- connecting a small module;
- soldering a thermistor or signal wire;
- prototype assembly.

Soldering is not the best choice for:

- frequently disassembled connections;
- power terminals without strain relief;
- wires that will move;
- connections inside hot zones without protection;
- mains 110-230V AC parts without proper terminals and enclosure.

## Minimal kit

For proper soldering you need:

- a soldering iron with temperature control;
- solder;
- flux;
- soldering iron stand;
- sponge or brass wire for cleaning the tip;
- wire cutters;
- wire stripper;
- tweezers or third hand;
- heat shrink tubing;
- isopropyl alcohol for cleaning if needed.

A soldering iron without a stand is a bad idea. A hot tip easily burns your hand, wire, enclosure or table.

## Tin a wire

Tinning a wire means coating the exposed strands with a thin layer of solder.

Procedure:

1. Strip a bit of insulation.
2. Twist the strands together if the wire is multi-strand.
3. Apply flux if solder doesn't flow well.
4. Heat the wire with the soldering iron.
5. Apply some solder to the heated area.
6. Let the solder flow across the strands.

Don't turn the wire end into a thick stiff blob. Tinning should be neat and thin.

## Solder a wire to a pad

Procedure:

1. Secure the board and wire.
2. Tin the pad.
3. Tin the wire.
4. Apply the wire to the pad.
5. Heat both the wire and pad simultaneously.
6. Let the solder melt and join the parts.
7. Remove the solder, then the iron.
8. Don't move the joint while the solder cools.

A good solder joint looks smooth and shiny or evenly dull, depending on the solder. It should not be a blob sitting on top that didn't wet the pad.

## Cold solder joints

A cold solder joint is where the solder didn't heat up properly and didn't flow normally.

Signs:

- rough surface;
- solder in a lump;
- wire moves;
- contact comes and goes;
- joint breaks with slight movement.

Cold solder joints are dangerous because they may work sometimes. In a heated or vibrating device, such a contact will degrade.

Usually a cold joint is fixed by reheating with flux until the solder flows properly.

## Overheated pad

If you heat a pad too long, it can lift off the board.

This especially affects:

- cheap modules;
- small pads;
- thin traces;
- multiple rework attempts;
- wires pulling on the pad.

If solder doesn't flow, you don't always need to heat longer. Often adding flux, cleaning the tip, using the right temperature or a larger tip helps.

## Flux

Flux helps solder wet the metal.

Without flux, solder often balls up and doesn't join parts well.

After soldering, some flux needs washing off. This depends on flux type:

- no-clean can often be left;
- water-soluble must be removed;
- active flux should not be left on the board.

If you don't know the flux type, use electronics-grade flux and read its description.

## Heat shrink and insulation

A soldered joint must be insulated.

For wires, heat shrink tubing is usually used.

Procedure:

1. Slide heat shrink over the wire before soldering.
2. Solder the wires.
3. Check the joint.
4. Slide the heat shrink into place.
5. Heat it gently.

Don't leave soldered joints exposed where they might touch the enclosure, another wire, a terminal or a fan.

## Strain relief

Solder doesn't like mechanical stress.

If a wire will pull, vibrate or move, you need strain relief:

- cable tie;
- clamp;
- strain relief connector;
- a silicone blob in a safe place;
- wire fastened to the enclosure;
- a connector instead of direct soldering.

Bad practice: the wire is held only by the solder pad. Over time it can tear the pad loose.

## Power wires

Power wires must be soldered extra carefully.

Verify:

- wire has the correct gauge;
- the joint is fully heated;
- no cold solder joints;
- no exposed strands;
- insulation is present;
- mechanical fastening is present;
- the joint is not next to a hot zone without protection.

For power lines, a proper terminal or connector is often better than soldering wires permanently.

## What to check after soldering

After soldering:

- inspect the joint;
- check that neighboring contacts are not shorted;
- use the multimeter to check the needed connection;
- verify no short between `+` and `GND`;
- gently pull the wire;
- confirm heat shrink covers the metal;
- check that the wire doesn't pull the pad.

## Common errors

- soldering with a dirty tip;
- not using flux;
- heating only the solder, not the pad and wire;
- making a solder blob;
- moving the wire while solder cools;
- overheating the pad;
- leaving an open joint without heat shrink;
- wire held only by solder;
- soldering power wire too thin with weak iron;
- using acid flux not meant for electronics.

## The essentials

- Good soldering requires heating both parts, not just dripping solder.
- Flux often solves poor wetting problems.
- Cold solder joints may work sometimes, so they are dangerous.
- A soldered joint must be insulated and mechanically relieved.
- For frequently disassembled and power connections, a connector or terminal is often better than soldering.

## Reference materials

- [SparkFun: How to Solder, Through-Hole Soldering](https://learn.sparkfun.com/tutorials/how-to-solder-through-hole-soldering) - tools, temperature, flux, good soldering and connection checking.
- [SparkFun: Soldering Your First Component](https://learn.sparkfun.com/tutorials/how-to-solder-through-hole-soldering/soldering-your-first-component) - basic rules: heating the pad and lead, solder application order, good joint shape.
- [Adafruit: Guide to Excellent Soldering](https://learn.adafruit.com/adafruit-guide-excellent-soldering) - practical soldering guide for electronics.
- [Adafruit: Common Soldering Problems](https://learn.adafruit.com/adafruit-guide-excellent-soldering/common-problems) - cold joints, overheating, too much solder and fixes.
- [NASA Workmanship: Soldered Electrical Connections](https://workmanship.nasa.gov/lib/insp/2%20books/links/sections/407%20Soldering.html) - reference material on solder joint quality and mechanical wire support.
