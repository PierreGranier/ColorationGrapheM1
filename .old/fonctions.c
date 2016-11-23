#include "fonctions.h"

int NOMBRE_DE_COULEURS = 0;


void initialiser_aretes() {
	// dimensionne le tableau à deux dimensions

	MATRICE_ARETES = (char**)malloc(NOMBRE_DE_SOMMETS * sizeof(char*)); // NxN
	for (int i = 0; i < NOMBRE_DE_SOMMETS; ++i) { // dimensionne chaque ligne
		MATRICE_ARETES[i] = (char*)malloc(NOMBRE_DE_SOMMETS * sizeof(char));
	}
	
	// remplit la matrice de '0'

	for (int i = 0; i < NOMBRE_DE_SOMMETS; ++i) {
		for (int j = 0; j < NOMBRE_DE_SOMMETS; ++j) {
			MATRICE_ARETES[i][j] = '0';
		}
	}
}

void initialiser_couleurs() {
	// dimensionne le tableau à deux dimensions

	MATRICE_COULEURS = (char**)malloc(0 * sizeof(char*)); // 0xN
}

void ajouter_couleurs(int indice_couleur) {

	// Pour chaque couleur à ajouter il faut ajouter un tableau à une dimension dans la matrice des couleurs
	// Il faut donc réallouer l'espace pour la matrice en prenant soin de sauvegarder les données de cette dernière et des les recopier une fois l'allocation faite

	while (NOMBRE_DE_COULEURS <= indice_couleur) {
		char** couleurs_sauvegarde = (char**)malloc(NOMBRE_DE_COULEURS * sizeof(char*));

		// Copie des données de la matrice des couleurs vers la sauvegarde (allouer l'espace de chaque ligne), ligne par ligne et case par case
		for (int i = 0; i < NOMBRE_DE_COULEURS; ++i) {
			couleurs_sauvegarde[i] = (char*)malloc(NOMBRE_DE_SOMMETS * sizeof(char)); // dimensionne la ligne
			for (int j = 0; j < NOMBRE_DE_SOMMETS; ++j) { // copie de chaque élément de la matrice pour cette ligne
				couleurs_sauvegarde[i][j] = MATRICE_COULEURS[i][j];
			}
		}

		// Redimensionnement de la nouvelle matrice des couleurs
		++NOMBRE_DE_COULEURS;
		MATRICE_COULEURS = (char**)malloc(NOMBRE_DE_COULEURS * sizeof(char*)); // redimensionne la matrice (ré-allocation mémoire)

		// Copie des données de la sauvegarde vers la nouvelle matrice (allouer l'espace de chaque ligne) et mise à '0' des éléments de la nouvelle et dernière ligne
		for (int i = 0; i < NOMBRE_DE_COULEURS; ++i) {
			MATRICE_COULEURS[i] = (char*)malloc(NOMBRE_DE_SOMMETS * sizeof(char)); // dimensionne la ligne
			if (i == NOMBRE_DE_COULEURS-1) {
				for (int j = 0; j < NOMBRE_DE_SOMMETS; ++j) { // mise à '0' de la nouvelle ligne
					MATRICE_COULEURS[i][j] = '0';
				}
			} else {
				for (int j = 0; j < NOMBRE_DE_SOMMETS; ++j) { // copie de chaque élément de la sauvegarde pour cette ligne
					MATRICE_COULEURS[i][j] = couleurs_sauvegarde[i][j];
				}
			}
		}

		// Liberation de la mémoire de la matrice de sauvegarde
		for (int i = 0; i < NOMBRE_DE_COULEURS-1; ++i) { // libère la mémoire dela sauvegarde
			free(couleurs_sauvegarde[i]);
		}
		free(couleurs_sauvegarde);
	}
}

void liberer_aretes() {
	for (int i = 0; i < NOMBRE_DE_SOMMETS; ++i) {
		free(MATRICE_ARETES[i]);
	}
	free(MATRICE_ARETES);
}

void liberer_couleurs() {
	for (int i = 0; i < NOMBRE_DE_COULEURS; ++i) {
		free(MATRICE_COULEURS[i]);
	}
	free(MATRICE_COULEURS);
}


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

