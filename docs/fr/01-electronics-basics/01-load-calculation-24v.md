# Courant, tension et puissance de charge

Avant de connecter un radiateur, un ventilateur, une bande LED, un servocommande ou tout autre module, vous devez comprendre trois choses :

- tension;
- courant;
- puissance.

Sans cela, il est facile d'acheter la mauvaise alimentation, de surcharger le fil, de faire fondre le connecteur, de brûler un module MOSFET, ou de connecter la charge au contrôleur de manière à ce qu'il fonctionne instabilement.

## Où trouver les paramètres

La tension, le courant et la puissance se trouvent généralement :

- sur le boîtier du composant ;
- sur l'étiquette de l'alimentation ;
- sur la page produit ;
- dans les spécifications techniques ;
- dans le manuel ;
- dans le schéma du circuit ou la broche.

Si le paramètre n'est pas spécifié, ce n'est pas un problème mineur. C'est une raison de vous arrêter et de comprendre exactement ce que vous connectez.

Pour les composants provenant du périphérique de l'imprimante 3D, les paramètres typiques ressemblent à ceci :

- ventilateur: `24V 0.2A` ;
- radiateur: `24V 100W` ;
- bande LED: `24V 9.6W/m` ;
- servocommande: `5V`, le courant dépend de la charge ;
- carte contrôleur: le courant maximal pour chaque sortie est spécifié séparément.

## La tension doit correspondre

Une charge est conçue pour une tension spécifique.

Exemples :

- Le ventilateur peut être `5V`, `12V` ou `24V` ;
- La bande LED peut être `5V`, `12V` ou `24V` ;
- La servocommande est souvent évaluée à `5V` ou `6V` ;
- Le radiateur peut être `12V`, `24V` ou `110-230V AC`.

Si vous connectez un ventilateur `24V` à `12V`, il peut ne pas démarrer ou fonctionner faiblement. Si vous connectez un ventilateur `12V` à `24V`, il peut échouer rapidement.

La règle principale :

**la tension de l'alimentation doit correspondre à la tension de la charge.**

Ne connectez pas un appareil à une tension plus élevée simplement parce que le connecteur s'adapte physiquement.

## La puissance indique la taille de la charge

La puissance indique la quantité d'énergie que la charge consomme ou convertit en travail, chaleur, lumière ou mouvement.

La puissance est mesurée en watts: `W`.

Exemples :

- `24V 5W` - petite charge ;
- `24V 24W` - environ `1A` ;
- `24V 120W` - environ `5A` ;
- `24V 240W` - environ `10A`.

Les radiateurs consomment généralement beaucoup d'énergie. Les ventilateurs consomment moins, mais ils peuvent avoir un courant d'appel élevé. Les bandes LED peuvent être une petite charge si elles sont courtes, ou une charge sérieuse si elles sont longues et brillantes.

## Le courant charge les fils et les éléments d'alimentation

Le courant indique la quantité d'électricité qui s'écoule à travers les fils, les bornes, les connecteurs et les éléments d'alimentation.

Le courant crée souvent des problèmes pratiques :

- les fils s'échauffent ;
- les bornes deviennent sombres ;
- les connecteurs fondent ;
- MOSFET surchauffe ;
- l'alimentation n'est pas suffisante ;
- l'appareil redémarre quand la charge s'active ;
- le fusible ne saute pas par hasard, mais en raison d'une véritable surcharge ou d'une erreur.

Par conséquent, il ne suffit pas de connaître uniquement la tension. Vous devez calculer le courant.

## Formule de calcul

Pour la plupart des calculs simples, vous avez besoin de la formule de puissance :

```text
P = U * I
```

Où :

- `P` - puissance en watts `W` ;
- `U` - tension en volts `V` ;
- `I` - courant en ampères `A`.

Pour trouver le courant :

```text
I = P / U
```

