#include <stdio.h>
#include <stdlib.h>
#include "aretes_matrice.h"
#include "couleurs_matrice.h"

// FONCTIONS

/*
 * Redimensionne la taille de la matrice des couleurs
 * Libère la mémoire occupée par les matrices
 */
void ajouter_couleur(int indice_couleur);
void liberer_matrices();

/*
 * Affiche les matrices, avec la possibilité de réduire leur taille pour n'en visualiser qu'un échantillon
 */
void afficher_matrice_aretes(int pourcentage_visible);
void afficher_matrice_couleurs(int pourcentage_visible);

/*
 * Retourne une chaine de charactères de la matrice des arêtes et des couleurs au format standard
 */
void format_standard_matrice_aretes();
void format_standard_matrice_couleurs();

/*
 * Met à '1' le char (indice1, indice2) de la matrice des aretes
 * Met à '0' les couleurs de l'indice du sommet donné et à '1' le char (indice_sommet, indice_couleur) de la matrice des couleurs
 */
void ajouter_arete(int indice1, int indice2); // teste une autre fonction qui alloue par bloc de 50 couleurs, et comparer le temps d'execution
void associer_couleur(int indice_sommet, int indice_couleur);

/*
 * Retourne la couleur du sommet
 */
char couleur_du_sommet(int indice_sommet);

/*
 * Vérifie que le graphe est bien colorié, c'est-à-dire qu'il ne contient pas de conflit
 * Un conflit intervient lorsque deux sommets adjascents/frères/liés sont de la même couleur
 * La fonction retourne 1 quand le graphe est correct, 0 sinon
 */
int est_bien_colorie();

/**
 * Algo de coloriage by Bob
 * Algo de coloriage by Tibo
 */
// void bob();
void meilleur_coloriage_opti_de_ouf_lol_tupeuxpastestmdr();
void tibo();