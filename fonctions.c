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
 * Retourne la premiere couleur minimale dispo dans le voisinage du sommet indice_sommet
 */
int chercher_premiere_couleur(int indice_sommet) {
	int i, couleur_min = 0;
	for(i = 0; i<NOMBRE_DE_SOMMETS; ++i) {
		if(MATRICE_ARETES[indice_sommet][i] == '1' && couleur_min == couleur_du_sommet(i)) {
			++couleur_min;
			i=0;		
		}
	}
return couleur_min;
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
			} else {
				// printf("(%d, %d) ", i, j);
			}
		}
	}
	return 1;
}

/*
 * S'il existe une arête entre tous les sommets d'un sous-graphe, alors ce sous-graphe est une N-clique, N étant le nombre de sommets appartenenant à la clique
 * Il peut exister plusieurs cliques dans un graphe ; cette fonction retourne la taille de la clique maximum
 */
int clique_maximum() {
	int max_clique = 0;
	for (int i = 0; i < NOMBRE_DE_SOMMETS; ++i) {
		// printf("\nRecherche d'une clique avec le sommet %d :\n", i);
		int voisins_de_clique[NOMBRE_DE_SOMMETS]; // tableau de sommets tous reliés entre eux
		int nb_voisins_de_clique = 0;
		voisins_de_clique[nb_voisins_de_clique++] = i;
		for (int j = 0; j < NOMBRE_DE_SOMMETS; ++j) {
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
	return max_clique;
}


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

	printf("\n================ tour 0 ================\n");
	printf("Le graphe est bien colorié : %d\n", est_bien_colorie());
	format_standard_couleurs();

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

		printf("\n================ tour %d ================\n", compteur_tours);
		printf("%d changements de couleur", compteur_changements);
		printf("\nLe graphe est bien colorié : %d\n", est_bien_colorie());
		format_standard_couleurs();
	}

	printf("\n================  fini  ================\n%d tours\n", compteur_tours);
	printf("%d changements de couleur\n", compteur_changements);
}


void tibo() {
	// compter les sommets avec la couleur k => possible avec matrice et tableau
	// connaitre la couleur d'un sommet => plus rapide avec un tableau : O(1) contre O(N) : constant contre linéaire

}
