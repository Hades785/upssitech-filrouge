#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <errno.h>
#include <assert.h>
#include "constantes.h"
#include "config_reader.h"

#include <sys/types.h>
#include <sys/stat.h>

enum Etape{
	ETAPE_DEMANDE_CHEMIN,
	ETAPE_DEMARRAGE,
	MENU_PRINCIPAL,
	MENU_RECHERCHE,
	MENU_CONFIGURATION,
	ETAPE_INDEXATION
};

ConfMap defaultConfMap(){
	unsigned char flag;
	ConfMap map = newConfMap(&flag);
	assert(flag != ECHEC);
	/*flag = addValue(&map,"chemin_bdd","");
	assert(flag != ECHEC);*/
	flag = addValueLong(&map,"nb_res_image",15);
	assert(flag != ECHEC);
	flag = addValueLong(&map,"nb_bits_image",4);
	assert(flag != ECHEC);
}

int main(){
	enum Etape etape = ETAPE_DEMARRAGE;
	unsigned char flag;
	unsigned char running = 1;
	puts("Moteur de recherche de fichiers équipe 3");
	fputs("Chargement",stdout);
	sds dirPath = sdscat(sdscat(sdsnew(getenv("HOME")),"/"),STORAGE_FOLDER_NAME);
	dirPath = sdscat(dirPath,"/");
	
	//on test si le repertoire existe et on le cree si besoin
	DIR * progDir = opendir(dirPath);
	if(progDir == NULL){
		if(errno == ENOENT){
			if(mkdir(dirPath,0x777) == -1){
				perror("Erreur fatale ");
				sdsfree(dirPath);
				return -1;
			}
		}else{
			perror("Erreur fatale ");
			sdsfree(dirPath);
			return -1;
		}
	}
	fputs(".",stdout);
	
	ConfMap map;
	
	//on regarde si le fichier de configuration existe
	if(config_file_exists() == 0){
		if(errno == ENOENT){
			map = defaultConfMap();
			flag = save_config_file(map);
			if(flag != SUCCES){
				perror("Erreur fatale ");
				sdsfree(dirPath);
				freeConfMap(map);
				return -1;
			}
		}else{
			perror("Erreur fatale ");
			sdsfree(dirPath);
			return -1;
		}
	}else{
		map = read_config_file(&flag);
		if(flag != SUCCES){
			perror("Erreur fatale ");
			sdsfree(dirPath);
			freeConfMap(map);
		}
	}
	fputs(".",stdout);
	
	DIR * dirBdd;
	
	unsigned char presence_key_chemin = 0;
	long pos = keyPosition(&map,"chemin_bdd");
	if(pos == -1){
		etape = ETAPE_DEMANDE_CHEMIN;
	}else{
		dirBdd = opendir(map.values->descripteurs[pos]);
		if(dirBdd == NULL){
			if(errno == ENOENT){
				etape = ETAPE_DEMANDE_CHEMIN;
			}else{
				perror("Erreur fatale ");
				sdsfree(dirPath);
				freeConfMap(map);
				return -1;
			}
		}else{
			presence_key_chemin = 1;
		}
	}
	puts(".");
	char buf[300];
	
	
	do{
		switch(etape){
			case ETAPE_DEMANDE_CHEMIN:
				puts("Entrer le chemin vers la base de données :");
				puts("(soit en relatif si l'execution se fait toujours depuis le même répertoire, soit en absolu.)");
				puts("(Rappel : sur WSL, les disques sont en /mnt/)");
				scanf("%300s",buf);
				dirBdd = opendir(buf);
				if(dirBdd == NULL){
					if(errno != ENOENT){
						perror("Erreur fatale ");
						running = 0;
					}
				}else if(presence_key_chemin){
					changeValue(&map,"chemin_bdd",buf);
				}else{
					addValue(&map,"chemin_bdd",buf);
					presence_key_chemin = 1;
					etape = MENU_PRINCIPAL;
				}
				break;
			case ETAPE_DEMARRAGE:
				etape = MENU_PRINCIPAL;//TODO
				break;
			case MENU_PRINCIPAL:
				puts("MENU PRINCIPAL");
				puts("1-Recherche");
				puts("2-Configuration");
				puts("3-Réindexation");
				puts("\n0-Quitter");
				scanf("%1s",buf);
				switch(buf[0]){
					case '1': etape = MENU_RECHERCHE; break;
					case '2': etape = MENU_CONFIGURATION; break;
					case '3': etape = ETAPE_INDEXATION; break;
					case '0': running = 0; break;
				}
				break;
			default:
				running = 0;
				puts("Fatal error : unknown state.");
				break;
		}
	}while(running);
	sdsfree(dirPath);
	freeConfMap(map);
}