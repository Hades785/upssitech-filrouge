#ifndef __RECHERCHE_TEXTE__
#define __RECHERCHE_TEXTE__

#include <stdlib.h>
#include <stdio.h>
#include "sds.h"
#include "indexation_texte.h"
#include "sauvegarde_descripteurs.h"

/**
 * DESCRIPTION Donne la liste des fichiers contenant le plus les mots cles
 * donnes en parametre par l utilisateur
 * Les mots cles sont donnee dans une seule chaine de caractere, separes par un espace.
 * Le dernier mot cle doit egalement etre suivit d un espace
 *
 * @param sds motscles
 * @param Capsule liste_base_texte
 * @param Capsule table_index_texte
 * @param int nb_res
 */
void recherche_texte_motscles(const sds motscles, Capsule liste_base_texte, Capsule table_index_texte, int nb_res);

/**
 * DESCRIPTION Donne la liste des fichiers les plus semblables a celui donne
 * en parametre
 *
 * @param  sds descripteur
 * @param Capsule liste_base_texte
 * @param Capsule table_index_texte
 * @param int nb_res
 */
void recherche_texte_fichier(const sds descripteur, Capsule liste_base_texte, Capsule table_index_texte, int nb_res);


#endif
