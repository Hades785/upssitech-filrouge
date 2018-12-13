#include <string.h>
#include "String.h"
typedef struct{
	int nbDescripteurs;
	String [] descripteurs;
}Capsule;

Capsule loadDescripteurs(unsigned char * successFlag,String fichierDescripteur);
void saveDescripteurs(Capsule capsule,String fichier);