#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <errno.h>
#include <assert.h>
#include "constantes.h"
#include "config_reader.h"
#include "indexation.h"
#include "recherche.h"

#include <sys/types.h>
#include <sys/stat.h>

enum Etape{
	MENU_DEMANDE_CHEMIN,
	MENU_DEMANDE_CHEMIN_TX,
	MENU_DEMANDE_CHEMIN_IM,
	MENU_DEMANDE_CHEMIN_AU,
	MENU_PRINCIPAL,
	MENU_RECHERCHE,
	MENU_CONFIGURATION,
	MENU_CONFIG_IMAGE,
	MENU_CONFIG_AUDIO,
	MENU_CONFIG_TEXTE,
	MENU_INDEXATION,
	MENU_REINITIALISATION
};

ConfMap defaultConfMap(){//valeurs par defaut
	unsigned char flag;
	ConfMap map = newConfMap(&flag);
	assert(flag != ECHEC);
	assert(addValueLong(&map,"nb_res_image",DEF_NB_RES_IMAGE) != ECHEC);
	assert(addValueLong(&map,"nb_bits_image",DEF_NB_BITS_IMAGE) != ECHEC);
	assert(addValueLong(&map,"nb_couleurs_max_image",DEF_NB_COULEURS_MAX_IMAGE) != ECHEC);
	assert(addValueFloat(&map,"seuil_couleur_image",DEF_SEUIL_COULEUR_IMAGE) != ECHEC);
	
	assert(addValueLong(&map,"nb_mots_max_texte",DEF_NB_MOTS_MAX_TEXTE) != ECHEC);
	assert(addValueLong(&map,"taille_min_mot",DEF_TAILLE_MIN_MOT) != ECHEC);
	assert(addValueLong(&map,"nb_res_texte",DEF_NB_RES_TEXTE) != ECHEC);
	
	assert(addValueLong(&map,"nb_echant_pfen",DEF_NB_ECHANT_PFEN) != ECHEC);
	assert(addValueLong(&map,"nb_inter_amp",DEF_NB_INTER_AMP) != ECHEC);
	assert(addValueLong(&map,"step_number",DEF_STEP_NUMBER) != ECHEC);
	
	return map;
}

unsigned char verifMinConf(ConfMap * map){
	unsigned char resp = 0;
	if(keyPosition(map,"nb_res_image") == -1){
		resp = 1;
		addValueLong(map,"nb_res_image",DEF_NB_RES_IMAGE);
	}
	if(keyPosition(map,"nb_bits_image") == -1){
		resp = 1;
		addValueLong(map,"nb_bits_image",DEF_NB_BITS_IMAGE);
	}
	if(keyPosition(map,"nb_couleurs_max_image") == -1){
		resp = 1;
		addValueLong(map,"nb_couleurs_max_image",DEF_NB_COULEURS_MAX_IMAGE);
	}
	if(keyPosition(map,"seuil_couleur_image") == -1){
		resp = 1;
		addValueFloat(map,"seuil_couleur_image",DEF_SEUIL_COULEUR_IMAGE);
	}
	if(keyPosition(map,"nb_mots_max_texte") == -1){
		resp = 1;
		addValueLong(map,"nb_mots_max_texte",DEF_NB_MOTS_MAX_TEXTE);
	}
	if(keyPosition(map,"taille_min_mot") == -1){
		resp = 1;
		addValueLong(map,"taille_min_mot",DEF_TAILLE_MIN_MOT);
	}
	if(keyPosition(map,"nb_res_texte") == -1){
		resp = 1;
		addValueLong(map,"nb_res_texte",DEF_NB_RES_TEXTE);
	}
	if(keyPosition(map,"nb_echant_pfen") == -1){
		resp = 1;
		addValueLong(map,"nb_echant_pfen",DEF_NB_ECHANT_PFEN);
	}
	if(keyPosition(map,"nb_inter_amp") == -1){
		resp = 1;
		addValueLong(map,"nb_inter_amp",DEF_NB_INTER_AMP);
	}
	if(keyPosition(map,"step_number") == -1){
		resp = 1;
		addValueLong(map,"step_number",DEF_STEP_NUMBER);
	}
	return resp;
}

unsigned char recherche_texte_en(ConfMap * map){
	unsigned char flag = 0;
	if(getConfigValueLong(map,"index_texte_valide",&flag) != 1)
		return 0;
	return 1;
}

