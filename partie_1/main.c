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
	MENU_DEMANDE_CHEMIN,
	ETAPE_DEMARRAGE,
	MENU_PRINCIPAL,
	MENU_RECHERCHE,
	MENU_CONFIGURATION,
	MENU_CONFIG_IMAGE,
	MENU_CONFIG_AUDIO,
	MENU_CONFIG_TEXTE,
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
	flag = addValueLong(&map,"nb_couleurs_max_image",50);
	assert(flag != ECHEC);
	flag = addValueFloat(&map,"seuil_couleur_image",0.1);
	assert(flag != ECHEC);
	return map;
}

unsigned char verifMinConf(ConfMap * map){
	unsigned char resp = 0;
	if(keyPosition(map,"nb_res_image") == -1){
		resp = 1;
		addValueLong(map,"nb_res_image",15);
	}
	if(keyPosition(map,"nb_bits_image") == -1){
		resp = 1;
		addValueLong(map,"nb_bits_image",4);
	}
	if(keyPosition(map,"nb_couleurs_max_image") == -1){
		resp = 1;
		addValueLong(map,"nb_couleurs_max_image",50);
	}
	if(keyPosition(map,"seuil_couleur_image") == -1){
		resp = 1;
		addValueFloat(map,"seuil_couleur_image",0.1);
	}
	return resp;
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
			if(mkdir(dirPath,S_IRWXU) == -1){
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
	unsigned char mapModif = 0;
	
	//on regarde si le fichier de configuration existe
	if(config_file_exists() == 0){
		if(errno == ENOENT){
			map = defaultConfMap();
			flag = save_config_file(map);//pas de mapmodif car on la save direct
			if(flag != SUCCES){
				perror("Erreur fatale 1 ");
				sdsfree(dirPath);
				freeConfMap(map);
				return -1;
			}
		}else{
			perror("Erreur fatale 2 ");
			sdsfree(dirPath);
			return -1;
		}
	}else{
		map = read_config_file(&flag);
		if(verifMinConf(&map))mapModif = 1;
		if(flag != SUCCES){
			perror("Erreur fatale 3 ");
			sdsfree(dirPath);
			freeConfMap(map);
		}
	}
	fputs(".",stdout);
	
	DIR * dirBdd;
	sds chemin_bdd;
	
	unsigned char presence_key_chemin = 0;
	long pos = keyPosition(&map,"chemin_bdd");
	if(pos == -1){
		etape = MENU_DEMANDE_CHEMIN;
		chemin_bdd = sdsempty();
	}else{
		chemin_bdd = sdsdup(map.values->descripteurs[pos]);
		dirBdd = opendir(chemin_bdd);
		if(dirBdd == NULL){
			if(errno == ENOENT){
				etape = MENU_DEMANDE_CHEMIN;
			}else{
				perror("Erreur fatale 4 ");
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
			case MENU_DEMANDE_CHEMIN:
				puts("Entrer le chemin vers la base de données :");
				puts("(soit en relatif si l'execution se fait toujours depuis le même répertoire, soit en absolu.)");
				puts("(Rappel : sur WSL, les disques sont en /mnt/)");
				if(presence_key_chemin) puts("(entrer '0' retournera au menu de configuration)");
				scanf("%300s",buf);
				if(buf[0] == '0' && presence_key_chemin){
					puts("Annulation");
					etape = MENU_CONFIGURATION;
				}else{
					dirBdd = opendir(buf);
					if(dirBdd == NULL){
						if(errno != ENOENT){
							perror("Erreur fatale 5 ");
							running = 0;
						}else{
							printf("Répertoire non trouvé : %s\n",buf);
						}
					}else if(presence_key_chemin){
						sdsfree(chemin_bdd);
						chemin_bdd = sdsnew(buf);
						changeValue(&map,"chemin_bdd",buf);
						mapModif = 1;
						etape = MENU_PRINCIPAL;
					}else{
						sdsfree(chemin_bdd);
						chemin_bdd = sdsnew(buf);
						addValue(&map,"chemin_bdd",buf);
						mapModif = 1;
						presence_key_chemin = 1;
						etape = MENU_PRINCIPAL;
					}
				}
				break;
			case ETAPE_DEMARRAGE:
				etape = MENU_PRINCIPAL;//TODO
				break;
			case MENU_PRINCIPAL:
				puts("\nMENU PRINCIPAL");
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
					case '*': puts("Crédits : Loïc Bréard, Arthur France, Ludivine Albertus, Moufdi Nom trop long tu le tapera toi meme, Nicolas Boirel"); break;
				}
				break;
			case MENU_CONFIGURATION:
				puts("\nMENU DE CONFIGURATION");
				printf("Chemin BDD : %s\n",chemin_bdd);
				puts("1-Modifier le chemin vers la BDD");
				puts("2-Modifier les parametres image");
				puts("3-Modifier les parametres audio");
				puts("4-Modifier les parametres texte");
				puts("\n0-Retour");
				scanf("%1s",buf);
				switch(buf[0]){
					case '1': etape = MENU_DEMANDE_CHEMIN; break;
					case '2': etape = MENU_CONFIG_IMAGE; break;
					case '3': etape = MENU_CONFIG_AUDIO; break;
					case '4': etape = MENU_CONFIG_TEXTE; break;
					case '0': etape = MENU_PRINCIPAL; break;
				}
				break;
			case MENU_CONFIG_IMAGE:
				puts("\nMENU DE CONFIGURATION IMAGE");
				puts("Paramètres :");
				printf("1-Nombre de bits de quantification par couleur : %ld\n",getConfigValueLong(&map,"nb_bits_image",&flag));
				printf("2-Nombre de couleurs maximum mémorisées par image : %ld\n",getConfigValueLong(&map,"nb_couleurs_max_image",&flag));
				printf("3-Seuil minimal de considération d'une couleur (en %% de couverture de l'image) : %f\n",getConfigValueFloat(&map,"seuil_couleur_image",&flag));
				printf("4-Nombre de résultats de recherche : %ld\n",getConfigValueLong(&map,"nb_res_image",&flag));
				puts("\n0-Retour");
				scanf("%1s",buf);
				switch(buf[0]){
					case '1':{
						unsigned int val;
						do{
							puts("Entrer le nombre de bits de quantification (1-8) (0->Annuler):");
							puts("/!\\ Plus le nombre de bits est élevé, plus la recherche est précise, mais le temps de calcul augmente");
							scanf("%u",&val);
						}while(val > 8);
						if(val == 0)
							puts("Annulation");
						else{
							flag = changeValueLong(&map,"nb_bits_image",val);
							if(flag != SUCCES){
								puts("Echec modification");
							}else{
								mapModif = 1;
							}
						}
						break;
					}
					case '2':{
						unsigned int val;
						do{
							puts("Entrer le nombre de couleurs max considérées(1 - 200) (0->Annuler):");
							puts("/!\\ Plus le nombre de couleurs est élevé, plus la recherche est précise, mais le temps de calcul augmente");
							scanf("%u",&val);
						}while(val > 200);
						if(val == 0)
							puts("Annulation");
						else{
							flag = changeValueLong(&map,"nb_couleurs_max_image",val);
							if(flag != SUCCES){
								puts("Echec modification");
							}else{
								mapModif = 1;
							}
						}
						break;
					}
					case '3':{
						float val;
						do{
							puts("Entrer le seuil minimal de considération d'une couleur (0.0-100) (-1 ->Annuler):");
							puts("(Valeur en pourcentage de couverture de l'image)");
							scanf("%f",&val);
						}while((val > 100 || val < 0) && val != -1);
						if(val == -1)
							puts("Annulation");
						else{
							flag = changeValueFloat(&map,"seuil_couleur_image",val);
							if(flag != SUCCES){
								puts("Echec modification");
							}else{
								mapModif = 1;
							}
						}
						break;
					}
					case '4':{
						unsigned int val;
						do{
							puts("Entrer le nombre de résultats affichés lors de la recherche (1 - 20) (0->Annuler):");
							puts("(Un nombre de résultats important a plus tendance a faire ressortir des résultats non révélateurs)");
							scanf("%u",&val);
						}while(val > 20);
						if(val == 0)
							puts("Annulation");
						else{
							flag = changeValueLong(&map,"nb_res_image",val);
							if(flag != SUCCES){
								puts("Echec modification");
							}else{
								mapModif = 1;
							}
						}
						break;
					}
					case '0': etape = MENU_CONFIGURATION; break;
				}
				break;
			default:
				running = 0;
				puts("Fatal error : unknown state.");
				break;
		}
	}while(running);
	if(mapModif){
		flag = save_config_file(map);
		if(flag != SUCCES){
			perror("Erreur sauvegarde fichier config ");
		}
	}
	puts("A bientôt !");
	closedir(progDir);closedir(dirBdd);
	sdsfree(dirPath);
	sdsfree(chemin_bdd);
	freeConfMap(map);
}