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
 * @param sds motscles : la liste des mots cles, suivie d'un espace
 * @param Capsule liste_base_texte : la capsule vers le fichier liste_base_texte (lien id->nom)
 * @param Capsule table_index_texte : la capsule vers le fichier liste_base_texte (occurences des mots dans chaque fichiers)
 * @param int nb_res : le nombre maximum de resultats voulus
 * @param sds resultats[] : le tableau dans lequel seront stockes les resultats
 */
void recherche_texte_motscles(const sds motscles, Capsule liste_base_texte, Capsule table_index_texte, int nb_res, sds resultats[]);

/**
 * DESCRIPTION Donne la liste des fichiers les plus semblables a celui donne
 * en parametre
 *
 * @param  sds descripteur : le descripteur du fichier avec lequel est effectue la recherche
 * @param Capsule liste_base_texte : la capsule vers le fichier liste_base_texte (lien id->nom)
 * @param Capsule table_index_texte : la capsule vers le fichier liste_base_texte (occurences des mots dans chaque fichiers)
 * @param int nb_res : le nombre maximum de resultats voulus
 * @param sds resultats[] : le tableau dans lequel seront stockes les resultats
 */
void recherche_texte_fichier(const sds descripteur, Capsule liste_base_texte, Capsule table_index_texte, int nb_res, sds resultats[]);


#endif
