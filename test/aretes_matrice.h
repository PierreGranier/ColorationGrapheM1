
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