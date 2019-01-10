#include "sds.h"
#include "constantes.h"

#define TAILLE_BUF 1000//taille des blocs lus entre chaque malloc du string du descripteur (en gros si tu comprends pas touche pas)
typedef struct{
	unsigned int nbDescripteurs;
	unsigned int size;
	sds * descripteurs;//liste des pointeurs vers les chaines de caracteres (les sds sont deja des pointeurs)
}Capsule;

/*
A noter que l'ajout de descripteurs se fait uniquement par addElement et addElementCopy. L'jout d'elements n'est pas limite et le tableau les contenant est automatiquement agrandi et relocalise. Conserver un pointeur vers ce tableau apres l'ajout d'elements est donc risque.
*/

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
 * libere l'espace utilise pour les stocker
 * la capsule est inutilisable ensuite, la supprimer.
 *
 * @param caps : la structure a free
 */
void freeCapsule(Capsule caps);

/**
 * Cree une capsule vide.
 * @param successFlag contiendra la valeur SUCCES ou ECHEC
 *
 * @return une capsule ne contenant aucun element et pret a en stocker (utiliser addElement)
 */
Capsule newCapsule(unsigned char * successFlag);

/**
 * Reinitialise une capsule et libere son contenu.
 * En cas d'echec, le contenu n'est pas libere.
 *
 * @param caps la capsule a reinitialiser
 *
 * @return SUCCES ou ECHEC
 */
unsigned char resetCapsule(Capsule * caps);

/**
 * ajoute un element a la capsule.
 * @param caps la capsule dans laquelle ajouter l'element
 * @param element le sds a ajouter. Une copie en sera faite, le modifier par la suite n'aura aucune influence, et il ne sera pas free lors du free de la capsule.
 * 
 * @return SUCCES ou ECHEC
 */
unsigned char addElementCopy(Capsule * caps,const sds element);

/**
 * ajoute un element a la capsule.
 * @param caps la capsule dans laquelle ajouter l'element
 * @param element le sds a ajouter. Modifier le sds par la suite peut casser la capsule, et il sera free lors du freeCapsule.
 * 
 * @return SUCCES ou ECHEC
 */
unsigned char addElement(Capsule * caps,sds element);

/**
 * indique le nombre de descripteurs stockes dans la capsule
 * 
 * @param caps la capsule a analyser
 * 
 * @return le nombre de sds dans le tableau de la capsule
 */
unsigned int nombreDescripteurs(const Capsule caps);