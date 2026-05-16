# Začínáme

Už tisknete na 3D tiskárně a chcete si postavit sušičku filamentu. Ale když otevřete schéma, hned se objeví otázky: jaký zdroj, kam jde zem, MOSFET nebo SSR, proč je třeba chladič. Tato sekce odpovídá na tyto otázky postupně — od prvního výpočtu proudu až k funkčnímu zařízení.

Po této sekci budete rozumět, co budujete, proč právě tímto způsobem, kde může být nebezpečí a jak zkontrolovat zařízení před jeho zapnutím.

Sekce vás postupně vede od jednoduchých konceptů k reálným výsledkům.

Cesta zde jde od jednoduchého ke složitému:

1. Nejprve pochopte výkon, proud, zátěž a základní bezpečnost.
2. Pak zjistěte, jaké řadiče existují a který si vybrat.
3. Pak pochopte základní součástky: topidlo, ventilátor, senzory, displeje, RFID a váhy.
4. Pak se naučte používat minimální nástroje: multimetr, USB-UART, páječku, kleště na krimpování.
5. Pak přejděte na praktické zapojení.
6. Pak přemýšlejte o krytu a 3D tištěných dílech.
7. Nakonec mějte po ruce seznam běžných chyb a kontrolní seznam diagnostiky.

Hlavní myšlenka:

Nemusíte chápat celou elektroniku najednou. Stačí jít krok za krokem a pokaždé pochopit další malý krok.

Co by vám tato sekce měla dát:

- pochopení, jak se liší nízkonapěťové obvody `12V`/`24V DC` od síťového `110-230V AC`;
- schopnost přibližně vypočítat proud zátěže;
- pochopení, kdy potřebujete MOSFET, SSR nebo relé;
- pochopení, jak se v praxi liší ESP32, Arduino, RP2040 a STM32;
- pochopení, proč je pro Klipper MCU lepší podívat se na RP2040 nebo STM32;
- základní pochopení senzorů, ventilátorů, topidel a displejů;
- minimální diagnostické dovednosti s multimetrem;
- pochopení, které tištěné díly se mohou nacházet blízko tepla;
- seznam chyb, které je lépe neopakovat.

Co tato sekce nedělá:

- nenahrazuje elektrikáře při práci s `110-230V AC`;
- neučí hlubokého návrhu obvodů;
- nesnaží se vysvětlit veškerou fyziku;
- nedává povolení skládat nebezpečná zařízení bez pochopení bezpečnosti.

Jak číst:

- pokud je téma nové — jděte v pořadí;
- pokud jste již stavěli zařízení — otevřete potřebnou sekci jako referenci;
- pokud zařízení nefunguje — nejdřív se podívejte na `08-common-mistakes`;
- pokud pracujete s `110-230V AC` — nejdřív přečtěte vše týkající se bezpečnosti, SSR, vodičů, svorek a ochranného uzemnění.

## Referenční materiály

- [SparkFun: Voltage, Current, Resistance, and Ohm's Law](https://learn.sparkfun.com/tutorials/voltage-current-resistance-and-ohms-law) - základní koncepty napětí, proudu, odporu, uzavřeného obvodu a Ohmova zákona.
- [SparkFun: Troubleshooting Tips](https://learn.sparkfun.com/tutorials/sparkfun-troubleshooting-tips/all) - praktický postup počáteční diagnostiky: napájení, spojení, polarita, páječná spojení, kabely a úbytek napětí.
- [Fluke: How to Measure Resistance with a Digital Multimeter](https://www.fluke.com/en-us/learn/best-practices/test-tools-basics/digital-multimeters/how-to-measure-resistance) - proč se měření odporu provádí bez napájení a proč je potřeba multimetr ke kontrole součástek.
- [OSHA: Electrical Incidents - Grounding](https://www.osha.gov/etools/construction/electrical-incidents/grounding) - proč je třeba ochranné uzemnění a proč práce se síťovým napětím vyžaduje samostatnou bezpečnostní disciplínu.

## Podívejte se také

- [Výpočet zátěže 24V](../01-electronics-basics/01-load-calculation-24v.md) - první praktické téma o napětí, proudu, výkonu a rezervě zdroje.
- [Běžné součástky](../03-common-components/01-overview.md) - přehled dílů, které se nejčastěji vyskytují v jednoduchých zařízeních.
- [Nástroje](../05-tools/01-overview.md) - co potřebujete ke kontrole, nahrání, pájení a diagnostice.
- [Praktické příručky](../06-practical-guides/01-connecting-a-fan.md) - příklad prvního bezpečného připojení zátěže přes řadič.
- [Běžné chyby](../08-common-mistakes/01-overview.md) - na co se podívat, pokud se zařízení nezapne, přehřívá se, dělá hluk nebo se chová nestabilně.
