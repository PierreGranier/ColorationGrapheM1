#include "fonctions.h"


int NOMBRE_DE_COULEURS = 0;


void initialiser_matrices() {
	// dimensionne les tableaux à deux dimensions

	MATRICE_ARETES = (char**)malloc(NOMBRE_DE_SOMMETS * sizeof(char*)); // NxN
	for (int i = 0; i < NOMBRE_DE_SOMMETS; ++i) { // dimensionne chaque ligne
		MATRICE_ARETES[i] = (char*)malloc(NOMBRE_DE_SOMMETS * sizeof(char));
	}
	
	MATRICE_COULEURS = (char**)malloc(0 * sizeof(char*)); // 0xN

	// remplit les matrices de '0'

	for (int i = 0; i < NOMBRE_DE_SOMMETS; ++i) {
		for (int j = 0; j < NOMBRE_DE_SOMMETS; ++j) {
			MATRICE_ARETES[i][j] = '0';
		}
	}
}

void liberer_matrices() {
	for (int i = 0; i < NOMBRE_DE_SOMMETS; ++i) {
		free(MATRICE_ARETES[i]); // pb quand nb de couleurs >= 4
	}
	free(MATRICE_ARETES);

	for (int i = 0; i < NOMBRE_DE_COULEURS; ++i) {
		free(MATRICE_COULEURS[i]);
	}
	free(MATRICE_COULEURS); // pb quand nb de couleurs >= 4
}


void afficher_matrice_aretes(int pourcentage_visible) {
	printf("\n\n########################################\n");
	printf("# MATRICE ARETES\n# Taille %d x %d (lignes x colonnes)\n# Visualisée à %d %%\n########################################\n\n", NOMBRE_DE_SOMMETS, NOMBRE_DE_SOMMETS, pourcentage_visible);
	
	for (int i = 0; i < NOMBRE_DE_SOMMETS*pourcentage_visible/100; ++i) {
		for (int j = 0; j < NOMBRE_DE_SOMMETS*pourcentage_visible/100; ++j)
		// for (int j = 0; j <= i; ++j)
			(i == j) ? printf("O ") : printf("%c ", MATRICE_ARETES[i][j]);
		printf("\n");
	}
	printf("\n");
}

void afficher_matrice_couleurs(int pourcentage_visible) {
	printf("\n\n########################################\n");
	printf("# MATRICE COULEURS\n# Taille %d x %d (lignes x colonnes)\n# Visualisée à %d %%\n########################################\n\n", NOMBRE_DE_COULEURS, NOMBRE_DE_SOMMETS, pourcentage_visible);
	
	for (int i = 0; i < NOMBRE_DE_COULEURS; ++i) {
		for (int j = 0; j < NOMBRE_DE_SOMMETS*pourcentage_visible/100; ++j) {
			printf("%c ", MATRICE_COULEURS[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}


void format_standard_matrice_aretes() {
	printf("p col %d %d\n", NOMBRE_DE_SOMMETS, NOMBRE_D_ARETES);
	for (int i = 0; i < NOMBRE_DE_SOMMETS; ++i) {
		for (int j = 0; j <= i; ++j) {
			if (MATRICE_ARETES[i][j] == '1') printf("e %d %d\n", i+1, j+1);
		}
	}
}

void format_standard_matrice_couleurs() {
	printf("K=%d\n", NOMBRE_DE_COULEURS);
	for (int j = 0; j < NOMBRE_DE_SOMMETS; ++j) {
		int couleur = -1; // -1 = pas de couleur assignée
		for (int i = 0; i < NOMBRE_DE_COULEURS; ++i) {
			if (MATRICE_COULEURS[i][j] == '1') {
				couleur = (couleur == -1) ? i : -2; // -2 = conflit (+ de 1 couleur assignée à ce sommet)
			}
		}
		printf(" %d ", couleur);
	}
	printf("\n");
}


void ajouter_arete(int indice1, int indice2) {
	MATRICE_ARETES[indice1][indice2] = '1';
	MATRICE_ARETES[indice2][indice1] = '1';
}

void ajouter_couleur(int indice_sommet, int indice_couleur) {
	// Pour chaque couleur à ajouter il faut ajouter un tableau à une dimension dans la matrice des couleurs
	// Il faut donc réallouer l'espace pour la matrice en prenant soin de sauvegarder les données de cette dernière et des les recopier une fois l'allocation faite

	while (NOMBRE_DE_COULEURS <= indice_couleur) {
		char** couleurs_sauvegarde = (char**)malloc(NOMBRE_DE_COULEURS * sizeof(char*));

		// Copie des données de la matrice des couleurs vers la sauvegarde (allouer l'espace de chaque ligne), ligne par ligne et case par case
		for (int i = 0; i < NOMBRE_DE_COULEURS; ++i) {
			couleurs_sauvegarde[i] = (char*)malloc(NOMBRE_DE_SOMMETS * sizeof(char)); // dimensionnne la ligne
			for (int j = 0; j < NOMBRE_DE_SOMMETS; ++j) { // copie de chaque élément de la matrice pour cette ligne
				couleurs_sauvegarde[i][j] = MATRICE_COULEURS[i][j];
			}
		}

		// Redimensionnement de la nouvelle matrice des couleurs
		++NOMBRE_DE_COULEURS;
		MATRICE_COULEURS = (char**)malloc(NOMBRE_DE_COULEURS * sizeof(char*)); // redimensionne la matrice (ré-allocation mémoire)

		// Copie des données de la sauvegarde vers la nouvelle matrice (allouer l'espace de chaque ligne) et mise à '0' des éléments de la nouvelle et dernière ligne
		for (int i = 0; i < NOMBRE_DE_COULEURS; ++i) {
			MATRICE_COULEURS[i] = (char*)malloc(NOMBRE_DE_SOMMETS * sizeof(char)); // dimensionne de la ligne
			if (i == NOMBRE_DE_COULEURS-1) {
				for (int j = 0; j < NOMBRE_DE_SOMMETS; ++j) { // mise à '0' de la nouvelle ligne
					MATRICE_COULEURS[i][j] = '0';
				}
			} else {
				for (int j = 0; j < NOMBRE_DE_SOMMETS; ++j) { // copie de chaque élément de la sauvegarde pour cette ligne
					MATRICE_COULEURS[i][j] = couleurs_sauvegarde[i][j];
				}
			}
		}

		// Liberation de la mémoire de la matrice de sauvegarde
		for (int i = 0; i < NOMBRE_DE_COULEURS-1; ++i) { // libère la mémoire dela sauvegarde
			free(couleurs_sauvegarde[i]);
		}
		free(couleurs_sauvegarde);
	}

	MATRICE_COULEURS[indice_couleur][indice_sommet] = '1';
}


void bob() {

}

void tibo() {
	
}

// quand on coloriera, il faudra re-allouer de la mémoire pour chaque nouvelle COULEURS