void afficher_couleurs(int pourcentage_visible) {
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


void format_standard_aretes() {
	printf("\np col %d %d\n", NOMBRE_DE_SOMMETS, NOMBRE_D_ARETES);
	for (int i = 0; i < NOMBRE_DE_SOMMETS; ++i) {
		for (int j = 0; j <= i; ++j) {
			if (MATRICE_ARETES[i][j] == '1') printf("e %d %d\n", i+1, j+1);
		}
	}
	printf("\n");
}

void format_standard_couleurs() {
	//printf("\nK=%d\n", NOMBRE_DE_COULEURS);
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


void ajouter_arete(int indice1, int indice2) {
	MATRICE_ARETES[indice1][indice2] = '1';
	MATRICE_ARETES[indice2][indice1] = '1';
}


void associer_couleur(int indice_sommet, int indice_couleur) {
	ajouter_couleurs(indice_couleur);

	// Enlever les autres couleurs assignées au sommet et lui ajouter la couleur demandée
	for (int i = 0; i < NOMBRE_DE_COULEURS; ++i) {
		MATRICE_COULEURS[i][indice_sommet] = '0';
	}
	MATRICE_COULEURS[indice_couleur][indice_sommet] = '1';
}


char couleur_du_sommet(int indice_sommet) {
	for (int i = 0; i < NOMBRE_DE_COULEURS; ++i) {
		if (MATRICE_COULEURS[i][indice_sommet] == '1') {
			return i;
		}
	}
	return '-';
}


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
	
	afficher_couleurs(20);
	//printf("lolilol cest bon tkt = %d\n", est_bien_colorie());
	//Ok donc maintenant on est sûr que y'a pas de conflits après cette fonction de coloration

	// Sans le code ci-dessus, on ne donne pas des couleurs à la volée, mais on fait un changement de couleur supplémentaire
	// Le coloriage semble être le même

	// Enfin, on reparcourt le graphe et on l'améliore en changeant les couleurs si possible : on prend une couleur déjà utilisée
	int variable_de_changement = 1;		//variable de changement. Check si une couleur a changé dans le dernier parcours
	int compteur_tours = 0;
	int compteur_changements = 0;
	int a = 0;
	while (variable_de_changement == 1 || a == 1) {
		variable_de_changement = 0;
		for (int i = 0; i < NOMBRE_DE_SOMMETS; ++i) { // pour chaque sommet
			int ancienne_couleur = couleur_du_sommet(i);
			associer_couleur(i, 0); // changement de sa couleur pour la plus petite
			for (int j = 0; j < NOMBRE_DE_SOMMETS; ++j) { // parcours des autres sommets
				if (MATRICE_ARETES[i][j] == '1' && couleur_du_sommet(i) == couleur_du_sommet(j)) { // s'il y a un conflit de couleur entre le sommets et un frère à lui
					associer_couleur(i, couleur_du_sommet(i)+1); // attribution d'une autre couleur
					j = 0;
				}
			}
			if (couleur_du_sommet(i) != ancienne_couleur) { // s'il y a eu un changement de couleur, il faudra re-parcourir le graphe pour re-optimiser et vérifier les conflits
				++compteur_changements;
				variable_de_changement = 1;
			}
		}
		++compteur_tours;
		format_standard_couleurs();
		// la technique de la dernière chance
		/*if (a == 1) {
			a = 0;
		} else {
			if (variable_de_changement == 1) {
				a = 0;
			} else {
				a = 1;
			}
		}*/
	}

	//printf("lolilol cest bon tkt = %d\n", est_bien_colorie());

	printf("\n================ fin ================\n%d tours\n", compteur_tours);
	printf("%d tours\n", compteur_tours);
	printf("%d changements de couleur\n", compteur_changements);
}

int compter_couleurs() {
	int i=0, nb_coul = 1, j=0;
	for(i=0; i<NOMBRE_D_ARETES; ++i) {
		if(couleur_du_sommet(i) > j) {
			nb_coul++;
			j++;
		}
	}
return nb_coul;
}

void tibo() {
	// compter les sommets avec la couleur k => possible avec matrice et tableau
	// connaitre la couleur d'un sommet => plus rapide avec un tableau : O(1) contre O(N) : constant contre linéaire

}
