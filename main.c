#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fonctions.h"

#define TAILLE_MAX 25

int main(int argc, char *argv[]) {

	/* LECTURE DU FICHIER */

	char* nom_fichier;

	if (argc == 1) { // argv[0] = le nom du fichier exécuté
		printf("Donner en paramètre le nom du fichier à exploiter\n");
		return EXIT_SUCCESS;
	} else {
		nom_fichier = (char*)malloc(strlen(argv[1]) * sizeof(char*)); // redimensionnement du tableau de char
		strcpy(nom_fichier, argv[1]); // copie de argv[1] dans nom_fichier
		printf("Lecture du fichier %s\n", nom_fichier);
	}

	FILE* fichier;
	fichier = fopen(nom_fichier, "r");

	if (fichier != NULL) {		// Ouverture ficher = OK
		char ligne[TAILLE_MAX];

		while (fgets(ligne, TAILLE_MAX, fichier) != NULL) {
			if(ligne[0] == 'p') { // p col x y		avec x le nombre de sommets et y le nombre d'arêtes
				char nb_sommets[TAILLE_MAX] = "";
				char nb_aretes[TAILLE_MAX] = "";
				int i;
				for(i=6; ligne[i] != ' '; ++i) { // lecture caractère par caractère de x
					nb_sommets[i-6] = ligne[i];	//nb_sommet est une chaine
				}
				int j = ++i;
				for(i=i; ligne[i] != ' '; ++i) { // lecture caractère par caractère de y
					nb_aretes[i-j] = ligne[i];
				}
				NOMBRE_DE_SOMMETS = atoi(nb_sommets);
				NOMBRE_D_ARETES = atoi(nb_aretes);
			} else if (ligne[0] == 'e') { // e x y		avec x et y le label de deux sommets
				char premier_sommet[TAILLE_MAX] = "";
				char deuxieme_sommet[TAILLE_MAX] = "";
				int i;
				for(i=2; ligne[i] != ' '; ++i) { // lecture caractère par caractère de x
					premier_sommet[i-2] = ligne[i];
				}
				int j = ++i;
				for(i=i; ligne[i] != ' '; ++i) { // lecture caractère par caractère de y
					deuxieme_sommet[i-j] = ligne[i];
				}
				ajouter_arete(atoi(premier_sommet), atoi(deuxieme_sommet));
			}
		}
	}
	else					// Echec de l'ouverture du fichier
	{
		printf("Impossible d'ouvrir le fichier %s", nom_fichier);
	}

	fclose(fichier);		// On ferme le fichier
	free(nom_fichier);

	/* CODE */

	initialiser_matrices();

	//afficher_sommets();

	free(SOMMETS);
	for (int i = 0; i < NOMBRE_DE_SOMMETS; ++i) {
		free(MATRICE_GRAPH[i]);
	}
	free(MATRICE_GRAPH);

	return EXIT_SUCCESS;
}