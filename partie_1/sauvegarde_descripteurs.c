#include <stdio.h>
#include <stdlib.h>
#include "sauvegarde_descripteurs.h"
//la premiere ligne du fichier contient le nombre de descripteurs contenus
//chaque ligne suivante contient un descripteur
Capsule loadDescripteurs(unsigned char * successFlag,String fichierDescripteur){
	FILE * fichier = fopen(fichierDescripteur.chaine,"r");
	Capsule caps;
	if(fichier == NULL){
		* successFlag = ECHEC;
		caps.nbDescripteurs = 0;
		caps.descripteurs = NULL;
		return caps;
	}
	fscanf(fichier,"%u",&caps.nbDescripteurs);
	caps.descripteurs = malloc(sizeof(String)*caps.nbDescripteurs);
	if(caps.descripteurs == NULL){
		caps.nbDescripteurs = 0;
		* successFlag = ECHEC;
		return caps;
	}
	int car;
	do{
		car = fgetc(fichier);
	}while(car != '{' && car != EOF);
	
	
	fclose(fichier);
	* successFlag = REUSSITE;
	return caps;
}
void saveDescripteurs(unsigned char * successFlag,Capsule capsule,String fichierDescripteurs){
	FILE * fichier = fopen(fichierDescripteur.chaine,"w");
	if(fichier == NULL){
		* successFlag = ECHEC;
	}
	fprintf(fichier,"%u\n",capsule.nbDescripteurs);
	for(unsigned int i = capsule.nbDescripteurs-1;i >= 0;i--){
		fputc('{',fichier);
		fputs(capsule.descripteurs[i],fichier);
		fputs("}\n",fichier);
	}
	
	fclose(fichier);
	* successFlag = REUSSITE;
}