#include "../fonctions.h"

#define PI 3.14159265

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
			printf("%c ", MATRICE_ARETES[i][j]);
		printf("\n");
	}
}

/*
 * Retourne une chaine de charactères de la matrice des arêtes au format standard
 */
void format_standard_aretes(char* nom_fichier) {
	printf("\np col %d %d\n", NOMBRE_DE_SOMMETS, NOMBRE_D_ARETES);
	for (int i = 0; i < NOMBRE_DE_SOMMETS; ++i) {
		for (int j = 0; j <= i; ++j) {
			if (MATRICE_ARETES[i][j] == '1') printf("e %d %d\n", i+1, j+1);
		}
	}
	printf("\n");
}

void format_html_aretes(char* nom_fichier) {
	int coords_sommets[2][NOMBRE_DE_SOMMETS]; // ligne x et ligne y
	int coords_aretes[5][NOMBRE_D_ARETES]; // ligne x et ligne y de départ, ligne width, ligne angle
	// si on met 4, coords_aretes[3][i] rempalce les valeurs de coords_sommets... wtf

	for (int i = 0; i < NOMBRE_DE_SOMMETS; ++i) {
		coords_sommets[0][i] = 0;
		coords_sommets[1][i] = 0;
	}
	for (int i = 0; i < NOMBRE_D_ARETES; ++i) {
		coords_aretes[0][i] = 0;
		coords_aretes[1][i] = 0;
		coords_aretes[2][i] = 0;
		coords_aretes[3][i] = 0;
	}

	/*int** coords_sommets = (int**)malloc(2 * sizeof(int*)); // 2xN
	for (int i = 0; i < 2; ++i) { // dimensionne chaque ligne
		coords_sommets[i] = (int*)calloc(NOMBRE_DE_SOMMETS, sizeof(int));
	}
	int** coords_aretes = (int**)malloc(4 * sizeof(int*)); // 4xN
	for (int i = 0; i < 4; ++i) { // dimensionne chaque ligne
		coords_aretes[i] = (int*)calloc(NOMBRE_D_ARETES, sizeof(int));
	}*/

	int pas = 400 / NOMBRE_DE_SOMMETS;
	int x = 0, y = 0, indice_sommet = 0, indice_arete = 0;

	// Répartition des coordonnées sur une spirale vers le centre
	while (x+pas <= 100 && indice_sommet < NOMBRE_DE_SOMMETS) {
		coords_sommets[0][indice_sommet] = x;
		coords_sommets[1][indice_sommet++] = y;
		x += pas;
	}
	while (y+pas <= 100 && indice_sommet < NOMBRE_DE_SOMMETS) {
		coords_sommets[0][indice_sommet] = x;
		coords_sommets[1][indice_sommet++] = y;
		y += pas;
	}
	while (x-pas >= 0 && indice_sommet < NOMBRE_DE_SOMMETS) {
		coords_sommets[0][indice_sommet] = x;
		coords_sommets[1][indice_sommet++] = y;
		x -= pas;
	}
	while (y-pas >= 50 && indice_sommet < NOMBRE_DE_SOMMETS) {
		coords_sommets[0][indice_sommet] = x;
		coords_sommets[1][indice_sommet++] = y;
		y -= pas;
	}
	while (x+pas <= 50 && indice_sommet < NOMBRE_DE_SOMMETS) {
		coords_sommets[0][indice_sommet] = x;
		coords_sommets[1][indice_sommet++] = y;
		x += pas;
	}

	// puts("== coords sommets ==");
	// for (int i = 0; i < 2; ++i) {
	// 	for (int j = 0; j < NOMBRE_DE_SOMMETS; ++j) {
	// 		printf("%d ", coords_sommets[i][j]);
	// 	}
	// 	printf("\n");
	// }
	
	// Ajout des coordonnées des arêtes sur les coordonnées des sommets frêres
	for (int i = 0; i < NOMBRE_DE_SOMMETS; ++i) {
		for (int j = 0; j < NOMBRE_DE_SOMMETS; ++j) {
			if (MATRICE_ARETES[i][j] == '1') {
				int delta_x = coords_sommets[0][j] - coords_sommets[0][i];
				int delta_y = coords_sommets[1][j] - coords_sommets[1][i];
				int longueur = (int) sqrt(delta_x*delta_x + delta_y*delta_y); // pythagore
				int angle = (delta_x == 0) ? -90 : (delta_y == 0) ? 0 : (int) (atan(delta_y / delta_x) * (180 / PI)); // trigonométrie
				if (delta_x < 0) angle += 180;
				coords_aretes[0][indice_arete] = coords_sommets[0][i];
				coords_aretes[1][indice_arete] = coords_sommets[1][i];
				coords_aretes[2][indice_arete] = longueur;
				coords_aretes[3][indice_arete] = angle;
				// printf("\n---\nLes coord de i : (%d, %d)", coords_sommets[0][i], coords_sommets[1][i]);
				// printf("\nLes coord de j : (%d, %d)", coords_sommets[0][j], coords_sommets[1][j]);
				// printf("\nDelta X = %d\nDelta Y = %d", delta_x, delta_y);
				// printf("\nLongueur = %d", longueur);
				// printf("\nAngle = %d", angle);
				// printf(" => x[%d] y[%d] width[%d] rotate[%d]\n", coords_aretes[0][indice_arete] , coords_aretes[1][indice_arete] , coords_aretes[2][indice_arete], coords_aretes[3][indice_arete]);
				++indice_arete;
			}
		}
	}

	// puts("== coords arêtes ==");
	// for (int i = 0; i < 4; ++i) {
	// 	for (int j = 0; j < NOMBRE_D_ARETES/4; ++j) {
	// 		printf("%d ", coords_aretes[i][j]);
	// 	}
	// 	printf("\n");
	// }

	// Tout dans un fichier html éponyme
	char sans_extension[strlen(nom_fichier)];
	int copier = 0;
	for (int i = strlen(nom_fichier)-1; i >= 0; --i) {
		sans_extension[i] = (copier == 1) ? nom_fichier[i] : '\0';
		if (nom_fichier[i] == '.') copier = 1;
	}

	FILE* fichier = NULL;
	fichier = fopen(strcat(sans_extension, ".html"), "w");

	if (fichier != NULL) {
		fprintf(fichier, "<style>* { margin: 0; padding: 0; }");
		fprintf(fichier, "sommet { position: absolute; width: 5px; height: 5px; text-align: center; font-size: 3px; color: darkslategray; background: white; border: 1px solid rgba(0, 0, 0, 0.3); border-radius: 10px; box-shadow: 0 1px 0px 0 rgba(0, 0, 0, 0.3); }");
		fprintf(fichier, "arete { position: absolute; height: 1px; background: rgba(255, 0, 0, 0.3); transform-origin: 0 0; }</style>");
		fprintf(fichier, "<graphe>");

		// puts("== coords sommets ==");
		// for (int i = 0; i < 2; ++i) {
		// 	for (int j = 0; j < NOMBRE_DE_SOMMETS; ++j) {
		// 		printf("%d ", coords_sommets[i][j]);
		// 	}
		// 	printf("\n");
		// }

		for (int i = 0; i < NOMBRE_DE_SOMMETS; ++i) {
			fprintf(fichier, "<sommet style=\"left: %dpx; top: %dpx\">%d</sommet>", coords_sommets[0][i], coords_sommets[1][i], i+1);
		}

		// puts("== coords arêtes ==");
		// for (int i = 0; i < 4; ++i) {
		// 	for (int j = 0; j < NOMBRE_D_ARETES/4; ++j) {
		// 		printf("%d ", coords_aretes[i][j]);
		// 	}
		// 	printf("\n");
		// }

		for (int i = 0; i < NOMBRE_D_ARETES; ++i) {
			fprintf(fichier, "<arete style=\"left: %dpx; top: %dpx; width: %dpx; transform: rotate(%ddeg)\"></arete>", coords_aretes[0][i], coords_aretes[1][i], coords_aretes[2][i], coords_aretes[3][i]);
		}

		fprintf(fichier, "</graphe>");
		fclose(fichier);
	}

	// for (int i = 0; i < 2; ++i) {
	// 	free(coords_sommets[i]);
	// }
	// free(coords_sommets);
	// for (int i = 0; i < 4; ++i) {
	// 	free(coords_aretes[i]);
	// }
	// free(coords_aretes);
}

