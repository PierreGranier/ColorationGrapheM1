#include "fonctions.h"

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

void ajouter_arete(int label1, int label2) {
	MATRICE_GRAPH[label1][label2] = 1;
	//SOMMETS[label2][label1] = 1;    //pas nécéssaire car graphe non orienté
}

// quand on coloriera, il faudra re-allouer de la mémoire pour chaque nouvelle couleur
/*
	MATRICE_COULEURS[NOMBRE_DE_COULEURS] = (char*)malloc(NOMBRE_DE_SOMMETS * sizeof(char));
	++NOMBRE_DE_COULEURS;
*/