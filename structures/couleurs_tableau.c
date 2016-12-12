#include "../fonctions.h"

// VARIABLES GLOBALES

int NOMBRE_DE_COULEURS;
int* TABLEAU_COULEURS; // matrice avec des char -1 par défaut

// FONCTIONS

/*
 * Rien à faire
 */
void initialiser_couleurs() {
	// Nombre de couleurs à 0
	NOMBRE_DE_COULEURS = 0;

	// Dimensionne un tableau à une dimension
	TABLEAU_COULEURS = (int*)malloc(NOMBRE_DE_SOMMETS * sizeof(int)); // 1xN
	for (int i = 0; i < NOMBRE_DE_SOMMETS; ++i) {
        TABLEAU_COULEURS[i] = -1;
	}
}

/*
 * Libère la mémoire occupée par les matrices
 */
void liberer_couleurs() {
	free(TABLEAU_COULEURS);
}

/*
 * Redimensionne la taille de la matrice des couleurs en rajoutant un bloc de lignes
 */
void ajouter_couleur() {
    ++NOMBRE_DE_COULEURS;
}

/*
 * Affiche le tableau, avec la possibilité de réduire leur taille pour n'en visualiser qu'un échantillon
 */
void afficher_couleurs(int pourcentage_visible) {
	pourcentage_visible = pourcentage_visible % 101;

	printf("\n########################################");
	printf("\n# TABLEAU COULEURS\n# Taille %d x %d (lignes x colonnes)\n# Visualisée à %d %%", 1, NOMBRE_DE_SOMMETS, pourcentage_visible);
	printf("\n########################################\n\n");

	for (int i = 0; i < NOMBRE_DE_SOMMETS*pourcentage_visible/100; ++i) {
        printf("%i ", TABLEAU_COULEURS[i]);
	}
    printf("\n");
}

/*
 * Retourne une chaine de charactères du tableau des couleurs au format standard
 */
void format_standard_couleurs(char* nom_fichier) {
	char sans_extension[5+strlen(nom_fichier)];
	int copier = 0;
	for (int i = strlen(nom_fichier)-1; i >= 0; --i) {
		sans_extension[i] = (copier == 1) ? nom_fichier[i] : '\0';
		if (nom_fichier[i] == '.') copier = 1;
	}

	FILE* fichier = NULL;
	fichier = fopen(strcat(sans_extension, "_out.txt"), "w");

	if (fichier != NULL) {
		fprintf(fichier, "\nK=%d\n", NOMBRE_DE_COULEURS);
		for (int i = 0; i < NOMBRE_DE_SOMMETS; ++i) {
			fprintf(fichier, " %i ", TABLEAU_COULEURS[i]);
		}
		fprintf(fichier, "\n");

		fclose(fichier);
	}


}

/*
 * Ecrase le nom de la couleur à l'indice du sommet donné dans le tableau des couleurs
 */
void associer_couleur(int indice_sommet, int indice_couleur) {
	// Si la couleur n'a pas encore été utilisée, il faut incrémenter le compteur de couleurs jusqu'à atteindre l'indice demandé
	while (indice_couleur >= NOMBRE_DE_COULEURS) {
		ajouter_couleur();
	}
	
	// Ecrase la couleur assignée au sommet par la couleur demandée
    TABLEAU_COULEURS[indice_sommet] = indice_couleur;
}

/*
 * Retourne la couleur du sommet
 */
int couleur_du_sommet(int indice_sommet) {
    return TABLEAU_COULEURS[indice_sommet];
}
