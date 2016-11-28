# Projet de coloration de graphe de Master 1

## GRANIER--RICHARD Pierre
## ROPERCH Thibaut

### Commandes

Compiler :
    make

Executer :
    make launch

Executer en donnant un fichier de graphe en argument :
    ./main.out nom_fichier

Nettoyer le projet :
    make clean

### Travail effectué

Nous avons mis en place trois algorithmes de coloration :
* Approche naïve
* Coloration des sommets trié par ordre décroissant de leur ordre
* Coloration des sommets de la maximum clique en priorité

### Résultats
| Premier algorithme | Deuxième algorithme | Troisième algorithme |
| ------------- |: -------------: | ---------:     |
| Colonne       |     Colonne     |      Colonne   |
| Alignée à     |      Alignée au |     Alignée à  |
| Gauche        |      Centre     |      Droite    |