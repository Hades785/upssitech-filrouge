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
 * @param sds[] motscles
 * @param sds[] liste_base_texte
 * @param sds[] table_index_texte
 */
void recherche_texte_motscles(const sds motscles[], const sds liste_base_texte, const sds table_index_texte);

/**
 * DESCRIPTION Donne la liste des fichiers les plus semblables a celui donne
 * en parametre
 *
 * @param  sds fichier
 * @param sds[] liste_base_texte
 * @param sds fichierDescripteurs
 */
void recherche_texte_fichier(const sds fichier, const sds liste_base_texte, const sds fichierDescripteurs);

#endif
