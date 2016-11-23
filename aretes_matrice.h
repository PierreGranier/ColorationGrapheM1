
// VARIABLES GLOBALES

int NOMBRE_DE_SOMMETS = 0, NOMBRE_D_ARETES = 0;
char **MATRICE_ARETES; // matrice avec des char 1 ou 0, 0 par défaut

// FONCTIONS

/*
 * Alloue la mémoire suffisante pour la matrice et la remplie de '0'
 */
void initialiser_aretes() {
	// Dimensionne un tableau à deux dimensions
	MATRICE_ARETES = (char**)malloc(NOMBRE_DE_SOMMETS * sizeof(char*)); // NxN
	for (int i = 0; i < NOMBRE_DE_SOMMETS; ++i) { // dimensionne chaque ligne
		MATRICE_ARETES[i] = (char*)malloc(NOMBRE_DE_SOMMETS * sizeof(char));
	}
	
	// Remplit la matrice de '0'
	for (int i = 0; i < NOMBRE_DE_SOMMETS; ++i) {
		for (int j = 0; j < NOMBRE_DE_SOMMETS; ++j) {
			MATRICE_ARETES[i][j] = '0';
		}
	}
}

/*
 * Libère la mémoire occupée par la matrice
 */
void liberer_aretes() {
	for (int i = 0; i < NOMBRE_DE_SOMMETS; ++i) {
		free(MATRICE_ARETES[i]);
	}
	free(MATRICE_ARETES);
}

/*
 * Affiche la matrice, avec la possibilité de réduire leur taille pour n'en visualiser qu'un échantillon
 */
void afficher_aretes(int pourcentage_visible) {
	printf("\n\n########################################");
	printf("\n# MATRICE ARETES\n# Taille %d x %d (lignes x colonnes)\n# Visualisée à %d %%", NOMBRE_DE_SOMMETS, NOMBRE_DE_SOMMETS, pourcentage_visible);
	printf("\n########################################\n\n");

	for (int i = 0; i < NOMBRE_DE_SOMMETS*pourcentage_visible/100; ++i) {
		for (int j = 0; j < NOMBRE_DE_SOMMETS*pourcentage_visible/100; ++j)
		// for (int j = 0; j <= i; ++j)
			(i == j) ? printf("O ") : printf("%c ", MATRICE_ARETES[i][j]);
		printf("\n");
	}
}

/*
 * Retourne une chaine de charactères de la matrice des arêtes au format standard
 */
void format_standard_aretes() {
	printf("\np col %d %d\n", NOMBRE_DE_SOMMETS, NOMBRE_D_ARETES);
	for (int i = 0; i < NOMBRE_DE_SOMMETS; ++i) {
		for (int j = 0; j <= i; ++j) {
			if (MATRICE_ARETES[i][j] == '1') printf("e %d %d\n", i+1, j+1);
		}
	}
	printf("\n");
}

/*
 * Met à '1' le char (indice1, indice2) de la matrice des aretes
 */
void ajouter_arete(int indice1, int indice2) {
	MATRICE_ARETES[indice1][indice2] = '1';
	MATRICE_ARETES[indice2][indice1] = '1';
}
