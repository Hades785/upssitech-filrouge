#include "sds.h"
#define TAILLE_BUF 1000//taille des blocs lus entre chaque malloc du string du descripteur (en gros si tu comprends pas touche pas)
typedef struct{
	unsigned int nbDescripteurs;
	sds ** descripteurs;
}Capsule;

Capsule loadDescripteurs(unsigned char * successFlag,const sds fichierDescripteur);
void saveDescripteurs(unsigned char * successFlag,const Capsule capsule,const sds fichierDescripteurs);