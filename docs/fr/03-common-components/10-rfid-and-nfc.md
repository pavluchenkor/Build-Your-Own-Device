# RFID et NFC

RFID est l'identification par radiofréquence. NFC est une technologie connexe pour une plage très courte, souvent à la fréquence `13,56 MHz`.

Dans un simple appareil DIY, c'est un moyen de lire une carte, un porte-clés, un autocollant ou une étiquette sans contact filaire. Par exemple, un utilisateur apporte une étiquette de bobine de filament, et l'appareil sélectionne le profil de matériau.

L'erreur principale est de penser que « RFID » signifie compatibilité universelle. En pratique, vous avez besoin que la fréquence, le type d'étiquette, la puce lecteur, la bibliothèque, l'interface, la puissance et le placement de l'antenne s'alignent tous.

## Où c'est utilisé

Dans les projets de type iDryer, RFID/NFC peut être utilisé pour :

- identifier une bobine de filament ;
- sélectionner un profil de matériau ;
- lier les paramètres à une étiquette ;
- accès au service ;
- confirmation d'action utilisateur ;
- suivi des consommables ;
- expériences avec les étiquettes sur les conteneurs, les bobines ou les cassettes.

Pour la sélection du profil de matériau, souvent simplement lire l'UID de l'étiquette et stocker une table `UID -> matériau` suffit. Mais cette approche doit avoir un repli manuel : si l'étiquette ne lit pas, l'utilisateur peut toujours choisir manuellement le profil.

## RFID et NFC en termes simples

RFID est un terme large. Il inclut différentes fréquences, normes, plages et types d'étiquettes.

NFC signifie généralement la communication en champ proche à `13,56 MHz`, compatible avec une partie de l'écosystème RFID. NFC est connue des cartes bancaires, des téléphones, des autocollants NTAG et des cartes MIFARE, mais cela ne signifie pas qu'un lecteur NFC lit n'importe quelle carte et n'importe quelles données.

Pour les petits appareils DIY, les modules `13,56 MHz` sont les plus courants :

- RC522 / MFRC522 ;
- PN532 ;
- lecteurs RFID/NFC USB/UART prêts à l'emploi ;
- modules NFC avec SPI, I2C ou UART.

Il existe d'autres systèmes RFID, comme les cartes d'accès `125 kHz` ou RFID UHF. Ils ne sont pas compatibles avec les modules NFC `13,56 MHz`.

## RC522

RC522 est un module `13,56 MHz` bon marché et courant pour les cartes et les étiquettes. Il est souvent utilisé avec Arduino et ESP32.

Avantages :

- bon marché ;
- beaucoup d'exemples ;
- adapté à la lecture simple d'UID ;
- généralement connecté via SPI.

Inconvénients :

- fonctionne souvent uniquement avec l'alimentation et la logique `3,3V` ;
- la qualité du module bon marché varie ;
- la plage de lecture est petite ;
- le support du type de carte est limité ;
- la broche `SDA` sur la carte signifie généralement `SS`/`CS` pour SPI, pas `SDA` I2C.

RC522 fonctionne si vous avez seulement besoin de lire UID à partir de cartes ou de porte-clés de type MIFARE à courte portée. Pour des tâches NFC plus larges, PN532 est généralement plus pratique.

## PN532

PN532 est un contrôleur NFC/RFID plus flexible. De nombreux modules PN532 peuvent fonctionner via :

- SPI ;
- I2C ;
- UART.

Mais l'interface choisie doit généralement être définie physiquement sur la carte : cavaliers, commutateurs DIP ou soudure. Vous ne pouvez pas connecter un module via I2C s'il est défini en mode SPI.

PN532 est souvent choisi si vous avez besoin de :

- plus d'options d'interface ;
- meilleur support du scénario NFC ;
- travail avec différents types d'étiquettes ;
- scénarios Python/CircuitPython/Raspberry Pi ;
- module mieux documenté.

Mais PN532 n'est pas un lecteur universel magique non plus. Vous devez vérifier les types de cartes spécifiques, la bibliothèque et le mode de fonctionnement.

## Fréquence et type d'étiquette

L'étiquette doit correspondre au lecteur.

Avant d'acheter des étiquettes, vérifiez :

