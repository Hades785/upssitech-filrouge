#include <string.h>
#include "String.h"
#define TAILLE_BUF 1000//taille des blocs lus entre chaque malloc du string du descripteur (en gros si tu comprends pas touche pas)
typedef struct{
	unsigned int nbDescripteurs;
	String * descripteurs;
}Capsule;

Capsule loadDescripteurs(unsigned char * successFlag,String fichierDescripteur);
void saveDescripteurs(unsigned char * successFlag,Capsule capsule,String fichierDescripteurs);