unsigned char recherche_image_en(ConfMap * map){
	unsigned char flag = 0;
	if(getConfigValueLong(map,"index_image_valide",&flag) != 1)
		return 0;
	return 1;
}

unsigned char recherche_audio_en(ConfMap * map){
	unsigned char flag = 0;
	if(getConfigValueLong(map,"index_audio_valide",&flag) != 1)
		return 0;
	return 1;
}

void indexation_texte_set(ConfMap * map){
	if(keyPosition(map,"index_texte_valide") != -1)
		changeValueLong(map,"index_texte_valide",1);
	else
		addValueLong(map,"index_texte_valide",1);
}

void indexation_image_set(ConfMap * map){
	if(keyPosition(map,"index_image_valide") != -1)
		changeValueLong(map,"index_image_valide",1);
	else
		addValueLong(map,"index_image_valide",1);
}

void indexation_audio_set(ConfMap * map){
	if(keyPosition(map,"index_audio_valide") != -1)
		changeValueLong(map,"index_audio_valide",1);
	else
		addValueLong(map,"index_audio_valide",1);
}

void indexation_texte_unset(ConfMap * map){
	if(keyPosition(map,"index_texte_valide") != -1)
		changeValueLong(map,"index_texte_valide",0);
}

void indexation_image_unset(ConfMap * map){
	if(keyPosition(map,"index_image_valide") != -1)
		changeValueLong(map,"index_image_valide",0);
}

void indexation_audio_unset(ConfMap * map){
	if(keyPosition(map,"index_audio_valide") != -1)
		changeValueLong(map,"index_audio_valide",0);
}

void indexation_auto(const char * descPath,unsigned char tx,unsigned char im,unsigned char au,ConfMap * map){
	if(tx == 0){
		indexer_texte(descPath,map);
		indexation_texte_set(map);
	}
	if(im == 0){
		indexer_image(descPath,map);
		indexation_image_set(map);
	}
	if(au == 0){
		indexer_audio(descPath,map);
		indexation_audio_set(map);
	}
}

