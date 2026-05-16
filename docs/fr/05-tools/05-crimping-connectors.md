# Sertissage des connecteurs

Le sertissage est une méthode pour connecter un fil à un terminal ou contact sans soudage.

Un bon sertissage offre :

- contact électrique ;
- rétention mécanique du fil ;
- support d'isolation ;
- répétabilité ;
- assemblage et maintenance pratiques.

Un mauvais sertissage peut chauffer, se détacher, causer des erreurs aléatoires et ressembler à presque normal.

## Pourquoi le sertissage est souvent meilleur que le soudage

Pour les connecteurs et terminaux, le sertissage est souvent meilleur que le soudage parce que :

- le fil reste flexible ;
- le contact est conçu par le fabricant ;
- l'isolation est conservée ;
- le joint gère mieux la vibration ;
- le connecteur peut être démonté et entretenu ;
- pas de risque de faire fondre le corps du connecteur en plastique pendant le soudage.

Le soudage est bon pour les pads et les fils, mais ne devrait pas remplacer un contact approprié dans un connecteur si le fabricant prévoyait le sertissage.

## Types de terminaux et connecteurs

Dans les appareils simples, vous trouvez souvent :

- Dupont - connexions de signal faible pour breadboards ;
- JST-XH/JST-PH et similaires - capteurs, ventilateurs, petits modules ;
- cosses - extrémités pour fil multibrins dans terminaux à vis ;
- Faston - terminaux plats pour certaines connexions d'alimentation ;
- terminaux en anneau et en pala ;
- terminaux à vis ;
- blocs de terminaux montés sur la carte.

Chaque type nécessite son propre contact, son propre calibre de fil et son propre outil.

## Vous avez besoin du bon outil

Les pinces ne sont pas un outil de sertissage.

Vous pouvez serrer un contact pour qu'il semble tenir, mais vous n'obtiendrez pas un sertissage approprié.

Pour un bon sertissage, vous avez besoin de :

- un terminal pour le calibre de fil correct ;
- longueur de dénudage correct ;
- matrice d'outil correcte ;
- position correcte du contact dans la matrice ;
- zones séparées pour sertissage de brin et d'isolation ;
- aucun brin endommagé.

Les fabricants professionnels de connecteurs fournissent des spécifications de sertissage, hauteur de sertissage, longueur de dénudage et force de traction. Pour l'assemblage DIY, vous n'avez pas toujours un contrôle total, mais le principe est le même : le contact, le fil et l'outil doivent correspondre l'un à l'autre.

## Sertissage de tonneau ouvert

De nombreux petits contacts, comme JST ou Dupont, ont deux paires d'« ailes » :

- une paire sertit le conducteur nu ;
- l'autre paire tient l'isolation.

Bon résultat :

- le conducteur est visible dans la zone correcte ;
- l'isolation est tenue par les ailes arrière ;
- la longueur exposée n'est pas trop longue ;
- les brins du conducteur ne dépassent pas ;
- le contact n'est pas asymétrique ;
- le contact entre dans le corps du connecteur et se verrouille en place.

Si l'isolation est entrée dans la zone de sertissage du conducteur, le contact électrique sera mauvais.

Si seulement le conducteur est sertit et l'isolation n'est pas tenue, le fil peut se casser quand il bouge.

## Cosses

Pour fil multibrins dans un terminal à vis, les cosses sont souvent utiles.

Elles :

- rassemblent tous les brins ensemble ;
- empêchent les brins de se séparer ;
- améliorent l'assise dans le terminal ;
- réduisent le risque que certains brins restent à l'extérieur ;
- rendent le joint plus net.

Cela est particulièrement utile pour les fils d'alimentation, les blocs de terminaux et les assemblages qui seront entretenus.

Mais les cosses doivent aussi correspondre au calibre du fil et être sertites avec la bonne matrice.

## Comment vérifier un sertissage

Après sertissage, vérifiez :

