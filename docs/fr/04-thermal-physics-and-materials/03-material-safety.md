# Matériaux, inflammabilité et émissions nocives

Le matériau de la chambre, du séchoir, du filtre, du boîtier ou du conduit d'air ne peut pas être choisi uniquement en fonction du prix, de l'épaisseur et de la facilité de découpe.

Dans un appareil chauffant, le matériau doit résister non seulement à un fonctionnement normal, mais également à des pannes raisonnables : arrêt du ventilateur, erreur de capteur, interrupteur bloqué, mauvais contact, borne surchauffée ou jet chaud localisé.

## Que signifie « adapté au chauffage »

Le matériau ne convient pas parce qu'il "ne fond pas immédiatement". Pour un appareil chauffé, plusieurs propriétés différentes comptent :

- maximum continuous working temperature;
- softening temperature or thermal deformation temperature;
- flammability;
- smoke generation;
- toxicité des produits de combustion;
- résistance de la colle, du film, du revêtement ou du laminage ;
- comportement au contact de l’air chaud ;
- exigences du fabricant pour l’assemblage.

La température de fusion en elle-même est presque inutile. Le plastique peut perdre sa rigidité et sa forme bien avant de fondre. L'isolation peut changer de dimensions. La colle peut se décoller. Une pièce imprimée peut se déformer sous la charge.

## Température de fonctionnement et marge de sécurité

Tout d'abord, il faut comprendre quelle sera la température non pas « en moyenne dans la chambre », mais à des endroits précis :

- près du radiateur ;
- at hot air outlet;
- à proximité des bornes et des fils ;
- on metal fasteners;
- on inner wall;
- on printed parts;
- under insulation;
- on outer surface.

Si la chambre contient `45°C`, cela ne signifie pas que toutes les pièces à l'intérieur sont également `45°C`. À proximité du radiateur ou dans le conduit d'air, il peut faire beaucoup plus chaud.

Règle pratique : le matériau doit avoir une marge de sécurité pour une température de travail continue exactement pour l'endroit où il se trouve. Pour la zone adjacente au radiateur, la marge doit être plus grande que pour le panneau décoratif extérieur.

## Inflammabilité - Ce n'est pas un seul mot

La documentation peut contenir différents systèmes de classification.

Pour les plastiques, UL 94 est souvent indiqué :

- `HB` - horizontal sample burns slower than specified limit;
- `V-1`, `V-0`, `V-0` - l'échantillon vertical doit s'auto-éteindre dans un délai spécifié, les différences incluent le comportement d'égouttement ;
- `5VA`, `5VA` - tests plus stricts pour certaines applications ;
- `HF-1`, `HF-2`, `HF-2` - classes pour matériaux en mousse.

Important : UL 94 est un test en laboratoire à petite échelle sur des échantillons. Cela aide à comparer les matériaux, mais ne prouve pas qu'une chambre faite maison est sûre en cas de panne.

Dans la documentation sur les matériaux de construction en langue russe, vous pouvez rencontrer :

- `НГ` - non-flammable material;
- `Г1-Г4` - flammability groups;
- `В1-В3` - ignitability;
- `Д1-Д3` - smoke-generating ability;
- `Т1-Т4` - toxicité des produits de combustion ;
- `РП1-РП4` - flame spread across surface.

Si un vendeur écrit « auto-extinguible », cela ne remplace pas la fiche technique. Le matériau peut encore fumer, couler, se carboniser, se déformer ou libérer des produits dangereux en cas de surchauffe.

## Exemple : XPS, EPS et PIR

Les matériaux d’isolation des bâtiments semblent souvent pratiques pour une chambre ou un séchoir : ils sont légers, plats, bon marché, bien coupés et bien isolés. Mais ils doivent être considérés comme des matériaux de construction avec leurs propres limites, et non comme des pièces universelles pour un appareil de chauffage.

| Material | Where It May Be Appropriate | Main Risks | What to Check |
| --- | --- | --- | --- |
| XPS, extruded polystyrene | external insulation of cold zones if separated from hot part | limited working temperature, deformation, flammability, smoke in fire | technical description, maximum temperature, fire characteristics, protective layer |
| EPS, expanded polystyrene | only cautiously and far from hot zones | low thermal resistance, flammability, deformation, smoke | material datasheet, no direct heating, cover with non-flammable layer |
| PIR / polyiso | building-type insulation, sometimes better fire behavior than polystyrene sheets | not automatically non-flammable, depends on facing and specific product | technical description, working temperature, reaction to fire class, manufacturer limitations |
| Mineral wool | thermal insulation where fibers are permissible and high thermal resistance is needed | dust, fibers, compression, moisture, need to seal airflow | permissible temperature, binder, protective facing, assembly |
| Metal | screen, inner wall, heat spreader | thermal bridges, hot outer surface, sharp edges | grounding for mains section, temperature, wire insulation |
| 3D-printed plastic | fasteners and shrouds outside hot zone | softening, creep under load, flammability | material, deformation temperature, actual part temperature |

Pour XPS, dans les données techniques du fabricant, la température de service maximale autour de `165°F` (`165°F`) est souvent indiquée. Cela ne signifie pas que tous les XPS sont identiques, mais montre l'ordre de limitation : ce matériau ne peut pas être automatiquement placé à côté d'un radiateur ou d'un air chaud.

Pour l'EPS, des recommandations visant à maintenir les températures de travail autour de `75°C` sont trouvées ; au-delà, le matériau peut perdre sa stabilité dimensionnelle. Là encore, la valeur exacte doit être tirée de la documentation spécifique du produit.

