

// STRUCTURE


typedef struct sommet {
	int label;
	int poids;
	int couleur;
} Sommet;



// VARIABLES GLOBALES


int NOMBRE_DE_SOMMETS, NOMBRE_D_ARETES;
Sommet *SOMMETS;
int **MATRICE_GRAPH;



// FONCTIONS


/*
 * Retourne l'indice du sommet correspondant au label, -1 sinon
 */
int indice_de(char* label);

/*
 * Appele la fonction d'ajout de sommet pour le label1 et le label2
 * Met à 1 les bits (i,j) et (j,i) de la matrice, i et j étant respectivement l'indice du sommet correspondant au label1 et l'indice du sommet correspondant au label2
 */
void ajouter_arete(char* label1, char* label2);

/*
 * Initialise un sommet à partir d'un label
 * L'ajoute au tableau des sommets s'il n'y a pas déjà de sommet correspondant à ce label
 */
void ajouter_sommet(char* label);

/**
 *
 */
void colorier();







/*
https://www.rocq.inria.fr/secret/Anne.Canteaut/COURS_C/chapitre3.html
https://openclassrooms.com/courses/apprenez-a-programmer-en-c/les-chaines-de-caracteres
*/



/* j'ai trouvé ça sur internet
size_t FindIndex( const int a[], size_t size, int value )
{
    size_t index = 0;

    while ( index < size && a[index] != value ) ++index;

    return ( index == size ? -1 : index );
}

int indice_de(char* label) {
	int index = 0;
	while (index < NOMBRE_DE_SOMMETS) {
		if (SOMMETS[index].label == atoi(label))
			return index;
		++index;
	}
	return -1;
}
*/