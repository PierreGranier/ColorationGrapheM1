#include "fonctions.h"


int NOMBRE_DE_COULEURS = 0;


void initialiser_matrices() {
	// dimensionne les tableaux à deux dimensions

	MATRICE_ARETES = (char**)malloc(NOMBRE_DE_SOMMETS * sizeof(char*)); // NxN
	for (int i = 0; i < NOMBRE_DE_SOMMETS; ++i) { // dimensionne chaque ligne
		MATRICE_ARETES[i] = (char*)malloc(NOMBRE_DE_SOMMETS * sizeof(char));
	}
	
	MATRICE_COULEURS = (char**)malloc(0 * sizeof(char*)); // 0xN

	// remplit les matrices de '0'

	for (int i = 0; i < NOMBRE_DE_SOMMETS; ++i) {
		for (int j = 0; j < NOMBRE_DE_SOMMETS; ++j) {
			MATRICE_ARETES[i][j] = '0';
		}
	}
}

void liberer_matrices() {
	for (int i = 0; i < NOMBRE_DE_SOMMETS; ++i) {
		free(MATRICE_ARETES[i]); // pb quand nb de couleurs >= 4
	}
	free(MATRICE_ARETES);

	for (int i = 0; i < NOMBRE_DE_COULEURS; ++i) {
		free(MATRICE_COULEURS[i]);
	}
	free(MATRICE_COULEURS); // pb quand nb de couleurs >= 4
}


void afficher_matrice_aretes(int pourcentage_visible) {
	printf("\n\n########################################");
	printf("\n# MATRICE ARETES\n# Taille %d x %d (lignes x colonnes)\n# Visualisée à %d %%", NOMBRE_DE_SOMMETS, NOMBRE_DE_SOMMETS, pourcentage_visible);
	printf("\n########################################\n\n");

	for (int i = 0; i < NOMBRE_DE_SOMMETS*pourcentage_visible/100; ++i) {
		for (int j = 0; j < NOMBRE_DE_SOMMETS*pourcentage_visible/100; ++j)
		// for (int j = 0; j <= i; ++j)
			(i == j) ? printf("O ") : printf("%c ", MATRICE_ARETES[i][j]);
		printf("\n");
	}
	printf("\n");
}

void afficher_matrice_couleurs(int pourcentage_visible) {
	printf("\n\n########################################");
	printf("\n# MATRICE COULEURS\n# Taille %d x %d (lignes x colonnes)\n# Visualisée à %d %%", NOMBRE_DE_COULEURS, NOMBRE_DE_SOMMETS, pourcentage_visible);
	printf("\n########################################\n\n");

	for (int i = 0; i < NOMBRE_DE_COULEURS; ++i) {
		for (int j = 0; j < NOMBRE_DE_SOMMETS*pourcentage_visible/100; ++j) {
			printf("%c ", MATRICE_COULEURS[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}


void format_standard_matrice_aretes() {
	printf("p col %d %d\n", NOMBRE_DE_SOMMETS, NOMBRE_D_ARETES);
	for (int i = 0; i < NOMBRE_DE_SOMMETS; ++i) {
		for (int j = 0; j <= i; ++j) {
			if (MATRICE_ARETES[i][j] == '1') printf("e %d %d\n", i+1, j+1);
		}
	}
}

void format_standard_matrice_couleurs() {
	printf("K=%d\n", NOMBRE_DE_COULEURS);
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

void ajouter_couleur(int indice_sommet, int indice_couleur) {

	// Pour chaque couleur à ajouter il faut ajouter un tableau à une dimension dans la matrice des couleurs
	// Il faut donc réallouer l'espace pour la matrice en prenant soin de sauvegarder les données de cette dernière et des les recopier une fois l'allocation faite

	while (NOMBRE_DE_COULEURS <= indice_couleur) {
		char** couleurs_sauvegarde = (char**)malloc(NOMBRE_DE_COULEURS * sizeof(char*));

		// Copie des données de la matrice des couleurs vers la sauvegarde (allouer l'espace de chaque ligne), ligne par ligne et case par case
		for (int i = 0; i < NOMBRE_DE_COULEURS; ++i) {
			couleurs_sauvegarde[i] = (char*)malloc(NOMBRE_DE_SOMMETS * sizeof(char)); // dimensionnne la ligne
			for (int j = 0; j < NOMBRE_DE_SOMMETS; ++j) { // copie de chaque élément de la matrice pour cette ligne
				couleurs_sauvegarde[i][j] = MATRICE_COULEURS[i][j];
			}
		}

		// Redimensionnement de la nouvelle matrice des couleurs
		++NOMBRE_DE_COULEURS;
		MATRICE_COULEURS = (char**)malloc(NOMBRE_DE_COULEURS * sizeof(char*)); // redimensionne la matrice (ré-allocation mémoire)

		// Copie des données de la sauvegarde vers la nouvelle matrice (allouer l'espace de chaque ligne) et mise à '0' des éléments de la nouvelle et dernière ligne
		for (int i = 0; i < NOMBRE_DE_COULEURS; ++i) {
			MATRICE_COULEURS[i] = (char*)malloc(NOMBRE_DE_SOMMETS * sizeof(char)); // dimensionne de la ligne
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
	
	MATRICE_COULEURS[indice_couleur][indice_sommet] = '1';
	
}

void ecraser_couleur(int indice_sommet, int indice_couleur) {
	// Enlever les autres couleurs assignées au sommet et lui ajouter la couleur demandée
	for (int i = 0; i < NOMBRE_DE_COULEURS; ++i) {
		MATRICE_COULEURS[i][indice_sommet] = '0';
	}
	
	ajouter_couleur(indice_sommet, indice_couleur);
}


char couleur_du_sommet(int indice_sommet) {
	for (int i = 0; i < NOMBRE_DE_COULEURS; ++i) {
		if (MATRICE_COULEURS[i][indice_sommet] == '1') {
			return i;
		}
	}
	return '-';
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
	ajouter_couleur(0, 0); // indice_sommet, indice_couleur
	for (int i = 1; i < NOMBRE_DE_SOMMETS; ++i) {
		ajouter_couleur(i, 1);
	}
	
	// Ensuite, on attribu une nouvelle couleur à chaque sommet qui entre en conflit avec son voisin
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
				ecraser_couleur(i, NOMBRE_DE_COULEURS);
			}
		}
	}

	// Enfin, on reparcourt le graphe et on l'améliore en changeant les couleurs si possible : on prend une couleur déjà utilisée
	//int verifier = 1;
	//while (verifier == 1) {
		for (int i = 0; i < NOMBRE_DE_SOMMETS; ++i) { // pour chaque sommet
			ecraser_couleur(i, 0); // changement de sa couleur pour la plus petite
			for (int j = 0; j < NOMBRE_DE_SOMMETS; ++j) { // parcours des autres sommets
				if (MATRICE_ARETES[i][j] == '1' && couleur_du_sommet(i) == couleur_du_sommet(j)) { // s'il y a un conflit de couleur entre le sommets et un frère à lui
					ecraser_couleur(i, couleur_du_sommet(i)+1); // attribution d'une autre couleur
				}
			}
		}
	//}
}

void tibo() {
	
}
