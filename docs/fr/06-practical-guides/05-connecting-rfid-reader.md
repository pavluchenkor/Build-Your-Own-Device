# Connexion d'un Lecteur RFID

Un lecteur RFID/NFC vous permet de lire une carte, une étiquette, ou une clé sans contact filaire.

Dans les appareils de type iDryer, cela peut être utile pour l'identification de bobine, la sélection de profil de matériau, l'accès au service, ou les expériences de suivi des consommables.

Erreur principale : achetez un « module RFID » et supposez que n'importe quelle carte lira à partir de n'importe quelle distance sur n'importe quel contrôleur. En réalité, vous devez vérifier la fréquence, le type d'étiquette, l'interface, l'alimentation, les niveaux logiques et le placement de l'antenne.

## Modules populaires

Les courants incluent :

- RC522 / MFRC522 ;
- PN532 ;
- lecteurs RFID prêts à l'emploi USB/UART ;
- modules NFC avec I2C, SPI, ou UART.

Pour les projets d'imprimante 3D simples, les modules et étiquettes 13.56 MHz sont les plus courants : cartes, clés, étiquettes compatibles NTAG/MIFARE.

## Ce qu'il faut vérifier avant de connecter

Avant de connecter, trouvez :

- fréquence du module ;
- types de carte et d'étiquette supportés ;
- interface : SPI, I2C, ou UART ;
- tension d'alimentation ;
- niveaux logiques ;
- brochage de la carte ;
- sélection d'interface via cavaliers ou ponts de soudure ;
- distance de lecture ;
- exigences d'antenne et de placement.

Si le module est évalué pour `3.3V`, vous ne pouvez pas simplement le connecter à la logique `5V` sans vérification. Certaines cartes ont des régulateurs de tension mais manquent de décalage de niveau sur les lignes de signal.

## RC522 : connexion SPI typique

Les modules RC522 bon marché fonctionnent généralement sur `3.3V` et se connectent le plus couramment via SPI.

Lignes typiques :

- `VCC` - alimentation `3.3V` ;
- `GND` - masse ;
- `SCK` - signal d'horloge SPI ;
- `MOSI` - données du contrôleur au module ;
- `MISO` - données du module au contrôleur ;
- `SDA`, `SS`, ou `CS` - sélection de puce SPI ;
- `RST` - réinitialisation ;
- `IRQ` - interruption, souvent inutilisée dans les projets simples.

![Module RFID RC522 (MFRC522) pour lire les cartes 13.56 MHz](../../../img/06-practical-guides/05-rfid-rc522-module.jpg)

*Source: [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:RFID-RC522_photo.jpg), Giacomo Alessandroni, CC BY-SA 4.0*

Les noms de broches peuvent différer. Par exemple, sur RC522, la broche `SDA` signifie souvent `SS`/`CS` pour SPI, pas la ligne I2C `SDA`. C'est une source courante de confusion.

## PN532 : SPI, I2C, ou UART

PN532 est un module plus flexible. Selon la carte, il peut fonctionner via :

- SPI ;
- I2C ;
- UART.

Mais vous ne pouvez pas simplement connecter n'importe quelles broches. Sur de nombreuses cartes PN532, l'interface est sélectionnée par des cavaliers, des commutateurs DIP, ou des ponts de soudure.

Avant de connecter, vérifiez :

- quelle interface est physiquement sélectionnée sur la carte ;
- quelles broches correspondent à l'interface sélectionnée ;
- si des résistances de tirage sont nécessaires pour I2C ;
- si une résistance de tirage ou une broche de réinitialisation est nécessaire ;
- si les niveaux logiques sont compatibles avec le contrôleur.

Si la carte dit « logique 3.3V », ne la connectez pas directement à GPIO 5V.

## Masse commune

Comme les autres modules, la masse commune est nécessaire.

Si le module RFID est alimenté par une source et le contrôleur par une autre, leur `GND` doit être connecté.

Sans masse commune, SPI/I2C/UART peut ne pas fonctionner ou fonctionner de manière instable.

## L'étiquette doit correspondre au lecteur

RFID/NFC n'est pas une norme universelle unique.

Un module ne peut lire physiquement que les étiquettes supportées par sa puce et sa bibliothèque.

Vérifiez :

- fréquence de l'étiquette ;
- type de carte ou de clé ;
- le module supporte-t-il MIFARE, NTAG, ISO14443A, ou le type nécessaire ;
- avez-vous seulement besoin de lire UID ou aussi de lire/écrire des données ;
- la bibliothèque choisie supporte-t-elle l'opération nécessaire.

Pour la sélection simple de profil de matériau, lire seulement l'UID de l'étiquette et stocker le mappage UID -> matériau dans le firmware ou l'hôte est généralement suffisant.

## Distance de lecture

La distance de lecture pour les petits modules RFID/NFC est généralement courte.

Les résultats dépendent de :

- taille de l'antenne ;
- type d'étiquette ;
- orientation de l'étiquette ;
- distance ;
- plastique du boîtier ;
- métal à proximité ;
- interférence ;
- alimentation du module.

Le métal près de l'antenne peut drastiquement aggraver la lecture. Si le lecteur est monté dans un sèche-linge, une chambre, ou un support de bobine, testez la distance dans l'assemblage réel, pas juste sur le banc.

