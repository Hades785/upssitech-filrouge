#ifndef __RECHERCHE_AUDIO__
#define __RECHERCHE_AUDIO__

#include <stdlib.h>
#include <stdio.h>
#include "sds.h"
#include "indexation_audio.h"
#include "sauvegarde_descripteurs.h"


typedef struct _rra
{
    sds filename;
    float match_time;
    int score;
    struct _rra* next;
} RESULT_RECHERCHE_AUDIO;


/**
 * Compare un fichier "jingle" avec les fichiers "corpus" de la base de 
 * descripteurs et permet d'identifier les temps d'apparition
 *
 * @param  chemin_fichier    Chemin vers le fichier "jingle"
 * @param  chemin_base       Chemin vers le fichier base de descripteurs
 * @param  window_step       Nombre de fenetres entre chaque calcul de distance sur les descripteurs de la base
 * @param  nb_sample_window  Nombre d'echantillons par fenetre (parametre d'indexation)
 * @param  nb_intervale_amp  Nombre d'intervalles d'amplitude par fenetre (parametre d'indexation)
 */
RESULT_RECHERCHE_AUDIO* recherche_audio(sds const chemin_fichier, const sds chemin_base, const int window_step, const int nb_sample_window, const int nb_intervalle_amp);

void free_results_audio(RESULT_RECHERCHE_AUDIO* results);

#endif
