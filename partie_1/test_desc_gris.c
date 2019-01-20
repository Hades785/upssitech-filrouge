#include "sauvegarde_descripteurs.h"
#include "indexation_image.h"
#include "constantes.h"

#include <assert.h>
#include <stdio.h>

int main(){
	unsigned char flag;
	unsigned char a=5;
	Capsule caps=newCapsule(&flag);
	assert(flag != ECHEC);
	for(unsigned int i = 51;i <= 63;i++){
		sds chem = sdscatprintf(sdsempty(),"../documents/images/gris/%02u.txt",i);
		printf("f:%s\n",chem);
		addElement(&caps,indexation_image(chem,50,0.1,i,a));
	}
	
	
	saveDescripteurs(&flag,caps,"rechercheimage.desc");
	assert(flag != ECHEC);
	freeCapsule(caps);
	return 0;
}