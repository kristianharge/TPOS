#include <stdio.h>
#include "tp-tas.h"
#include <ctype.h>


/*
 * Affiche le tas
 */
void afficher_tas()
{
	int i, j;
	printf ("Première zone libre: %d\n\n", libre);
	// Affichage du tas ligne par ligne
	for (i = 0; i < N_LIGNES; i++)
	{
		for (j = 0; j < TAILLE_LIGNE_AFFICHAGE; j++)
		{
			// Affichage du numéro de case
			printf("%4d", j + TAILLE_LIGNE_AFFICHAGE*i);
		}
		printf("\n");
		for (j = 0; j < TAILLE_LIGNE_AFFICHAGE; j++)
		{ 
			// Affichage du contenu de la case
			printf("%4d", tas[j + TAILLE_LIGNE_AFFICHAGE*i]);
		}
		printf("\n");
		
		for (j = 0; j < TAILLE_LIGNE_AFFICHAGE; j++)
		{
			if (isprint(tas[j + 16*i]))
			{ // Si la case contient un caractère imprimable, l'imprimer
				printf("%4c", tas[j + 16*i]);
			} else { // Sinon afficher des espaces
				printf("    ");
			}
		}
		printf("\n\n");
	}
	printf("---------------------------------------------------------------\n\n");
}

/*
 * Initialise le tas vide: l'ensemble du tas est une seule grande zone libre
 */
void tas_init() {
	libre = 0;
	tas[0] = TAILLE_TAS -1;
	tas[1] = FIN;
	// Debug -- on met toutes les autres cases  (non initialisées) à 'z'
	/*for (int i = 2; i < TAILLE_TAS; i++) {
		tas[i] = 'z';
	}*/
}

/* ------------------------------------ */

/* Stratégie first fit: renvoie l'indice de la première zone libre trouvée de
 * taille assez grande
 * Si aucune zone n'est assez grande, renvoie -1.
 * *precedent est l'indice de la zone libre précédente, ou -1 si la zone libre
 * renvoyée est la première
 */
int first_fit(unsigned int taille, int* precedent)
{
	//TODO: question 2.1 DONE
	int i = libre, FIN = -1;

	//Chercher les zones libres
	while (i < TAILLE_TAS){
		//alors la zone est libre
		if (tas[i+1] == -1){
			//on controle la taille
			if (tas[i] >= taille){
				FIN = i;
				break;
			}
			*precedent = i;
		}
		i += tas[i] + 1;	
	}

	return FIN;
}

/* tas_malloc: alloue une zone libre de taille demandée et renvoie un pointeur vers
 * elle, ou NULL en cas d'échec.
 */
char* tas_malloc(unsigned int taille)
{
	//TODO: question 2.2
	int index, i;
	index = first_fit(taille, -1);
	if (index == -1){
		fprintf( stderr, "Zone pas trouvee dans %d, %s\n", __LINE__, __FILE__);
		return NULL;
	}
	
	tas[index] = taille;
	tas[index + 1] = '';
	//recreer le tas vide correspondant au reste de la zone alouee
	return index;
}

/* tas_free: libère la zone dont le début est désigné par ptr */
void tas_free(char* ptr)
{
	//TODO: question 2.3
	return;
}


int main(int argc, char* argv[])
{
	tas_init();
	afficher_tas();
	// TODO: Appelez vos fonctions ici (tests et question 2.4)
	return 0;
}