int main(){
	enum Etape etape = MENU_PRINCIPAL;
	unsigned char flag;
	unsigned char running = 1,reinit = 0;
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
		verifMinConf(&map);
		if(flag != SUCCES){
			perror("Erreur fatale 3 ");
			sdsfree(dirPath);
			freeConfMap(map);
		}
	}
	fputs(".",stdout);
	
	//DIR * dirBdd;
	DIR * dirBddTexte = NULL;
	DIR * dirBddImage = NULL;
	DIR * dirBddAudio = NULL;
	//sds chemin_bdd;
	sds chemin_bdd_tx,chemin_bdd_im,chemin_bdd_au;
	
	unsigned char presence_key_chemin_tx = 0;
	long pos = keyPosition(&map,"chemin_bdd_tx");
	if(pos == -1){
		etape = MENU_DEMANDE_CHEMIN;
		chemin_bdd_tx = sdsempty();
	}else{
		chemin_bdd_tx = sdsdup(map.values->descripteurs[pos]);
		dirBddTexte = opendir(chemin_bdd_tx);
		if(dirBddTexte == NULL){
			if(errno == ENOENT){
				etape = MENU_DEMANDE_CHEMIN;
			}else{
				perror("Erreur fatale 4 ");
				sdsfree(dirPath);
				freeConfMap(map);
				return -1;
			}
		}else{
			presence_key_chemin_tx = 1;
		}
	}
	
	unsigned char presence_key_chemin_im = 0;
	pos = keyPosition(&map,"chemin_bdd_im");
	if(pos == -1){
		etape = MENU_DEMANDE_CHEMIN;
		chemin_bdd_im = sdsempty();
	}else{
		chemin_bdd_im = sdsdup(map.values->descripteurs[pos]);
		dirBddImage = opendir(chemin_bdd_im);
		if(dirBddImage == NULL){
			if(errno == ENOENT){
				etape = MENU_DEMANDE_CHEMIN;
			}else{
				perror("Erreur fatale 4 ");
				sdsfree(dirPath);
				freeConfMap(map);
				return -1;
			}
		}else{
			presence_key_chemin_im = 1;
		}
	}
	
	unsigned char presence_key_chemin_au = 0;
	pos = keyPosition(&map,"chemin_bdd_au");
	if(pos == -1){
		etape = MENU_DEMANDE_CHEMIN;
		chemin_bdd_au = sdsempty();
	}else{
		chemin_bdd_au = sdsdup(map.values->descripteurs[pos]);
		dirBddAudio = opendir(chemin_bdd_au);
		if(dirBddAudio == NULL){
			if(errno == ENOENT){
				etape = MENU_DEMANDE_CHEMIN;
			}else{
				perror("Erreur fatale 4 ");
				sdsfree(dirPath);
				freeConfMap(map);
				return -1;
			}
		}else{
			presence_key_chemin_au = 1;
		}
	}
	puts(".");
	char buf[300];
	
	//on teste si les indexations sont valides
	unsigned char rech_tx_en,rech_im_en,rech_au_en;
	rech_tx_en = recherche_texte_en(&map);
	rech_im_en = recherche_image_en(&map);
	rech_au_en = recherche_audio_en(&map);
	
	do{
		switch(etape){
			case MENU_DEMANDE_CHEMIN:
				if(!presence_key_chemin_tx) etape = MENU_DEMANDE_CHEMIN_TX;
				else if(!presence_key_chemin_im) etape = MENU_DEMANDE_CHEMIN_IM;
				else if(!presence_key_chemin_au) etape = MENU_DEMANDE_CHEMIN_AU;
				else{
					puts("\nMENU CHANGEMENT CHEMIN");
					printf("1-Textes : %s\n",chemin_bdd_tx);
					printf("2-Images : %s\n",chemin_bdd_im);
					printf("3-Audio  : %s\n",chemin_bdd_au);
					puts("\n0-Retour");
					scanf("%1s",buf);
					switch(buf[0]){
						case '0': etape = MENU_CONFIGURATION; break;
						case '1': etape = MENU_DEMANDE_CHEMIN_TX; break;
						case '2': etape = MENU_DEMANDE_CHEMIN_IM; break;
						case '3': etape = MENU_DEMANDE_CHEMIN_AU; break;
					}
				}
				break;
			case MENU_DEMANDE_CHEMIN_TX:
				puts("Entrer le chemin vers la base de données de textes:");
				puts("(soit en relatif si l'execution se fait toujours depuis le même répertoire, soit en absolu.)");
				puts("(Rappel : sur WSL, les disques sont montés en /mnt/)");
				if(presence_key_chemin_tx) puts("(entrer '0' pour annuler)");
				scanf("%300s",buf);
				if(buf[0] == '0' && presence_key_chemin_tx){
					puts("Annulation");
					etape = MENU_DEMANDE_CHEMIN;
				}else{
					if(dirBddTexte != NULL) closedir(dirBddTexte);
					dirBddTexte = opendir(buf);
					if(dirBddTexte == NULL){
						if(errno != ENOENT){
							perror("Erreur fatale 5 ");
							running = 0;
						}else{
							printf("Répertoire non trouvé : %s\n",buf);
						}
					}else if(presence_key_chemin_tx){
						sdsfree(chemin_bdd_tx);
						chemin_bdd_tx = sdsnew(buf);
						changeValue(&map,"chemin_bdd_tx",buf);
						indexation_texte_unset(&map);
						rech_tx_en = 0;
						etape = MENU_DEMANDE_CHEMIN;
					}else{
						sdsfree(chemin_bdd_tx);
						chemin_bdd_tx = sdsnew(buf);
						addValue(&map,"chemin_bdd_tx",buf);
						indexation_texte_unset(&map);
						rech_tx_en = 0;
						presence_key_chemin_tx = 1;
						etape = MENU_DEMANDE_CHEMIN;
					}
				}
				break;
			case MENU_DEMANDE_CHEMIN_IM:
				puts("Entrer le chemin vers la base de données d'images:");
				puts("(soit en relatif si l'execution se fait toujours depuis le même répertoire, soit en absolu.)");
				puts("(Rappel : sur WSL, les disques sont montés en /mnt/)");
				if(presence_key_chemin_im) puts("(entrer '0' pour annuler)");
				scanf("%300s",buf);
				if(buf[0] == '0' && presence_key_chemin_im){
					puts("Annulation");
					etape = MENU_DEMANDE_CHEMIN;
				}else{
					if(dirBddImage != NULL) closedir(dirBddImage);
					dirBddImage = opendir(buf);
					if(dirBddImage == NULL){
						if(errno != ENOENT){
							perror("Erreur fatale 5 ");
							running = 0;
						}else{
							printf("Répertoire non trouvé : %s\n",buf);
						}
					}else if(presence_key_chemin_im){
						sdsfree(chemin_bdd_im);
						chemin_bdd_im = sdsnew(buf);
						changeValue(&map,"chemin_bdd_im",buf);
						indexation_image_unset(&map);
						rech_im_en = 0;
						etape = MENU_DEMANDE_CHEMIN;
					}else{
						sdsfree(chemin_bdd_im);
						chemin_bdd_im = sdsnew(buf);
						addValue(&map,"chemin_bdd_im",buf);
						indexation_image_unset(&map);
						rech_im_en = 0;
						presence_key_chemin_im = 1;
						etape = MENU_DEMANDE_CHEMIN;
					}
				}
				break;
			case MENU_DEMANDE_CHEMIN_AU:
				puts("Entrer le chemin vers la base de données audio:");
				puts("(soit en relatif si l'execution se fait toujours depuis le même répertoire, soit en absolu.)");
				puts("(Rappel : sur WSL, les disques sont montés en /mnt/)");
				if(presence_key_chemin_au) puts("(entrer '0' pour annuler)");
				scanf("%300s",buf);
				if(buf[0] == '0' && presence_key_chemin_au){
					puts("Annulation");
					etape = MENU_DEMANDE_CHEMIN;
				}else{
					if(dirBddAudio != NULL) closedir(dirBddAudio);
					dirBddAudio = opendir(buf);
					if(dirBddAudio == NULL){
						if(errno != ENOENT){
							perror("Erreur fatale 5 ");
							running = 0;
						}else{
							printf("Répertoire non trouvé : %s\n",buf);
						}
					}else if(presence_key_chemin_au){
						sdsfree(chemin_bdd_au);
						chemin_bdd_au = sdsnew(buf);
						changeValue(&map,"chemin_bdd_au",buf);
						indexation_audio_unset(&map);
						rech_au_en = 0;
						etape = MENU_DEMANDE_CHEMIN;
					}else{
						sdsfree(chemin_bdd_au);
						chemin_bdd_au = sdsnew(buf);
						addValue(&map,"chemin_bdd_au",buf);
						indexation_audio_unset(&map);
						rech_au_en = 0;
						presence_key_chemin_au = 1;
						etape = MENU_DEMANDE_CHEMIN;
					}
				}
				break;
			case MENU_PRINCIPAL:
				puts("\nMENU PRINCIPAL");
				if(rech_tx_en || rech_im_en || rech_au_en)
					puts("1-Recherche");
				else
					puts("X-Recherche (Indexation nécessaire)");
				puts("2-Configuration");
				puts("3-Indexation");
				puts("\n0-Quitter");
				scanf("%1s",buf);
				switch(buf[0]){
					case '1':
						if(rech_tx_en || rech_im_en || rech_au_en)
							etape = MENU_RECHERCHE;
						break;
					case '2': etape = MENU_CONFIGURATION; break;
					case '3': etape = MENU_INDEXATION; break;
					case '0': running = 0; break;
					case '*': puts("Crédits : Loïc Bréard, Arthur France, Ludivine Albertus, Moufdi Oulad hadj messaoud, Nicolas Boirel"); break;
				}
				break;
			case MENU_INDEXATION:
				puts("\nMENU INDEXATION");
				puts("1-Tout indexer");
				puts("2-Indexation texte");
				puts("3-Indexation image");
				puts("4-Indexation audio");
				puts("\n0-Retour");
				scanf("%1s",buf);
				switch(buf[0]){
					case '0': etape = MENU_PRINCIPAL; break;
					case '1':
						indexer_texte(chemin_bdd_tx,&map);
						indexer_image(chemin_bdd_im,&map);
						indexer_audio(chemin_bdd_au,&map);
						indexation_texte_set(&map);
						rech_tx_en = 1;
						indexation_image_set(&map);
						rech_im_en = 1;
						indexation_audio_set(&map);
						rech_au_en = 1;
						break;
					case '2':
						indexer_texte(chemin_bdd_tx,&map);
						indexation_texte_set(&map);
						rech_tx_en = 1;
						break;
					case '3':
						indexer_image(chemin_bdd_im,&map);
						indexation_image_set(&map);
						rech_im_en = 1;
						break;
					case '4':
						indexer_audio(chemin_bdd_au,&map);
						indexation_audio_set(&map);
						rech_au_en = 1;
						break;
				}
				break;
			case MENU_RECHERCHE:
				puts("\nMENU RECHERCHE");
				if(rech_tx_en){
					puts("1-Recherche de textes par mot-clé");
					puts("2-Recherche de textes par texte de référence");
				}else{
					puts("X-Recherche de textes par mot-clé            (indexation nécéssaire)");
					puts("X-Recherche de textes par texte de référence (indexation nécéssaire)");
				}
				if(rech_im_en){
					puts("3-Recherche d'images par code couleur");
					puts("4-Recherche d'images par nom de couleur");
					puts("5-Recherche d'images par image de référence");
				}else{
					puts("X-Recherche d'images par code couleur        (indexation nécéssaire)");
					puts("X-Recherche d'images par nom de couleur      (indexation nécéssaire)");
					puts("X-Recherche d'images par image de référence  (indexation nécéssaire)");
				}
				if(rech_au_en){
					puts("6-Recherche de fichiers audio à partir d'un jingle");
				}else{
					puts("X-Recherche de fichiers audio à partir d'un jingle (indexation nécéssaire)");
				}
				puts("\n0-Retour");
				scanf("%1s",buf);
				switch(buf[0]){
					case '0': etape = MENU_PRINCIPAL; break;
					case '1': if(rech_tx_en) recherche_texte_mot(&map); break;
					case '2': if(rech_tx_en) recherche_texte_pfichier(&map); break;
					case '3': if(rech_im_en) recherche_image_code(&map); break;
					case '4': if(rech_im_en) recherche_image_nom(&map); break;
					case '5': if(rech_im_en) recherche_image_fichier(&map); break;
					case '6': if(rech_au_en) rechercher_audio(&map); break;
				}
				break;
			case MENU_CONFIGURATION:
				puts("\nMENU DE CONFIGURATION");
				puts("1-Modifier les chemins vers les BDD");
				puts("2-Modifier les parametres texte");
				puts("3-Modifier les parametres image");
				puts("4-Modifier les parametres audio");
				if(!rech_tx_en || !rech_im_en || !rech_au_en)
					puts("\n0-Indexation et Retour");
				else
					puts("\n0-Retour");
				scanf("%1s",buf);
				switch(buf[0]){
					case '1': etape = MENU_DEMANDE_CHEMIN; break;
					case '2': etape = MENU_CONFIG_TEXTE; break;
					case '3': etape = MENU_CONFIG_IMAGE; break;
					case '4': etape = MENU_CONFIG_AUDIO; break;
					case '0':
						etape = MENU_PRINCIPAL;
						if(!rech_tx_en || !rech_im_en || !rech_au_en){
							indexation_auto(dirPath,rech_tx_en,rech_im_en,rech_au_en,&map);
							rech_tx_en = 1;
							rech_im_en = 1;
							rech_au_en = 1;
						}
						break;
					case '=': etape = MENU_REINITIALISATION; break;
				}
				break;
			case MENU_CONFIG_TEXTE:
				puts("\nMENU DE CONFIGURATION TEXTE");
				puts("Paramètres :");
				printf("1-Nombre de mots maximum retenus par fichier: %ld\n",getConfigValueLong(&map,"nb_mots_max_texte",&flag));
				printf("2-Taille minimale des mots retenus : %ld\n",getConfigValueLong(&map,"taille_min_mot",&flag));
				printf("3-Nombre de résultats de recherche : %ld\n",getConfigValueLong(&map,"nb_res_texte",&flag));
				puts("\n0-Retour");
				scanf("%1s",buf);
				switch(buf[0]){
					case '1':{
						unsigned int val;
						puts("Entrer le nombre maximum de mots par fichier (0->Annuler):");
						scanf("%u",&val);
						if(val == 0)
							puts("Annulation");
						else{
							flag = changeValueLong(&map,"nb_mots_max_texte",val);
							rech_tx_en = 0;
							indexation_texte_unset(&map);
							if(flag != SUCCES)
								puts("Echec modification");
						}
						break;
					}
					case '2':{
						unsigned int val;
						puts("Entrer la taille minimale des mots (0->Annuler):");
						scanf("%u",&val);
						if(val == 0)
							puts("Annulation");
						else{
							flag = changeValueLong(&map,"taille_min_mot",val);
							rech_tx_en = 0;
							indexation_texte_unset(&map);
							if(flag != SUCCES)
								puts("Echec modification");
						}
						break;
					}
					case '3':{
						unsigned int val;
						puts("Entrer le nombre de résultats affichés lors de la recherche (1 - 20) (0->Annuler):");
						puts("(Un nombre de résultats important a plus tendance a faire ressortir des résultats non révélateurs)");
						scanf("%u",&val);
						if(val == 0)
							puts("Annulation");
						else{
							flag = changeValueLong(&map,"nb_res_texte",val);
							rech_tx_en = 0;
							indexation_texte_unset(&map);
							if(flag != SUCCES)
								puts("Echec modification");
						}
						break;
					}
					case '0': etape = MENU_CONFIGURATION; break;
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
							rech_im_en = 0;
							indexation_image_unset(&map);
							if(flag != SUCCES)
								puts("Echec modification");
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
							rech_im_en = 0;
							indexation_image_unset(&map);
							if(flag != SUCCES)
								puts("Echec modification");
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
							rech_im_en = 0;
							indexation_image_unset(&map);
							if(flag != SUCCES)
								puts("Echec modification");
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
							rech_im_en = 0;
							indexation_image_unset(&map);
							if(flag != SUCCES)
								puts("Echec modification");
						}
						break;
					}
					case '0': etape = MENU_CONFIGURATION; break;
				}
				break;
			case MENU_CONFIG_AUDIO:
				puts("\nMENU DE CONFIGURATION AUDIO");
				puts("Paramètres :");
				printf("1-Nombre d'échantillons par fenêtre : %ld\n",getConfigValueLong(&map,"nb_echant_pfen",&flag));
				printf("2-Nombre d'intervalles en amplitude : %ld\n",getConfigValueLong(&map,"nb_inter_amp",&flag));
				printf("3-Nombre de fenêtres de décalage entre mesure : %ld\n",getConfigValueLong(&map,"step_number",&flag));
				puts("\n0-Retour");
				scanf("%1s",buf);
				switch(buf[0]){
					case '1':{
						unsigned int val;
						puts("Entrer le nombre d'échantillons par fenêtre (0->Annuler):");
						scanf("%u",&val);
						if(val == 0)
							puts("Annulation");
						else{
							flag = changeValueLong(&map,"nb_echant_pfen",val);
							rech_au_en = 0;
							indexation_audio_unset(&map);
							if(flag != SUCCES)
								puts("Echec modification");
						}
						break;
					}
					case '2':{
						unsigned int val;
						puts("Entrer le nombre d'intervalles en amplitude (0->Annuler):");
						scanf("%u",&val);
						if(val == 0)
							puts("Annulation");
						else{
							flag = changeValueLong(&map,"nb_inter_amp",val);
							rech_au_en = 0;
							indexation_audio_unset(&map);
							if(flag != SUCCES)
								puts("Echec modification");
						}
						break;
					}
					case '3':{
						unsigned int val;
						puts("Entrer le nombre de fenêtres de décalage entre mesure (0->Annuler):");
						puts("(Un nombre élevé accélère la recherche mais diminue la précision des résultats)");
						scanf("%u",&val);
						if(val == 0)
							puts("Annulation");
						else{
							flag = changeValueLong(&map,"step_number",val);
							rech_au_en = 0;
							indexation_audio_unset(&map);
							if(flag != SUCCES)
								puts("Echec modification");
						}
						break;
					}
					case '0': etape = MENU_CONFIGURATION; break;
				}
				break;
			case MENU_REINITIALISATION:
				puts("\nREINITIALISATION");
				puts("Toutes les données générées par le logiciel vont être supprimmées.");
				puts("Êtes-vous sûr ? Y/n");
				scanf("%1s",buf);
				if(buf[0] == 'Y'){
					sds cmd = sdscat(sdsnew("rm -r "),dirPath);
					system(cmd);
					//printf("Commande system : %s\n",cmd);
					sdsfree(cmd);
					running = 0;
					reinit = 1;
				}else
					etape = MENU_CONFIGURATION;
				break;
			default:
				running = 0;
				puts("Fatal error : unknown state.");
				break;
		}
	}while(running);
	if(!reinit){
		flag = save_config_file(map);
		if(flag != SUCCES){
			perror("Erreur sauvegarde fichier config ");
		}
	}
	puts("A bientôt !");
	closedir(progDir);closedir(dirBddTexte);closedir(dirBddImage);closedir(dirBddAudio);
	sdsfree(dirPath);
	sdsfree(chemin_bdd_tx);sdsfree(chemin_bdd_im);sdsfree(chemin_bdd_au);
	freeConfMap(map);
}