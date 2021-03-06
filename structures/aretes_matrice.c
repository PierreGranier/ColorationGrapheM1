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
	pourcentage_visible = pourcentage_visible % 101;

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
	// si on met 4, coords_aretes[3][i] remplace les valeurs de coords_sommets... wtf

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

	// int** coords_sommets = (int**)malloc(2 * sizeof(int*)); // 2xN
	// for (int i = 0; i < 2; ++i) { // dimensionne chaque ligne
	// 	coords_sommets[i] = (int*)calloc(NOMBRE_DE_SOMMETS, sizeof(int));
	// }
	// int** coords_aretes = (int**)malloc(4 * sizeof(int*)); // 4xN
	// for (int i = 0; i < 4; ++i) { // dimensionne chaque ligne
	// 	coords_aretes[i] = (int*)calloc(NOMBRE_D_ARETES, sizeof(int));
	// }

	// Répartition des coordonnées sur une spirale vers le centre
	int pas = (400 - NOMBRE_DE_SOMMETS*10) / NOMBRE_DE_SOMMETS;
	int x = 0, y = 0, indice_sommet = 0, indice_arete = 0;
	
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
	int pour_le_bug = 0;
	for (int i = 0; i < NOMBRE_DE_SOMMETS; ++i) {
		for (int j = 0; j < i; ++j) {
			if (MATRICE_ARETES[i][j] == '1') {
				int delta_x = coords_sommets[0][j] - coords_sommets[0][i];
				int delta_y = coords_sommets[1][j] - coords_sommets[1][i];
				int longueur = (int) sqrt(delta_x*delta_x + delta_y*delta_y); // pythagore
				int angle = (delta_x == 0) ? (delta_y < 0) ? -90 : 90 : (delta_y == 0) ? 0 : (int) (atan((double) delta_y / delta_x) * (180 / PI)); // trigonométrie
				if (delta_x < 0) angle += 180;
				coords_aretes[0][indice_arete] = coords_sommets[0][i];
				coords_aretes[1][indice_arete] = coords_sommets[1][i];
				coords_aretes[2][indice_arete] = longueur;
				coords_aretes[3][indice_arete] = angle;
				// printf("\n---\nLes coord de i : (%d, %d)", coords_sommets[0][i], coords_sommets[1][i]);
				// printf("\nLes coord de j : (%d, %d)", coords_sommets[0][j], coords_sommets[1][j]);
				// printf("\nDelta X = %d\nDelta Y = %d", delta_x, delta_y);
				// printf("\n%d => x[%d] y[%d] width[%d] rotate[%d]\n", indice_arete, coords_aretes[0][indice_arete] , coords_aretes[1][indice_arete] , coords_aretes[2][indice_arete], coords_aretes[3][indice_arete]);
				if (indice_arete == 0) { pour_le_bug = coords_sommets[0][i]; }
				++indice_arete;
			}
		}
	}

	// puts("== coords arêtes ==");
	// for (int i = 0; i < 4; ++i) {
	// 	for (int j = 0; j < NOMBRE_D_ARETES; ++j) {
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
		int echelle = 5;
		
		fprintf(fichier, "<style>* { margin: 0; padding: 0; } graphe { position: absolute; width: 100%%; height: 100%%; margin: 10px;}");
		fprintf(fichier, "sommet { position: absolute; width: 1px; height: 1px; text-align: center; font-size: 8px; color: darkslategray; border: 1px solid block; border-radius: 10px; }");
		fprintf(fichier, "arete { position: absolute; height: 2px; background: rgba(255, 0, 0, 0.5); transform-origin: 0 0; }</style>");
		fprintf(fichier, "<graphe>");

		// puts("== coords sommets ==");
		// for (int i = 0; i < 2; ++i) {
		// 	for (int j = 0; j < NOMBRE_DE_SOMMETS; ++j) {
		// 		printf("%d ", coords_sommets[i][j]);
		// 	}
		// 	printf("\n");
		// }

		for (int i = 0; i < NOMBRE_DE_SOMMETS; ++i) {
			fprintf(fichier, "<sommet style=\"left: %dpx; top: %dpx\">%d</sommet>", coords_sommets[0][i]*echelle, coords_sommets[1][i]*echelle, i+1);
		}

		// puts("== coords arêtes ==");
		// for (int i = 0; i < 4; ++i) {
		// 	for (int j = 0; j < NOMBRE_D_ARETES; ++j) {
		// 		printf("%d ", coords_aretes[i][j]);
		// 	}
		// 	printf("\n");
		// }
		
		coords_aretes[0][0] = pour_le_bug; // ...
		for (int i = 0; i < NOMBRE_D_ARETES; ++i) {
			fprintf(fichier, "<arete style=\"left: %dpx; top: %dpx; width: %dpx; transform: rotate(%ddeg)\"></arete>", coords_aretes[0][i]*echelle, coords_aretes[1][i]*echelle, coords_aretes[2][i]*echelle, coords_aretes[3][i]);
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
int clique_maximum(int* res) {
	int max_clique = 0; // nombre de sommets dans la max clique

	// Recherche de toutes les cliques en partant de chaque sommet du graphe
	for (int i = 0; i < NOMBRE_DE_SOMMETS; ++i) {
		// Recherche d'un sommet appartenant à la clique en les parcourant tous et en les ajoutant au tableau de clique s'ils sont aptes à en faire partie
		// Étant donné que l'ajout d'un sommet à la clique a une influence sur l'ajout ou pas des sommets suivant, il faut en omettre certains pour qu'ils ne bloquent pas la situation
		// Donc boucle for supplémentaire pour trouver toutes les cliques possibles
		// Ca sert à rien d'omettre les x premiers sommets s'il ne reste que y sommets à regarder, y étant inférieur à la max clique trouvée, car il sera imppossible avec y sommets de faire une clique plus grande que celle déjà enregistrée
		// for (int sommet_de_depart = 0; sommet_de_depart < NOMBRE_DE_SOMMETS; ++sommet_de_depart) {
		for (int sommet_de_depart = 0; sommet_de_depart < (NOMBRE_DE_SOMMETS-max_clique); ++sommet_de_depart) {
			// printf("\nRecherche d'une clique avec le sommet %d :\n", i);
			int voisins_de_clique[NOMBRE_DE_SOMMETS];
			int nb_voisins_de_clique = 0;
			voisins_de_clique[nb_voisins_de_clique++] = i;
			for (int j = sommet_de_depart; j < NOMBRE_DE_SOMMETS; ++j) {
				// Si les sommets sont différents (il faut vérifier car le sommet i est déjà dans le tableau)
				if (j != i) {
					// printf("%d en lien avec : ", j);
					// S'il y a une arête entre j et tous les sommets du tableau, ce sommet fait partie de la clique
					int ajouter = 1;
					int k = 0;
					// Il faut que le sommet j soit en lien avec tous les sommets k du tableau de clique et que j soit différent de k pour l'ajouter au tableau de clique
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
			}
			// Si c'est un record, l'enregistrer
			if (nb_voisins_de_clique > max_clique) {
				if (res != NULL) {
					for (int i = 0; i < nb_voisins_de_clique; ++i) {
						res[i] = voisins_de_clique[i];
					}
				}
				max_clique = nb_voisins_de_clique;
			}
		}
	}

	return max_clique;
}

int clique_maximum2(int* res) {
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
			if (res != NULL) {
				for (int i = 0; i < nb_clique; ++i) {
					res[i] = tab_clique[i];
				}
			}
			max_clique = nb_clique;
		}
		free(tab_clique);
	}

	return max_clique;
}

