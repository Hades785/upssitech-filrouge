#include "recherche_image.h"
#include "indexation_image.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>

sds * recherche_image(const sds couleur,const Capsule caps,unsigned int nbResMax){
	if(strcmp(NOIR_T,couleur))
		return recherche_image(NOIR,caps,nbResMax);
	if(strcmp(BLANC_T,couleur))
		return recherche_image(BLANC,caps,nbResMax);
	if(strcmp(ROUGE_T,couleur))
		return recherche_image(ROUGE,caps,nbResMax);
	if(strcmp(VERT_T,couleur))
		return recherche_image(VERT,caps,nbResMax);
	if(strcmp(BLEU_T,couleur))
		return recherche_image(BLEU,caps,nbResMax);
	if(strcmp(CYAN_T,couleur))
		return recherche_image(CYAN,caps,nbResMax);
	if(strcmp(MAGENTA_T,couleur))
		return recherche_image(MAGENTA,caps,nbResMax);
	if(strcmp(JAUNE_T,couleur))
		return recherche_image(JAUNE,caps,nbResMax);
	return recherche_image(DEFAULT_COLOR,caps,nbResMax);
}

sds * recherche_image(unsigned int couleur,const Capsule caps,unsigned int nbResMax){
	//on prépare un tableau pour stocker les resultats
	//chaque resultat est le nom d'un fichier
	sds * tabRes = malloc(sizeof(sds)*nbResMax);
	//on prepare un tableau pour pouvoir les classer
	//c'est le tableau contenant le niveau de 'match'
	unsigned int * tabPoints = malloc(sizeof(unsigned int)*nbResMax);
	assert(tabRes != NULL && tabPoints != NULL);
	
	//on commence par 
	
}