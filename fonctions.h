#include <stdio.h>
#include <stdlib.h>

// VARIABLES GLOBALES

int NOMBRE_DE_SOMMETS, NOMBRE_D_ARETES, NOMBRE_DE_COULEURS;
char** MATRICE_ARETES;

// FONCTIONS SUR LES STRUCTURES
// implémentées dans les .c du dossier structures

void initialiser_aretes();
void initialiser_couleurs();
void ajouter_couleurs(int indice_couleur);
void liberer_aretes();
void liberer_couleurs();
void afficher_aretes(int pourcentage_visible);
void afficher_couleurs(int pourcentage_visible);
void format_standard_aretes();
void format_standard_couleurs();
void ajouter_arete(int indice1, int indice2);
void associer_couleur(int indice_sommet, int indice_couleur);
char couleur_du_sommet(int indice_sommet);

// FONCTIONS POUR LE COLORIAGE
// implémentées dans fonctions.c

int compter_couleurs();
int est_bien_colorie();
void meilleur_coloriage_opti_de_ouf_lol_tupeuxpastestmdr();
void tibo();
