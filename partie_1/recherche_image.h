#ifndef __RECHERCHE_IMAGE__
#define __RECHERCHE_IMAGE__

#include "sds.h"
#include "sauvegarde_descripteurs.h"

#define NOIR			000000
#define BLANC			111111
#define ROUGE			110000
#define VERT			001100
#define BLEU			000011
#define CYAN			001111
#define MAGENTA			110011
#define JAUNE			111100
#define DEFAULT_COLOR	000000

#define NOIR_T		"noir"
#define BLANC_T		"blanc"
#define ROUGE_T		"rouge"
#define VERT_T		"vert"
#define BLEU_T		"bleu"
#define CYAN_T		"cyan"
#define MAGENTA_T	"magenta"
#define JAUNE_T		"jaune"

#define NB_POINTS_SIM 3
#define DIVISEUR_PAR_BIT 3
//le calcul est base sur la somme [prop col x ob] * [prop col y ba] * NB_POINTS_SIM * (DIVISEUR_PAR_BIT ^ [nombre de bits de difference])
//pour toute les combinaisons de x et y balayant les couleurs de chacun
//ce calcul est fait en float

/**
La comparaison se base sur un systeme de points
	- plus la couleur demandee est presente, plus l'image obtient de points
	- si une couleur proche est presente, elle obtient les memes points mais divises par DIVISEUR_PROX_COULEUR*le nombre de bits d'ecart
	
*/

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
sds * recherche_image(const sds couleur,const Capsule caps,unsigned int nbResMax);

sds * recherche_image(unsigned int couleur,const Capsule caps,unsigned int nbResMax);

sds * recherche_image(const sds fichier,const Capsule caps,unsigned int nbResMax);

#endif
