#include "recherche.h"
#include "recherche_texte.h"
#include "recherche_image.h"
#include "recherche_audio.h"
#include "sauvegarde_descripteurs.h"
#include "constantes.h"

#include <stdio.h>
#include <string.h>
#include <assert.h>

sds getDirPath(){
	return sdscat(sdscat(sdsnew(getenv("HOME")),"/"),STORAGE_FOLDER_NAME);
}

void fin_rech_texte(sds * resultats,unsigned int nb_resultats){
	for(unsigned int i = 0;i < nb_resultats && resultats[i] != NULL;i++){
		printf("%u\t%s\n",i+1,resultats[i]);
	}
	//TODO permettre l'affichage
}

void recherche_texte_mot(ConfMap * map){
	unsigned char flag;
	sds dirPath = sdscat(getDirPath(),"/");
	sds temp = sdscat(sdsdup(dirPath),NOM_FICH_MAP_MOTS);
	Capsule base_mots = loadDescripteurs(&flag,temp);
	sdsfree(temp);
	temp = sdscat(sdsdup(dirPath),NOM_FICH_MAP_NOM_TEXT);
	Capsule mapNoms = loadDescripteurs(&flag,temp);
	sdsfree(temp);
	sdsfree(dirPath);
	
	unsigned int nb_res_max = getConfigValueLong(map,"nb_res_texte",&flag);
	if(flag != SUCCES){
		puts("Erreur parametre");
		assert(flag != ECHEC);
	}
	
	fputs("\nEntrer le(s) mot(s) à rechercher :",stdout);
	char buf[300];
	scanf("%298s",buf);
	buf[strlen(buf)] = ' ';
	
	sds * resultats = malloc(sizeof(sds*)*nb_res_max);
	assert(resultats != NULL);
	for(unsigned int i = 0;i < nb_res_max;i++){
		resultats[i] = NULL;
	}
	recherche_texte_motscles(buf, mapNoms, base_mots, nb_res_max, resultats);
	
	// traitement du resultat
	fin_rech_texte(resultats,nb_res_max);
	
	for(int i = 0; i < nb_res_max; i++)
	{
		sdsfree(resultats[i]);
	}
	free(resultats);
	freeCapsule(base_mots);
	freeCapsule(mapNoms);
}

void recherche_texte_pfichier(ConfMap * map){
	unsigned char flag;
	sds dirPath = sdscat(getDirPath(),"/");
	sds temp = sdscat(sdsdup(dirPath),NOM_FICH_MAP_MOTS);
	Capsule base_mots = loadDescripteurs(&flag,temp);
	sdsfree(temp);
	temp = sdscat(sdsdup(dirPath),NOM_FICH_MAP_NOM_TEXT);
	Capsule mapNoms = loadDescripteurs(&flag,temp);
	sdsfree(temp);
	sdsfree(dirPath);
	
	unsigned int nb_res_max = getConfigValueLong(map,"nb_res_texte",&flag);
	if(flag != SUCCES){
		puts("Erreur parametre");
		assert(flag != ECHEC);
	}
	
	unsigned int taille_min_mot = getConfigValueLong(map,"taille_min_mot",&flag);
	if(flag != SUCCES){
		puts("Erreur parametre");
		assert(flag != ECHEC);
	}
	
	unsigned int nb_mots_max = getConfigValueLong(map,"nb_mots_max_texte",&flag);
	if(flag != SUCCES){
		puts("Erreur parametre");
		assert(flag != ECHEC);
	}
	
	fputs("\nEntrer l'adresse du fichier à rechercher :",stdout);
	char buf[300];
	scanf("%300s",buf);
	
	sds * resultats = malloc(sizeof(sds*)*nb_res_max);
	assert(resultats != NULL);
	for(unsigned int i = 0;i < nb_res_max;i++){
		resultats[i] = NULL;
	}
	sds descripteur = indexation_texte(buf, 0, nb_mots_max, taille_min_mot);
	recherche_texte_fichier(descripteur, mapNoms, base_mots, nb_res_max, resultats);
	sdsfree(descripteur);
	
	fin_rech_texte(resultats,nb_res_max);
	
	for(int i = 0; i < nb_res_max; i++)
	{
		sdsfree(resultats[i]);
	}
	free(resultats);
	freeCapsule(base_mots);
	freeCapsule(mapNoms);
}

