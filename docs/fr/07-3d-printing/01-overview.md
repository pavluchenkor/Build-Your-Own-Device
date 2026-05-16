# Impression 3D

Cette section n'est pas un cours d'impression 3D.

Elle sert un objectif différent : aider à comprendre quelles pièces imprimées peuvent être utilisées en toute sécurité dans un appareil fait maison, et lesquelles deviennent un risque près des chauffages, de l'électronique, du câblage et des pièces mobiles.

Dans les projets semblables à iDryer, l'impression 3D est généralement utilisée pour :

- les boîtiers ;
- les capots ;
- les conduits d'air ;
- les supports de ventilateurs ;
- les porte-capteurs ;
- les guides ;
- les poignées et les clips ;
- les panneaux décoratifs ou de service.

Imprimer une pièce est facile. La faire fonctionner en toute sécurité dans un boîtier chaud pendant des mois est plus difficile.

## Questions clés

Avant d'imprimer une pièce pour un appareil, vous devez répondre non seulement à « le fichier STL entrera-t-il dans le slicer », mais aussi à plusieurs questions :

- où la pièce sera-t-elle située ;
- quelle température y aura-t-il là ;
- y a-t-il un chauffage à proximité ;
- y a-t-il du courant alternatif 110-230V à proximité ;
- la pièce supportera-t-elle une charge ;
- entrera-t-elle en contact avec des fils ;
- dirigera-t-elle l'air chaud ;
- peut-elle être remplacée ou entretenue ;
- que se passe-t-il si elle se déforme.

Si la déformation d'une pièce peut décaler un capteur, bloquer le flux d'air, rapprocher un fil d'une zone chaude ou desserrer le montage du chauffage, ce n'est plus seulement un « défaut cosmétique ».

## Le fichier STL n'est pas une instruction d'assemblage

Le fichier STL décrit la forme d'une pièce, mais ne vous dit pas :

- dans quel matériau l'imprimer ;
- dans quelle orientation l'imprimer ;
- combien de parois utiliser ;
- quel remplissage appliquer ;
- où les supports sont nécessaires ;
- quelles vis utiliser ;
- quelle température la pièce supportera ;
- dans quelle direction elle sera plus faible.

Le même modèle peut être un capot normal ou un mauvais support structurel selon le matériau, l'orientation et les conditions de travail.

Par conséquent, une pièce fonctionnelle nécessite non seulement un fichier STL, mais aussi du contexte : matériau, paramètres d'impression, lieu d'installation, charge et régime de température.

## Le matériau est plus important que l'apparence

Pour un prototype, le PLA fonctionne souvent. Il s'imprime facilement et produit une pièce d'aspect agréable.

Mais pour les pièces près de la chaleur, le PLA est un mauvais choix. Le problème n'est pas qu'il fondra immédiatement, mais qu'il peut progressivement perdre sa rigidité et sa forme aux températures trouvées dans un boîtier fermé ou près d'un chauffage.

Pour les pièces fonctionnelles autour d'un séchoir, d'une chambre ou d'un chauffage, vous considérez généralement :

- l'ABS ;
- l'ASA ;
- des matériaux techniques plus résistants à la chaleur, si vous avez de l'expérience et une imprimante appropriée.

Le matériau est choisi en fonction des conditions :

- la température de travail ;
- la rigidité ;
- la résistance aux chocs ;
- le rétrécissement et la déformation ;
- l'odeur et les émissions lors de l'impression ;
- le comportement lorsqu'il est chauffé ;
- la documentation du fabricant.

## Température à l'intérieur d'un boîtier

La température à l'intérieur d'un boîtier fermé diffère de la température ambiante.

Même si le chauffage ne touche pas le plastique, une pièce peut être :

- dans un flux d'air chaud ;
- près du chauffage ;
- près d'un dissipateur thermique ;
- près de l'alimentation électrique ;
- dans une zone avec une mauvaise ventilation ;
- sur une paroi qui se réchauffe lentement.

Par conséquent, vous ne pouvez pas évaluer la sécurité avec seulement la phrase « la pièce ne touche pas le chauffage ». Vous devez comprendre quelle température sera présente à cet endroit pendant une opération prolongée.

![Zones dans un boîtier imprimé pour un appareil chauffé](../../../img/06-3d-printing/01-printed-device-zones.svg)

## La résistance dépend de la direction des couches

Les pièces FDM ne sont pas également résistantes dans toutes les directions.

La direction des couches affecte la façon dont une pièce se casse :

- le long des lignes de plastique, elle est généralement plus résistante ;
- entre les couches, elle est souvent plus faible ;
- les poteaux et clips minces peuvent se casser entre les couches ;
- les vis peuvent délaminier une pièce si la géométrie n'est pas conçue pour cela.