## Où placer le lecteur

Pour une bobine de filament, il est préférable de placer le lecteur RFID/NFC où l'utilisateur apporte intentionnellement l'étiquette.

Ne concevez pas la logique en supposant que l'étiquette lira toujours automatiquement.

Options pratiques :

- zone « apportez l'étiquette ici » sur le boîtier ;
- emplacement près du support de bobine ;
- zone de service pour la carte d'accès ;
- panneau séparé avec courte distance de lecture.

Si l'étiquette est sur la bobine, testez avec différentes bobines, orientation d'étiquette différente, plastique différent et proximité de métal.

## Premier démarrage

Avant l'intégration :

1. Connectez le module sur le banc.
2. Exécutez un exemple de la bibliothèque pour votre module.
3. Vérifiez que la carte ou l'étiquette lit stablement.
4. Enregistrez l'UID de plusieurs étiquettes.
5. Vérifiez que les cartes non supportées ne cassent pas la logique.
6. Montez le module dans le boîtier et testez de nouveau.

À ce stade, ne construisez pas des systèmes de profil complexes tout de suite. D'abord, obtenez une lecture UID stable.

## Exemple de logique d'appareil

Pour le profil de matériau, la logique simple peut être :

1. L'utilisateur apporte l'étiquette.
2. L'appareil lit l'UID.
3. L'UID est recherché dans une table.
4. Si UID est connu, le profil de matériau est sélectionné.
5. Si UID est inconnu, l'appareil demande la sélection manuelle du profil.

RFID ne doit pas être la seule méthode de contrôle. Vous avez besoin d'une sauvegarde manuelle : profil dans le menu, bouton, écran, ou paramètre d'interface.

## Ce qu'il faut vérifier après l'assemblage

Vérifiez :

- le module reçoit la tension correcte ;
- les niveaux logiques sont compatibles avec le contrôleur ;
- l'interface correcte est sélectionnée ;
- `MOSI`, `MISO`, `SCK`, `CS` ne sont pas permutés pour SPI ;
- `SDA`, `SCL` ne sont pas permutés pour I2C ;
- `TX` et `RX` sont correctement croisés pour UART ;
- la masse commune existe ;
- les réinitialisation/IRQ sont connectées comme la bibliothèque l'exige ;
- les étiquettes du bon type lisent ;
- la distance de lecture est normale dans le boîtier ;
- le métal et les fils ne bloquent pas l'antenne ;
- l'appareil fonctionne normalement si l'étiquette n'est pas lue.

## Erreurs courantes

- connexion du RC522 3.3V à l'alimentation 5V ou la logique 5V ;
- confusion du RC522 `SDA` avec I2C `SDA` ;
- oubli de `CS`/`SS` sur SPI ;
- permutation de `MOSI` et `MISO` ;
- sélection d'une interface sur PN532 avec des cavaliers mais câblage d'une autre ;
- utilisation du type de carte non supportée ;
- placement de l'antenne à côté du métal ;
- test de distance de lecture sur le banc mais pas dans le boîtier ;
- faire du RFID la seule méthode de sélection de profil ;
- stockage de la logique importante seulement dans UID sans vérification d'erreur de lecture.

## Points clés

- Le module RFID/NFC doit être choisi pour des étiquettes et une interface spécifiques.
- RC522 a généralement besoin de `3.3V` et SPI.
- PN532 peut fonctionner via SPI, I2C, ou UART, mais l'interface doit être sélectionnée sur la carte.
- La masse commune est requise.
- Le métal près de l'antenne peut grandement aggraver la lecture.
- Pour les profils de matériau, l'UID de l'étiquette est souvent suffisant, mais la sélection de sauvegarde manuelle est nécessaire.
- Testez dans le boîtier réel, pas juste sur le banc.

## Lectures connexes

- [Adafruit: PN532 RFID/NFC Breakout Wiring](https://learn.adafruit.com/adafruit-pn532-rfid-nfc/breakout-wiring) - connexion PN532, sélection SPI/I2C/UART et avertissements de logique 3.3V.
- [Adafruit: PN532 RFID/NFC guide, single page](https://learn.adafruit.com/adafruit-pn532-rfid-nfc?view=all) - guide PN532 complet, câblage, CircuitPython, Raspberry Pi et sélection d'interface.
- [Adafruit PN532 product page](https://www.adafruit.com/product/364) - capacités PN532, support d'étiquette NFC/RFID et interfaces UART/I2C/SPI 3.3V.
- [NXP: MFRC522 Standard performance MIFARE and NTAG frontend](https://www.nxp.com/products/rfid-nfc/nfc-hf/nfc-readers/standard-performance-mifare-and-ntag-frontend:MFRC52202HN1) - page officielle MFRC522/RC522 pour scénarios MIFARE/NTAG 13.56 MHz.
- [DigiKey: MFRC522 Datasheet by NXP](https://www.digikey.com/htmldatasheets/production/993456/0/0/1/mfrc522.html) - fiche technique technique MFRC522 : cartes supportées, alimentation, interfaces de communication avec contrôleur et effets d'antenne/puissance sur la distance.