int clique_maximum3(int* res) {
	int max_clique = 0; // nombre de sommets dans la max clique

	// Recherche de toutes les cliques en partant de chaque sommet du graphe
	for (int i = 0; i < NOMBRE_DE_SOMMETS; ++i) {
		// Recherche d'un sommet appartenant à la clique en les parcourant tous et en les ajoutant au tableau de clique s'ils sont aptes à en faire partie
		// Étant donné que l'ajout d'un sommet à la clique a une influence sur l'ajout ou pas des sommets suivant, il faut en omettre certains pour qu'ils ne bloquent pas la situation
		int sommet_de_depart = 0;
		int rechercher_clique = 1;
		while (rechercher_clique == 1 && sommet_de_depart < NOMBRE_DE_SOMMETS) {
			// Arrêt de la recherche si tous les sommets de départ ont été épuisés
			while (MATRICE_ARETES[i][sommet_de_depart] != '1') {
				++sommet_de_depart;
				if (sommet_de_depart == NOMBRE_DE_SOMMETS) {
					rechercher_clique = 0;
					break;
				}
			}
			if (rechercher_clique == 1) {
				int voisins_de_clique[NOMBRE_DE_SOMMETS];
				int nb_voisins_de_clique = 0;
				voisins_de_clique[nb_voisins_de_clique++] = i;
				voisins_de_clique[nb_voisins_de_clique++] = sommet_de_depart;
				for (int j = 0; j < NOMBRE_DE_SOMMETS; ++j) {
					// S'il y a une arête entre j et tous les sommets du tableau, ce sommet fait partie de la clique
					int ajouter = (j == i || j == sommet_de_depart) ? 0 : 1;
					int k = 0;
					// Il faut que le sommet j soit en lien avec tous les sommets k du tableau de clique et que j soit différent de k pour l'ajouter au tableau de clique
					while (ajouter == 1 && k < nb_voisins_de_clique) {
						if (MATRICE_ARETES[j][voisins_de_clique[k]] == '0' && j != voisins_de_clique[k]) {
							ajouter = 0;
						}
						++k;
					}
					// printf("\n");
					if (ajouter == 1) {
						voisins_de_clique[nb_voisins_de_clique++] = j;
						// printf("+ Le sommet %d\n", j);
					}
				}
				// Si c'est un record, l'enregistrer
				if (nb_voisins_de_clique > max_clique) {
					if (res != NULL) {
						for (int i = 0; i < nb_voisins_de_clique; ++i) {
							res[i] = voisins_de_clique[i];
						}
					}
					max_clique = nb_voisins_de_clique;
				}
			}
			++sommet_de_depart;
		} // fin while rechercher_clique == 1
	}

	return max_clique;
}

