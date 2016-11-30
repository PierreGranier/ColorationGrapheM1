# Projet de coloration de graphe de Master 1

## GRANIER--RICHARD Pierre, ROPERCH Thibaut

### Commandes

Compiler :

    make

Executer :

    make launch

Executer en donnant un fichier de graphe en argument :

    ./main.out nom_fichier

Nettoyer le projet (supprime les exécutables) :

    make clean

Exemple d'utlisation des commandes :

    make clean ; make ; ./main.out graphes/r1000.1c.col

### Travail effectué

Nous avons mis en place trois algorithmes de coloration :
* Approche naïve
* Coloration des sommets triés par ordre décroissant de leur ordre
* Coloration des sommets de la maximum clique en priorité

Via le menu, il est possible d'executer ces algorithmes :
* Ensemble - L'algorithme qui aura utilisé le moins de couleurs sera retenu et la coloration du graphe sera enregistrée dans un fichier de sortie
* Individuellement - La coloration du graphe sera enregistrée dans un fichier de sortie

*Notes :*
*Le fichier de sortie contient sur une ligne le nombre de couleurs utilisées et sur une deuxième ligne la couleur de chaque sommet ordonnés selon leur nom par ordre croissant.*
*Le fichier sera nommé NomGraphe_out.txt et généré dans le même dossier que le fichier NomGraphe.col donné au programme.*

### Graphes de test

[Lien pour télécharger des graphes de test](http://www.info.univ-angers.fr/pub/porumbel/graphs/)
