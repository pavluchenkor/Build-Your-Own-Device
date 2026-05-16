# Soudage

Le soudage est utilisé lorsque vous devez connecter de manière fiable un fil à un pad, souder un connecteur, réparer une connexion cassée ou assembler un petit module.

Mais le soudage ne devrait pas remplacer un connecteur approprié, un terminal ou un attachement mécanique où le fil tirera, vibrera ou chauffera.

## Quand le soudage est approprié

Le soudage est bon pour :

- souder les fils à une carte ;
- installer un connecteur de broches ;
- réparer un fil cassé ;
- connecter un petit module ;
- souder une thermistance ou fil de signal ;
- assemblage de prototype.

Le soudage n'est pas le meilleur choix pour :

- les connexions fréquemment désassemblées ;
- les terminaux d'alimentation sans soulagement de la déformation ;
- les fils qui bougeront ;
- les connexions dans les zones chaudes sans protection ;
- les parties AC 110-230V secteur sans terminaux et enceinte appropriés.

## Kit minimal

Pour un soudage approprié, vous avez besoin de :

- un fer à souder avec contrôle de température ;
- soudure ;
- flux ;
- support de fer à souder ;
- éponge ou fil de laiton pour nettoyer la pointe ;
- pinces à couper ;
- dénudeur de fil ;
- pincettes ou troisième main ;
- gaine thermorétractable ;
- alcool isopropylique pour nettoyage si nécessaire.

Un fer à souder sans support est une mauvaise idée. Une pointe chaude brûle facilement votre main, le fil, l'enceinte ou la table.

## Étamer un fil

Étamer un fil signifie revêtir les brins exposés d'une fine couche de soudure.

Procédure :

1. Dénudez un peu d'isolation.
2. Torsadez les brins ensemble si le fil est multibrins.
3. Appliquez du flux si la soudure ne s'écoule pas bien.
4. Chauffez le fil avec le fer à souder.
5. Appliquez de la soudure à la zone chauffée.
6. Laissez la soudure s'écouler sur les brins.

Ne transformez pas l'extrémité du fil en un blob épais et rigide. L'étamage doit être net et fin.

## Souder un fil à un pad

Procédure :

1. Fixez la carte et le fil.
2. Étamez le pad.
3. Étamez le fil.
4. Appliquez le fil au pad.
5. Chauffez le fil et le pad simultanément.
6. Laissez la soudure fondre et joindre les parties.
7. Retirez la soudure, puis le fer.
8. Ne bougez pas le joint pendant que la soudure refroidit.

Un bon joint de soudure ressemble lisse et brillant ou uniformément terne, selon la soudure. Ce ne devrait pas être un blob assis sur le dessus qui n'a pas mouillé le pad.

## Joints de soudure froids

Un joint de soudure froid est où la soudure n'a pas chauffé correctement et n'a pas coulé normalement.

Signes :

- surface rugueuse ;
- soudure en morceau ;
- le fil bouge ;
- le contact va et vient ;
- le joint se brise avec un léger mouvement.

Les joints de soudure froids sont dangereux parce qu'ils peuvent fonctionner parfois. Dans un appareil chauffé ou vibrant, un tel contact se dégradara.

Généralement, un joint froid est réparé en le réchauffant avec du flux jusqu'à ce que la soudure s'écoule correctement.

## Pad surchauffé

Si vous chauffez un pad trop longtemps, il peut se lever de la carte.

Cela affecte particulièrement :

- les modules bon marché ;
- les petits pads ;
- les fines traces ;
- les tentatives de retouche multiples ;
- les fils tirant sur le pad.

Si la soudure ne s'écoule pas, vous n'avez pas toujours besoin de chauffer plus longtemps. Souvent, ajouter du flux, nettoyer la pointe, utiliser la bonne température ou une pointe plus grande aide.

## Flux

Le flux aide la soudure à mouiller le métal.

Sans flux, la soudure s'agglomère souvent et ne joint pas bien les parties.

Après soudage, du flux doit être lavé. Cela dépend du type de flux :

- no-clean peut souvent rester ;
- hydrosoluble doit être retiré ;
- flux actif ne devrait pas rester sur la carte.

