#include "indexation.h"
#include "constantes.h"
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <assert.h>
#include <string.h>

#include "indexation_image.h"
#include "indexation_texte.h"
#include "indexation_audio.h"

sds getDirPathI(){
	return sdscat(sdscat(sdsnew(getenv("HOME")),"/"),STORAGE_FOLDER_NAME);
}

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
	unsigned char flag;
	unsigned int nb_mots_max = (unsigned int)getConfigValueLong(map,"nb_mots_max_texte",&flag);
	if(flag != SUCCES){
		puts("Erreur parametre");
		assert(flag != ECHEC);
	}
	unsigned int taille_min_mot = (unsigned int)getConfigValueLong(map,"taille_min_mot",&flag);
	if(flag != SUCCES){
		puts("Erreur parametre");
		assert(flag != ECHEC);
	}
	Capsule descs = newCapsule(&flag);
	Capsule mapNoms = newCapsule(&flag);
	Capsule fichiers = newCapsule(&flag);
	getAllFiles(getConfigValue(map,"chemin_bdd_tx"),".xml",&fichiers);
	for(unsigned int i = 0;i < fichiers.nbDescripteurs;i++){
		printf("Indexation texte : %s\n",fichiers.descripteurs[i]);
		addElement(&mapNoms,sdscatprintf(sdsempty(),"%u:%s",i,fichiers.descripteurs[i]));
		addElement(&descs,indexation_texte(fichiers.descripteurs[i],i,nb_mots_max,taille_min_mot));
	}
	freeCapsule(fichiers);
	sds chemin = sdscat(sdscat(getDirPathI(),"/"),NOM_FICH_DESC_TEXT);
	saveDescripteurs(&flag,descs,chemin);
	sdsfree(chemin);
	if(flag != SUCCES){
		puts("Erreur seuvegarde descripteurs");
		assert(flag != ECHEC);
	}
	chemin = sdscat(sdscat(getDirPathI(),"/"),NOM_FICH_MAP_NOM_TEXT);
	saveDescripteurs(&flag,mapNoms,chemin);
	freeCapsule(mapNoms);
	sdsfree(chemin);
	if(flag != SUCCES){
		puts("Erreur seuvegarde descripteurs");
		assert(flag != ECHEC);
	}
	Capsule mapMots = genere_table(descs);
	freeCapsule(descs);
	chemin = sdscat(sdscat(getDirPathI(),"/"),NOM_FICH_MAP_MOTS);
	saveDescripteurs(&flag,mapMots,chemin);
	freeCapsule(mapMots);
	sdsfree(chemin);
	if(flag != SUCCES){
		puts("Erreur seuvegarde descripteurs");
		assert(flag != ECHEC);
	}
}

void indexer_image(const char * chemin_desc,const ConfMap * map){
	unsigned char flag;
	unsigned int nbCouleurs = getConfigValueLong(map,"nb_couleurs_max_image",&flag);
	if(flag != SUCCES){
		puts("Erreur parametre");
		assert(flag != ECHEC);
	}
	
	float seuil = getConfigValueFloat(map,"seuil_couleur_image",&flag);
	if(flag != SUCCES){
		puts("Erreur parametre");
		assert(flag != ECHEC);
	}
	
	unsigned int nbBits = getConfigValueLong(map,"nb_bits_image",&flag);
	if(flag != SUCCES){
		puts("Erreur parametre");
		assert(flag != ECHEC);
	}
	
	Capsule descs = newCapsule(&flag);
	Capsule fichiers = newCapsule(&flag);
	getAllFiles(getConfigValue(map,"chemin_bdd_im"),".txt",&fichiers);
	for(unsigned int i = 0;i < fichiers.nbDescripteurs;i++){
		printf("Indexation image : %s\n",fichiers.descripteurs[i]);
		addElement(&descs,indexation_image(fichiers.descripteurs[i],nbCouleurs,seuil,i,nbBits));
	}
	sds chemin = sdscat(sdscat(getDirPathI(),"/"),NOM_FICH_DESC_IMG);
	saveDescripteurs(&flag,descs,chemin);
	sdsfree(chemin);
	freeCapsule(descs);
	freeCapsule(fichiers);
	if(flag != SUCCES){
		puts("Erreur seuvegarde descripteurs");
		assert(flag != ECHEC);
	}
}

void indexer_audio(const char * chemin_desc,const ConfMap * map){
	unsigned char flag;
	unsigned int nb_echant_pFen = (unsigned int)getConfigValueLong(map,"nb_echant_pfen",&flag);
	if(flag != SUCCES){
		puts("Erreur parametre");
		assert(flag != ECHEC);
	}
	unsigned int nb_int_amp = (unsigned int)getConfigValueLong(map,"nb_inter_amp",&flag);
	if(flag != SUCCES){
		puts("Erreur parametre");
		assert(flag != ECHEC);
	}
	Capsule descs = newCapsule(&flag);
	Capsule fichiers = newCapsule(&flag);
	getAllFiles(getConfigValue(map,"chemin_bdd_au"),".txt",&fichiers);
	for(unsigned int i = 0;i < fichiers.nbDescripteurs;i++){
		printf("Indexation audio : %s\n",fichiers.descripteurs[i]);
		//TODO: tests
		sds s = sdsdup(fichiers.descripteurs[i]);
		sds t = indexation_audio(fichiers.descripteurs[i], nb_echant_pFen, nb_int_amp);
		s = sdscat(s, ";");
		s = sdscat(s, t);
		addElementCopy(&descs, s);
		
		sdsfree(t);
		sdsfree(s);
	}
	sds chemin = sdscat(sdscat(getDirPathI(),"/"),NOM_FICH_DESC_AUD);
	saveDescripteurs(&flag,descs,chemin);
	sdsfree(chemin);
	freeCapsule(descs);
	freeCapsule(fichiers);
	if(flag != SUCCES){
		puts("Erreur seuvegarde descripteurs");
		assert(flag != ECHEC);
	}
}