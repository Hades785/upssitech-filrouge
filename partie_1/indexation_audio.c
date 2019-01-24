#include "indexation_audio.h"

sds indexation_audio(const sds chemin_fichier, const int nb_sample_window, const int nb_intervalle_amp) {
    FILE* file = fopen(chemin_fichier, "r");    // Fichier
    sds desc = sdsempty();                      // Descripteur
    double amp;                                 // Amplitude
    int desc_frame[nb_intervalle_amp];          // Trame de descripteur (une fenetre d'echantillons)

    if(file == NULL) {
        fputs("Fichier non ouvrable / inexistant", stdout);
    }
    else {
        // Scan tout le fichier
        while(!feof(file)) {
            desc = sdscat(desc, "[");
            // Reset trame descripteur
            for(int j=0; j<nb_intervalle_amp; ++j)
                desc_frame[j] = 0;

            // Scan fenetre d'echantillons
            for(int i=0; i<nb_sample_window; ++i) {
                fscanf(file, "%lf", &amp);

                // Segmentation par amplitude
                for(int j=0; j<nb_intervalle_amp; ++j)
                    if(-1+(j)*((float)2/nb_intervalle_amp) < amp && amp < -1+(j+1)*((float)2/nb_intervalle_amp))
                        desc_frame[j]++;
            }

            // Transfert de la trame descripteur dans le descripteur
            for(int i=0; i<nb_intervalle_amp; ++i) {
                sds tmp = sdsfromlonglong(desc_frame[i]);
                if(i != nb_intervalle_amp-1)
                    tmp = sdscat(tmp, " ");
                desc = sdscat(desc, tmp);
                sdsfree(tmp);
            }
            desc = sdscat(desc, "]");
        }

        // Close opened file
        fclose(file);
    }

    return desc;
}
