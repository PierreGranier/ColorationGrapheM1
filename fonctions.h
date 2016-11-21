#include <stdio.h>
#include <stdlib.h>

// VARIABLES GLOBALES

int NOMBRE_DE_SOMMETS, NOMBRE_D_ARETES, NOMBRE_DE_COULEURS;
char **MATRICE_ARETES, **MATRICE_COULEURS; // matrices avec des char 1 ou 0, 0 par défaut

// FONCTIONS

/*
 * Alloue la mémoire suffisante et remplie les matrices de 0
 */
void initialiser_matrices();

/*
 * Afficher les matrices, avec la possibilité de réduire leur taille pour n'en visualiser qu'un échantillon
 */
void afficher_matrice_aretes(int div_par);
void afficher_matrice_couleurs(int div_par);

/*
 * Met à 1 le char (indice1, indice2) de la matrice des aretes
 */
void ajouter_arete(int indice1, int indice2);

/**
 * Faire plusieurs algos de coloriage
 */
void colorier();

/*
 * Libère la mémoire occupée par les matrices
 */
void liberer_matrices();