#include <inttypes.h>
#include <math.h>
#include "recherche_audio.h"
#include "constantes.h"

typedef struct _sample {
    sds* values;
    int count_values;
} Sample;


// RESULTATS

void add_result(RESULT_RECHERCHE_AUDIO** results, const sds filename, const float match_time, const int score) {
    if(*results == NULL) {
        *results = (RESULT_RECHERCHE_AUDIO*) malloc(sizeof(RESULT_RECHERCHE_AUDIO));
        (*results)->filename = filename;
        (*results)->match_time = match_time;
        (*results)->score = score;
        (*results)->next = NULL;
    } else add_result(&(*results)->next, filename, match_time, score);
}

void free_results_audio(RESULT_RECHERCHE_AUDIO* results) {
    if(results->next != NULL)
        free_results_audio(results->next);
    sdsfree(results->filename);
    free(results);
}


// RECHERCHE

int distance_loop_iterations(const int count_corpus_lines, const int count_jingle_lines, const int window_step) {
    return (int) floor((((float)count_corpus_lines)/window_step)-(((float)count_jingle_lines)/window_step)+1);
}

float match_time(const int dist_loop_iteration, const int count_corpus_lines, const int count_jingle_lines, const int nb_sample_window, const int window_step) {
    return (float)dist_loop_iteration*count_corpus_lines/distance_loop_iterations(count_corpus_lines, count_jingle_lines, window_step)/(16000/nb_sample_window);
}

int distance(const sds* ligne_desc_corpus, const sds* ligne_desc_jingle, const int nb_intervalle_amp) {
    unsigned int dist = 0;
    for(int i = 0; i < nb_intervalle_amp; i++) {
        char* endptr;
        dist += abs(strtoimax(ligne_desc_corpus[i], &endptr, 10) - strtoimax(ligne_desc_jingle[i], &endptr, 10));
    }
    return dist;
}

RESULT_RECHERCHE_AUDIO* recherche_audio(const sds chemin_fichier, const Capsule desc_base, const int window_step, const int nb_sample_window, const int nb_intervalle_amp) {
    RESULT_RECHERCHE_AUDIO* resultats = NULL;
    
    // Recuperation du descripteur du fichier "jingle"
    sds desc_jingle = indexation_audio(chemin_fichier, nb_sample_window, nb_intervalle_amp); // OPTION: NO REINDEX -> FETCH INDEX IN DB

    // Separation des echantillons descripteur "jingle"
    int count_desc_lines = 0;
    sds* desc_jingle_lines = sdssplitlen(desc_jingle, sdslen(desc_jingle), "]", 1, &count_desc_lines);

    // Separation des echantillons descripteurs base
    int* count_base_descs_lines = (int*) malloc(sizeof(int)*nombreDescripteurs(desc_base));
    sds** base_descs_lines = (sds**) malloc(sizeof(sds*)*nombreDescripteurs(desc_base));
    sds* filenames = (sds*) malloc(sizeof(sds) * nombreDescripteurs(desc_base));
    for(int i = 0; i < nombreDescripteurs(desc_base); i++) {
        filenames[i] = sdsnewlen("",50);
        sscanf(desc_base.descripteurs[i], "%[^;]", filenames[i]);
        sdsupdatelen(filenames[i]);

        sds filename = sdsdup(filenames[i]);
        filename = sdscat(filename, ";");
        sdstrim(desc_base.descripteurs[i], filename);
        base_descs_lines[i] = sdssplitlen(desc_base.descripteurs[i], sdslen(desc_base.descripteurs[i]), "]", 1, &count_base_descs_lines[i]);
        sdsfree(filename);
    }
    
    // Separation des valeurs des echantillons du fichier "jingle"
    Sample* samples_j = (Sample*) malloc(sizeof(Sample)*count_desc_lines);
    for(int i = 0; i < count_desc_lines; i++) {
        sdstrim(desc_jingle_lines[i], "[");
        samples_j[i].values = sdssplitlen(desc_jingle_lines[i], sdslen(desc_jingle_lines[i]), " ", 1, &samples_j[i].count_values);
    }

    // Separation des valeurs des echantillons des fichiers de la base
    Sample** samples_c = (Sample**) malloc(sizeof(Sample*)*nombreDescripteurs(desc_base));
    for(int i = 0; i < nombreDescripteurs(desc_base); i++) {
        samples_c[i] = (Sample*) malloc(sizeof(Sample)*count_base_descs_lines[i]);
        for(int j = 0; j < count_base_descs_lines[i]; j++) {
            sdstrim(base_descs_lines[i][j], "[");
            samples_c[i][j].values = sdssplitlen(base_descs_lines[i][j], sdslen(base_descs_lines[i][j]), " ", 1, &samples_c[i][j].count_values);
        }
    }
    
    // Tableau de recuperation des evaluations de distance
    int** distances = (int**) malloc(sizeof(int*) * nombreDescripteurs(desc_base));
    for(int i = 0; i < nombreDescripteurs(desc_base); i++) {
        int a = distance_loop_iterations(count_base_descs_lines[i], count_desc_lines, window_step);
        distances[i] = (int*) malloc(sizeof(int*) * a);
        for(int j = 0; j < a; j++)
            distances[i][j] = 0;
    }

    // Comparaison
    for(int i = 0; i < nombreDescripteurs(desc_base); i++) {
        // For every *window_step* sample evalute distance with "jingle" samples
        for(int j = 0, jj = 0; j < count_base_descs_lines[i]-1 && j <= count_base_descs_lines[i]-count_desc_lines; j+=window_step, jj++) {
            for(int k = 0; k < count_desc_lines-1; k++)
                // Calcul de distance entre les echantillons
                distances[i][jj] += distance(samples_c[i][j+k].values, samples_j[k].values, nb_intervalle_amp);
        }
    }

    // Resultats
    for(int i = 0; i < nombreDescripteurs(desc_base); i++) {
        int a = distance_loop_iterations(count_base_descs_lines[i], count_desc_lines, window_step);
        for(int j = 0; j < a; j++)
            if(distances[i][j] < 5000) {
                float matched_time = match_time(j, count_base_descs_lines[i], count_desc_lines, nb_sample_window, window_step);
                // printf("%s : %fs (score : %d)\n", filenames[i], matched_time, distances[i][j]);
                add_result(&resultats, sdsdup(filenames[i]), matched_time, distances[i][j]);
            }
        // printf("\n");
    }

    // Liberation memoire allouee
    for(int i = 0; i < nombreDescripteurs(desc_base); i++) {
        free(distances[i]);
    }
    free(distances);
    for(int i = 0; i < nombreDescripteurs(desc_base); i++) {
        for(int j = 0; j < count_base_descs_lines[i]; j++)
            sdsfreesplitres(samples_c[i][j].values, samples_c[i][j].count_values);
        free(samples_c[i]);
    }
    free(samples_c);
    for(int i = 0; i < nombreDescripteurs(desc_base); i++)
        sdsfreesplitres(base_descs_lines[i], count_base_descs_lines[i]);
    free(base_descs_lines);
    free(count_base_descs_lines);
    for(int i = 0; i < count_desc_lines; i++)
        sdsfreesplitres(samples_j[i].values, samples_j[i].count_values);
    free(samples_j);
    sdsfreesplitres(desc_jingle_lines, count_desc_lines);
    for(int i = 0; i < nombreDescripteurs(desc_base); i++)
        sdsfree(filenames[i]);
    free(filenames);
    sdsfree(desc_jingle);

    // Retour
    return resultats;
}