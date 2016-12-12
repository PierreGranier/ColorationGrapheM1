#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fonctions.h"

#define TAILLE_MAX 90

int main(int argc, char *argv[]) {
	char nom_fichier[TAILLE_MAX];
	int ok = 1;

	if (argc == 2) { // argv[0] = le nom du fichier exécuté
		ok = 2;
	}

	int choix = -1;
	while (choix != 10) {

		/* LECTURE DU FICHIER */

		if (choix == -1 || choix == 9) {
			
			if (ok == 2) {
				strcpy(nom_fichier, argv[1]); // copie de argv[1] dans nom_fichier
				ok = 1;
			} else {
				printf("\nNom du fichier contenant le graphe : ");
				ok = scanf("%s", nom_fichier);
			}

			FILE* fichier = NULL;
			fichier = fopen(nom_fichier, "r");

			if (fichier != NULL) {		// Ouverture ficher = OK
				printf("\n########################################");
				printf("\n# Lecture du fichier %s", nom_fichier);
				
				char ligne[TAILLE_MAX];

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
						j = ++i; // ++i car il faut passer l'espace avant y
						for(i=i; ligne[i] != ' ' && ligne[i] != '\n'; ++i) { // lecture caractère par caractère de y
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
						for(i=i; ligne[i] != ' ' && ligne[i] != '\n'; ++i) { // lecture caractère par caractère de y
							deuxieme_sommet[i-j] = ligne[i];
						}
						ajouter_arete(atoi(premier_sommet)-1, atoi(deuxieme_sommet)-1);		// le -1 sert parce que le tableau commence à 0 contrairement au num du sommet 
					}
				}
				printf("OK");
				fclose(fichier);		// On ferme le fichier
				printf("\n# Fin de la lecture du fichier");
				printf("\n########################################\n");
				// format_html_aretes(nom_fichier);
			}
			else {						// Echec de l'ouverture du fichier
				printf("\n# Impossible d'ouvrir le fichier %s\n", nom_fichier);
				// return EXIT_SUCCESS;
				ok = 0;
			}
		}

		/* CODE */

		if (ok != 0) {
			printf("\n\n\n\n########################################");
			printf("\n# %s", nom_fichier);
			printf("\n########################################");
			printf("\nChoisissez une action à effectuer :");
			printf("\n\t[0] Comparaison des algorithmes de coloriage");
			printf("\n\t[1] Colorier avec le premier algorithme (approche naïve)");
			printf("\n\t[2] Colorier avec le deuxième algorithme (sommets triés par leur ordre)");
			printf("\n\t[3] Colorier avec le troisième algorithme (sommets d'une clique en premier)");
			printf("\n\t[4] Voir la matrice des arêtes");
			printf("\n\t[5] Recherche d'une clique maximale");
			printf("\n\t[6] Recherche de la clique maximale (peu prendre beaucoup de temps)");
			printf("\n\t[9] Lire un autre graphe");
			printf("\n\t[10] Quittez le programme\n");
			ok = scanf("%d", &choix);
			if (ok == 0);

			printf("\n\n\n\n");

			switch (choix) {
				case 0:
					printf("\n########################################");
					printf("\n# EXECUTION ET COMPARAISON DES TROIS ALGOS");
					printf("\n########################################\n\n");
					int meilleur_algo;
					int comparaison[3];
					printf("  Premier algorithme en cours de coloriage...\n");
						liberer_couleurs();
						initialiser_couleurs();
						premier_algorithme();
						printf("    %d couleurs\n\n", NOMBRE_DE_COULEURS);
						comparaison[0] = NOMBRE_DE_COULEURS;
						meilleur_algo = 1;
					printf("  Deuxième algorithme en cours de coloriage...\n");
						liberer_couleurs();
						initialiser_couleurs();
						deuxieme_algorithme();
						printf("    %d couleurs\n\n", NOMBRE_DE_COULEURS);
						comparaison[1] = NOMBRE_DE_COULEURS;
						if (comparaison[1] < comparaison[0]) meilleur_algo = 2;
					printf("  Troisième algorithme en cours de coloriage...\n");
						liberer_couleurs();
						initialiser_couleurs();
						troisieme_algorithme();
						printf("    %d couleurs\n\n", NOMBRE_DE_COULEURS);
						comparaison[2] = NOMBRE_DE_COULEURS;
						if (comparaison[2] < comparaison[meilleur_algo-1]) meilleur_algo = 3;
					printf("  -> Meilleur algorithme de coloration de graphe : %d\n\n  Ré-exécution du meilleur algorithme...\n", meilleur_algo);
						liberer_couleurs();
						initialiser_couleurs();
						switch (meilleur_algo) { // ré-execution du meilleur algo avant que le xxx_out.txt soit créé
							case 1:
								premier_algorithme();
								break;
							case 2:
								deuxieme_algorithme();
								break;
							case 3:
								troisieme_algorithme();
								break;
							default:
								break;
						}
					break;
				case 1:
					printf("\n########################################");
					printf("\n# COLORIAGE AVEC LE PREMIER ALGORITHME");
					printf("\n# APPROCHE NAIVE");
					printf("\n########################################\n");
					liberer_couleurs();
					initialiser_couleurs();
					premier_algorithme();
					printf("\nNombre de couleurs utilisées : %d", compter_couleurs());
					printf("\nLe graphe est bien colorié : %d\n", est_bien_colorie());
					break;
				case 2:
					printf("\n########################################");
					printf("\n# COLORIAGE AVEC LE DEUXIEME ALGORITHME");
					printf("\n# SOMMETS COLORIES PAR ORDRE DÉCROISSANT");
					printf("\n########################################\n");
					liberer_couleurs();
					initialiser_couleurs();
					deuxieme_algorithme();
					printf("\nNombre de couleurs utilisées : %d", compter_couleurs());
					printf("\nLe graphe est bien colorié : %d\n", est_bien_colorie());
					break;
				case 3:
					printf("\n########################################");
					printf("\n# COLORIAGE AVEC LE TROISIEME ALGORITHME");
					printf("\n# INITIÉ PAR UNE CLIQUE MAXIMALE");
					printf("\n########################################\n");
					liberer_couleurs();
					initialiser_couleurs();
					troisieme_algorithme();
					printf("\nNombre de couleurs utilisées : %d", compter_couleurs());
					printf("\nLe graphe est bien colorié : %d\n", est_bien_colorie());	
					break;
				case 4:
					printf("\nDonnez le pourcentage de la matrice des arêtes à afficher : [?] %%\n");
					int pourcentage;
					ok = scanf("%d", &pourcentage);
					afficher_aretes(pourcentage);
					break;
				case 5:
					// http://stackoverflow.com/questions/20654191/c-stack-memory-goto-and-jump-into-scope-of-identifier-with-variably-modified
					printf("\n########################################");
					printf("\n# RECHERCHE D'UNE CLIQUE MAX");
					printf("\n########################################\n\n");
					int clique_max;
					printf("  Premier algorithme en cours de recherche...\n");
						clique_max = clique_maximum(NULL);
						printf("    %d sommets\n\n", clique_max);
						comparaison[0] = clique_max;
						meilleur_algo = 1;
					printf("  Deuxième algorithme en cours de recherche...\n");
						clique_max = clique_maximum2(NULL);
						printf("    %d sommets\n\n", clique_max);
						comparaison[1] = clique_max;
						if (comparaison[1] > comparaison[0]) meilleur_algo = 2;
					printf("  -> Meilleur algorithme de recherche d'une clique max : %d\n", meilleur_algo);
					break;
				case 6:
					printf("\n########################################");
					printf("\n# RECHERCHE DE LA CLIQUE MAX (TEMPS ÉLEVÉ)");
					printf("\n########################################\n\n");
					int clique = clique_genetique(NULL);
					printf("  -> %d sommets\n", clique);
					break;
				case 9:
					puts("");
					break;
				default:
					break;
			}
			
			if (choix == 0 || choix == 1 || choix == 2 || choix == 3) {
				char sans_extension[strlen(nom_fichier)];
				int copier = 0;
				for (int i = strlen(nom_fichier)-1; i >= 0; --i) {
					sans_extension[i] = (copier == 1) ? nom_fichier[i] : '\0';
					if (nom_fichier[i] == '.') copier = 1;
				}
				
				printf("\n# Les couleurs des sommets ont été enregistrées dans le fichier %s_out.txt", sans_extension);
				format_standard_couleurs(nom_fichier);
			}
		} // fin if ok == 0
	}

	if (NOMBRE_DE_SOMMETS > 0) {
		liberer_aretes();
	}
	if (NOMBRE_DE_COULEURS > 0) {
		liberer_couleurs();
	}

	return EXIT_SUCCESS;
}