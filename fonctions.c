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
			} else {
				// printf("(%d, %d) ", i, j);
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
	for(i = 0; i<NOMBRE_DE_SOMMETS; ++i) {
		if(MATRICE_ARETES[indice_sommet][i] == '1' && couleur_min == couleur_du_sommet(i)) {
			++couleur_min;
			i=0;		
		}
	}
return couleur_min;
}

/*
 * Première approche
 */
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

/*
 * Sommets non triés, pour chaque voisin, association de la plus petite couleur non utilisée par ses voisins
 */
void premier_algo_bis() {
	for (int i = 0; i < NOMBRE_DE_SOMMETS; ++i) {
		associer_couleur(i, chercher_premiere_couleur(i));
	}
}

/*
 * Sommets coloriés dans l'ordre croissant de leur ordre (ceux qui ont le plus de voisins sont coloriés en premier)
 */
void deuxieme_algo() {
	while (est_entierement_colorie() == 0) {
		int sommet_max;
		int odre_sommet_max = 0;
		// Pour chaque sommet (non colorié), si son ordre > ordre_sommet_max, on le retient comme étant le sommet_max
		for (int i = 0; i < NOMBRE_DE_SOMMETS; ++i) {
			if (couleur_du_sommet(i) == -1 && ordre(i) > odre_sommet_max) {
				sommet_max = i;
				odre_sommet_max = ordre(i);
			}
		}
		// Associer au sommet max la plus petite couleur disponible (non occupée par ses voisins)
		associer_couleur(sommet_max, chercher_premiere_couleur(sommet_max));
	}
}

// tenter avec un algo qui part du sommet qui a le plus grand ordre et qui apartient à la plus grande clique
