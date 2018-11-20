/* Definition du tas */

#define TAILLE_TAS 128	/* Taille de la zone mémoire dévolue au tas */
#define TAILLE_MIN 2	/* le plus petit bloc utilisable */
#define FIN -1		/* marqueur de fin de la liste chaînée des zones libres */

#define TAILLE_LIGNE_AFFICHAGE 16 // Taille des lignes pour l'affichage
#define N_LIGNES TAILLE_TAS/TAILLE_LIGNE_AFFICHAGE

char tas[TAILLE_TAS]; // Zone mémoire du tas

int libre;		/* indice du premier bloc libre dans le tas, ou
			   FIN si aucun bloc libre */


// Prototypes
void afficher_tas();
void tas_init(void);
int first_fit(unsigned int taille, int* precedent);
char* tas_malloc(unsigned int taille);
void tas_free(char* ptr);

