#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fonctions.h"

#define TAILLE_MAX 50

int main(int argc, char *argv[]) {

	/* LECTURE DU FICHIER */

	char* nom_fichier;

	if (argc == 1) { // argv[0] = le nom du fichier exécuté
		printf("Donner en paramètre le nom du fichier à exploiter\n");
		return EXIT_SUCCESS;
	} else {
		nom_fichier = (char*)malloc(strlen(argv[1]) * sizeof(char*)); // redimensionnement du tableau de char
		strcpy(nom_fichier, argv[1]); // copie de argv[1] dans nom_fichier
		printf("\n########################################");
		printf("\n# Lecture du fichier %s", nom_fichier);
	}

	FILE* fichier;
	fichier = fopen(nom_fichier, "r");

	if (fichier != NULL) {		// Ouverture ficher = OK
		char ligne[TAILLE_MAX] = "";

		while (fgets(ligne, TAILLE_MAX, fichier) != NULL) {
			puts(ligne);
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
				printf("\n# Initialisation des tableaux d'arêtes et de couleurs : ");
				initialiser_aretes();
				initialiser_couleurs();
				printf("OK");
				printf("\n# Ajout des arêtes : ");
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
				ajouter_arete(atoi(premier_sommet)-1, atoi(deuxieme_sommet)-1);		// le -1 sert parce que le tableau commence à 0 contrairement au num du sommet 
			}
		}
	}
	else					// Echec de l'ouverture du fichier
	{
		printf("Impossible d'ouvrir le fichier %s", nom_fichier);
	}

	printf("OK");

	fclose(fichier);		// On ferme le fichier
	free(nom_fichier);

	printf("\n# Fin de la lecture du fichier");
	printf("\n########################################\n");

	/* CODE */

	afficher_aretes(0);
	// format_standard_matrice_aretes();
	
	printf("\n########################################\n");
	printf("# COLORIAGE DE OUF TROP BIEN LOLPASTESTTRUCBOBMDR");
	printf("\n########################################\n");

	meilleur_coloriage_opti_de_ouf_lol_tupeuxpastestmdr();

	//afficher_couleurs(10);
	format_standard_couleurs();
	printf("Nombre de couleurs utilisées : %d\n\n", compter_couleurs());

	printf("\nLe graphe est bien colorié : %d\n\n", est_bien_colorie());

	// liberer_aretes();
	// liberer_couleurs();

	return EXIT_SUCCESS;
}