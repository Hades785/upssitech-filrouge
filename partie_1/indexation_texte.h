#ifndef __INDEXATION_TEXTE__
#define __INDEXATION_TEXTE__


#include "sds.h"

typedef struct
{
	unsigned int nbEle;
	unsigned int size;
	sds * mots;
	unsigned int * nbOcc;
}TabOcc;

void afficher_tabocc(TabOcc t);

long position_mot_dans_tabocc(TabOcc t, sds mot);

void ajout_mot(TabOcc *t, sds mot);

unsigned int totalOccurences(TabOcc t);

TabOcc newTabOcc();

void triTabOcc(TabOcc * t);

TabOcc lecture_fichier(const sds accesFichier, unsigned int * nbMotsTotal);

/**
 * DESCRIPTION PLACEHOLDER
 *
 * @param  PLACEHOLDER
 * @return PLACEHOLDER
 */


 
sds indexation_texte(const sds accesFichier, int valId);
void gestion_descripteurs();

#endif
