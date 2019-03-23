#include "utility.h"

#include <dirent.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

sds getDirPathI(){
	return sdscat(sdscat(sdsnew(getenv("HOME")),"/"),STORAGE_FOLDER_NAME);
}

sds getDirPath(){
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
	closedir(fileDirectory);
}