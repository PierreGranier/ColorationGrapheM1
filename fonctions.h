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
 */
void ajouter_arete(int indice1, int indice2);
void ajouter_couleur(int indice_sommet, int indice_couleur);

/**
 * Algo de coloriage by Bob
 * Algo de coloriage by Tibo
 */
void bob();
void tibo();
