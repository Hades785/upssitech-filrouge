#ifndef __INDEXATION_AUDIO__
#define __INDEXATION_AUDIO__

#include <stdlib.h>
#include <stdio.h>
#include "sds.h"

/**
 * Indexe un fichier audio donne.
 *
 * @param  chemin_fichier     Chemin vers le fichier a indexer
 * @param  nb_sample_window   Nombre d'echantillons par fenetre
 * @param  nb_intervalle_amp  Nombre d'intervalles d'amplitude par fenetre
 * @return Descripteur du fichier donne.
 */
sds indexation_audio(sds const chemin_fichier, const int nb_sample_window, const int nb_intervalle_amp);

#endif
