#define TAILLE_BLOC 20 // nombre de lignes allouées dynamiquement

// VARIABLES GLOBALES

int NOMBRE_DE_COULEURS = 0;
char **MATRICE_COULEURS; // matrice avec des char 1 ou 0, 0 par défaut
int blocs_alloues = 0;

// FONCTIONS

/*
 * Alloue la mémoire suffisante pour la matrice et la remplie de '0'
 */
void initialiser_couleurs() {
	// Dimensionne un tableau à deux dimensions
	
	MATRICE_COULEURS = (char**)malloc(TAILLE_BLOC * sizeof(char*)); // TAILLE_BLOCxN
    ++blocs_alloues;
	for (int i = 0; i < blocs_alloues*TAILLE_BLOC; ++i) { // dimensionne chaque ligne
		MATRICE_COULEURS[i] = (char*)malloc(blocs_alloues*TAILLE_BLOC * sizeof(char));
	}

	// Remplit la matrices de '0'

	for (int i = 0; i < blocs_alloues*TAILLE_BLOC; ++i) {
		for (int j = 0; j < blocs_alloues*TAILLE_BLOC; ++j) {
			MATRICE_COULEURS[i][j] = '0';
		}
	}
}