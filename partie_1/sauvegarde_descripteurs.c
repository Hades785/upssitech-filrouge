#include <stdio.h>
#include <stdlib.h>
#include "sauvegarde_descripteurs.h"

//la premiere ligne du fichier contient le nombre de descripteurs contenus
//chaque ligne suivante contient un descripteur
Capsule loadDescripteurs(unsigned char * successFlag,const sds fichierDescripteur){
	FILE * fichier = fopen(fichierDescripteur.chaine,"r");
	char * buf[TAILLE_BUF];
	Capsule caps;
	if(fichier == NULL){
		* successFlag = ECHEC;
		caps.nbDescripteurs = 0;
		caps.descripteurs = NULL;
		return caps;
	}
	
	fscanf(fichier,"%u",&caps.nbDescripteurs);
	caps.descripteurs = malloc(sizeof(sds)*caps.nbDescripteurs);
	if(caps.descripteurs == NULL){
		caps.nbDescripteurs = 0;
		caps.descripteurs = NULL;
		* successFlag = ECHEC;
		return caps;
	}
	
	int car;
	for(unsigned int i = caps.nbDescripteurs-1;i >= 0;i--){
		//on cherche le premier '{'
		do{
			car = fgetc(fichier);
		}while(car != '{' && car != EOF);
		if(car == EOF) break;
		
		sds s = sdsnew("");
		int j;
		do{
			fgets(buf,TAILLE_BUF,fichier);
			for(j = strlen(buf)-1;j >= 0;j--){
				//on recherche la brace fermante '}'
				if(buf[j] == '}'){
					buf[j] = '\0';
					break;
				}
			}
			s = sdscat(s,buf);
		}while(j >= 0);
		caps.descripteurs[i]=s;
	}
	
	fclose(fichier);
	* successFlag = SUCCES;
	return caps;
}
void saveDescripteurs(unsigned char * successFlag,const Capsule capsule,const sds fichierDescripteurs){
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
	* successFlag = SUCCES;
}
void freeCapsule(Capsule * caps){
	for(unsigned int i = caps->nbDescripteurs-1;i >= 0;i--){
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