#include <stdio.h>
#include <stdlib.h>


// STRUCTURE

typedef struct sommet {
	int label;
	int poids;
	int couleur;
} Sommet;


// VARIABLES GLOBALES

int NOMBRE_DE_SOMMETS, NOMBRE_D_ARETES;
Sommet *SOMMETS;
char **MATRICE_GRAPH; // matrice avec des char


// FONCTIONS

/*
 * Retourne l'indice du sommet correspondant au label, -1 sinon
 */
int indice_de(int label);

/*
 * Appele la fonction d'ajout de sommet pour le label1 et le label2
 * Met à 1 les bits (i,j) et (j,i) de la matrice, i et j étant respectivement l'indice du sommet correspondant au label1 et l'indice du sommet correspondant au label2
 */
void ajouter_arete(int label1, int label2);

/*
 * Initialise un sommet à partir d'un label
 * L'ajoute au tableau des sommets s'il n'y a pas déjà de sommet correspondant à ce label
 */
void ajouter_sommet(int label);

/**
 * en faire plusieurs
 */
void colorier();
