#include "recherche.h"
#include "recherche_texte.h"
#include "recherche_image.h"
#include "recherche_audio.h"
#include "sauvegarde_descripteurs.h"
#include "constantes.h"

#include <stdio.h>
#include <string.h>

void recherche_texte_mot(ConfMap * map){
	unsigned char flag;
	Capsule base = loadDescripteurs(&flag,NOM_FICH_DESC_TEXT);
	fputs("\nEntrer le(s) mot(s) à rechercher :",stdout);
	char buf[300];
	scanf("%298s",buf);
	buf[strlen(buf)] = ' ';
	//TODO
	
	freeCapsule(base);
}

void recherche_texte_pfichier(ConfMap * map){
	unsigned char flag;//TODO
}

void fin_rech_image(sds * res){
	unsigned int i = 0;
	while(res[i] != NULL){
		printf("%u\t%s\n",i+1,res[i]);
		i++;
	}
	puts("\nPour ouvrir une image, entrer son numéro. 0 pour quitter.");
	unsigned int resNum;
	scanf("%u",&resNum);
	if(resNum != 0 && resNum < i){
		//TODO ouvrir image
	}
}

void recherche_image_nom(ConfMap * map){
	unsigned char flag;
	unsigned int nbResMax = (unsigned int)getConfigValueLong(map,"nb_res_image",&flag);
	if(flag != SUCCES){
		puts("Erreur parametre");
		return;
	}
	unsigned char nbBits = (unsigned int)getConfigValueLong(map,"nb_bits_image",&flag);
	if(flag != SUCCES){
		puts("Erreur parametre");
		return;
	}
	Capsule base = loadDescripteurs(&flag,NOM_FICH_DESC_IMG);
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
	unsigned char nbBits = (unsigned int)getConfigValueLong(map,"nb_bits_image",&flag);
	if(flag != SUCCES){
		puts("Erreur parametre");
		return;
	}
	Capsule base = loadDescripteurs(&flag,NOM_FICH_DESC_IMG);
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
	unsigned char nbBits = (unsigned int)getConfigValueLong(map,"nb_bits_image",&flag);
	if(flag != SUCCES){
		puts("Erreur parametre");
		return;
	}
	unsigned char nbCouleursMax = (unsigned int)getConfigValueLong(map,"nb_couleurs_max_image",&flag);
	if(flag != SUCCES){
		puts("Erreur parametre");
		return;
	}
	float seuil = getConfigValueFloat(map,"seuil_couleur_image",&flag);
	if(flag != SUCCES){
		puts("Erreur parametre");
		return;
	}
	Capsule base = loadDescripteurs(&flag,NOM_FICH_DESC_IMG);
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

void recherche_audio(ConfMap * map){
	
}