![Loi d'Ohm: circuit avec source de tension, courant et résistance](../../../img/01-electronics-basics/01-ohms-law-circuit.svg)

*Source: [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:Ohm%27s_Law_with_Voltage_source_TeX.svg), GorillaWarfare, CC0 Public Domain*

Cette formule n'est pas pour un examen. Elle est nécessaire pour comprendre si l'alimentation, le fil, la borne, le module MOSFET, le relais, le SSR ou la sortie du circuit pourra la supporter.

## Tableau rapide pour 24V

Dans les imprimantes 3D et les périphériques, `24V` est courant. Pour une évaluation rapide, il est utile de se souvenir :

| Puissance | Courant à 24V |
|---:|---:|
| `12W` | `0.5A` |
| `24W` | `1A` |
| `48W` | `2A` |
| `96W` | `4A` |
| `120W` | `5A` |
| `240W` | `10A` |
| `300W` | `12.5A` |

Ce sont des valeurs approximatives, mais pour le premier choix de l'alimentation, du fil et du commutateur d'alimentation, elles sont très utiles.

## Exemple : radiateur 24V 100W

Vous avez un radiateur :

```text
24V 100W
```

Calculez le courant :

```text
I = 100W / 24V = 4.17A
```

Cela signifie que les éléments suivants doivent supporter plus de `4.17A` :

- alimentation ;
- fil ;
- bornes ;
- connecteur ;
- MOSFET ou SSR ;
- fusible et porte-fusible ;
- pistes du circuit, si le radiateur est connecté au circuit.

Si l'alimentation est évaluée à `24V 5A`, elle s'approche formellement de la charge, mais presque sans marge. Pour un véritable appareil, il est préférable d'en prendre davantage.

## Exemple : charges multiples

Supposons qu'un appareil `24V` possède :

- radiateur `100W` ;
- ventilateur `24V 0.2A` ;
- bande LED `24V 1A` ;
- un autre ventilateur `24V 0.15A`.

Calculez le radiateur :

```text
100W / 24V = 4.17A
```

Additionnez-les :

```text
4.17A + 0.2A + 1A + 0.15A = 5.52A
```

Une alimentation minimale « juste adaptée » serait environ `24V 6A`, mais ce n'est pas un bon choix pour le fonctionnement à long terme. Avec une marge de `50%` :

```text
5.52A * 1.5 = 8.28A
```

Pratiquement, vous devriez chercher une alimentation `24V 9A`, `24V 10A` ou plus grande, si le boîtier, le refroidissement et la sécurité le permettent.

## La marge est obligatoire

L'alimentation, le câblage, les bornes et les modules d'alimentation ne peuvent pas être sélectionnés exactement selon le courant calculé.

Pour ce guide, une règle simple pour l'évaluation initiale approximative :

**planifiez au moins 50% de marge**, sauf si la documentation d'un composant spécifique en exige davantage. Ce n'est pas une garantie universelle, mais une estimation initiale. La sélection finale est effectuée selon les spécifications techniques, la température à l'intérieur du boîtier, le refroidissement, la réduction d'échelon et le chauffage réel des bornes/fils.

La marge est nécessaire parce que :

- l'alimentation s'échauffe ;
- la température à l'intérieur du boîtier peut être plus élevée que la température ambiante ;
- les ventilateurs et les moteurs ont un courant d'appel ;
- les contacts vieillissent et se relâchent ;
- les bornes ont des limites de courant et de température ;
- SSR et MOSFET génèrent de la chaleur ;
- l'alimentation peut avoir une réduction d'échelon - réduction de la puissance maximale à température élevée ou mauvaise ventilation.

Les alimentations industrielles ont souvent une courbe de réduction d'échelon dans la spécification technique — une courbe de puissance maximale réduite à mesure que la température augmente. La réduction d'échelon signifie que le fabricant réduit la puissance maximale autorisée à haute température ou mauvaise ventilation. Par conséquent, l'étiquette `240W` sur une alimentation ne signifie pas toujours qu'elle livrera en toute sécurité `240W` dans un boîtier chaud et fermé.

## Le point faible peut ne pas être l'alimentation

Même si l'alimentation est puissante, le circuit peut être faible ailleurs.

Vous devez vérifier l'ensemble du circuit :

- sortie d'alimentation ;
- fil ;
- bloc de bornes ;
- connecteur ;
- fusible ;
- module MOSFET ;
- relais ou SSR ;
- pistes du circuit ;
- la charge elle-même.

Par exemple, une alimentation peut supporter `10A`, mais un petit connecteur ou une mauvaise borne à vis peut s'échauffer déjà à courant inférieur. Ceci est particulièrement important pour les radiateurs et les bandes LED.

## Qu'est-ce qu'un commutateur d'alimentation

Un commutateur d'alimentation est un commutateur contrôlé.

Le contrôleur n'alimente pas directement une charge importante. Il donne un signal de contrôle faible, et le commutateur d'alimentation active ou désactive le courant de la charge.

Exemples :

- module MOSFET pour charges DC `12V`/`24V` ;
- relais ;
- SSR ;
- pilote de charge prêt à l'emploi ;
- sortie d'alimentation standard du circuit, si elle est évaluée pour la charge nécessaire.

Pour les radiateurs, les ventilateurs, les bandes LED et les moteurs, la règle s'applique presque toujours :

**GPIO du contrôleur n'alimente pas la charge. GPIO contrôle seulement.**

## Un peu sur la loi d'Ohm

La loi d'Ohm relie la tension, le courant et la résistance :

```text
U = I * R
```

Pour cet article, l'idée simple est importante : si vous appliquez une tension à une charge, le courant s'écoule à travers elle. La quantité de courant qui s'écoule dépend de la charge elle-même.

Mais toutes les charges ne se comportent pas de la même manière :

- le radiateur est proche d'une charge résistive ;
- le ventilateur et le moteur ont un courant d'appel ;
- la servocommande augmente fortement le courant en cas de blocage ;
- la bande LED consomme du courant en fonction de la longueur et de la luminosité ;
- le module électronique peut avoir un courant transitoire lors de la mise sous tension.

Par conséquent, pour un véritable appareil, il est préférable d'obtenir les données des spécifications techniques ou de mesurer le courant avec un multimètre / alimentation de laboratoire si c'est sûr.

## Avant de connecter

Avant de connecter la charge, répondez :

1. Pour quelle tension la charge est-elle évaluée?
2. Est-ce une charge CC ou CA?
3. Quelle puissance ou courant est spécifié?
4. Quel courant obtiendrez-vous à partir de la formule `I = P / U`?
5. Quelles autres charges se trouvent sur la même alimentation?
6. Y a-t-il au moins `50%` de marge?
7. Les fils, bornes, connecteurs et circuit résistent-ils?
8. Qu'est-ce qui contrôle la charge : MOSFET, relais, SSR ou sortie standard?
9. Un fusible est-il nécessaire?
10. Que se passe-t-il en cas de court-circuit, blocage du moteur ou défaillance du ventilateur?

Si c'est un radiateur ou une tension secteur `110-230V AC`, les exigences de sécurité sont plus strictes. La section d'alimentation ne peut pas être assemblée en devinant : vous avez besoin d'un boîtier approprié, d'un fusible, d'une isolation, d'une mise à la terre de protection `PE`, d'un soulagement de traction pour les fils et d'une vérification par une personne qualifiée.

## L'essentiel

- La tension d'alimentation doit correspondre à la tension de la charge.
- La puissance indique la taille de la charge.
- Le courant indique la charge sur les fils, les bornes, les connecteurs et les éléments d'alimentation.
- Formule de base : `I = P / U`.
- Dans un système `24V`, `24W` est environ `1A`, `120W` est environ `5A`, `240W` est environ `10A`.
- Les courants de toutes les charges sur une alimentation s'ajoutent.
- Vous avez besoin d'une marge d'au moins `50%` pour une estimation initiale approximative ; la sélection précise est effectuée selon les spécifications techniques, la température, le refroidissement et la réduction d'échelon.
- Le point faible peut ne pas être l'alimentation, mais une borne, un connecteur, un fil, un MOSFET ou une piste de circuit.
- GPIO du contrôleur n'alimente pas une charge importante, contrôle uniquement un commutateur d'alimentation.

## Matériaux de référence

- [SparkFun: Voltage, Current, Resistance, and Ohm's Law](https://learn.sparkfun.com/tutorials/voltage-current-resistance-and-ohms-law) - explication claire et fondamentale de la tension, du courant, de la résistance et de la loi d'Ohm.
- [DigiKey: Ohm's Law Calculator](https://www.digikey.com/en/resources/conversion-calculators/conversion-calculator-ohms) - calculatrice pour calculer les relations de tension, courant, résistance et puissance.
- [Mean Well: How to read a derating curve](https://meanwellpowersupplies.com/technical-articles/faq/how-to-read-a-derating-curve/) - pourquoi la puissance maximale d'une alimentation dépend de la température, de la ventilation et de la tension d'entrée.
- [DigiKey: Selecting and Applying AC/DC Power Supplies](https://www.digikey.com/en/articles/selecting-and-applying-ac-dc-power-supplies) - sélection d'une alimentation en tenant compte de la température, de la réduction d'échelon, des câbles et du type de charge.
- [Weidmuller: Derating curve / current-carrying capacity](https://www.weidmuller.com/en/products/connectivity/pcb_terminals_and_connectors/derating_curve.jsp) - pourquoi le courant maximal des bornes et des connecteurs dépend de la température et de la conception.
