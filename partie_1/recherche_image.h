#ifndef __RECHERCHE_IMAGE__
#define __RECHERCHE_IMAGE__

#include <stdlib.h>
#include <stdio.h>
#include "sds.h"
#include "indexation_image.h"

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


#endif
