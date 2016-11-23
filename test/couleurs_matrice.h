
#define TAILLE_BLOC 10 // nombre de lignes allouées dynamiquement

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
    ++blocs_alloues;
	MATRICE_COULEURS = (char**)malloc(blocs_alloues*TAILLE_BLOC * sizeof(char*)); // TAILLE_BLOCxN
	for (int i = 0; i < blocs_alloues*TAILLE_BLOC; ++i) { // dimensionne chaque ligne
		MATRICE_COULEURS[i] = (char*)malloc(NOMBRE_DE_SOMMETS * sizeof(char));
	}

	// Remplit la matrices de '0'
	for (int i = 0; i < blocs_alloues*TAILLE_BLOC; ++i) {
		for (int j = 0; j < NOMBRE_DE_SOMMETS; ++j) {
			MATRICE_COULEURS[i][j] = '0';
		}
	}
}

/*
 * Libère la mémoire occupée par les matrices
 */
void liberer_couleurs() {
	for (int i = 0; i < blocs_alloues*TAILLE_BLOC; ++i) {
		free(MATRICE_COULEURS[i]);
	}
	free(MATRICE_COULEURS);
}

/*
 * Redimensionne la taille de la matrice des couleurs en rajoutant un bloc de lignes
 */
void ajouter_couleurs() {
	// Lorsque le nombre de couleurs proposé par la matrice n'est pas suffisant il faut ajouter des tableaux à une dimension dans la matrice des couleurs
	// Il faut donc réallouer l'espace pour la matrice en prenant soin de sauvegarder les données de cette dernière et des les recopier une fois l'allocation faite

	char** couleurs_sauvegarde = (char**)malloc(blocs_alloues*TAILLE_BLOC * sizeof(char*));

	// Copie des données de la matrice des couleurs vers la sauvegarde (allouer l'espace de chaque ligne), ligne par ligne et case par case
	for (int i = 0; i < blocs_alloues*TAILLE_BLOC; ++i) { // dimensionne chaque ligne
		couleurs_sauvegarde[i] = (char*)malloc(NOMBRE_DE_SOMMETS * sizeof(char));
		for (int j = 0; j < NOMBRE_DE_SOMMETS; ++j) { // copie de chaque élément de la matrice dans cette ligne
			couleurs_sauvegarde[i][j] = MATRICE_COULEURS[i][j];
		}
	}

	// Redimensionnement de la nouvelle matrice des couleurs
    ++blocs_alloues;
	MATRICE_COULEURS = (char**)malloc(blocs_alloues*TAILLE_BLOC * sizeof(char*)); // redimensionne la matrice (ré-allocation mémoire)

	// Copie des données de la sauvegarde vers la nouvelle matrice (allouer l'espace de chaque ligne) et mise à '0' des éléments des nouvelles lignes
	for (int i = 0; i < (blocs_alloues-1)*TAILLE_BLOC; ++i) {
		MATRICE_COULEURS[i] = (char*)malloc(NOMBRE_DE_SOMMETS * sizeof(char)); // dimensionne la ligne
		for (int j = 0; j < NOMBRE_DE_SOMMETS; ++j) { // copie de chaque élément de la sauvegarde pour cette ligne
			MATRICE_COULEURS[i][j] = couleurs_sauvegarde[i][j];
		}
	}
	for (int i = (blocs_alloues-1)*TAILLE_BLOC; i < blocs_alloues*TAILLE_BLOC; ++i) {
		MATRICE_COULEURS[i] = (char*)malloc(NOMBRE_DE_SOMMETS * sizeof(char)); // dimensionne la ligne
		for (int j = 0; j < NOMBRE_DE_SOMMETS; ++j) { // mise à '0' de la nouvelle ligne
			MATRICE_COULEURS[i][j] = '0';
		}
	}

	// Liberation de la mémoire de la matrice de sauvegarde
	for (int i = 0; i < (blocs_alloues-1)*TAILLE_BLOC; ++i) { // libère la mémoire dela sauvegarde
		free(couleurs_sauvegarde[i]);
	}
	free(couleurs_sauvegarde);
}

/*
 * Affiche les matrices, avec la possibilité de réduire leur taille pour n'en visualiser qu'un échantillon
 */
void afficher_matrice_couleurs(int pourcentage_visible) {
	printf("\n########################################");
	printf("\n# MATRICE COULEURS\n# Taille %d x %d (lignes x colonnes)\n# Visualisée à %d %%", NOMBRE_DE_COULEURS, NOMBRE_DE_SOMMETS, pourcentage_visible);
	printf("\n########################################\n\n");

	for (int i = 0; i < NOMBRE_DE_COULEURS; ++i) {
		for (int j = 0; j < NOMBRE_DE_SOMMETS*pourcentage_visible/100; ++j) {
			printf("%c ", MATRICE_COULEURS[i][j]);
		}
		printf("\n");
	}
}

/*
 * Retourne une chaine de charactères de la matrice des arêtes et des couleurs au format standard
 */
void format_standard_matrice_couleurs() {
	printf("\nK=%d\n", NOMBRE_DE_COULEURS);
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

/*
 * Met à '0' les couleurs de l'indice du sommet donné et à '1' le char (indice_sommet, indice_couleur) de la matrice des couleurs
 */
void associer_couleur(int indice_sommet, int indice_couleur) {
	// Si la couleur n'a pas encore été utilisée, il faut incrémenter le compteur de couleurs jusqu'à atteindre l'indice demandé
	while (indice_couleur >= NOMBRE_DE_COULEURS) {
		++NOMBRE_DE_COULEURS;
		// Si la matrice des couleurs ne donne pas assez de places il faut l'agrandir
		if (NOMBRE_DE_COULEURS > blocs_alloues*TAILLE_BLOC) {
			ajouter_couleurs();
		}
	}
	
	// Enlever les autres couleurs assignées au sommet et lui ajouter la couleur demandée
	for (int i = 0; i < NOMBRE_DE_COULEURS; ++i) {
		MATRICE_COULEURS[i][indice_sommet] = '0';
	}
	MATRICE_COULEURS[indice_couleur][indice_sommet] = '1';
}

/*
 * Retourne la couleur du sommet
 */
char couleur_du_sommet(int indice_sommet) {
	for (int i = 0; i < NOMBRE_DE_COULEURS; ++i) {
		if (MATRICE_COULEURS[i][indice_sommet] == '1') {
			return i;
		}
	}
	return '-';
}
