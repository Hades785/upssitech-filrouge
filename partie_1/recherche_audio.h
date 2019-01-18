#ifndef __RECHERCHE_AUDIO__
#define __RECHERCHE_AUDIO__

#include <stdlib.h>
#include <stdio.h>
#include "sds.h"
#include "indexation_audio.h"
#include "sauvegarde_descripteurs.h"

/**
 * Compare un fichier "jingle" avec les fichiers "corpus" de la base de 
 * descripteurs et permet d'identifier les temps d'apparition
 *
 * @param  chemin_fichier  Chemin vers le fichier "jingle"
 * @return PLACEHOLDER
 */
void recherche_audio(sds const chemin_fichier, const sds chemin_base);

#endif