void fin_rech_image(sds * res){
	unsigned int i = 0;
	while(res[i] != NULL){
		printf("%u\t%s\n",i+1,res[i]);
		i++;
	}
	/*puts("\nPour ouvrir une image, entrer son numéro. 0 pour quitter.");
	unsigned int resNum;
	scanf("%u",&resNum);
	if(resNum != 0 && resNum < i){
		puts("ENCORE A FAIRE !!!!!!!");//TODO ouvrir image
	}*/
}

void recherche_image_nom(ConfMap * map){
	unsigned char flag;
	unsigned int nbResMax = (unsigned int)getConfigValueLong(map,"nb_res_image",&flag);
	if(flag != SUCCES){
		puts("Erreur parametre");
		return;
	}
	unsigned int nbBits = (unsigned int)getConfigValueLong(map,"nb_bits_image",&flag);
	if(flag != SUCCES){
		puts("Erreur parametre");
		return;
	}
	sds dirPath = sdscat(sdscat(getDirPath(),"/"),NOM_FICH_DESC_IMG);
	Capsule base = loadDescripteurs(&flag,dirPath);
	if(flag != SUCCES){
		printf("Echec ouverture base descripteurs : %s\n",dirPath);
		sdsfree(dirPath);
		assert(flag != ECHEC);
	}
	sdsfree(dirPath);
	//printf("Nombre de descripteurs : %u\n",base.nbDescripteurs);
	puts("Choisissez une couleur :");
	puts("1-noir     2-blanc");
	puts("3-rouge    4-vert");
	puts("5-bleu     6-cyan");
	puts("7-magenta  8-jaune");
	char buf[3];
	scanf("%1s",buf);
	sds * reponse;
	switch(buf[0]){
		case '1': reponse = recherche_image_col(NOIR_T,base,nbResMax,nbBits); break;
		case '2': reponse = recherche_image_col(BLANC_T,base,nbResMax,nbBits); break;
		case '3': reponse = recherche_image_col(ROUGE_T,base,nbResMax,nbBits); break;
		case '4': reponse = recherche_image_col(VERT_T,base,nbResMax,nbBits); break;
		case '5': reponse = recherche_image_col(BLEU_T,base,nbResMax,nbBits); break;
		case '6': reponse = recherche_image_col(CYAN_T,base,nbResMax,nbBits); break;
		case '7': reponse = recherche_image_col(MAGENTA_T,base,nbResMax,nbBits); break;
		case '8': reponse = recherche_image_col(JAUNE_T,base,nbResMax,nbBits); break;
		default:
			puts("Erreur entrée utilisateur");
			break;
	}
	freeCapsule(base);
	fin_rech_image(reponse);
	unsigned int i = 0;
	while(reponse[i] != NULL){
		sdsfree(reponse[i]);
		i++;
	}
	free(reponse);
}

void recherche_image_code(ConfMap * map){
	unsigned char flag;
	unsigned int nbResMax = (unsigned int)getConfigValueLong(map,"nb_res_image",&flag);
	if(flag != SUCCES){
		puts("Erreur parametre");
		return;
	}
	unsigned int nbBits = (unsigned int)getConfigValueLong(map,"nb_bits_image",&flag);
	if(flag != SUCCES){
		puts("Erreur parametre");
		return;
	}
	sds dirPath = sdscat(sdscat(getDirPath(),"/"),NOM_FICH_DESC_IMG);
	Capsule base = loadDescripteurs(&flag,dirPath);
	if(flag != SUCCES){
		printf("Echec ouverture base descripteurs : %s\n",dirPath);
		sdsfree(dirPath);
		assert(flag != ECHEC);
	}
	sdsfree(dirPath);
	fputs("Entrer la couleur en Hexadécimal sur 24 bits (RVB) : ",stdout);
	unsigned int color;
	scanf("%6X",&color);
	sds * reponse;
	
	reponse = recherche_image(color,base,nbResMax,nbBits);
	
	freeCapsule(base);
	fin_rech_image(reponse);
	unsigned int i = 0;
	while(reponse[i] != NULL){
		sdsfree(reponse[i]);
		i++;
	}
	free(reponse);
}