void calculer_clique(int* sommets_clique_max, int* taille_clique_max, int* sommets_clique, int taille_clique) {
	// Initialisation si clique pas encore recherchée
	if (sommets_clique == NULL) {
		int tab[NOMBRE_DE_SOMMETS];
		sommets_clique = tab;
		taille_clique = 0;
	}
	// if (*taille_clique_max <= taille_clique) { for (int i = 0; i < taille_clique; ++i) { printf("%d, ", sommets_clique[i]); } printf("\n"); }
	if (*taille_clique_max < taille_clique) { printf("  Nouvelle clique trouvée ; taille : %d sommets\n", taille_clique); }
	// Recherche des sommets pas encore dans la clique pouvant appartenir à la clique
	int suivants[NOMBRE_DE_SOMMETS];
	int nb_suivants = 0;
	for (int i = 0; i < NOMBRE_DE_SOMMETS; ++i) {
		int ajoutable = (ordre_du_sommet(i) > *taille_clique_max) ? 1 : 0;
		int j = 0;
		// Vérifie que le sommet i est en lien avec tous les sommets de la clique
		while (ajoutable == 1 && j < taille_clique) {
			if (MATRICE_ARETES[i][sommets_clique[j]] == '0') ajoutable = 0;
			++j;
		}
		if (ajoutable == 1) suivants[nb_suivants++] = i;
	}
	// Pour chaque sommet pouvant appartenir à la clique, continuer la recherche de la clique avec le sommet
	for (int i = 0; i < nb_suivants; ++i) {
		int tmp[taille_clique+1];
		for (int i = 0; i < taille_clique; ++i) tmp[i] = sommets_clique[i];
		tmp[taille_clique] = suivants[i];
		calculer_clique(sommets_clique_max, taille_clique_max, tmp, taille_clique+1);
	}
	if (taille_clique > *taille_clique_max) {
		if (sommets_clique_max != NULL)
		for (int i = 0; i < taille_clique; ++i) {
			sommets_clique_max[i] = sommets_clique[i];
		}
		*taille_clique_max = taille_clique;
	}
}

