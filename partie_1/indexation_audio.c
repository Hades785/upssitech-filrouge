#include "indexation_audio.h"
#include "constantes.h"

#define TEST_INDEX_AUDIO

sds indexation_audio(const sds chemin_fichier) {
    FILE* file = fopen(chemin_fichier, "r");    // Fichier
    sds desc = sdsempty();                      // Descripteur TODO
    double amp;                                 // Amplitude
    int desc_frame[NB_AMP_INTERVAL];            // Trame de descripteur (une fenetre d'echantillons)

    // LOG FILE FOR DEBUG WARNING
    FILE* log = fopen("/home/fuzuki/UPSSITECH/code/upssitech-filrouge/documents/audio/log", "w");

    // Scan tout le fichier
    while(!feof(file)) {
        // Reset trame descripteur
        for(int j=0; j<NB_AMP_INTERVAL; ++j)
            desc_frame[j] = 0;

        // Scan fenetre d'echantillons
        for(int i=0; i<NB_SAMPLE_WINDOW; ++i) {
            fscanf(file, "%lf", &amp);

            // Segmentation par amplitude
            for(int j=0; j<NB_AMP_INTERVAL; ++j) {
                if(-1+(j)*((float)2/NB_AMP_INTERVAL) < amp && amp < -1+(j+1)*((float)2/NB_AMP_INTERVAL)) {
                    desc_frame[j]++;
                }
            }
        }

        // Transfert la trame descripteur dans le descripteur
        for(int i=0; i<NB_AMP_INTERVAL; ++i)
            fprintf(log, "%4d ", desc_frame[i]);
        fprintf(log, "\n");
    }

    // CLOSE DEBUG LOG FILE WARNING
    fclose(log);

    // Close opened file
    fclose(file);

    return desc;
}

#ifdef TEST_INDEX_AUDIO

int main() {
    sds path = sdsnew("/home/fuzuki/UPSSITECH/code/upssitech-filrouge/documents/audio/jingle_fi.txt");

    sds s = indexation_audio(path);

    sdsfree(s);
    sdsfree(path);
}

#endif