void recherche_image_fichier(ConfMap * map){
	unsigned char flag;
	unsigned int nbResMax = (unsigned int)getConfigValueLong(map,"nb_res_image",&flag);
	if(flag != SUCCES){
		puts("Erreur parametre");
		return;
	}
	unsigned int nbBits = (unsigned int)getConfigValueLong(map,"nb_bits_image",&flag);
	if(flag != SUCCES){
		puts("Erreur parametre");
		return;
	}
	unsigned int nbCouleursMax = (unsigned int)getConfigValueLong(map,"nb_couleurs_max_image",&flag);
	if(flag != SUCCES){
		puts("Erreur parametre");
		return;
	}
	float seuil = getConfigValueFloat(map,"seuil_couleur_image",&flag);
	if(flag != SUCCES){
		puts("Erreur parametre");
		return;
	}
	sds dirPath = sdscat(sdscat(getDirPath(),"/"),NOM_FICH_DESC_IMG);
	Capsule base = loadDescripteurs(&flag,dirPath);
	if(flag != SUCCES){
		printf("Echec ouverture base descripteurs : %s\n",dirPath);
		sdsfree(dirPath);
		assert(flag != ECHEC);
	}
	sdsfree(dirPath);
	fputs("Entrer le chemin (absolu ou relatif à l'éxecution) de l'image a rechercher (.txt):",stdout);
	char buf[300];
	scanf("%300s",buf);
	sds * reponse;
	
	reponse = recherche_image_file(buf,base,nbResMax,nbBits,nbCouleursMax,seuil);
	
	freeCapsule(base);
	fin_rech_image(reponse);
	unsigned int i = 0;
	while(reponse[i] != NULL){
		sdsfree(reponse[i]);
		i++;
	}
	free(reponse);
}

void rechercher_audio(ConfMap * map){
	unsigned char flag;
	unsigned int nb_echant_pFen = (unsigned int)getConfigValueLong(map,"nb_echant_pfen",&flag);
	if(flag != SUCCES){
		puts("Erreur parametre");
		return;
	}
	unsigned int nb_int_amp = (unsigned int)getConfigValueLong(map,"nb_inter_amp",&flag);
	if(flag != SUCCES){
		puts("Erreur parametre");
		return;
	}
	unsigned int step_number = (unsigned int)getConfigValueLong(map,"step_number",&flag);
	if(flag != SUCCES){
		puts("Erreur parametre");
		return;
	}
	sds dirPath = sdscat(sdscat(getDirPath(),"/"),NOM_FICH_DESC_AUD);
	Capsule base = loadDescripteurs(&flag,dirPath);
	if(flag != SUCCES){
		printf("Echec ouverture base descripteurs : %s\n",dirPath);
		sdsfree(dirPath);
		assert(flag != ECHEC);
	}
	sdsfree(dirPath);

	// TODO: Get chemin fichier (non, le fichier n'est pas le jingle predefini, il doit pouvoir etre choisi)
	sds chemin_fichier = sdsempty();
	
	RESULT_RECHERCHE_AUDIO* resultats = recherche_audio(chemin_fichier, base, step_number, nb_echant_pFen, nb_int_amp);

    RESULT_RECHERCHE_AUDIO* ptr = resultats;
    while(ptr != NULL) {
        printf("%s : %fs (%d)\n", ptr->filename, ptr->match_time, ptr->score);
        ptr = ptr->next;
    }

    free_results_audio(resultats);

	sdsfree(chemin_fichier);
	
	freeCapsule(base);
}