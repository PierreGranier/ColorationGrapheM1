#include <stdio.h>
#include <stdlib.h>

// VARIABLES GLOBALES

int NOMBRE_DE_SOMMETS, NOMBRE_D_ARETES, NOMBRE_DE_COULEURS;
char **MATRICE_ARETES, **MATRICE_COULEURS; // matrices avec des char 1 ou 0, 0 par défaut

// FONCTIONS

/*
 * Alloue la mémoire suffisante pour les matrices et les remplie de '0'
 * Libère la mémoire occupée par les matrices
 */
void initialiser_matrices();
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
 * Met à '1' le char (indice_sommet, indice_couleur) de la matrice des couleurs
 * Met à '0' les couleurs de l'indice du sommet donné et à '1' l'indice de la couleur donnée pour le sommet
 */
void ajouter_arete(int indice1, int indice2); // teste une autre fonction qui alloue par bloc de 50 couleurs, et comparer le temps d'execution
void ajouter_couleur(int indice_sommet, int indice_couleur);
void ecraser_couleur(int indice_sommet, int indice_couleur);

/*
 * Retourne la couleur du sommet
 */
char couleur_du_sommet(int indice_sommet);

/**
 * Algo de coloriage by Bob
 * Algo de coloriage by Tibo
 */
// void bob();
void meilleur_coloriage_opti_de_ouf_lol_tupeuxpastestmdr();
void tibo();
