# 2023-2024-4GP-BriereRome-Clair
Projet Capteur de Jules et Gabriel 
# Projet Capteur
## Contexte <br>
Nous avons rélalisé ce projet dans le cadre de notre cours de MOSH (Microcontroleur en Open Source Hardware) à l'INSA Toulouse en 4ème année au sein du département de Génie Physique. <br>
L'objectif de ce projet est de tester les caractéristiques d'un capteur de flexion en graphite. <br>
## Somaire
### [1. Présentation Générale](#pg)
### [2. L'électronique analogique](#ea)
### [3. KiCad](KiCad)
### [4. L'Arduino](#dudu)
### [5. L'Application](#app)
### [6. Résultats et datasheet](#res) 

# 1. Présentation Générale <a name="pg">
Voici ci-dessous un schéma de notre projet qui permet de visualiser le lien entre chaque partie. <br>
```mermaid
    graph TD;
    classDef PCB1 fill:pink,color:black,stroke:black;
    classDef App fill:lightblue,color:black,stroke:black;
    B((Carte Arduino))-->Module_BT;
    Boutons-->B((Carte Arduino));
    Ampli-->B((Carte Arduino));
    Potentiomètre -.- OLED;
    Potentiomètre-->Ampli; 
    D[Capteur Graphite]-->Ampli;
    Boutons -.- Potentiomètre;
    B((Carte Arduino))-->Potentiomètre;
    Module_BT -.-> appli;
    B((Carte Arduino))-->OLED;
    A[Flex Sensor]-->B((Carte Arduino));
    PCB
    class Ampli PCB1;
    class Potentiomètre PCB1;
    class Boutons PCB1;
    class OLED PCB1;
    class Module_BT PCB1;
    class Appli App;
    class PCB PCB1;
``` 
Afin de mesurer la flexion de notre capteur graphite nous mesurons sa resistance. Cependant, sa resitance étant très grande, le signal à mesurer est très faible. Nous utilisons donc un amplificateur pour augmenter le signal et qu'il soit ainsi mesurable. Nous utilisons ensuite une carte arduino uno pour mesurer ce signal et le transmettre via bluetooth à une application mobile. Nous utilisons aussi des boutons et un afficheur OLED afin de changer la valeur d'un potententiomètre digital qui module le gain de l'amplificateur. <br>

# 2. L'electronique analogique <a name="ea">
La résistance de notre capteur en graphite varie en fonction de sa flexion. Nous cherchons donc à mesurer les variations de résistance de ce capteur. Cependant il n'y a que des entrée analogique de tension, et les variations de signal sont très petites, il nous faut donc utiliser un circuit amplificateur transimpédence afin d'obtenir une variation de tension mesurable par les convertisseur Analogique-Numérique de l'Arduino.

La résistance du capteur varie en fonction de sa déformation. On impose une tension à ses bornes et on détecte donc une variation de courrant. On fait passer ce courrant dans une résistance de shunt vers la masse, la tension au borne de cette résistance de shunt varie donc avec la déformation du capteur. C'est cette tension que l'on va amplifier.
<br>
Schéma de l'amplificateur : <br>
<img src="Images/ElecAna"   width=50%> <br>
La résistance R2 est remplacée par un potentiomètre digital afin de pouvoir régler le gain de l'amplificateur.

# 3. KiCad : [ici pour les docs](https://github.com/MOSH-Insa-Toulouse/2023-2024-4GP-BriereRome-Clair/tree/main/Shield) <a name="KiCad">
Nous avons réalisé un PCB en utilisant l'application KiCad8. Pour ce faire, nous avons repris le schéma éléctrique decrit ci-dessus. <br>
Nos contraintes etaient les suivantes:
* Largeur de la piste : 0,5 mm minimum
* Isolation des pistes : 0.5mm minimum
* Bluetooth, OLED, Connecteurs (header) : pad à 1mm de diamètre, ovale 2*2.54mm
* Résistance, condensateur, support AOP : Pad à 0.8mm de diamètre, Cercle 2.54mm
* Support AOP, Pot Digital : pad n°1 rectangulaire, les autres ovales ou ronds

Nous avons créé la plupart des emprintes pour les rajouter au PCB. Elles sont disponibles dans nos fichiers. <br>
Une fois le document complété, nous avons imprimé le PCB et avons soudé chacun des composants. <br>
    <br>
   Partie Schématique: <br>
   <img src="Images/Kicad%20partie%201.png"   width=80%> <br>
   <br>
   Partie PCB : <br>
   <img src="Images/Kicad%20partie%202.png"   width=80%> <br>