- fréquence : `13,56 MHz`, `125 kHz` ou autre ;
- type : MIFARE Classic, NTAG213/215/216, ISO14443A ou autre ;
- si vous avez seulement besoin de lire l'UID ;
- si vous avez besoin de lire/écrire des données personnalisées ;
- si votre bibliothèque choisie supporte les opérations nécessaires ;
- si vous pouvez placer physiquement l'étiquette sur une bobine ou un boîtier.

Si la tâche consiste à sélectionner un profil de matériau, généralement simplement lire UID et stocker le profil séparément est plus simple. L'écriture de données à l'intérieur de l'étiquette complique le projet : vous devez penser au format de données, à la compatibilité, à la protection en écriture et aux erreurs d'écriture.

## UID - Pas la sécurité

L'UID d'une carte ou d'une étiquette est pratique à utiliser comme identifiant. Mais UID n'est pas une protection fiable.

Pour un profil de bobine, c'est normal : si UID est connu, sélectionnez le profil. Une erreur n'est pas critique car l'utilisateur peut vérifier le matériau à la main.

Pour l'accès à des fonctions dangereuses, des modes de service ou déverrouillage d'un radiateur, UID seul est faible. Certains UID peuvent être copiés ou contrefaits, et certaines cartes ont des limites de sécurité connues.

Règle pratique :

- UID est bon pour la commodité et l'identification des consommables ;
- UID ne doit pas être la seule protection pour les modes dangereux ;
- pour les radiateurs et les pièces sous tension, vous avez toujours besoin de vérifications de sécurité séparées.

## Puissance et niveaux logiques

De nombreux modules RFID/NFC sont évalués pour une logique `3,3V`. C'est particulièrement important pour les modules RC522 et PN532 breakout.

Vérifiez :

- tension d'alimentation du module ;
- niveau logique sur SPI/I2C/UART ;
- si la carte a un régulateur ;
- si les lignes de signal ont une correspondance de niveau ;
- si les résistances de pull-up I2C sont nécessaires ;
- si la masse commune avec le contrôleur est nécessaire.

La présence de la broche `5V` sur une carte module ne signifie pas toujours que les lignes de signal tolèrent `5V`. Certains modules peuvent être alimentés par `5V` via un régulateur, mais la logique reste `3,3V`.

## Interface de connexion

Un module RFID/NFC peut se connecter via SPI, I2C ou UART.

SPI :

- rapide et courant ;
- nécessite `SCK`, `MOSI`, `MISO`, `CS` ;
- sur RC522, la broche `SDA` signifie souvent réellement `CS` ;
- important de ne pas confondre `MOSI` et `MISO`.

I2C :

- utilise `SDA` et `SCL` ;
- peut partager le bus avec d'autres appareils ;
- a besoin de résistances de pull-up correctes ;
- important de vérifier l'adresse et le mode de module sélectionné.

UART :

- utilise `TX` et `RX` ;
- `TX` d'un appareil va à `RX` d'un autre ;
- pratique pour certains lecteurs prêts à l'emploi ;
- a besoin d'une vitesse et d'un protocole correspondants.

