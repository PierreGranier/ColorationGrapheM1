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
 * Retourne le cardinal du plus grand sous-graphe complet (ou clique maximum)
 * S'il existe une arête entre tous les sommets d'un sous-graphe, alors ce sous-graphe est une N-clique, N étant le nombre de sommets appartenenant à la clique
 */
int clique_maximum() {
	int max_clique = 0;
	// Recherche de toutes les cliques en partant de chaque sommet du graphe
	for (int i = 0; i < NOMBRE_DE_SOMMETS; ++i) {
		// Recherche d'un sommet appartenant à la clique en les parcourant tous et en les ajoutant au tableau de clique s'ils sont aptes,à en faire partie
		// Étant donné que l'ajout d'un sommet à la clique a une influence sur l'ajout ou pas des sommets suivant, il faut en ommettre certains pour qu'ils ne bloquent pas la situation
		// Donc boucle for supplémentaire pour trouver toutes les cliques possibles
		// Ca sert à rien d'ommettre les x premiers sommets s'il ne reste que y sommets à regarder, y étant inférieur à la max clique trouvée, car il sera imppossible avec y sommets de faire une clique plus grande que celle déjà enregistrée
		// for (int ommettre = 0; ommettre < NOMBRE_DE_SOMMETS; ++ommettre) {
		for (int ommettre = 0; ommettre < (NOMBRE_DE_SOMMETS-max_clique); ++ommettre) {
			// printf("\nRecherche d'une clique avec le sommet %d :\n", i);
			int voisins_de_clique[NOMBRE_DE_SOMMETS]; // tableau de sommets tous reliés entre eux
			int nb_voisins_de_clique = 0;
			voisins_de_clique[nb_voisins_de_clique++] = i;
			for (int j = ommettre; j < NOMBRE_DE_SOMMETS; ++j) {
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


void meilleur_coloriage_opti_de_ouf_lol_tupeuxpastestmdr() {
	//Bon, j'avais fait plein de trucs mais comme j'ai toujours pas compris les nouvelles variables je vais tenter de faire du pseudo-code :)
/*
	Parcours_graphe()
		si sommet[i] = debut 
		alors sommet[i].couleur = 1
		sinon sommet[i].couleur = couleur+1

		parcourir_graphe_erreur()			//on pourrait mettre une variable de changement. Lorsque un sommet change de couleur, la variable passe à vraie et on peut reboucler. Lorsque la variable est fausse, aucune couleur n'a été changée donc on peut s'arrêter
			int indice = chercher() 		//parcourt le graphe jusqu'à la première erreur. Donne l'indice du sommet et check si une meilleure coloration existe
				sommet[indice].couleur = sommet[i].couleur++
		OU SINON 
		parcourir_graphe_erreur()
			int var_conflit = 1, var_meilleure_coul = 1
			si var_conflit = 1 
			alors int indice = chercher_conflit() //parcourt le graphe jusqu'à la première erreur. Donne l'indice du sommet et change sa couleur avec nb_couleur++
				si indice != -1
				alors sommet[indice].couleur = sommet[i].couleur++
				sinon 				//pas d'erreur trouvée
					var_conflit = 0
			sinon int indice = chercher_meilleure_couleur() //parcourt le graphe pour voir si une meilleure coloration est possible
				si indice != -1 
				alors sommet[indice].couleur = sommet[i].couleur++
				sinon 				//pas de meilleure coloration 
					var_meilleure_col = 0

		EDIT : En fait c'est nul parce que faut faire les deux fonctions en même temps. Donc une fonction qui check d'abord si y'a des conflits sur le sommet.
		Si y'a, on change la couleur et on passe au sommet suivant et on change la variable de changement
		Si y'en a pas, on regarde si y'a une meilleure coloration. 
		Si y'a, on change la couleur et on passe au sommet suivant et on change la variable de changement
		Si y'en a pas on passe au suivant.
*/
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
