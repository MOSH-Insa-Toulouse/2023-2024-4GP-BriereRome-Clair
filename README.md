# 2023-2024-4GP-BriereRome-Clair
Projet Capteur de Jules et Gabriel 
# Projet Capteur

## Le projet


## Contexte <br>
Nous avons rélaié ce projet dans le carde de notre cours de MOSH à l'INSA Toulouse en 4A au sein du Génie Physique. <br>
L'objectif de ce projet est de tester les caractéristiques d'un capteur en graphique. <br>

## Contact <br>
Jules: jules.briere-rome@insa-toulouse.fr <br>
Gabriel: clair@insa-toulouse.fr

# 1. Presentation Générale
<details>
<summary> plus </summary>
Voici un petit schéma de notre projet.
    ```mermaid
graph TD;
    A[Flex Sensor]-->B((Carte Arduino));
    B((Carte Arduino))-->G[Module BT];
    E[Boutons]-->B((Carte Arduino));
    E[Boutons]-.-F[OLED];
    B[Capteur Graphite]-->C[Ampli];
    C[Ampli]-->B((Carte Arduino));
    C[Ampli]<--> D[Potetiomètre];
    D[Potetiomètre] -.- E[Boutons];
    H[(Appli)] -.- G[Module BT];
    ``` 
    Le projet comprend plusieures parties differentes. Le principe est que nous amplificatieur pour lire la valeur de la du capteur sur l'arduino. Nous utilisons ensuite une application mobile pour lire les mesures sur notre téléphone. <br>
        Chacune de parties de ce projet est detaillé ci-dessous.
</details>

# 2. L'electronique analogique
<details>
<summary> plus </summary>
Notre capteur est un capteur à resistance variable. Ainsi, pour lire la valeur de la resistance, nous utilisons un pont diviseur de tension.<br>
    Cependnat, le signal obtenu est très faible. Pour l'amplifier, nous utilisons un montage...<br>
    Gabriel c'est ta partie
</details>

# 3. KiCad : [ici pour les docs](https://github.com/MOSH-Insa-Toulouse/2023-2024-4GP-BriereRome-Clair/tree/main/Shield)
<details>
<summary> plus </summary>
    Nous avons réalisé un PCB en utilisant l'application Kicad. Pour ce faire, nous avons repris le schéma éléctrique decrit ci-dessus. <br>
    Une fois le document complété, nous avons imprimé le PCB et avons soudé chacun des composants. <br>
    
</details>

# 4. L'Arduino : [ici pour le code](lien)
<details>
<summary> plus </summary>
Coucou
</details>

# 5. L'Application
<details>
<summary> plus </summary>
Coucou
</details>


