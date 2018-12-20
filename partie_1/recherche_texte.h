#ifndef __RECHERCHE_TEXTE__
#define __RECHERCHE_TEXTE__

#include <stdlib.h>
#include <stdio.h>
#include "sds.h"
#include "indexation_texte.h"

/**
 * DESCRIPTION Donne la liste des fichiers contenant le plus les mots cles
 * donnes en parametre par l utilisateur
 *
 * @param sds motscles
 * @param sds repertoire
 */
void recherche_texte_motscles(sds motscles, const sds[] descripteurs);

/**
 * DESCRIPTION Donne la liste des fichiers le plus semblable a celui donne
 * en parametre
 *
 * @param  sds fichier
 * @param sds repertoire
 */
void recherche_texte_fichier(sds fichier, const sds[] descripteurs);

#endif