Le PIR/polyiso peut avoir une plage admissible plus élevée dans certains produits, mais cela n'élimine pas la vérification des propriétés au feu, du revêtement, de la colle, de la fumée et des recommandations du fabricant.

## Matériel sûr "Pile"

Pour une chambre chauffée, il est souvent préférable de ne pas penser à un « matériau de paroi » mais à des couches.

![Example of material layers next to heat](../../img/04-thermal-physics-and-materials/03-safe-material-stack.svg)

Exemple de logique plus solide :

- à l'intérieur de la zone chaude - métal, céramique, verre ou autre matériau qui résiste à la température et ne s'enflamme pas en raison d'une surchauffe locale ;
- en outre - un espace d'air ou une isolation si cela est vraiment nécessaire ;
- à l'extérieur - un logement qui ne chauffe pas à des températures dangereuses ;
- les fils et bornes ne touchent pas l'isolant et ne sont pas cachés dans des zones où une surchauffe passerait inaperçue ;
- il existe une protection indépendante contre la surchauffe si une défaillance du contrôle peut entraîner un échauffement dangereux.

L’isolation ne doit pas être le premier matériau à voir le radiateur.

## 3D-Printed Parts Near Heat

Le plastique imprimé est pratique pour les supports, les carénages, les supports de capteurs et les conduits d'air. Mais dans une chambre chauffée, il peut se comporter pire qu'il n'y paraît à partir de la bobine.

Risques typiques :

- Le PLA perd rapidement sa rigidité lorsqu'il est chauffé et sous charge ;
- Le PETG est meilleur que le PLA, mais peut également fluer et se déformer ;
- L'ABS/ASA tolère généralement mieux la chambre chaude, mais nécessite une vérification réelle de la température ;
- Les matériaux PC et techniques peuvent résister à davantage, mais nécessitent une impression appropriée et n'éliminent toujours pas l'évaluation au feu.

Pour les pièces proches du radiateur, vous ne pouvez pas vous fier uniquement au nom en plastique. La marque du filament, les paramètres d'impression, l'épaisseur, la charge, la direction de la couche, la ventilation et la température réelle de la pièce sont importants.

## Que lire avant d'acheter

Recherchez des documents techniques, pas marketing :

- technical description or product datasheet;
- FDS/MSDS si le matériau peut chauffer, être coupé, poncé ou brûler ;
- classement au feu/réaction au feu ;
- UL 94 ou autre classe d'inflammabilité pour les plastiques ;
- maximum continuous working temperature;
- assembly limitations;
- limitations du contact avec les sources de chaleur ;
- exigences relatives au revêtement avec un parement, du métal, des cloisons sèches ou une autre couche.

Si le matériau est vendu uniquement comme « feuille isolante » sans fiche technique appropriée, il ne doit pas être placé dans un appareil chauffant fait maison.

## Ce qui n'est définitivement pas normal

Bad solutions:

- coller de la mousse ou du XPS directement à côté du radiateur ;
- directing hot stream at unknown plastic;
- recouvrir les bornes et les fils d'isolant ;
- placer un matériau inflammable à côté de la section secteur `110-230V AC` ;
- s'appuyer sur un seul capteur de température ;
- traiter les matériaux de construction comme étant sans danger pour la chambre sans vérification ;
- utiliser « auto-extinguible » en remplacement d'une protection indépendante contre la surchauffe ;
- faire un premier échauffement sans observation ni mesures.

## Conclusion principale

La sécurité des matériaux n’est pas un seul paramètre. Vous devez examiner la température de travail, l'inflammabilité, la fumée, la toxicité des produits de combustion, les colles, les revêtements et les scénarios de défaillance réels.

Si le matériel n’a pas de documentation claire, il ne peut pas être placé à proximité du radiateur comme protection primaire. Si le matériau est inflammable, il doit être retiré de la zone chaude, recouvert d'une couche appropriée et vérifié par mesure en mode de fonctionnement réel.

## Matériaux sur le Topic

- [UL Solutions: Combustion Fire Tests for Plastics](https://www.ul.com/services/combustion-fire-tests-plastics) - explanation of UL 94, vertical/horizontal tests, classes for plastics and foam materials.
- [UL Solutions Code Authorities: UL 94 Rating Certifications and Limitations](https://code-authorities.ul.com/about/blog/understanding-ul-94-rating-certifications-and-limitations/) - limitations of UL 94 application to real products and large parts.
- [Russian Emergency Ministry: Federal Law No. 123-FZ, Technical Regulations on Fire Safety Requirements](https://mchs.gov.ru/uploads/document/2022-04-08/c907f456516c1f21009131cfdb944deb.pdf) - Russian fire hazard classification of materials: flammability, ignitability, smoke, toxicity, flame spread.
- [DuPont: Styrofoam Brand XPS Product Information Sheet](https://www.dupont.com/content/dam/dupont/amer/us/en/performance-building-solutions/public/documents/en/styrofoam-brand-ultra-sl-pis-43-D100087-enUS.pdf) - example of XPS technical description with maximum service temperature `165°F`.
- [IKO: EPS Insulation in an IKO Roof System](https://www.iko.com/comm/documents/bulletin-eps-insulation-in-an-iko-roof-system/) - example of EPS working temperature limitation and dimensional stability.
- [Prusa Knowledge Base: Material table](https://help.prusa3d.com/materials) - practical reference for thermal resistance of popular 3D printing materials.
