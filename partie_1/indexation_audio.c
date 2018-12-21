#include "indexation_audio.h"
#include "constantes.h"

sds indexation_audio(const sds chemin_fichier) {
    FILE* file = fopen(chemin_fichier, "r");    // Fichier
    sds desc = sdsempty();                      // Descripteur
    double amp;                                 // Amplitude
    int desc_frame[NB_AMP_INTERVAL];            // Trame de descripteur (une fenetre d'echantillons)

    // Scan tout le fichier
    while(!feof(file)) {
        // Reset trame descripteur
        for(int j=0; j<NB_AMP_INTERVAL; ++j)
            desc_frame[j] = 0;

        // Scan fenetre d'echantillons
        for(int i=0; i<NB_SAMPLE_WINDOW; ++i) {
            fscanf(file, "%lf", &amp);

            // Segmentation par amplitude
            for(int j=0; j<NB_AMP_INTERVAL; ++j)
                if(-1+(j)*((float)2/NB_AMP_INTERVAL) < amp && amp < -1+(j+1)*((float)2/NB_AMP_INTERVAL))
                    desc_frame[j]++;
        }

        // Transfert la trame descripteur dans le descripteur
        for(int i=0; i<NB_AMP_INTERVAL; ++i) {
            sds tmp = sdsfromlonglong(desc_frame[i]);
            tmp = sdscat(tmp, " ");
            desc = sdscat(desc, tmp);
            sdsfree(tmp);
        }
        desc = sdscat(desc, "\n");
    }

    // Close opened file
    fclose(file);

    return desc;
}

#ifdef TEST_INDEX_AUDIO

int main() {
    sds path = sdsnew("/home/fuzuki/UPSSITECH/code/upssitech-filrouge/documents/audio/corpus_fi.txt");

    sds s = indexation_audio(path);

//     fprintf(stdout, "%s\n", s);
//     fprintf(stdout, "%s\n", path);

    // Log file
    FILE* log = fopen("/home/fuzuki/UPSSITECH/code/upssitech-filrouge/documents/audio/log", "w");

    fprintf(log, "%s", s);

    // Close log file
    fclose(log);

    sdsfree(s);
    sdsfree(path);
}

#endif
