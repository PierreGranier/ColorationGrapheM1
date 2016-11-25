#include <stdio.h>
#include <stdlib.h>

// VARIABLES GLOBALES

int NOMBRE_DE_SOMMETS, NOMBRE_D_ARETES, NOMBRE_DE_COULEURS;
char** MATRICE_ARETES;

// FONCTIONS SUR LES STRUCTURES
// implémentées dans les .c du dossier structures

void initialiser_aretes();
void liberer_aretes();
void afficher_aretes(int pourcentage_visible);
void format_standard_aretes();
void ajouter_arete(int indice1, int indice2);
int ordre_du_sommet(int i);
int clique_maximum();

void initialiser_couleurs();
void liberer_couleurs();
void ajouter_couleurs(int indice_couleur);
void afficher_couleurs(int pourcentage_visible);
void format_standard_couleurs();
void associer_couleur(int indice_sommet, int indice_couleur);
int couleur_du_sommet(int indice_sommet);

// FONCTIONS POUR LE COLORIAGE
// implémentées dans fonctions.c

int compter_couleurs();
int chercher_premiere_couleur(int indice_sommet);
int est_entierement_colorie();
int est_bien_colorie();
int clique_maximum();
void premier_algorithme();
void deuxieme_algorithme();


