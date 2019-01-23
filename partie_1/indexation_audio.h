#ifndef __INDEXATION_AUDIO__
#define __INDEXATION_AUDIO__

#include <stdlib.h>
#include <stdio.h>
#include "sds.h"

/**
 * Indexe un fichier audio donne.
 *
 * @param  chemin_fichier  Chemin vers le fichier a indexer.
 * @return Descripteur du fichier donne.
 */
sds indexation_audio(sds const chemin_fichier, const int nb_sample_window, const int nb_intervalle_amp);

#endif
