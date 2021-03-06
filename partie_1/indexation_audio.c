#include "indexation_audio.h"


/**
 * Indexe un fichier audio donne.
 *
 * @param  chemin_fichier     Chemin vers le fichier a indexer
 * @param  nb_sample_window   Nombre d'echantillons par fenetre
 * @param  nb_intervalle_amp  Nombre d'intervalles d'amplitude par fenetre
 * @return Descripteur du fichier donne.
 */
sds indexation_audio(const sds chemin_fichier, const int nb_sample_window, const int nb_intervalle_amp) {
    FILE* file = fopen(chemin_fichier, "r");    // Fichier
    sds desc = sdsempty();                      // Descripteur
    double amp;                                 // Amplitude
    int desc_frame[nb_intervalle_amp];          // Trame de descripteur (une fenetre d'echantillons)
    int test = 1;

    if(file == NULL) {
        puts("Fichier non ouvrable / inexistant");
    }
    else {
        // Scan tout le fichier
        while(!feof(file) && test > 0) {
            desc = sdscat(desc, "[");
            // Reset trame descripteur
            for(int j=0; j<nb_intervalle_amp; ++j)
                desc_frame[j] = 0;

            // Scan fenetre d'echantillons
            for(int i=0; i<nb_sample_window; ++i) {
                test = fscanf(file, "%lf", &amp);

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
