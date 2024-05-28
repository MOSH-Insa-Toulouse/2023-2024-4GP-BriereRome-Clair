# 2023-2024-4GP-BriereRome-Clair
Projet Capteur de Jules et Gabriel 
### Projet Capteur

## Le projet
```mermaid
graph TD;
    A[Flex Sensor]-->B((Carte Arduino));
    B((Carte Arduino))-->G[Module BT];
    E[Boutons]-->B((Carte Arduino));
    B[Capteur Graphite]-->C[Ampli];
    C[Ampli]-->B((Carte Arduino));
    C[Ampli]<--> D[Potetiomètre];
    D[Potetiomètre] -.- E[Boutons];
    E[Boutons]-.-F[OLED];
    H[(Appli)] -.- G[Module BT];

```

### Contexte <br>
Nous avons rélaié ce projet dans le carde de notre cours de MOSH à l'INSA Toulouse en 4A au sein du Génie Physique. <br>
### Contact <br>
Jules: jules.briere-rome@insa-toulouse.fr <br>
Gabriel: clair@insa-toulouse.fr

### Table des matières
## Nous avons séparé notre travail en plusieurs parties: 
[Le Kicad](


