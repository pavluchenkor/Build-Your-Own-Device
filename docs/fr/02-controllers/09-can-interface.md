```markdown
# Interface CAN

CAN est une interface de communication pour plusieurs appareils sur une ligne différentielle commune. Acronyme de : `Controller Area Network`.

CAN est issu de l'électronique automobile et industrielle, mais dans les imprimantes 3D il est devenu populaire pour les cartes de tête d'outil, les MCU distants et les modules où l'on a besoin d'une communication plus longue et plus fiable qu'avec I2C/SPI.

## Cas d'utilisation du CAN

Dans les imprimantes et les périphériques de type iDryer, CAN est utilisé pour :

- les cartes de tête d'outil sur la tête d'impression ;
- un MCU supplémentaire dans un bloc distant ;
- la réduction du nombre de fils dans le faisceau de câbles ;
- la communication avec un filtre CAN, une caméra ou des cartes de sécheur ;
- un système distribué de plusieurs contrôleurs ;
- les cas où USB ou un long I2C/SPI est peu pratique.

CAN est particulièrement utile lorsqu'un nœud est éloigné de l'hôte ou de la carte principale, et qu'il y a des moteurs, des éléments chauffants et d'autres sources de bruit à proximité.

## CANH, CANL et GND

Un bus CAN physique utilise généralement :

- `CANH` ;
- `CANL` ;
- parfois `GND` ou un fil de référence commune ;
- l'alimentation du module séparément, si nécessaire.

Le signal est transmis comme la différence entre `CANH` et `CANL`. C'est pourquoi CAN gère mieux le bruit que les lignes de signal simples.

Schéma simplifié :

![Bus CAN haute vitesse ISO 11898-2 avec plusieurs nœuds et terminateurs](../../img/02-controllers/09-can-iso11898-2-network.png)

*Source : [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:CAN_ISO11898-2_Network.png), EE JRW, CC BY-SA 4.0*

Pour le câblage, une paire torsadée est souvent utilisée pour `CANH`/`CANL`. `GND` dépend du circuit spécifique, des cartes et de la documentation, mais dans les petits systèmes DIY, une référence commune est souvent nécessaire pour un fonctionnement stable et la sécurité de l'interface.

## Un émetteur-récepteur CAN est requis

Important : la prise en charge du CAN dans le microcontrôleur et la présence du CAN sur la carte ne sont pas la même chose.

Pour que CAN fonctionne, il vous faut :

- un microcontrôleur avec contrôleur CAN ou une prise en charge appropriée dans le firmware ;
- un émetteur-récepteur CAN sur la carte ;
- des connecteurs `CANH`/`CANL` corrects ;
- l'alimentation de l'émetteur-récepteur ;
- des terminateurs ;
- un firmware compilé pour CAN.

Si la fiche technique du microcontrôleur mentionne CAN, mais que la carte n'a pas d'émetteur-récepteur, vous ne pouvez pas vous connecter directement au bus CAN.

## Topologie et terminateurs

CAN est un bus. Une bonne topologie ressemble à une ligne avec des nœuds connectés via de courtes branches.

Deux terminateurs de `120 Ohm` sont généralement nécessaires :

- un à une extrémité physique du bus ;
- un second à l'autre extrémité physique.

Pas un, pas trois, et pas « sur chaque carte ». Exactement deux aux extrémités.

Si l'alimentation est coupée, sur un bus correctement terminé, un multimètre entre `CANH` et `CANL` affiche souvent environ `60 Ohm`, car deux résistances de `120 Ohm` sont en parallèle.

De nombreuses cartes ont un cavalier de terminateur. Certaines ont un terminateur intégré sans possibilité de désactivation pratique. Avant l'assemblage, vérifiez donc les schémas de toutes les cartes sur le bus.

## Débit binaire

La vitesse CAN doit être identique sur tous les nœuds. Dans Klipper, CAN utilise souvent `1000000`, soit `1 Mbit/s`, mais la valeur spécifique dépend du firmware, des paramètres et de la longueur du bus.

Si le débit binaire est différent, les nœuds ne pourront pas communiquer normalement.

Pour un câblage long ou problématique, la vitesse peut être critique. Plus la vitesse est élevée, plus le bus est exigeant en matière de topologie, de terminateurs et de qualité des câbles.

## CAN dans Klipper

Dans Klipper, CAN est utilisé comme moyen de communiquer avec le MCU.

Un appareil sur CAN n'est généralement pas spécifié via `serial:`. La configuration utilise à la place `canbus_uuid` :

```ini
[mcu toolhead]
canbus_uuid: 11aa22bb33cc
```

Côté Linux, une interface `can0` est généralement nécessaire. L'hôte doit disposer d'un adaptateur CAN :

- adaptateur USB-CAN ;
- carte en mode pont USB-to-CAN ;
- HAT/adaptateur pour SBC ;
- autre circuit pris en charge.

Klipper dispose d'un outil pour trouver le `canbus_uuid` des nouveaux appareils non initialisés. Il est important de comprendre que si un appareil est déjà configuré par Klipper, il peut ne plus apparaître dans la liste en tant que « nouveau ».

## Pont USB-to-CAN

Certaines cartes peuvent être flashées en mode pont USB-to-CAN. La carte se connecte alors à l'hôte via USB et apparaît à Linux comme un adaptateur CAN.

C'est pratique, mais il y a une limitation importante : le mode pont est nécessaire pour communiquer avec un vrai bus CAN et d'autres nœuds CAN. Si vous n'avez qu'une seule carte près de l'hôte et pas de vrai bus CAN, il est généralement plus simple d'utiliser le mode USB/série normal.

De plus, le pont USB-to-CAN ne sera pas visible en tant que `/dev/serial/by-id/...`. Il est configuré comme interface CAN et utilise `canbus_uuid`, et non `serial:`.

## Quand le CAN est justifié

CAN vaut la peine d'être envisagé si :

- vous devez connecter une carte de tête d'outil ;
- vous devez faire passer la communication sur un long faisceau de câbles ;
- vous avez besoin de plusieurs MCU distants ;
- vous souhaitez réduire les fils entre les parties mobiles et l'enceinte ;
- vous disposez déjà d'une infrastructure CAN ;
- la carte choisie est bien documentée pour Klipper CAN.

CAN peut être inutile si :

- la carte est près de l'hôte ;
- vous n'avez besoin que d'un seul MCU supplémentaire ;
- USB fonctionne de manière stable ;
- vous n'avez aucune expérience avec le flashage, `can0`, les terminateurs et la mise en réseau Linux ;
- la carte choisie est mal documentée.

Pour un premier contrôleur supplémentaire simple, USB est souvent plus rapide et plus clair. CAN prend tout son sens quand il résout un vrai problème de câblage ou de distribution des cartes.

## CAN n'alimente pas les charges

CAN n'est que de la communication.

Si une carte CAN contrôle un ventilateur, un élément chauffant, un SSR ou un servo, elle a toujours besoin de :

- l'alimentation de la carte ;
- l'alimentation de la charge ;
- MOSFET/driver/SSR ;
- des fusibles ;
- des bornes appropriées ;
- une protection thermique pour les éléments chauffants ;
- une enceinte sécurisée.

CAN ne remplace pas l'électronique de puissance et ne rend pas un élément chauffant sûr.

## Ce qu'il faut vérifier avant d'acheter

Avant d'acheter une carte CAN, vérifiez :

- quel microcontrôleur est utilisé ;
- si la carte prend en charge Klipper CAN ;
- s'il y a un émetteur-récepteur CAN ;
- où se trouvent `CANH` et `CANL` ;
- s'il y a un terminateur et comment l'activer ;
- quel connecteur est utilisé ;
- comment la carte est alimentée ;
- comment la carte est flashée ;
- s'il y a des instructions pour `canbus_uuid` ;
- si un adaptateur USB-CAN séparé est nécessaire ;
- s'il existe un schéma et un brochage ;
- quelles broches et sorties d'alimentation sont disponibles.

Si le vendeur écrit « CAN » uniquement parce que la puce le supporte théoriquement, mais que la carte n'a ni émetteur-récepteur ni documentation, c'est un mauvais choix.

## Erreurs typiques

- confusion entre `CANH` et `CANL` ;
- oubli que l'émetteur-récepteur CAN est obligatoire ;
- installation d'un seul terminateur au lieu de deux ;
- activation des terminateurs sur chaque carte ;
- absence de vérification de la résistance entre `CANH` et `CANL` ;
- choix de débits binaires différents sur les nœuds ;
- attente de `/dev/serial/by-id` depuis un pont USB-to-CAN ;
- flashage de la carte pour USB, mais connexion en CAN ;
- flashage pour CAN, mais absence de configuration de `can0` ;
- création d'une étoile avec de longues branches au lieu d'un bus ;
- croire que CAN est un moyen d'alimenter les charges.

## À retenir

CAN est une bonne interface pour les MCU distants, les cartes de tête d'outil et les systèmes distribués à l'intérieur d'une imprimante. Il utilise une paire différentielle `CANH`/`CANL`, nécessite des émetteurs-récepteurs CAN, une topologie correcte et deux terminateurs aux extrémités du bus.

Pour Klipper, CAN est utile mais plus complexe que USB : il faut flasher la carte pour CAN, configurer l'adaptateur/`can0`, trouver le `canbus_uuid` et vérifier le bus physique. Utilisez CAN là où il simplifie réellement le câblage ou améliore la robustesse de la connexion.

## Ressources associées

- [Klipper : CANBUS](https://www.klipper3d.org/CANBUS.html) - documentation CAN officielle de Klipper : matériel, adaptateur hôte, `can0`, `canbus_uuid`, terminateurs et pont USB-to-CAN.
- [Klipper : protocole CANBUS](https://www.klipper3d.org/CANBUS_protocol.html) - comment Klipper attribue l'identifiant de nœud CAN et utilise `canbus_uuid`.
- [CAN Bus Debugger : Terminaison du bus CAN expliquée](https://www.canbusdebugger.com/articles/can-bus-termination) - explication pratique des deux terminateurs de `120 Ohm`, de la mesure à `60 Ohm` et des erreurs courantes.
- [DigiKey : Le bus CAN expliqué](https://www.digikey.com/en/blog/can-bus-explained) - vue d'ensemble générale du bus CAN, de la communication différentielle et de son application dans les systèmes distribués.
- [Texas Instruments : Introduction au CAN](https://www.ti.com/lit/an/sloa101b/sloa101b.pdf) - description de base de la couche physique CAN, des émetteurs-récepteurs et du réseau typique.
```
