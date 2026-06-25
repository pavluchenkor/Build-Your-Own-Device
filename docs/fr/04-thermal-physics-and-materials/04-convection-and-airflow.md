# Convection et flux d'air

La convection est le transfert de chaleur par le courant d'air. Dans un séchoir, une chambre d'imprimante, un filtre chauffant ou un appareil de type iHeater, l'air détermine souvent si la chaleur atteint là où elle est nécessaire.

Un radiateur à lui seul convertit uniquement l’énergie électrique en chaleur. Le ventilateur et le conduit d'air déterminent si cette chaleur est répartie uniformément dans toute la chambre ou si elle reste un petit point chaud dangereux.

## Trois modes d'un seul appareil de chauffage

Le même radiateur `100 W` peut fonctionner complètement différemment.

![Convection cells: warm air rises, cold air falls](../../img/04-thermal-physics-and-materials/04-convection-cells.svg)

*Source: [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:Convection_cells.svg), McSush, CC BY-SA 3.0*

Sans flux d'air :

- le radiateur chauffe fortement dans la zone locale ;
- air nearby heats up, but mixes poorly;
- une partie éloignée de la chambre peut rester froide ;
- plastic, terminals, or insulation nearby may overheat;
- le capteur de température peut ne pas indiquer ce qui se passe à proximité du radiateur.

Avec un débit d'air faible ou inapproprié :

- un peu de chaleur entre dans la chambre ;
- mixing occurs;
- but flow may bypass heater;
- filter, screen, or narrow channel may greatly reduce airflow;
- hot spots still remain.

Avec un débit normal :

- air passes through hot zone;
- la chaleur s'échappe du radiateur vers la chambre ;
- temperature becomes more even;
- Le contrôle PID fonctionne de manière plus prévisible ;
- nearby parts overheat less locally.

Le flux d’air ne crée pas de puissance supplémentaire. Cela aide à éliminer la chaleur déjà générée et à la transférer au bon endroit.

## Convection naturelle et forcée

Il existe deux modes utiles :

- convection naturelle - l'air chaud monte tout seul ;
- convection forcée - le flux est créé par un ventilateur, un ventilateur ou un ventilateur centrifuge.

Pour les petits appareils chauffants, la convection naturelle est souvent insuffisante. Il est lent, dépend de la forme du boîtier et crée facilement des zones de température.

La convection forcée est généralement préférable si vous devez :

- retirez rapidement la chaleur du radiateur ;
- heat chamber evenly;
- pass air through a filter;
- dry filament;
- cool power electronics;
- Gardez le capteur de température dans un flux d'air significatif.

## Fan Is Not Just Size

La phrase « je mettrai un ventilateur de 40 mm » ne vous dit quasiment rien sur le résultat.

Pour un appareil réel, les éléments importants sont :

- air flow;
- static pressure;
- point de fonctionnement après installation dans le boîtier ;
- flow direction;
- résistance des écrans, des filtres et des conduits d'air ;
- air temperature at fan;
- bruit et vibrations ;
- resource under load;
- starting current;
- tachometer or rotation control.

Le catalogue répertorie souvent le débit maximum et la pression statique maximale. Dans un appareil réel, le ventilateur ne fonctionne pas à ces points idéaux. Le filtre, le tamis, le canal étroit, la tournure du conduit d'air et le chauffage dense créent une résistance, de sorte que le débit réel peut être beaucoup plus faible.

Si l'air doit passer à travers un filtre, un radiateur, un nid d'abeilles ou un canal étroit, vous avez souvent besoin non seulement de « plus de CFM », mais aussi d'un ventilateur ou d'une soufflante centrifuge avec une pression statique appropriée.

## Air Path

Good design answers four questions:

1. D’où provient l’air ?
2. Par quoi passe-t-il ?
3. Où dégage-t-il de la chaleur ?
4. Où retourne-t-il ?

Pour une chambre ou un séchoir, la circulation en boucle fermée est utile :

```text
chamber -> fan -> heater -> hot stream -> chamber -> return
```

Pour un filtre, une logique différente peut s'appliquer :

```text
chamber -> filter -> fan -> exhaust or return
```

L’essentiel est que le flux n’emprunte pas le chemin inutile le plus simple en passant par le chauffage ou le filtre. L'air choisit toujours le chemin présentant le moins de résistance.

## Le capteur de température doit voir le bon endroit

Bad options:

- le capteur est juste au niveau du radiateur et détecte une surchauffe locale ;
- le capteur est dans la zone morte et voit un coin froid ;
- le capteur touche le mur métallique et mesure le mur, pas l'air ;
- le capteur est situé avant le chauffage, bien que la température après soit importante ;
- Le capteur est soufflé par un flux qui ne reflète pas la température de la chambre.

