#include "sauvegarde_descripteurs.h"
#include "indexation_image.h"
#include "recherche_image.h"
#include "constantes.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
	unsigned char flag;
	unsigned char a=5;
	/*Capsule caps=newCapsule(&flag);
	assert(flag != ECHEC);
	for(unsigned int i = 1;i <= 50;i++){
		sds chem = sdscatprintf(sdsempty(),"../documents/images/rgb/%02u.txt",i);
		//printf("f:%s\n",chem);
		addElement(&caps,indexation_image(chem,50,0.1,i,a));
	}
	
	
	saveDescripteurs(&flag,caps,"rechercheimage.desc");
	assert(flag != ECHEC);
	
	//printf("gate1");getchar();
	
	freeCapsule(caps);
	
	//printf("gate2");getchar();*/
	
	Capsule caps = loadDescripteurs(&flag,"rechercheimage.desc");
	
	//printf("gate3");getchar();
	
	sds* res = recherche_image_file("../documents/images/rgb/15.txt",caps,10,a,50,0.1);
	
	//printf("gate4");getchar();
	
	/*unsigned int i = 0;
	while(res[i] != NULL){
		//printf("res:%u",i);getchar();
		printf("%u:%s\n",i,res[i]);
		i++;
	}*/
	
	unsigned int i = 0;
	while(res[i] != NULL){
		sdsfree(res[i]);
		i++;
	}
	free(res);
	
	//printf("lastFree");getchar();
	freeCapsule(caps);
	return 0;
}