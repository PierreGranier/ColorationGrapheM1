#include "fonctions.h"

/*
 * Retourne le nombre de couleurs utilisées dans le graphe
 */
int compter_couleurs() {
	int i=0, nb_coul=0;
	for(i=0; i<NOMBRE_DE_SOMMETS; ++i) {
		while(couleur_du_sommet(i) >= nb_coul) {
			++nb_coul;
		}
	}
	return nb_coul;
}

/*
 * Retourne 1 si tous les sommets ont une couleur, 0 sinon
 */
int est_entierement_colorie() {
	for (int i = 0; i < NOMBRE_DE_SOMMETS; ++i) {
		if (couleur_du_sommet(i) == -1) return 0;
	}
	return 1;
}

/*
 * Vérifie que le graphe est bien colorié, c'est-à-dire qu'il ne contient pas de conflit
 * Un conflit intervient lorsque deux sommets adjascents/frères/liés sont de la même couleur
 * La fonction retourne 1 quand le graphe est correct, 0 sinon
 */
int est_bien_colorie() {
	// Pour chaque sommet i
	for (int i = 0; i < NOMBRE_DE_SOMMETS; ++i) {
		// Pour chaque sommet j
		for (int j = 0; j < NOMBRE_DE_SOMMETS; ++j) {
			// Si le sommet i est lié au sommet j et qu'ils ont tous les deux la même couleur : conflit
			if (MATRICE_ARETES[i][j] == '1' && couleur_du_sommet(i) == couleur_du_sommet(j)) {
				// printf("\nConflit entre (%d, %d)", i, j);
				return 0;
			}
		}
	}
	return 1;
}

/*
 * Retourne la premiere couleur minimale dispo dans le voisinage du sommet indice_sommet
 */
int chercher_premiere_couleur(int indice_sommet) {
	int i, couleur_min = 0;
	for(i = 0; i < NOMBRE_DE_SOMMETS; ++i) {
		if(MATRICE_ARETES[indice_sommet][i] == '1' && couleur_min == couleur_du_sommet(i)) {
			++couleur_min;
			i=-1;
		}
	}
	return couleur_min;
}

/*
 * Sommets non triés
 * attribution d'une même couleur à tous les sommets sauf au premier
 * Association d'une nouvelle couleur à un sommet s'il est en conflit
 * Boucle d'optimisation sur N tours : pour chaque sommet, association de la plus petite couleur non utilisée par ses voisins
 */
void premier_algorithme() {
	// Au début, on associe une première couleur au premier sommet
	associer_couleur(0, 0); // indice_sommet, indice_couleur
	for (int i = 1; i < NOMBRE_DE_SOMMETS; ++i) {
		associer_couleur(i, 1);
	}
	
	// Ensuite, on attribue une nouvelle couleur à chaque sommet qui entre en conflit avec son voisin
	for (int i = 0; i < NOMBRE_DE_SOMMETS; ++i) {
		for (int j = 0; j < NOMBRE_DE_SOMMETS; ++j) {
			// Conflit = même couleur pour deux sommets voisins
			// Checker la couleur de chaque sommet si ce sommet est un voisin du sommet
			if (MATRICE_ARETES[i][j] == '1' && couleur_du_sommet(i) == couleur_du_sommet(j)) { // s'il le sommet a un frère et qu'ils ont la même couleur : conflit
				// Changer la couleur de i en fonction de ses voisins
				// Parcourir les voisins, mettre la première couleur disponible
				// OU
				// Changer la couleur de i en fonction du nombre de couleurs déjà utilisées
				// Attribuer une nouvelle couleur au sommet
				associer_couleur(i, NOMBRE_DE_COULEURS);
			}
		}
	}
	// Sans le code ci-dessus, on ne donne pas des couleurs à la volée, mais on fait un changement de couleur supplémentaire
	// Le coloriage semble être le même

	// afficher_couleurs(20);
	//printf("lolilol cest bon tkt = %d\n", est_bien_colorie());
	//Ok donc maintenant on est sûr que y'a pas de conflits après cette fonction de coloration

	// printf("\n================ tour 0 ================\n");
	// printf("Le graphe est bien colorié : %d\n", est_bien_colorie());
	// format_standard_couleurs();

	// Enfin, on reparcourt le graphe et on l'améliore en changeant les couleurs si possible : on prend une couleur déjà utilisée
	int variable_de_changement = 1;
	int compteur_tours = 0;
	int compteur_changements = 0;
	while (variable_de_changement == 1) {
		++compteur_tours;
		variable_de_changement = 0;
		for (int i = 0; i < NOMBRE_DE_SOMMETS; ++i) { // pour chaque sommet
			int ancienne_couleur = couleur_du_sommet(i);
			associer_couleur(i, 0); // changement de sa couleur pour la plus petite
			for (int j = 0; j < NOMBRE_DE_SOMMETS; ++j) { // parcours des autres sommets
				if (MATRICE_ARETES[i][j] == '1' && couleur_du_sommet(i) == couleur_du_sommet(j)) { // s'il y a un conflit de couleur entre le sommets et un frère à lui
					associer_couleur(i, chercher_premiere_couleur(i)); // attribution d'une autre couleur
					//j = 0;
				}
			}
			if (couleur_du_sommet(i) != ancienne_couleur) { // s'il y a eu un changement de couleur, il faudra re-parcourir le graphe pour re-optimiser et vérifier les conflits
				++compteur_changements;
				variable_de_changement = 1;
			}
		}
		NOMBRE_DE_COULEURS = compter_couleurs();

		// printf("\n================ tour %d ================\n", compteur_tours);
		// printf("%d changements de couleur", compteur_changements);
		// printf("\nLe graphe est bien colorié : %d\n", est_bien_colorie());
		// format_standard_couleurs();
	}

	// printf("\n================  fini  ================\n%d tours\n", compteur_tours);
	// printf("%d changements de couleur\n", compteur_changements);
}