- le contact ne bouge pas sur le fil ;
- l'isolation est tenue ;
- le conducteur ne se détache pas ;
- aucun brin n'est coupé ;
- la longueur exposée n'est pas trop longue ;
- le contact entre dans le corps du connecteur ;
- le verrouille se met en place ;
- le fil résiste à une traction douteuse.

Un test de traction douce est utile : tirez doucement le fil. Il ne devrait pas se détacher du contact.

Pas besoin de tirer de toutes vos forces. L'objectif est de trouver les mauvais sertissages avant installation.

## Pourquoi les mauvais sertissages chauffent

Un mauvais sertissage crée une résistance élevée.

Sous courant, cela devient de la chaleur.

D'abord, le terminal peut juste être chaud. Ensuite, le plastique s'assombrit, le contact s'aggrave, la chaleur augmente.

Cela est particulièrement dangereux pour :

- les chauffages ;
- les ventilateurs avec courant significatif ;
- les bandes LED ;
- les alimentations ;
- les circuits SSR/MOSFET ;
- les connexions secteur.

Si un terminal chauffe, éteignez l'alimentation et refaites la connexion.

## Dupont n'est pas pour l'alimentation

Dupont est pratique pour les breadboards et les signaux faibles.

Mais il ne peut pas être utilisé comme connecteur d'alimentation approprié pour :

- un chauffage ;
- l'alimentation de l'appareil ;
- une bande LED puissante ;
- les parties secteur ;
- un moteur ou servo avec courant important.

Même si le connecteur s'adapte physiquement aux broches, cela ne signifie pas qu'il est évalué pour le courant, la vibration et la chaleur nécessaires.

## Erreurs courantes

- sertit avec les pinces ;
- a choisi le mauvais terminal de calibre ;
- dénudé trop d'isolation ;
- dénudé trop peu d'isolation ;
- sertit l'isolation au lieu du conducteur ;
- n'a pas sertit le support d'isolation ;
- coupé certains brins ;
- le contact n'a pas verrouillé dans le corps ;
- la ligne d'alimentation tenue sur Dupont ;
- mauvais calibre de cosse ;
- n'a pas fait de test de traction ;
- le terminal chauffe mais l'appareil continue de fonctionner.

## Les éléments essentiels

- Le sertissage est à la fois contact électrique et rétention mécanique.
- Le contact, le fil et l'outil doivent correspondre l'un à l'autre.
- Les pinces ne remplacent pas un outil de sertissage.
- Pour fil multibrins dans un terminal à vis, les cosses sont souvent utiles.
- Les mauvais sertissages peuvent chauffer et être dangereux.
- Les parties d'alimentation ne devraient pas s'appuyer sur les connecteurs faibles du breadboard.

## Matériaux de référence

- [Molex: Quality Crimp Handbook](https://www.molex.com/content/dam/molex/molex-dot-com/products/automated/en-us/commercialcrimpbookpdf/638/63800/TM-638000029-001.pdf?inline=) - référence de qualité de sertissage détaillée, force de traction, sertissage de conducteur et d'isolation.
- [Molex: Industrial Crimp Quality Handbook](https://www.molex.com/content/dam/molex/molex-dot-com/products/automated/en-us/industrialcrimpbookpdf/640/64016/TM-640160065-001.pdf?inline=) - inspection visuelle du sertissage de tonneau ouvert et fermé, longueur de dénudage, pinceau de fil et défauts courants.
- [JST: Application Tooling Guide, Crimp Style](https://www.jst.com/resources/application-tooling-guide/crimp-style/) - exemple de comment les contacts JST spécifiques ont besoin d'outils spécifiques, longueur de dénudage et spécifications de traction.
- [American Electrical: Wire Ferrules](https://www.americanelectrical.com/wire-ferrules/) - pourquoi les cosses sont utiles pour fil multibrins dans blocs de terminaux.
- [TE Connectivity: Wire Splices](https://www.te.com/en/products/terminals-splices/splices.html) - types de connexion de sertissage/épissure industriels et pourquoi le sertissage est conçu séparément, pas compression aléatoire.