/*
 * Retourne le nombre de voisins du sommet donné
 */
int ordre_du_sommet(int indice) {
	int ordre = 0;
	for (int i = 0; i < NOMBRE_DE_SOMMETS; ++i) {
		if (MATRICE_ARETES[indice][i] == '1') ++ordre;
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

int ordre_max() {
	int max = 0;
	for(int i=0; i<NOMBRE_DE_SOMMETS; ++i) {
			if(ordre_du_sommet(i) > max) {
				max = ordre_du_sommet(i);
			}
	}
	return max;
}

int clique_maximum2() {
	int max_clique = 0;

	for(int i= 0; i<NOMBRE_DE_SOMMETS; ++i) {
		int* tab_clique;
		tab_clique = (int*) malloc(ordre_max()*sizeof(int));
		tab_clique[0] = i;
		int nb_clique = 1;
		for(int j=0; j<NOMBRE_DE_SOMMETS; ++j) {
			
			/*for(int ct=0; ct<ordre_max(); ++ct) {
				if(i != tab[ct]) {
					tab_clique[ct] = i;
				}
			}	*/
			if(MATRICE_ARETES[i][j] == '1') {
				int ajout_ok=1;
				//parcourir le tableau et vérifier qu'il y a un lien entre j et chaque sommet du tableau
				for(int ct=0; ct<nb_clique; ++ct) {
					if(MATRICE_ARETES[j][tab_clique[ct]] == '0') {
						ajout_ok = 0;
						break;
					}
					
				}
				if(ajout_ok == 1) {
					tab_clique[nb_clique++] = j;
				}
			}
		}
		if(nb_clique > max_clique) {
			max_clique = nb_clique;
		}
		free(tab_clique);
	}
return max_clique;
}