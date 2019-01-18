#include <inttypes.h>
#include "recherche_audio.h"
#include "constantes.h"

typedef struct _sample {
    sds* values;
    int count_values;
} Sample;


int distance(const sds ligne_desc_corpus[NB_AMP_INTERVAL], const sds ligne_desc_jingle[NB_AMP_INTERVAL]) {
    for(int i = 0; i < NB_AMP_INTERVAL; i++) {
        // CONVERSION CHAR -> int TODO
        char* endptr;
        printf("%ld\n", (strtoimax(ligne_desc_corpus[i], &endptr, 10) - strtoimax(ligne_desc_jingle[i], &endptr, 10)));
    }
    return 0;
}

void recherche_audio(const sds chemin_fichier, const sds chemin_base) {
    // Recuperation descripteurs base
    char flag;
    Capsule capsule = loadDescripteurs(&flag, chemin_base);
    if(flag == ECHEC)
        return;
    
    // Recuperation du descripteur du fichier "jingle"
    sds desc_jingle = indexation_audio(chemin_fichier); // OPTION: NO REINDEX -> FETCH INDEX IN DB

    // Separation des echantillons descripteur "jingle"
    int count_desc_lines = 0;
    sds* desc_jingle_lines = sdssplitlen(desc_jingle, sdslen(desc_jingle), "]", 1, &count_desc_lines);

    // Separation des echantillons descripteurs base
    int* count_base_descs_lines = (int*) malloc(sizeof(int)*nombreDescripteurs(capsule));
    sds** base_descs_lines = (sds**) malloc(sizeof(sds*)*nombreDescripteurs(capsule));
    for(int i = 0; i < nombreDescripteurs(capsule); i++) {
        sds filename = sdsnewlen("",50);
        sscanf(capsule.descripteurs[i], "%[^;]", filename);
        sdsupdatelen(filename);
        filename = sdscat(filename, ";");
        sdstrim(capsule.descripteurs[i], filename);
        base_descs_lines[i] = sdssplitlen(capsule.descripteurs[i], sdslen(capsule.descripteurs[i]), "]", 1, &count_base_descs_lines[i]);
        sdsfree(filename);
    }
    
    // Separation des valeurs des echantillons du fichier "jingle"
    Sample* samples_j = (Sample*) malloc(sizeof(Sample)*count_desc_lines);
    for(int i = 0; i < count_desc_lines; i++) {
        sdstrim(desc_jingle_lines[i], "[");
        samples_j[i].values = sdssplitlen(desc_jingle_lines[i], sdslen(desc_jingle_lines[i]), " ", 1, &samples_j[i].count_values);
    }

    // Separation des valeurs des echantillons des fichiers de la base
    Sample** samples_d = (Sample**) malloc(sizeof(Sample*)*nombreDescripteurs(capsule));
    for(int i = 0; i < nombreDescripteurs(capsule); i++) {
        samples_d[i] = (Sample*) malloc(sizeof(Sample)*count_base_descs_lines[i]);
        for(int j = 0; j < count_base_descs_lines[i]; j++) {
            sdstrim(base_descs_lines[i][j], "[");
            samples_d[i][j].values = sdssplitlen(base_descs_lines[i][j], sdslen(base_descs_lines[i][j]), " ", 1, &samples_d[i][j].count_values);
        }
    }

    // COMPARAISON: TODO
    for(int i = 0; i < nombreDescripteurs(capsule); i++)
        for(int j = 0; j < samples_d[i][j].count_values && j < samples_j[j].count_values; j++)
            for(int k = 0; k < samples_d[i][j].count_values && k < samples_j[k].count_values; k++)
                distance(samples_d[i][j].values, samples_j[k].values);

    // for(int i = 0; i < count_desc_lines; i++) {
    //     for(int j = 0; j < samples[i].count_values; j++) {
    //         printf("%s/", samples[i].values[j]);
    //     }
    //     printf("\n");
    // }


    // Liberation memoire allouee
    for(int i = 0; i < nombreDescripteurs(capsule); i++) {
        for(int j = 0; j < count_base_descs_lines[i]; j++)
            sdsfreesplitres(samples_d[i][j].values, samples_d[i][j].count_values);
        free(samples_d[i]);
    }
    free(samples_d);
    for(int i = 0; i < nombreDescripteurs(capsule); i++)
        sdsfreesplitres(base_descs_lines[i], count_base_descs_lines[i]);
    free(base_descs_lines);
    free(count_base_descs_lines);
    for(int i = 0; i < count_desc_lines; i++)
        sdsfreesplitres(samples_j[i].values, samples_j[i].count_values);
    free(samples_j);
    sdsfreesplitres(desc_jingle_lines, count_desc_lines);
    freeCapsule(capsule);
    sdsfree(desc_jingle);
}