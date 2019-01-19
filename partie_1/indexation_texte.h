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

long position_mot_dans_tabocc(TabOcc t, const char * mot);

void ajout_mot(TabOcc *t, const char * mot);

unsigned int totalOccurences(TabOcc t);

TabOcc newTabOcc();

void triTabOcc(TabOcc * t);

void freeTabOcc(TabOcc * t);

unsigned char test_alpha(int lettre);

int suppr_accent_et_maj(int lettre);

TabOcc lecture_fichier(const char * accesFichier, unsigned int * nbMotsTotal);

/**
 * DESCRIPTION PLACEHOLDER
 *
 * @param  PLACEHOLDER
 * @return PLACEHOLDER
 */

	// Cette fonction est chargée de créer le sds décrivant le fichier donné en paramètre.
	// Le descripteur ainsi créer est de la forme :
	// [valeur;valeur;valeur][mot :occurence;...;motN :occurenceN]
	// (Les 3 premières valeurs sont : id ; nombreDeMotsAuTotal ; nombreDeMotsRetenus)
	//[id;nbMotsTotal;nbMotsRetenus][mot1:occ1;mot2:occ2;...]
 
sds indexation_texte(const char * accesFichier, int valId);

void gestion_descripteur_texte();

#endif
