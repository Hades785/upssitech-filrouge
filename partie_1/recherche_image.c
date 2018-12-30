#include "recherche_image.h"
#include "indexation_image.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>

//cette structure n'est pas destinee a etre utilisee depuis l'exerieur, de meme que les fonctions qui suivent
typedef struct{
	int id;
	sds cheminAbs;
	unsigned int nbCouleurs;
	unsigned int nbPixels;
	unsigned int * couleurs;
	unsigned int * nbOcc;
}DescripteurImage;

DescripteurImage decodeDescripteur(const sds descripteur){
	char chemin[200];
	DescripteurImage descIm;
	sscanf(descripteur,"[%d,%[^,],%u,%u",&(descIm.id),chemin,&(descIm.nbCouleurs),&(descIm.nbPixels));
	descIm.couleurs = malloc(sizeof(unsigned int)*descIm.nbCouleurs);
	descIm.nbOcc = malloc(sizeof(unsigned int)*descIm.nbCouleurs);
	assert(descIm.couleurs != NULL && descIm.nbOcc != NULL);
	char * debutNb = strchr(descripteur+1,'[');//+1 pour eviter celui de l'en tete
	assert(debutNb != NULL);
	for(unsigned int i = 0;i < descIm.nbCouleurs;i++){
		debutNb++;
		sscanf(debutNb,"%u=%u",&(descIm.couleurs[i]),&(descIm.nbOcc[i]));
		if(i < (descIm.nbCouleurs-1)){
			debutNb = strchr(descripteur,',');
			assert(debutNb != NULL);
		}
	}
	descIm.cheminAbs = sdsnew(chemin);
	return descIm;
}

void freeDescIm(DescripteurImage descIm){
	sdsfree(descIm.cheminAbs);
	free(descIm.couleurs);
	free(descIm.nbOcc);
}

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
	//le classement des resultats se fait selon un systeme de points,
	//attribues en fonction de la proximite des couleurs
	//on prepare un tableau pour stocker les points du haut du classement
	//(si un descripteur est en dessous c'est que suffisamment d'autres sont plus proches)
	
	float tabPoints = malloc(sizeof(float)*nbResMax);
	
	//et un tableau pour stocker les descripteurs decodes du top du classement (y faut bien savoir qui a gagne)
	unsigned int tabIndices = malloc(sizeof(unsigned int)*nbResMax);
	assert(tabPoints != NULL && tabIndices != NULL);
	
	//on balaye les descripteurs pour trouver leur nombre de points
	//on fait le calcul du total de points pour pouvoir faire le classement en meme temps, et ainsi ne pas avoir a stocker un total par descripteur de la base.
	
	//pour chaque element de la base
	for(unsigned int i = 0;i < caps.nbDescripteurs;i++){
		//pour chaque couleur de l'image de la base
		for(unsigned int c = 0;c < )
	}
}