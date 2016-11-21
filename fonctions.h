#include <stdio.h>
#include <stdlib.h>

// VARIABLES GLOBALES

int NOMBRE_DE_SOMMETS, NOMBRE_D_ARETES;
int NOMBRE_DE_COULEURS = 0;
char **MATRICE_ARETES, **MATRICE_COULEURS; // matrices avec des char 1 ou 0, 0 par défaut

// FONCTIONS

/*
 * Alloue la mémoire suffisante et remplie les matrices de 0
 */
void initialiser_matrice();

/*
 * Met à 1 le char (indice1, indice2) de la matrice des aretes
 */
void ajouter_arete(int indice1, int indice2);

/*
 * Affiche les labels de tous les sommets
 */
void afficher_sommets();

/**
 * Faire plusieurs algos
 */
void colorier();