Pour les chambres, il est généralement utile de mesurer l'air là où la température doit être contrôlable, mais pas directement au niveau du chauffage. Pour la protection contre la surchauffe à proximité du radiateur, un capteur séparé ou un thermostat/coupure thermique indépendant est nécessaire.

Un capteur de contrôle et un élément d'urgence indépendant valent bien mieux qu'un seul capteur responsable de tout.

## Les filtres et les écrans peuvent tuer le flux

Un filtre, un écran, une grille décorative ou un espace étroit ajoute de la résistance.

Erreurs typiques :

- mettre un filtre dense sur un ventilateur axial faible ;
- entrée semi-bloquante avec écran décoratif ;
- faire un virage serré à droite après le ventilateur ;
- positioning heater so air goes around it;
- oublier que le filtre se bouche avec la poussière et que la résistance augmente ;
- ne laissant aucun accès pour l’entretien du filtre.

Si l'appareil dépend du débit, vérifiez non seulement « le ventilateur tourne » mais aussi que l'air passe réellement dans le bon chemin.

## Que se passe-t-il si le ventilateur tombe en panne

Scénario le plus dangereux pour un chauffage à flux d'air :

```text
fan stopped -> heater keeps working -> local temperature quickly rises
```

Par conséquent, un appareil de chauffage qui repose sur le flux d’air nécessite les mesures suivantes :

- independent overheat protection near hot zone;
- power limiting;
- matériau avec marge de température ;
- distance entre le radiateur et le plastique et l'isolation ;
- contrôle du tachymètre du ventilateur si le ventilateur est critique ;
- vérification du micrologiciel pour le chauffage si vous utilisez Klipper ou similaire ;
- premier test sous observation.

Le micrologiciel aide mais ne remplace pas la protection physique. MOSFET, SSR ou relais peuvent échouer à l'état activé.

## Vérification minimale après assemblage

Après avoir construit un appareil chauffant, vérifiez :

- flow direction;
- y a-t-il un débit à la sortie, pas seulement une rotation du ventilateur ;
- temperature at heater;
- température après chauffage ;
- température dans une partie éloignée de la chambre ;
- température des fils, des bornes et des pièces imprimées ;
- temperature of fan;
- comportement avec filtre partiellement bloqué ;
- le chauffage s'arrête-t-il si le capteur tombe en panne ?
- effectue un déclenchement indépendant de protection contre la surchauffe dans un scénario dangereux.

Faites un premier échauffement sous observation. Il est préférable d'effectuer les mesures après stabilisation et après un fonctionnement prolongé, car le boîtier, les fixations et l'isolation chauffent plus lentement que l'air.

## Connexion à Clipper

Dans Klipper, plusieurs mécanismes sont utiles :

- `heater_fan` - le ventilateur s'allume avec le chauffage ou lorsque la température est atteinte ;
- `temperature_fan` - le ventilateur est contrôlé par un capteur de température séparé ;
- `verify_heater` - vérifie que le chauffage se comporte comme prévu ;
- `tachometer_pin` pour le ventilateur - permet de voir le régime si le ventilateur prend en charge le signal du tachymètre.

Il ne s'agit pas d'un système de sécurité complet, mais d'un bon niveau de contrôle pour les appareils où la température et le débit sont importants.

## Conclusion principale

Dans un appareil chauffé, ce qui compte n’est pas seulement la puissance du chauffage mais aussi le cheminement de l’air. Un bon flux élimine la chaleur du radiateur et la transfère vers la chambre. Un mauvais débit laisse un point chaud, trompe le capteur et augmente le risque de surchauffe du matériau.

Si le chauffage dépend du ventilateur, la panne du ventilateur doit constituer un scénario d’urgence distinct et non une surprise.

## Matériaux sur le Topic

- [Engineering ToolBox: Convective Heat Transfer](https://www.engineeringtoolbox.com/amp/convective-heat-transfer-d_430.html) - explanation of natural and forced convection.
- [SANYO DENKI: Fan Airflow and Static Pressure](https://techcompass.sanyodenki.com/en/training/cooling/fan_basic/004/index.html) - why maximum flow and maximum pressure from catalog do not equal real device operation.
- [SANYO DENKI: Guideline in Selecting a Fan](https://products.sanyodenki.com/info/sanace/en/technical_material/select.html) - practical approach to choosing fan by thermal power, temperature rise, and actual tests.
- [DigiKey: Selecting a Fan](https://www.digikey.com/en/articles/selecting-a-fan) - difference between axial and centrifugal fans, impact of housing and flow resistance.
- [Klipper Documentation: Configuration Reference](https://www.klipper3d.org/Config_Reference.html) - parameters for `heater_fan`, `temperature_fan`, `verify_heater`, and fan tachometer.

## See Also

- [iDryer docs: Connecting a Fan](../06-practical-guides/01-connecting-fan.md) - local instruction on fan power, MOSFET, common GND, and Klipper examples.
