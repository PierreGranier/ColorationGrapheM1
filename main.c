#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "main.h"

#define TAILLE_MAX 1000

int main(int argc, char *argv[]) {
	
//	int N;			//Nombre de sommets
//	int degre;		//Degre max
	int test = 1234;
	FILE* fichier = NULL;
	fichier = fopen("test.txt", "r");	
	#define SUPER test //c degueu lol
    if (fichier != NULL)	{	//Ouverture ficher = OK
		//int car = 0;
		char chaine[TAILLE_MAX] = "";
		
		while(fgets(chaine, TAILLE_MAX, fichier)) {
			int i;
			char *nb_som = "";
			if(chaine[0] == 'p') {
				for(i=6; chaine[i] != ' '; ++i) {
					if(isdigit(chaine[i])) {
						printf("%c", chaine[i]);
						strcat(nb_som, &chaine[i]);
					}
					if(chaine[i] == ' ') {
						printf("ok");			
						//strcat(atoi(chaine[i]);
					}
				}
				printf("nb de sommet = %s", nb_som); 
			}
		}
		/*while(fgets(chaine, TAILLE_MAX, fichier)) {		//lecture des lignes et stockage dans chaine

			printf("tour %d\n", i);
			++i;
			
			if(chaine[0] == 'p') {
				char* nb_som = "";
				for(car = 0; car != 32; car = fgetc(fichier)) {			// 32 = espace 
					printf("car = %c\n", car);
					//sprintf(nb_som, car);
					//printf("nb_som = %s\n", nb_som);
					
				}
				N = strtol(nb_som, NULL, 10);
			}*/				
		//printf("Nombre de sommets = %d\n", N);
    }
    else				//Echec de l'ouverture du fichier
    {
        printf("Impossible d'ouvrir le fichier test.txt");
    }


	fclose(fichier);		//On ferme le fichier	

return 0;
}
