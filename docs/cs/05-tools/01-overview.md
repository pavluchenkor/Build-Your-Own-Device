# Nástroje

Tato sekce se nejedná o sběrání nástrojů.

Jedná se o minimální sadu, která vám pomůže bezpečně sestavit zařízení, ověřit připojení a najít jednoduché chyby bez hádání.

V domácích zařízeních kolem iDryeru a 3D tiskáren jsou nástroje potřebné pro praktické úkoly:

- zkontrolovat, zda je na napáječi přítomný 24V;
- pochopit, zda je plus a minus prohozeny;
- zkontrolovat spojitost na vodiči;
- testovat termistor;
- zjistit, zda signál UART dorazí;
- flashnout ovladač;
- vytvořit správný konektor;
- najít propady napájecího zdroje;
- pochopit, proč se ventilátor nebo topný prvek nerozsvítí.

## Minimální sada

Pro většinu jednoduchých staveb jsou užitečnými nástroji:

- multimetr;
- USB-UART nebo USB-TTL adaptér;
- páječka;
- kleští na seřízení konektorů;
- stříhač drátů a odstraňovač izolace;
- teplem smrštitelná trubice;
- správné svítidla a konektory;
- ST-Link, pokud pracujete s STM32;
- osciloskop nebo alespoň multimetr s čítačem frekvence pro složitější diagnostiku.

Ne všechno je třeba koupit najednou. Ale multimetr a správné drátové nástroje si obvykle rychle vrátí.

## Nástroje nenahrazují porozumění

Multimetr neučiní bezpečný díl sítě.

Páječka neopravuje špatné schéma.

Osciloskop není potřeba, pokud jsou plus a minus prohozeny.

Takže pořadí je:

1. Pochopit, co by mělo být připojeno.
2. Zkontrolujte napájecí zdroj.
3. Zkontrolujte zapojení.
4. Zkontrolujte senzory a signály.
5. Teprve potom hledejte složité problémy.

## Co bude v této sekci

- `02-multimeter.md` - měření stejnosměrného napětí, spojitost, odpor, pojistky a proč je měření proudu nebezpečnější.
- `03-usb-ttl-adapter.md` - USB-UART adaptéry, TX/RX/GND, logické úrovně 3,3V/5V, flashování a protokoly.
- `04-soldering.md` - pájení vodičů, podkladů, modulů, studené spoje, teplem smrštitelné trubice a ochrana před tahu.
- `05-crimping-connectors.md` - Dupont, JST, ferrule, Faston, svítidla a kontroly kvality zešroubování.
- `06-st-link.md` - ST-Link, STM32, SWD, zotavení desky po selhání flashování.
- `07-oscilloscope.md` - PWM, UART, propady napájecího zdroje, šum a kritické upozornění bezpečnosti na napětí sítě.

## Co stojí za to koupit správně

Jsou věci, na kterých byste neměli šetřit:

- multimetr se správnými sondy a režimem spojitosti;
- páječka s regulací teploty;
- kvalitní pájecí cín a flux;
- kleští na seřízení konektorů pro konkrétní svítidla;
- konektory a svítidla hodnocená pro potřebný proud;
- teplem smrštitelná trubice;
- vodiče správné tloušťky.

Špatné seřízení nebo slabá svítidla mohou způsobit více problémů než špatný firmware.

## Co nemůžete dělat

Nemůžete:

- měřit odpor v energizovaném obvodu;
- měřit proud stejně jako měříte napětí;
- podráždit multimetr do 110-230V AC bez porozumění bezpečnosti;
- pájet díl se sítí „nějak";
- používat Dupont pro topný prvek;
- měnit vodiče, když je napájení zapnuté;
- ponechávat otevřené části sítě na stole;
- myslet, že pokud vodič "drží", kontakt je dobrý.

## Podstatné

- Multimetr je první diagnostický nástroj.
- USB-UART je potřeba pro protokoly, flashování a komunikaci se zařízeními UART.
- Pájení a seřízení jsou různé úkoly a pro konektory je seřízení často lepší.
- ST-Link je potřeba, když pracujete s STM32 a SWD.
- Osciloskop není potřeba všem, ale rychle ukazuje signály, propady a šum.
- Pro díl se sítí záleží na kvalitě kontaktu, tloušťce vodiče a bezpečnosti více než na vzhledu montáže.

## Referenční materiály

- [SparkFun: How to Use a Multimeter](https://learn.sparkfun.com/tutorials/how-to-use-a-multimeter/all) - základy multimetru: napětí, proud, odpor, spojitost.
- [SparkFun: Troubleshooting Tips](https://learn.sparkfun.com/tutorials/sparkfun-troubleshooting-tips/hardware-checks) - kontroly hardwaru pro napájení, připojení a teplo.
- [SparkFun: Serial Communication](https://learn.sparkfun.com/tutorials/serial-communication) - UART a základní logika sériové komunikace.
- [Adafruit: Guide to Excellent Soldering](https://learn.adafruit.com/adafruit-guide-excellent-soldering) - praktický průvodce pájením a kvalitou spojení.
- [STMicroelectronics: ST-LINK/V2 User Manual](https://www.st.com/resource/en/user_manual/um1075-stlinkv2-incircuit-debuggerprogrammer-for-stm8-and-stm32-stmicroelectronics.pdf) - oficiální dokumentace ST-Link a SWD/SWIM.
