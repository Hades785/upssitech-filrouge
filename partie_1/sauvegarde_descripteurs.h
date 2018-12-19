#include <string.h>
#include "String.h"
typedef struct{
	unsigend int nbDescripteurs;
	String * descripteurs;
}Capsule;

Capsule loadDescripteurs(unsigned char * successFlag,String fichierDescripteur);
void saveDescripteurs(unsigned char * successFlag,Capsule capsule,String fichierDescripteurs);