# 4. L'Arduino : [ici pour le code](https://github.com/MOSH-Insa-Toulouse/2023-2024-4GP-BriereRome-Clair/blob/main/Projet_capt.ino) <a name="dudu">
## Présentation générale
Le programme Arduino permet de réaliser 4 fonctions :
* ***Régalage*** du calibre de l'amplificateur avec **3 boutons**
* ***Affichage*** du choix sur un **ecran OLED**
* ***Acquisition*** des mesurese du **flex sensor**
* ***Communication*** vers une appli Android via **bluetooth**
Le code est modulaire, chaque fonctionnalité est assurée par une fonction indépendante.

## Détail sur les bouton
On utilise 3 boutons (+, - et ok) pour choisir la valeur du gain. La boucle générale met assez de temps à s'exécuter pour ne pas avopir à gérer le débouncing des boutons. On a aussi implémenter un timer qui permet que la valeur de change pas trop vite en cas d'appuie long.
Le code utilise 2 variables (valeur séléctionnée et valeur validée)

## Détail sur l'écran
Nous avons utilisé très simplement la librairie ecranOLED

## Détail sur le potentiomètre numérique
Ce composant communique avec le protocole SPI, nous avons donc utilisé la librairie SPI.

## Détail sur l'acquisition des données
Nous avons fait une lecture analogique sur les entrée puis utilisé map pour que les données soient transférable via le module bluetooth en un seul octet.

## Détail sur la communication
Nous avons écrit les données sur un port série relié au module bluetooth.

# 5. L'Application <a name="app">
Afin de communiquer avec l'adruino, nous avons créé une application en utilisant "MIT app inventor".
## Présentation générale
Notre application comporte : <br>
* 2 graphiques :
    * 1 pour le capteur graphite
    * 1 pour le flex sensor
* 2 afficheurs numériques avec des valeurs entre 0 et 255
  * 1 pour le capteur graphite
  * 1 pour le flex sensor
* 1 bouton de sélection Bluetooth
* 1 bouton de reset pour les graphiques
  <br>
   <img src="Images/code%20app.png"  width=60%> 
   <img src="Images/ecrant%20app.png"  width= 30%> <br>
## Partie 1 : Sélection du périphérique Bluetooth
En cliquant sur le bouton "select bluetooth", vous pouvez ouvrir une liste déroulante et selectionner le bluetooth correspondant au module bluetooth utillisé sur le PCB.
 <img src="Images/code%20app1.png"  width=80%> 
 
## Partie 2 : Reception des données
Le fait de sélectionner un Bluetooth déclenche une horloge qui va séquencer la reception de données. <br>
La boucle de l'horloge verifie si des données sont disponibles. Si il y en a, elle met chacune des deux valeurs (Flex sensor et capteur graphite) dans une variable. <br>
<img src="Images/code%20app2.png"  width=80%> 

## Partie 3 : Affichage graphique
Afin de rendre les données facilement lisibles, nous avons décidé d'utiliser des graphiques. Pour cela nous avons utilisé les chart2D. <br>
Afin de recentrer automatiquement le graphique, nous attendons d'avoir le bon nombre de mesures et utilisons ensuite la fonction SetDomain pour décaler le graphique. Le bouton reset permet de remettre l'echelle à 0.
<img src="Images/code%20app3.png"  width=80%> 

# 6. Résultats et datasheet <a name="res">
### Objectifs
Nous avons monté un banc de test afin d'etudier l'influence du type de crayon utilisé sur les performances du capteur et regarder la variation de résistance. <br>
### Méthode
Pour cela nous avons utilisé des cercles de diamètre differnent (2cm, 3cm, 4cm et 5cm). La déformation est calculée selon l'expression suivante : $\varepsilon = \frac{D}{e}$ avec $D$ diamètre du demi-cercle et épaisseur du papier. <br>
Nous avons ensuite exprimé la variation de résistance en fonction de la deformation. <br>
### Résultats
Nous avons obtenu les courbes ci-dessous. Nous observons que la variation est lineaire et que le type de crayon a une forte influence. Les crayons plus durs ("hard") semblent avoir une plus grande sensibilité que les crayons doux. <br>
Ce resultat est le même en compression et en tension. <br>
<br>
<img src="Images/mesures flexion tension.png"  width=40%>
<img src="Images/mesures flexion compression.png"  width=41%><br>
### datasheet
Afin de synthétiser nos résultats, nous avons fait une datasheet disponible [ici](https://github.com/MOSH-Insa-Toulouse/2023-2024-4GP-BriereRome-Clair/blob/main/Datasheet.docx).