La connexion RC522 SPI détaillée se trouve dans la section pratique : [Connexion d'un lecteur RFID](../06-practical-guides/05-connecting-rfid-reader.md).

## Antenne et boîtier

RFID/NFC fonctionne via une antenne. Sur les petits modules, elle est généralement imprimée directement sur la carte.

La lecture est affectée par :

- taille de l'antenne ;
- orientation de l'étiquette ;
- distance ;
- plastique du boîtier ;
- métal à proximité ;
- câbles et lignes d'alimentation à proximité ;
- puissance du module ;
- type d'étiquette ;
- où l'utilisateur apporte la carte.

Le métal près de l'antenne peut fortement aggraver la lecture. Si le lecteur est monté près du cadre métallique de l'imprimante, des vis, de l'écran, de l'alimentation ou du panneau en aluminium, la plage peut devenir beaucoup pire.

Pour le boîtier, il est préférable de créer une zone claire : « apportez l'étiquette ici ». N'attendez pas que l'étiquette sur une bobine soit toujours lue automatiquement à travers le plastique, l'air, l'arbre, le support et les pièces à proximité.

## Logique de l'appareil

RFID devrait améliorer la commodité, pas la casser contrôle.

Logique normale pour une bobine :

1. L'utilisateur apporte une étiquette.
2. L'appareil lit l'UID.
3. L'UID est recherché dans la table de profil.
4. Si l'UID est trouvé, le profil de matériau est suggéré.
5. L'utilisateur peut confirmer ou modifier le profil.
6. Si l'UID n'est pas trouvé ou n'a pas lu, la sélection manuelle est disponible.

Mauvaise logique :

- l'appareil ne peut pas démarrer sans une étiquette ;
- l'étiquette inconnue sélectionne un profil aléatoire ;
- l'erreur de lecture gardera silencieusement l'ancien profil ;
- le profil change sans confirmation de l'utilisateur ;
- UID est la seule protection pour un mode de service.

Pour un radiateur, il est particulièrement important que la sélection du profil ne contourne pas les limites de température, les capteurs et la protection d'urgence.

## Quoi vérifier avant d'acheter

Avant d'acheter, vérifiez :

- fréquence du module ;
- types d'étiquettes supportés ;
- interface : SPI, I2C, UART, USB ;
- tension d'alimentation ;
- niveaux logiques ;
- disponibilité de la correspondance de niveau ;
- disponibilité de la documentation et du pinout ;
- comment l'interface est sélectionnée sur la carte ;
- s'il y a une bibliothèque pour votre contrôleur ;
- taille de l'antenne ;
- type et taille de l'étiquette ;
- plage attendue dans un vrai cas ;
- si la sélection de repli manuelle est possible.

Pour un premier projet, choisissez un module avec une bonne documentation et des exemples, pas le moins cher sans schéma.

## Erreurs typiques

- acheté une carte `125 kHz` pour un lecteur `13,56 MHz` ;
- connecté RC522 `3,3V` à l'alimentation ou la logique `5V` ;
- pris la broche `SDA` sur RC522 pour I2C `SDA` ;
- confondus `MOSI` et `MISO` ;
- oublié `CS`/`SS` dans SPI ;
- défini une interface sur PN532 avec des cavaliers mais connecté une interface différente ;
- n'a pas placé les pull-ups I2C où c'était nécessaire ;
- mis l'antenne près du métal ;
- testé la lecture sur établi mais n'a pas testé en cas ;
- fait RFID le seul moyen de sélectionner le profil ;
- utiliser l'UID comme protection d'accès fiable ;
- n'a pas géré la situation « l'étiquette n'a pas lu ».

## Point principal

RFID/NFC est utile pour l'identification de la bobine, la sélection du profil de matériau et l'entrée simple du service. Mais ce n'est pas un lecteur universel pour n'importe quelles cartes et pas un système de sécurité fiable en soi.

D'abord, choisissez les fréquences et les types d'étiquettes, puis le module, l'interface, l'alimentation et le placement de l'antenne. Ensuite, testez la lecture en cas réel et certainement gardez la sélection de repli manuelle.

## Matériaux de référence

- [Adafruit: PN532 RFID/NFC Breakout Wiring](https://learn.adafruit.com/adafruit-pn532-rfid-nfc/breakout-wiring) - connexion PN532, sélection SPI/I2C/UART et mise en garde concernant la logique `3,3V`.
- [Adafruit: PN532 RFID/NFC guide, single page](https://learn.adafruit.com/adafruit-pn532-rfid-nfc?view=all) - guide complet PN532, CircuitPython/Python, interfaces et configuration du cavalier SEL.
- [Adafruit PN532 product page](https://www.adafruit.com/product/364) - description du module PN532, interfaces prises en charge et capacités NFC/RFID.
- [NXP: MFRC522 Standard performance MIFARE and NTAG frontend](https://www.nxp.com/products/rfid-nfc/nfc-hf/nfc-readers/standard-performance-mifare-and-ntag-frontend:MFRC52202HN1) - page de la puce MFRC522/RC522 et son objectif pour les scénarios MIFARE/NTAG `13,56 MHz`.
- [DigiKey: MFRC522 Datasheet by NXP](https://www.digikey.com/htmldatasheets/production/993456/0/0/1/mfrc522.html) - description technique de MFRC522 : lecteur/écrivain `13,56 MHz`, support ISO/IEC 14443 A/MIFARE/NTAG et interfaces de communication.
