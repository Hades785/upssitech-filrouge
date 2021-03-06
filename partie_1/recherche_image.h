#ifndef __RECHERCHE_IMAGE__
#define __RECHERCHE_IMAGE__

#include "sds.h"
#include "sauvegarde_descripteurs.h"

#define NOIR			0x000000
#define BLANC			0xffffff
#define ROUGE			0xff0000
#define VERT			0x00ff00
#define BLEU			0x0000ff
#define CYAN			0x00ffff
#define MAGENTA			0xff00ff
#define JAUNE			0xffff00
#define DEFAULT_COLOR	0x000000

#define NOIR_T		"noir"
#define BLANC_T		"blanc"
#define ROUGE_T		"rouge"
#define VERT_T		"vert"
#define BLEU_T		"bleu"
#define CYAN_T		"cyan"
#define MAGENTA_T	"magenta"
#define JAUNE_T		"jaune"

#define NB_POINTS_SIM 100000
#define DIVISEUR_PAR_BIT 1.50
//le tri se fait selon un calcul de points:
//le calcul est base sur la somme [prop col x ob] * [prop col y ba] * NB_POINTS_SIM * (DIVISEUR_PAR_BIT ^ [nombre de bits de difference])
//pour toute les combinaisons de x et y balayant les couleurs de chacun
//ce calcul est fait en float
//le nombre de bits de difference est en realite la difference entre la valeur recherchee et la valeur de la couleur trouvee

//(lire propostion de la couleur x de l'objectif/base de donnee)
//(nombre de points par combinaison)

//l'image obtenant le plus de points se retrouve en premiere position des resultats

//cette structure n'est pas destinee a etre utilisee depuis l'exerieur, de meme que les fonctions qui suivent
typedef struct{
	int id;
	sds cheminAbs;
	unsigned int nbCouleurs;
	unsigned int nbPixels;
	unsigned int * couleurs;
	unsigned int * nbOcc;
}DescripteurImage;

DescripteurImage decodeDescripteur(const char * descripteur);

void freeDescIm(DescripteurImage * descIm);

unsigned int valDiff(unsigned int couleur1,unsigned int couleur2,unsigned char nbBits);

sds * resultGenerator(unsigned int nbResMax,DescripteurImage ** tabDesc);

unsigned int simpColor(unsigned int fullColor,unsigned char nbBits);

/**
 * renvoie un tableau de sds
 * chaque sds est un resultat par ordre decroissant de match
 * un resultat est un chemin absolu vers un fichier
 *
 * @param  couleur : nom de la couleur a chercher
 * @param  caps : capsule contenant les descripteurs de la base de donnees
 * @return un tableau de resultats se terminant par un pointeur vers null (de taille nbResMax)
 * ne pas oublier de free ce tableau ainsi que tout ses sds
 */
sds * recherche_image_col(const char * couleur,const Capsule caps,unsigned int nbResMax,unsigned char nbBits);

sds * recherche_image(unsigned int couleur,const Capsule caps,unsigned int nbResMax,unsigned char nbBits);

sds * recherche_image_file(const char * fichier,const Capsule caps,unsigned int nbResMax,unsigned char nbBits,unsigned int nbCouleursMax,float seuilMin);

#endif