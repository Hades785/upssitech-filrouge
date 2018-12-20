#include "sds.h"
#define TAILLE_BUF 1000//taille des blocs lus entre chaque malloc du string du descripteur (en gros si tu comprends pas touche pas)
typedef struct{
	unsigned int nbDescripteurs;
	sds * descripteurs;//liste des pointeurs vers les chaines de caracteres (les sds sont deja des pointeurs)
}Capsule;

/**
 * lis le fichier donne, en extrait les descripteurs stockes avec "saveDescripteurs"
 *
 * @param *successFlag : est modifie a SUCCES ou ECHEC
 * @param fichierDescripteur le chemin vers le fichier a lire
 *
 * @return Capsule : une capsule contenant le nombre de descripteurs stockes et un tableau de pointeurs vers les sds les contenant
 */
Capsule loadDescripteurs(unsigned char * successFlag,const sds fichierDescripteur);

/**
 * lis le fichier donne, en extrait les descripteurs stockes avec "saveDescripteurs"
 *
 * @param *successFlag : est modifie a SUCCES ou ECHEC
 * @param fichierDescripteur le chemin vers le fichier a lire
 */
void saveDescripteurs(unsigned char * successFlag,const Capsule capsule,const sds fichierDescripteurs);

/**
 * libere l'espace occupe par les sds
 *
 * @param caps : la structure a free
 */
void freeCapsule(Capsule * caps);

/**
 * initialise la capsule a la taille donnee
 * les pointeurs vers les descripteurs ne sont pas initialises a NULL, mais y a rien derriere, a charge de faire le sdsnew
 *
 * @param caps : la capsule a initialiser
 * 
 * @return SUCCES ou ECHEC
 */
unsigned char initCapsule(Capsule * caps,const unsigned int nbDescripteurs);