#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fonctions.h"

#define TAILLE_MAX 90

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
			// puts(ligne);
			if(ligne[0] == 'p') { // p col x y		avec x le nombre de sommets et y le nombre d'arêtes
				char nb_sommets[TAILLE_MAX] = "";
				char nb_aretes[TAILLE_MAX] = "";
				int i = 2; // ligne[2] = c ou e (pour col ou edge)
				while (ligne[i] != ' ') ++i; // p col ou p edge
				int j = ++i; // ++i car il faut passer l'espace avant x
				for(i=i; ligne[i] != ' '; ++i) { // lecture caractère par caractère de x
					nb_sommets[i-j] = ligne[i];	// nb_sommet est une chaine
				}
				j = ++i; // ++i icar il faut passer l'espace avant y
				for(i=i; ligne[i] != ' '; ++i) { // lecture caractère par caractère de y
					nb_aretes[i-j] = ligne[i];
				}
				NOMBRE_DE_SOMMETS = atoi(nb_sommets);
				NOMBRE_D_ARETES = atoi(nb_aretes);
				printf("\n# Initialisation de la matrice d'arêtes : ");
				initialiser_aretes();
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
	
	int choix = 0;
	while (choix != 9) {
		printf("\nChoisissez une action à effectuer :");
		printf("\n\t[0] Comparaison des algorithmes de coloriage");
		printf("\n\t[1] Colorier avec le premier algorithme (approche naïve)");
		printf("\n\t[2] Colorier avec le deuxième algorithme (sommets triés par ordre)");
		printf("\n\t[3] Colorier avec le troisième algorithme (sommets de la clique en premier)");
		printf("\n\t[7] Voir la matrice des arêtes");
		printf("\n\t[8] Calculer la taille de la clique maximum (et nombre chromatique)");
		printf("\n\t[9] Quittez le programme\n");
		int ok = scanf("%d", &choix);
		if (ok == 0);

		switch (choix) {
			case 0:
				printf("\n");
				int meilleur_algo;
				int comparaison[3];
				printf("Premier algorithme en cours...\n");
					initialiser_couleurs();
					premier_algorithme();
					comparaison[0] = NOMBRE_DE_COULEURS;
					meilleur_algo = 1;
				printf("Deuxième algorithme en cours...\n");
					initialiser_couleurs();
					deuxieme_algorithme();
					comparaison[1] = NOMBRE_DE_COULEURS;
					if (comparaison[1] < comparaison[0]) meilleur_algo = 2;
				printf("Troisième algorithme en cours...\n");
					initialiser_couleurs();
					troisieme_algorithme();
					comparaison[2] = NOMBRE_DE_COULEURS;
					if (comparaison[2] < comparaison[meilleur_algo-1]) meilleur_algo = 3;
				printf("\n[%d]\t[%d]\t[%d]", comparaison[0], comparaison[1], comparaison[2]);
				printf("\nMeilleur algorithme : %d\n", meilleur_algo);
				break;
			case 1:
				printf("\n########################################");
				printf("\n# COLORIAGE AVEC LE PREMIER ALGORITHME");
				printf("\n# APPROCHE NAIVE");
				printf("\n########################################\n");
				initialiser_couleurs();
				premier_algorithme();
				printf("\nNombre de couleurs utilisées : %d", compter_couleurs());
				printf("\nLe graphe est bien colorié : %d\n", est_bien_colorie());
				printf("\n########################################\n");
				printf("# RECAP POUR LE COMPTE RENDU");
				printf("\n########################################\n");
				format_standard_couleurs();
				break;
			case 2:
				printf("\n########################################");
				printf("\n# COLORIAGE AVEC LE DEUXIEME ALGORITHME");
				printf("\n# SOMMETS COLORIES PAR ORDRE CROISSANT");
				printf("\n########################################\n");
				initialiser_couleurs();
				deuxieme_algorithme();
				printf("\nNombre de couleurs utilisées : %d", compter_couleurs());
				printf("\nLe graphe est bien colorié : %d\n", est_bien_colorie());
				printf("\n########################################\n");
				printf("# RECAP POUR LE COMPTE RENDU");
				printf("\n########################################\n");
				format_standard_couleurs();
				break;
			case 3:
				printf("\n########################################");
				printf("\n# COLORIAGE AVEC LE TROISIEME ALGORITHME");
				printf("\n# INITIÉ PAR LA CLIQUE MAXIMALE");
				printf("\n########################################\n");
				initialiser_couleurs();
				troisieme_algorithme();
				printf("\nNombre de couleurs utilisées : %d", compter_couleurs());
				printf("\nLe graphe est bien colorié : %d\n", est_bien_colorie());
				printf("\n########################################\n");
				printf("# RECAP POUR LE COMPTE RENDU");
				printf("\n########################################\n");
				format_standard_couleurs();
				break;
			case 7:
				printf("\nDonnez le pourcentage de la matrice des arêtes à afficher : [?] %%\n");
				int pourcentage;
				ok = scanf("%d", &pourcentage);
				afficher_aretes(pourcentage);
				break;
			case 8:
				printf("\nTaille de la clique maximum (nombre chromatique) TIBO : %d\n", clique_maximum());
				printf("\nTaille de la clique maximum (nombre chromatique) BOB  : %d\n", clique_maximum2());
				break;
			default:
				break;
		}
	}

	liberer_aretes();
	liberer_couleurs();

	return EXIT_SUCCESS;
}