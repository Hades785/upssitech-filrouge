#include "recherche_audio.h"
#include "constantes.h"

typedef struct _sample {
    sds* values;
    int count_values;
} Sample;


int distance(const int ligne_desc_corpus[NB_AMP_INTERVAL], const int ligne_desc_jingle[NB_AMP_INTERVAL]) {
    for(int i = 0; i < NB_AMP_INTERVAL; i++) {
        printf("%d", (ligne_desc_corpus[i] - ligne_desc_jingle[i]));
    }
}

void recherche_audio(const sds chemin_fichier) {
    // Recuperation du descripteur du fichier "jingle"
    sds desc_jingle = indexation_audio(chemin_fichier);

    // Séparation des échatillons
    int count_desc_lines = 0;
    sds* desc_jingle_lines = sdssplitlen(desc_jingle, sdslen(desc_jingle), "]", 1, &count_desc_lines);
    
    // Séparation des valeurs des échantillons
    Sample* samples = (Sample*) malloc(sizeof(Sample)*count_desc_lines);
    for(int i = 0; i < count_desc_lines; i++) {
        sdstrim(desc_jingle_lines[i], "[");
        samples[i].values = sdssplitlen(desc_jingle_lines[i], sdslen(desc_jingle_lines[i]), " ", 1, &samples[i].count_values);
    }


    // for(int i = 0; i < count_desc_lines; i++) {
    //     for(int j = 0; j < samples[i].count_values; j++) {
    //         printf("%s/", samples[i].values[j]);
    //     }
    //     printf("\n");
    // }


    // Liberation memoire allouee
    for(int i = 0; i < count_desc_lines; i++)
        sdsfreesplitres(samples[i].values, samples[i].count_values);
    free(samples);
    sdsfreesplitres(desc_jingle_lines, count_desc_lines);
    sdsfree(desc_jingle);
}