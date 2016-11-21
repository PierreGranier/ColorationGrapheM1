#include "fonctions.h"

int NOMBRE_DE_COULEURS = 0;

void initialiser_matrices() {
	// dimensionne les tableaux à deux dimensions

	MATRICE_ARETES = (char**)malloc(NOMBRE_DE_SOMMETS * sizeof(char*)); // NxN
	for (int i = 0; i < NOMBRE_DE_SOMMETS; ++i) { // dimensionne chaque ligne à une dimension
		MATRICE_ARETES[i] = (char*)malloc(NOMBRE_DE_SOMMETS * sizeof(char));
	}
	
	MATRICE_COULEURS = (char**)malloc(NOMBRE_DE_COULEURS * sizeof(char*)); // 0xN

	// remplit les matrices de '0'

	for (int i = 0; i < NOMBRE_DE_SOMMETS; ++i) {
		for (int j = 0; j < NOMBRE_DE_SOMMETS; ++j) {
			MATRICE_ARETES[i][j] = '0';
		}
	}

	for (int i = 0; i < NOMBRE_DE_COULEURS; ++i) {
		for (int j = 0; j < NOMBRE_DE_SOMMETS; ++j) {
			MATRICE_COULEURS[i][j] = '0';
		}
	}
}

void afficher_matrice_aretes(int div_par) {
	printf("\n\n########################################\n");
	printf("# MATRICE ARETES\n# Taille %d x %d (lignes x colonnes)\n# Visualisée à %d %%\n########################################\n\n", NOMBRE_DE_SOMMETS, NOMBRE_DE_SOMMETS, 100/div_par);
	
	for (int i = 0; i < NOMBRE_DE_SOMMETS/div_par; ++i) {
		// for (int j = 0; j < NOMBRE_DE_SOMMETS/div_par; ++j)
		for (int j = 0; j <= i; ++j)
			(i == j) ? printf("\\") : printf("%c ", MATRICE_ARETES[i][j]);
		printf("\n");
	}
	printf("\n");
}

void afficher_matrice_couleurs(int div_par) {
	printf("\n\n########################################\n");
	printf("# MATRICE COULEURS\n# Taille %d x %d (lignes x colonnes)\n# Visualisée à %d %%\n########################################\n\n", NOMBRE_DE_COULEURS, NOMBRE_DE_SOMMETS, 100/div_par);
	
	for (int i = 0; i < NOMBRE_DE_COULEURS/div_par; ++i)
		for (int j = 0; j < NOMBRE_DE_SOMMETS/div_par; ++j)
			printf("%c ", MATRICE_COULEURS[i][j]);
		printf("\n");
}

void ajouter_arete(int indice1, int indice2) {
	MATRICE_ARETES[indice1][indice2] = '1';
	// MATRICE_ARETES[indice2][indice1] = '1';
}

// quand on coloriera, il faudra re-allouer de la mémoire pour chaque nouvelle couleur
/*
	MATRICE_COULEURS[NOMBRE_DE_COULEURS] = (char*)malloc(NOMBRE_DE_SOMMETS * sizeof(char));
	++NOMBRE_DE_COULEURS;
*/

void liberer_matrices() {
	for (int i = 0; i < NOMBRE_DE_SOMMETS; ++i) {
		free(MATRICE_ARETES[i]);
	}
	free(MATRICE_ARETES);

	for (int i = 0; i < NOMBRE_DE_COULEURS; ++i) {
		free(MATRICE_COULEURS[i]);
	}
	free(MATRICE_COULEURS);
}