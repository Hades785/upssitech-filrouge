#include "sauvegarde_descripteurs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//la premiere ligne du fichier contient le nombre de descripteurs contenus
//chaque ligne suivante contient un descripteur
Capsule loadDescripteurs(unsigned char * successFlag,const char * fichierDescripteur){
	FILE * fichier = fopen(fichierDescripteur,"r");
	char buf[TAILLE_BUF];
	Capsule caps;
	
	//printf("init lecture");
	//getchar();
	
	if(fichier == NULL){
		* successFlag = ECHEC;
		caps.nbDescripteurs = 0;
		caps.descripteurs = NULL;
		return caps;
	}
	
	//printf("lecture nombre");
	//getchar();
	
	fscanf(fichier,"%u",&caps.nbDescripteurs);
	sds * descs = malloc(sizeof(sds)*caps.nbDescripteurs);
	if(descs == NULL){
		caps.nbDescripteurs = 0;
		caps.descripteurs = NULL;
		* successFlag = ECHEC;
		return caps;
	}
	
	//printf("nombre: %u\nparsing",caps.nbDescripteurs);
	//getchar();
	
	char * pt;
	
	unsigned int nbDescReel = 0;
	int car;
	for(unsigned int i = 0;i < caps.nbDescripteurs;i++){
		//on cherche le premier '{'
		//printf("descripteur courant: %u\n",i);
		do{
			car = fgetc(fichier);
			/*if(car != '\n')
				printf("car : %c\n",car);
			else
				printf("car : \\n\n");*/
		}while(car != '{' && car != EOF);
		if(car == EOF) break;
		
		sds s = sdsnew("");
		//printf("new sds: %s\n",s);
		int j;
		do{
			pt = fgets(buf,TAILLE_BUF,fichier);
			//printf("getted from file: %s\n",pt);
			unsigned int temp = strlen(buf);
			for(j = 0;j < temp;j++){
				//on recherche la brace fermante '}'
				/*if(buf[j] != '\n')
					printf("car : %c\n",buf[j]);
				else
					printf("car : \\n\n");*/
				if(buf[j] == '}'){
					buf[j] = '\0';
					break;
				}
			}
			s = sdscat(s,buf);
			//printf("String final: %s\n",s);
			nbDescReel++;
		}while(j == 0 && pt != NULL);
		descs[i]=s;
	}
	
	caps.descripteurs = descs;
	caps.nbDescripteurs = nbDescReel;
	
	fclose(fichier);
	* successFlag = SUCCES;
	return caps;
}

void saveDescripteurs(unsigned char * successFlag,const Capsule capsule,const char * fichierDescripteurs){
	printf("Ecriture fichier %s\n",fichierDescripteurs);
	FILE * fichier = fopen(fichierDescripteurs,"w");
	if(fichier == NULL){
		* successFlag = ECHEC;
		return;
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

void freeCapsule(Capsule caps){
	for(unsigned int i = 0;i < caps.nbDescripteurs;i++){
		sdsfree(caps.descripteurs[i]);
	}
	free(caps.descripteurs);
}

Capsule newCapsule(unsigned char * successFlag){
	Capsule caps;
	caps.nbDescripteurs = 0;
	caps.descripteurs = malloc(sizeof(sds)*10);
	if(caps.descripteurs == NULL){
		*successFlag = ECHEC;
		caps.size = 0;
		return caps;
	}
	caps.size = 10;
	*successFlag = SUCCES;
	return caps;
}

unsigned char resetCapsule(Capsule * caps){
	sds * newTab = malloc(sizeof(sds)*10);
	if(newTab != NULL){
		freeCapsule(*caps);
		caps->nbDescripteurs = 0;
		caps->size = 10;
		caps->descripteurs = newTab;
		return SUCCES;
	}
	return ECHEC;
}

unsigned char addElementCopy(Capsule * caps,const char * element){
	return addElement(caps,sdsnew(element));
}

unsigned char addElement(Capsule * caps,sds element){
	if(caps->nbDescripteurs == caps->size){
		sds * newTab = malloc(sizeof(sds)*(caps->size+10));
		if(newTab == NULL)
			return ECHEC;
		memcpy(newTab,caps->descripteurs,sizeof(sds)*(caps->size));
		caps->size+=10;
		free(caps->descripteurs);
		caps->descripteurs = newTab;
	}
	caps->descripteurs[caps->nbDescripteurs] = element;
	caps->nbDescripteurs++;
	return SUCCES;
}

unsigned int nombreDescripteurs(const Capsule caps){
	return caps.nbDescripteurs;
}

void removeDescripteur(Capsule * caps,unsigned int index){
	if(index < caps->nbDescripteurs){
		sdsfree(caps->descripteurs[index]);
		for(unsigned int i = index;i < (caps->nbDescripteurs-1);i++){
			caps->descripteurs[i] = caps->descripteurs[i+1];
		}
		caps->nbDescripteurs--;
	}
}