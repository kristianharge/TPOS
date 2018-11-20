#include <stdio.h>
#include "tp-tas.h"
#include <ctype.h>
#include <string.h>


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
	//i = indice zone actuelle
	int i;
	if(*precedent != -1)
		i = *precedent;
	else
		i = 0;

	//Chercher les zones libres
	while (i < TAILLE_TAS){
		//alors la zone est libre
		if (tas[i + 1] == FIN){
			//on controle la taille
			if (tas[i] >= taille){
				return i;
			}
			//dans ce cas precedent est la zone actuelle
			*precedent = i;
		}
		i += tas[i] + 1;
	}

	return -1;
}

/* tas_malloc: alloue une zone libre de taille demandée et renvoie un pointeur vers
 * elle, ou NULL en cas d'échec.
 */
char* tas_malloc(unsigned int taille)
{
	//TODO: question 2.2 Done
	int index;
	index = first_fit(taille, &libre);
	if (index == -1){
		fprintf( stderr, "Zone pas trouvee dans %d, %s\n", __LINE__, __FUNCTION__);
		return NULL;
	}
	
	//recreer le tas vide correspondant au reste de la zone alouee
	if (tas[index] > taille + 1){//il nous faut au moins deux cases pour déclarer une zone vide
		tas[index + taille + 1] = tas[index] - taille - 1;//on déclare la taille de la zone vide
		tas[index + taille + 2] = -1;//on déclare le début de la zone vide
	}
	//allouer la mémoire
	tas[index] = taille;
	tas[index + 1] = '\0';
	return tas + index + 1;
}

/* tas_free: libère la zone dont le début est désigné par ptr sans espaces contigus*/
void tas_free(char* ptr)
{
	//TODO: question 2.3 Done
	int i;
	*ptr = -1;
	for (i = 1; i < *ptr; i++){
		*(ptr + i) = 0;
	}
	ptr = NULL;
	return;
}

//Le jeu d'essai de la question 2 dans le .txt
void jeu_essai(){
	char *p1, *p2, *p3, *p4;
	tas_init();
	afficher_tas();
	p1 = (char *) tas_malloc(10);
	p2 = (char *) tas_malloc(12);
	p3 = (char *) tas_malloc(5);
	afficher_tas();
	strcpy( p1, "tp 1" );
	strcpy( p2, "tp 2" );
	strcpy( p3, "tp 3" );
	afficher_tas();
	tas_free( p2 );
	afficher_tas();
	p4 = (char *) tas_malloc(9);
	strcpy( p4, "systeme" );
	afficher_tas();
}

void jeu_essai_v2(){
	char *p1, *p2, *p3, *p4;
	tas_init();
	afficher_tas();
	p1 = (char *) tas_malloc(10);
	p2 = (char *) tas_malloc(12);
	p3 = (char *) tas_malloc(5);
	afficher_tas();
	strcpy( p1, "tp 1" );
	strcpy( p2, "tp 2" );
	strcpy( p3, "tp 3" );
	afficher_tas();
	tas_free_v2(p2, &libre);
	tas_free_v2(p3, &libre);
	afficher_tas();
	p4 = (char *) tas_malloc(9);
	strcpy( p4, "systeme" );
	afficher_tas();
}


int main(int argc, char* argv[])
{
	// TODO: Appelez vos fonctions ici (tests et question 2.4)
	jeu_essai_v2();
	return 0;
}
