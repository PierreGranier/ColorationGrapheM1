#include "fonctions.h"

int indice_de(int label) {
    //int i;
    /*for(i = 0; i < NOMBRE_DE_SOMMETS; ++i) {
        if(SOMMETS[i].label == )
    }*/
    return 0;
}

void ajouter_arete(int label1, int label2) {
    MATRICE_GRAPH[label1][label2] = 1;
    //SOMMETS[label2][label1] = 1;    //pas nécéssaire car graphe non orienté
}

void afficher_sommets() {
	for (int i = 0; i < NOMBRE_DE_SOMMETS; ++i) {
		printf("%d", SOMMETS[i].label);
	}
}