#include "../fonctions.h"

// VARIABLES GLOBALES

int NOMBRE_DE_SOMMETS = 0, NOMBRE_D_ARETES = 0;
char** MATRICE_ARETES; // matrice avec des char 1 ou 0, 0 par défaut

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
 * Met à '1' le char (indice1, indice2) de la matrice des aretes
 */
void ajouter_arete(int indice1, int indice2) {
	MATRICE_ARETES[indice1][indice2] = '1';
	MATRICE_ARETES[indice2][indice1] = '1';
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
 * Retourne le nombre de voisins du sommet donné
 */
int ordre_du_sommet(int i) {
	int ordre = 0;
	for (int i = 0; i < NOMBRE_DE_SOMMETS; ++i) {
		for (int j = 0; j < NOMBRE_DE_SOMMETS; ++j) {
			if (MATRICE_ARETES[i][j] == '1') ++ordre;
		}
	}
	return ordre;
}

/*
 * Retourne le cardinal du plus grand sous-graphe complet (ou clique maximum)
 * S'il existe une arête entre tous les sommets d'un sous-graphe, alors ce sous-graphe est une N-clique, N étant le nombre de sommets appartenenant à la clique
 */
int clique_maximum() {
	int max_clique = 0;
	// Recherche de toutes les cliques en partant de chaque sommet du graphe
	for (int i = 0; i < NOMBRE_DE_SOMMETS; ++i) {
		// Recherche d'un sommet appartenant à la clique en les parcourant tous et en les ajoutant au tableau de clique s'ils sont aptes à en faire partie
		// Étant donné que l'ajout d'un sommet à la clique a une influence sur l'ajout ou pas des sommets suivant, il faut en omettre certains pour qu'ils ne bloquent pas la situation
		// Donc boucle for supplémentaire pour trouver toutes les cliques possibles
		// Ca sert à rien d'omettre les x premiers sommets s'il ne reste que y sommets à regarder, y étant inférieur à la max clique trouvée, car il sera imppossible avec y sommets de faire une clique plus grande que celle déjà enregistrée
		// for (int omettre = 0; omettre < NOMBRE_DE_SOMMETS; ++omettre) {
		for (int omettre = 0; omettre < (NOMBRE_DE_SOMMETS-max_clique); ++omettre) {
			// printf("\nRecherche d'une clique avec le sommet %d :\n", i);
			int voisins_de_clique[NOMBRE_DE_SOMMETS]; // tableau de sommets tous reliés entre eux
			int nb_voisins_de_clique = 0;
			voisins_de_clique[nb_voisins_de_clique++] = i;
			for (int j = omettre; j < NOMBRE_DE_SOMMETS; ++j) {
				// printf("%d en lien avec : ", j);
				// s'il y a une arête entre j et tous les sommets du tableau, ce sommet fait partie de la clique
				int ajouter = 1;
				int k = 0;
				while (k < nb_voisins_de_clique && ajouter == 1) {
					if (MATRICE_ARETES[j][voisins_de_clique[k]] == '0' && j != voisins_de_clique[k]) {
						ajouter = 0;
					}
					// (ajouter == 1) ? printf("%d(Oui) ", voisins_de_clique[k]) : printf("%d(Non) STOP", voisins_de_clique[k]);
					++k;
				}
				// printf("\n");
				if (ajouter == 1) {
					voisins_de_clique[nb_voisins_de_clique++] = j;
					// printf("+ Le sommet %d\n", j);
				}
			}
			max_clique = (nb_voisins_de_clique > max_clique) ? nb_voisins_de_clique : max_clique;
		}
	}
	return max_clique;
}
