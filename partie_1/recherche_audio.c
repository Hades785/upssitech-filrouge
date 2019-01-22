#include <inttypes.h>
#include <math.h>
#include "recherche_audio.h"
#include "constantes.h"

typedef struct _sample {
    sds* values;
    int count_values;
} Sample;


int distance(const sds* ligne_desc_corpus, const sds* ligne_desc_jingle, const int nb_intervalle_amp) {
    unsigned int dist = 0;
    for(int i = 0; i < nb_intervalle_amp; i++) {
        char* endptr;
        dist += abs(strtoimax(ligne_desc_corpus[i], &endptr, 10) - strtoimax(ligne_desc_jingle[i], &endptr, 10));
    }
    return dist;
}

void recherche_audio(const sds chemin_fichier, const sds chemin_base, const int window_step, const int nb_sample_window, const int nb_intervalle_amp) {
    // Recuperation descripteurs base
    char flag;
    Capsule capsule = loadDescripteurs(&flag, chemin_base);
    if(flag == ECHEC)
        return;
    
    // Recuperation du descripteur du fichier "jingle"
    sds desc_jingle = indexation_audio(chemin_fichier, nb_sample_window, nb_intervalle_amp); // OPTION: NO REINDEX -> FETCH INDEX IN DB

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
    Sample** samples_c = (Sample**) malloc(sizeof(Sample*)*nombreDescripteurs(capsule));
    for(int i = 0; i < nombreDescripteurs(capsule); i++) {
        samples_c[i] = (Sample*) malloc(sizeof(Sample)*count_base_descs_lines[i]);
        for(int j = 0; j < count_base_descs_lines[i]; j++) {
            sdstrim(base_descs_lines[i][j], "[");
            samples_c[i][j].values = sdssplitlen(base_descs_lines[i][j], sdslen(base_descs_lines[i][j]), " ", 1, &samples_c[i][j].count_values);
        }
    }
    
    // Tableau de recuperation des evaluations de distance
    int** distances = (int**) malloc(sizeof(int*) * nombreDescripteurs(capsule));
    for(int i = 0; i < nombreDescripteurs(capsule); i++) {
        int a = (int) floor((((float)count_base_descs_lines[i])/window_step)-(((float)count_desc_lines)/window_step)+1);
        distances[i] = (int*) malloc(sizeof(int*) * a);
        for(int j = 0; j < a; j++)
            distances[i][j] = 0;
    }

    // Comparaison [*TODO* store results of sample distance and interpret results to give time]
    for(int i = 0; i < nombreDescripteurs(capsule); i++) {
        // For every *window_step* sample evalute distance with "jingle" samples
        for(int j = 0, jj = 0; j < count_base_descs_lines[i]-1 && j <= count_base_descs_lines[i]-count_desc_lines; j+=window_step, jj++) {
            for(int k = 0; k < count_desc_lines-1; k++)
                // Calcul de distance entre les echantillons [*TODO*]
                distances[i][jj] += distance(samples_c[i][j+k].values, samples_j[k].values, nb_intervalle_amp);
        }
    }

    // [*DEBUG*] print distances probablements match
    for(int i = 0; i < nombreDescripteurs(capsule); i++) {
        int a =(int) floor((((float)count_base_descs_lines[i])/window_step)-(((float)count_desc_lines)/window_step)+1);
        printf("%d : %d -> %d\n", i, count_base_descs_lines[i]-1, a);
        for(int j = 0; j < a; j++)
            if(distances[i][j] < 5000)
                printf("%d|%d : %d\n", i, j, distances[i][j]);
        printf("\n");
    }

    // Liberation memoire allouee
    for(int i = 0; i < nombreDescripteurs(capsule); i++) {
        free(distances[i]);
    }
    free(distances);
    for(int i = 0; i < nombreDescripteurs(capsule); i++) {
        for(int j = 0; j < count_base_descs_lines[i]; j++)
            sdsfreesplitres(samples_c[i][j].values, samples_c[i][j].count_values);
        free(samples_c[i]);
    }
    free(samples_c);
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