/*
 * Sommets non triés, pour chaque voisin, association de la plus petite couleur non utilisée par ses voisins
 */
void premier_algorithme_bis() {
	for (int i = 0; i < NOMBRE_DE_SOMMETS; ++i) {
		associer_couleur(i, chercher_premiere_couleur(i));
	}
}

/*
 * Sommets coloriés dans l'ordre décroissant de leur ordre (ceux qui ont le plus de voisins sont coloriés en premier)
 */
void deuxieme_algorithme() {
	/*while (est_entierement_colorie() == 0) {
		int sommet_max = 0;
		int ordre_sommet_max = 0;
		// Pour chaque sommet (non colorié), si son ordre > ordre_sommet_max, on le retient comme étant le sommet_max
		for (int i = 0; i < NOMBRE_DE_SOMMETS; ++i) {
			if (couleur_du_sommet(i) == -1 && ordre_du_sommet(i) > ordre_sommet_max) {
				sommet_max = i;
				ordre_sommet_max = ordre_du_sommet(i);
			}
		}
		// Associer au sommet max la plus petite couleur disponible (non occupée par ses voisins)
		associer_couleur(sommet_max, chercher_premiere_couleur(sommet_max));
	}*/

	int sommets_tries[NOMBRE_DE_SOMMETS];
	int ordres_sommets[NOMBRE_DE_SOMMETS];

	// Initialisation des tableaux
	for (int i = 0; i < NOMBRE_DE_SOMMETS; ++i) {
		sommets_tries[i] = i;
		ordres_sommets[i] = ordre_du_sommet(i);
	}

	// Tri à bulle
	for (int i = NOMBRE_DE_SOMMETS - 1; i > 0; --i) {
		for (int j = 0; j < i; ++j) {
			if (ordres_sommets[j+1] > ordres_sommets[j]) {
				// Echange des deux entiers dans le tableau des ordres
				int tmp = ordres_sommets[j];
				ordres_sommets[j] = ordres_sommets[j+1];
				ordres_sommets[j+1] = tmp;
				// Echange des deux entiers dans le tableau des sommets
				tmp = sommets_tries[j];
				sommets_tries[j] = sommets_tries[j+1];
				sommets_tries[j+1] = tmp;
			}
		}
	}

	// Pour chaque sommet du tableau des sommets triés par odre croissant
	for (int i = 0; i < NOMBRE_DE_SOMMETS; ++i) {
		associer_couleur(sommets_tries[i], chercher_premiere_couleur(sommets_tries[i]));
	}
}

/*
 * Coloration des sommets de la clique maximale en priorité
 */
void troisieme_algorithme() {
	int sommets_clique_max[NOMBRE_DE_SOMMETS];
	// int clique_max = clique_maximum(sommets_clique_max);
	int clique_max = clique_maximum2(sommets_clique_max);

	// Colorier les sommets de la cliques ordonnés par leur ordre décroisant
	int sommets_tries[clique_max];
	int ordres_sommets[clique_max];

	for (int i = 0; i < clique_max; ++i) {
		sommets_tries[i] = sommets_clique_max[i];
		ordres_sommets[i] = ordre_du_sommet(sommets_clique_max[i]);
	}
	
	/*for (int i = clique_max - 1; i > 0; --i) {
		for (int j = 0; j < i; ++j) {
			if (ordres_sommets[j+1] > ordres_sommets[j]) {
				// Echange des deux entiers dans le tableau des ordres
				int tmp = ordres_sommets[j];
				ordres_sommets[j] = ordres_sommets[j+1];
				ordres_sommets[j+1] = tmp;
				// Echange des deux entiers dans le tableau des sommets
				tmp = sommets_tries[j];
				sommets_tries[j] = sommets_tries[j+1];
				sommets_tries[j+1] = tmp;
			}
		}
	}*/

	for (int i = 0; i < clique_max; ++i) {
		associer_couleur(sommets_tries[i], chercher_premiere_couleur(sommets_tries[i]));
	}	

	// Colorier les autres sommets
	for (int i = 0; i < NOMBRE_DE_SOMMETS; ++i) {
		if (couleur_du_sommet(i) == -1) {
			associer_couleur(i, chercher_premiere_couleur(i));
		}
	}
}

/*

test2.txt
clique1		triés		73
			non triés	71
clique2		triés		73
			non triés	74

r1000.1c.col
clique 1	triés		139
			non triés	136
clique2		triés		139
			non triés	140

Vérifier à la fin de la clique que les sommets du tableau sont bien tous liés entre eux
double for
	[i][j] != '1' => return 0
essayer de tourner avec la mtrice de couleurs pour comparer les temps d'execution
*/