Pour les supports structuraux, il est important de penser à la direction de la charge.

Si un support de ventilateur s'accroche simplement à un mur, c'est une chose. Si un support maintient un chauffage ou un axe de bobine, l'orientation de l'impression et l'épaisseur de la paroi deviennent importants.

## Le boîtier doit être facile à entretenir

Un bon boîtier n'est pas seulement une boîte jolie.

Il doit permettre :

- l'accès aux bornes ;
- le remplacement d'un ventilateur ;
- l'inspection d'un capteur de température ;
- le serrage des fixations ;
- le retrait d'un contrôleur ;
- le remplacement d'un fil ;
- de voir si quelque chose s'est surchauffé ou noirci.

Si vous devez démonter la moitié de l'appareil pour accéder à un fusible ou à une borne, il sera entretenu moins souvent. C'est une mauvaise pratique d'ingénierie.

## La pièce imprimée ne doit pas compromettre la sécurité

Un boîtier imprimé peut être utile, mais il ne doit pas transformer une petite erreur en situation dangereuse.

Mauvais scénarios :

- le support du chauffage s'est ramolli ;
- le conduit d'air s'est déformé et le flux d'air à travers le chauffage a diminué ;
- le support du thermisteur s'est déplacé ;
- un fil s'est frotté contre une arête vive ;
- la borne s'est retrouvée serrée contre le plastique ;
- le capot a bloqué la ventilation de l'alimentation électrique ;

Pour les zones chaudes et soumises à des charges, il est préférable de penser ainsi : si une pièce imprimée se déforme, l'appareil doit soit rester sûr, soit entrer dans un état d'erreur, pas continuer à chauffer à l'aveugle.

## Ce qui sera couvert dans cette section

La section couvre plusieurs sujets pratiques :

- `02-what-is-stl.md` - pourquoi le fichier STL ne contient pas le matériau, l'orientation, la résistance ou les instructions d'assemblage.
- `03-materials-petg-abs-asa.md` - les choix élémentaires entre le PETG, l'ABS et l'ASA.
- `04-heat-resistant-materials.md` - comment penser aux pièces près de la chaleur.
- `05-enclosure-design.md` - les zones du boîtier, la ventilation, la fixation, l'accès et le câblage.
- `06-why-pla-is-risky.md` - pourquoi le PLA est pratique pour les prototypes mais risqué près de la chaleur.

## Ce que cette section ne fait pas

Il n'y aura pas de cours complet d'impression 3D ici.

Nous ne nous plongerons pas dans :

- tous les plastiques du monde ;
- les paramètres de rétraction ;
- le post-traitement décoratif ;
- les modèles artistiques ;
- l'étalonnage parfait de l'imprimante ;
- la sélection spécifique de marques de filaments.

L'accent est simple : les pièces pour un appareil réel doivent être suffisamment robustes, résistantes à la chaleur, faciles à entretenir et sûres.

## Points clés

- Le fichier STL n'est que la géométrie, pas les instructions d'assemblage sûres.
- Le matériau est choisi en fonction de la température de travail et de la charge, pas de l'apparence.
- Le PLA est pratique pour les prototypes mais risqué près de la chaleur.
- L'orientation de l'impression affecte la résistance.
- Le boîtier doit séparer la zone chaude, l'électronique, le câblage d'alimentation et la zone utilisateur.
- Une pièce imprimée ne doit pas être la seule chose protégeant la sécurité de l'appareil.

## Références

- [Base de connaissances Prusa : Guide des matériaux](https://help.prusa3d.com/category/material-guide_220) - aperçu des matériaux populaires, des conditions d'impression et des propriétés.
- [Base de connaissances Prusa : PLA](https://help.prusa3d.com/article/pla_2062) - description du PLA comme matériau simple pour les prototypes et les pièces sans charge thermique élevée.
- [Base de connaissances Prusa : Poteau de guide du boîtier](https://cdn.help.prusa3d.com/article/enclosure-guidepost_366332) - pourquoi une chambre d'impression fermée est nécessaire et comment la température ambiante affecte l'impression et les matériaux.
- [Bambu Lab : Guide de comparaison des filaments pour imprimante 3D](https://bambulab.com/en-us/filament-guide) - tableau comparatif des matériaux, y compris le PLA, le PETG, l'ABS, l'ASA et les plastiques techniques.
- [Makelab : L'impression 3D est-elle suffisamment résistante pour les pièces fonctionnelles ?](https://help.makelab.com/help/article/is-3d-printing-strong-enough-for-functional-parts) - notes pratiques sur le matériau, l'orientation de l'impression, les parois, le remplissage et les pièces fonctionnelles.
