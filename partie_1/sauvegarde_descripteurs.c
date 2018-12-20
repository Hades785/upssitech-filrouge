#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sauvegarde_descripteurs.h"

//la premiere ligne du fichier contient le nombre de descripteurs contenus
//chaque ligne suivante contient un descripteur
Capsule loadDescripteurs(unsigned char * successFlag,const sds fichierDescripteur){
	FILE * fichier = fopen(fichierDescripteur,"r");
	char buf[TAILLE_BUF];
	Capsule caps;
	
	printf("init lecture");
	getchar();
	
	if(fichier == NULL){
		* successFlag = ECHEC;
		caps.nbDescripteurs = 0;
		caps.descripteurs = NULL;
		return caps;
	}
	
	printf("lecture nombre");
	getchar();
	
	fscanf(fichier,"%u",&caps.nbDescripteurs);
	sds * descs = malloc(sizeof(sds)*caps.nbDescripteurs);
	if(descs == NULL){
		caps.nbDescripteurs = 0;
		caps.descripteurs = NULL;
		* successFlag = ECHEC;
		return caps;
	}
	
	printf("parsing");
	getchar();
	
	char * pt;
	
	unsigned int nbDescReel = 0;
	int car;
	for(unsigned int i = 0;i < caps.nbDescripteurs;i++){
		//on cherche le premier '{'
		do{
			car = fgetc(fichier);
		}while(car != '{' && car != EOF);
		if(car == EOF) break;
		
		sds s = sdsnew("");
		int j;
		do{
			pt = fgets(buf,TAILLE_BUF,fichier);
			unsigned int temp = strlen(buf);
			for(j = 0;j < temp;j++){
				//on recherche la brace fermante '}'
				if(buf[j] == '}'){
					buf[j] = '\0';
					break;
				}
			}
			s = sdscat(s,buf);
			nbDescReel++;
		}while(j >= 0 && pt != NULL);
		descs[i]=s;
	}
	
	caps.descripteurs = descs;
	caps.nbDescripteurs = nbDescReel;
	
	fclose(fichier);
	* successFlag = SUCCES;
	return caps;
}

void saveDescripteurs(unsigned char * successFlag,const Capsule capsule,const sds fichierDescripteurs){
	FILE * fichier = fopen(fichierDescripteurs,"w");
	if(fichier == NULL){
		* successFlag = ECHEC;
	}
	fprintf(fichier,"%u\n",capsule.nbDescripteurs);
	for(unsigned int i = 0;i < capsule.nbDescripteurs;i++){
		fputc('{',fichier);
		fputs(capsule.descripteurs[i],fichier);
		fputs("}\n",fichier);
	}
	fclose(fichier);
	* successFlag = SUCCES;
}

void freeCapsule(Capsule * caps){
	for(unsigned int i = 0;i < caps->nbDescripteurs;i++){
		sdsfree(caps->descripteurs[i]);
	}
	free(caps->descripteurs);
	caps->descripteurs = NULL;
	caps->nbDescripteurs = 0;
}

unsigned char initCapsule(Capsule * caps,const unsigned int nbDescripteurs){
	caps->nbDescripteurs = nbDescripteurs;
	caps->descripteurs = malloc(sizeof(sds)*nbDescripteurs);
	if(caps->descripteurs == NULL){
		caps->nbDescripteurs = 0;
		return ECHEC;
	}
	return SUCCES;
}