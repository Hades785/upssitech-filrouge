#include "indexation.h"
#include "constantes.h"
#include <stdio.h>
#include <dirent.h>
#include <assert.h>

void getAllFiles(const char * chemin_fichiers,const char * extension,Capsule * caps){
	DIR * fileDirectory = opendir(chemin_fichiers);
	assert(fileDirectory != NULL);
	struct dirent * fichierTrouve = readdir(fileDirectory);
	do{
		addElementCopy(caps,fichierTrouve->d_name);//TODO chemin absolu
		fichierTrouve = readdir(fileDirectory);
	}while(fichierTrouve != NULL);
}

void indexer_texte(const char * chemin_desc,const ConfMap * map){
	
}

void indexer_image(const char * chemin_desc,const ConfMap * map){
	
}

void indexer_audio(const char * chemin_desc,const ConfMap * map){
	
}