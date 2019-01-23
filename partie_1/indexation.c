#include "indexation.h"
#include "constantes.h"
#include <stdio.h>
#include <dirent.h>
#include <assert.h>
#include <string.h>

void getAllFiles(const char * chemin_fichiers,const char * extension,Capsule * caps){
	printf("Indexation dossier : %s\n",chemin_fichiers);
	DIR * fileDirectory = opendir(chemin_fichiers);
	if(fileDirectory == NULL)
		perror("Erreur acces dossier ");
	assert(fileDirectory != NULL);
	struct dirent * fichierTrouve = readdir(fileDirectory);
	do{
		if(fichierTrouve->d_type == DT_REG){
			sds name = sdsnew(fichierTrouve->d_name);
			sdsrange(name,-strlen(extension),-1);
			if(strcmp(name,extension) == 0)
				addElement(caps,sdscat(sdscat(sdsnew(chemin_fichiers),"/"),fichierTrouve->d_name));
			sdsfree(name);
		}else if(fichierTrouve->d_type == DT_DIR){
			if(!(strcmp(fichierTrouve->d_name,".") == 0 || strcmp(fichierTrouve->d_name,"..") == 0)){
				sds s = sdscat(sdscat(sdsnew(chemin_fichiers),"/"),fichierTrouve->d_name);
				getAllFiles(s,extension,caps);
				sdsfree(s);
			}
		}
		fichierTrouve = readdir(fileDirectory);
	}while(fichierTrouve != NULL);
}

void indexer_texte(const char * chemin_desc,const ConfMap * map){
}

void indexer_image(const char * chemin_desc,const ConfMap * map){
	unsigned char flag;
	unsigned int nbCouleurs = getConfigValueLong(map,"nb_couleurs_max",&flag);
	if(flag != SUCCES){
		puts("Erreur parametres");
		assert(flag != ECHEC);
	}
	Capsule descs = newCapsule(&flag);
	Capsule fichiers = newCapsule(&flag);
	getAllFiles(getConfigValue(map,"chemin_bdd_im",&flag),".txt",&fichiers);
	for(unsigned int i = 0;i < fichiers.nbDescripteurs;i++){
		addElement(&descs,indexation_image(fichiers.descripteurs[i],)
	}
}

void indexer_audio(const char * chemin_desc,const ConfMap * map){
	
}