int clique_genetique(int* res) {
	int taille_clique_max = 0;

	calculer_clique(res, &taille_clique_max, NULL, 0);

	return taille_clique_max;
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

void comparer_verifier_cliques() {
	int sommets_clique_max[NOMBRE_DE_SOMMETS];
	int clique_max;
	
	clique_max = clique_maximum(sommets_clique_max);
	printf("\n=============\nClique Tibo : %d\n-------------", clique_max);

	printf("\n# Vérification que les sommets de cette clique sont bien tous liés entre eux :\n[Début] ");
	for (int i = 0; i < clique_max; ++i) {
		printf("%d ", sommets_clique_max[i]);
		for (int j = 0; j < clique_max; ++j) {
			if (MATRICE_ARETES[sommets_clique_max[i]][sommets_clique_max[j]] != '1' && sommets_clique_max[i] != sommets_clique_max[j]) {
				printf("[Problème] ");
			}
		}
	}
	printf("[Fin]\n");

	printf("# Liste des autres sommets pouvant faire partie de cette clique :\n[Début] ");
	for (int i = 0; i < NOMBRE_DE_SOMMETS; ++i) {
		int peut_faire_partie = 1;
		int j = 0;
		while (j < clique_max && peut_faire_partie == 1) {
			if ( (MATRICE_ARETES[i][sommets_clique_max[j]] != '1' && i != sommets_clique_max[j]) || i == sommets_clique_max[j]) {
				peut_faire_partie = 0;
			}
			++j;
		}
		if (peut_faire_partie == 1) {
			printf("%d ", i);
		}
	}
	printf("[Fin]\n");

	clique_max = clique_maximum2(sommets_clique_max);
	printf("\n=============\nClique Bob : %d\n-------------\n", clique_max);

	printf("# Vérification que les sommets de cette clique sont bien tous liés entre eux :\n[Début] ");
	for (int i = 0; i < clique_max; ++i) {
		printf("%d ", sommets_clique_max[i]);
		for (int j = 0; j < clique_max; ++j) {
			if (MATRICE_ARETES[sommets_clique_max[i]][sommets_clique_max[j]] != '1' && sommets_clique_max[i] != sommets_clique_max[j]) {
				printf("[Problème] ");
			}
		}
	}
	printf("[Fin]\n");

	printf("# Liste des autres sommets pouvant faire partie de cette clique :\n[Début] ");
	for (int i = 0; i < NOMBRE_DE_SOMMETS; ++i) {
		int peut_faire_partie = 1;
		int j = 0;
		while (j < clique_max && peut_faire_partie == 1) {
			if ( (MATRICE_ARETES[i][sommets_clique_max[j]] != '1' && i != sommets_clique_max[j]) || i == sommets_clique_max[j]) {
				peut_faire_partie = 0;
			}
			++j;
		}
		if (peut_faire_partie == 1) {
			printf("%d ", i);
		}
	}
	printf("[Fin]\n");

	clique_max = clique_maximum3(sommets_clique_max);
	printf("\n=============\nClique Tibo2 : %d\n-------------", clique_max);

	printf("\n# Vérification que les sommets de cette clique sont bien tous liés entre eux :\n[Début] ");
	for (int i = 0; i < clique_max; ++i) {
		printf("%d ", sommets_clique_max[i]);
		for (int j = 0; j < clique_max; ++j) {
			if (MATRICE_ARETES[sommets_clique_max[i]][sommets_clique_max[j]] != '1' && sommets_clique_max[i] != sommets_clique_max[j]) {
				printf("[Problème] ");
			}
		}
	}
	printf("[Fin]\n");

	printf("# Liste des autres sommets pouvant faire partie de cette clique :\n[Début] ");
	for (int i = 0; i < NOMBRE_DE_SOMMETS; ++i) {
		int peut_faire_partie = 1;
		int j = 0;
		while (j < clique_max && peut_faire_partie == 1) {
			if ( (MATRICE_ARETES[i][sommets_clique_max[j]] != '1' && i != sommets_clique_max[j]) || i == sommets_clique_max[j]) {
				peut_faire_partie = 0;
			}
			++j;
		}
		if (peut_faire_partie == 1) {
			printf("%d ", i);
		}
	}
	printf("[Fin]\n");
}