Si vous ne connaissez pas le type de flux, utilisez du flux de qualité électronique et lisez sa description.

## Gaine thermorétractable et isolation

Un joint soudé doit être isolé.

Pour les fils, une gaine thermorétractable est généralement utilisée.

Procédure :

1. Faites glisser la gaine thermorétractable sur le fil avant soudage.
2. Soudez les fils.
3. Vérifiez le joint.
4. Faites glisser la gaine thermorétractable en place.
5. Chauffez-la doucement.

Ne laissez pas les joints soudés exposés où ils pourraient toucher l'enceinte, un autre fil, un terminal ou un ventilateur.

## Soulagement de la déformation

La soudure n'aime pas la contrainte mécanique.

Si un fil tirera, vibrera ou bougera, vous avez besoin d'un soulagement de la déformation :

- serre-câble ;
- pince ;
- connecteur de soulagement de la déformation ;
- un blob de silicone dans un endroit sûr ;
- fil fixé à l'enceinte ;
- un connecteur au lieu de soudage direct.

Mauvaise pratique : le fil est tenu seulement par le pad de soudure. Avec le temps, il peut déchirer le pad.

## Fils d'alimentation

Les fils d'alimentation doivent être soudés très soigneusement.

Vérifiez :

- le fil a le bon calibre ;
- le joint est entièrement chauffé ;
- pas de joints de soudure froids ;
- pas de brins exposés ;
- l'isolation est présente ;
- l'attachement mécanique est présent ;
- le joint n'est pas à côté d'une zone chaude sans protection.

Pour les lignes d'alimentation, un terminal ou connecteur approprié est souvent meilleur que de souder les fils de manière permanente.

## Ce qu'il faut vérifier après soudage

Après soudage :

- inspectez le joint ;
- vérifiez que les contacts voisins ne sont pas court-circuités ;
- utilisez le multimètre pour vérifier la connexion nécessaire ;
- vérifiez pas de court-circuit entre `+` et `GND` ;
- tirez doucement le fil ;
- confirmez que la gaine thermorétractable couvre le métal ;
- vérifiez que le fil ne tire pas le pad.

## Erreurs courantes

- soudage avec une pointe sale ;
- pas d'utilisation de flux ;
- chauffage seulement de la soudure, pas du pad et du fil ;
- faire un blob de soudure ;
- bouger le fil pendant que la soudure refroidit ;
- surchauffer le pad ;
- laisser un joint ouvert sans gaine thermorétractable ;
- le fil tenu seulement par la soudure ;
- soudage du fil d'alimentation trop fin avec fer faible ;
- utilisation de flux acide non prévu pour l'électronique.

## Les éléments essentiels

- Un bon soudage nécessite chauffer les deux parties, pas seulement verser de la soudure.
- Le flux résout souvent les problèmes de mouillage pauvre.
- Les joints de soudure froids peuvent fonctionner parfois, donc ils sont dangereux.
- Un joint soudé doit être isolé et mécaniquement soulagé.
- Pour les connexions fréquemment désassemblées et d'alimentation, un connecteur ou terminal est souvent meilleur que soudage.

## Matériaux de référence

- [SparkFun: How to Solder, Through-Hole Soldering](https://learn.sparkfun.com/tutorials/how-to-solder-through-hole-soldering) - outils, température, flux, bon soudage et vérification de connexion.
- [SparkFun: Soldering Your First Component](https://learn.sparkfun.com/tutorials/how-to-solder-through-hole-soldering/soldering-your-first-component) - règles de base : chauffage du pad et de la broche, ordre d'application de la soudure, bonne forme de joint.
- [Adafruit: Guide to Excellent Soldering](https://learn.adafruit.com/adafruit-guide-excellent-soldering) - guide de soudage pratique pour l'électronique.
- [Adafruit: Common Soldering Problems](https://learn.adafruit.com/adafruit-guide-excellent-soldering/common-problems) - joints froids, surchauffe, trop de soudure et corrections.
- [NASA Workmanship: Soldered Electrical Connections](https://workmanship.nasa.gov/lib/insp/2%20books/links/sections/407%20Soldering.html) - matériel de référence sur la qualité du joint de soudure et le support mécanique du fil.
