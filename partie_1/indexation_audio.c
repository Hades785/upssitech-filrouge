#include "indexation_audio.h"
#include "constantes.h"

sds indexation_audio(const sds chemin_fichier) {
    FILE* file = fopen(chemin_fichier, "r");    // Fichier
    sds desc = sdsempty();                      // Descripteur
    double amp;                                 // Amplitude
    int desc_frame[NB_AMP_INTERVAL];            // Trame de descripteur (une fenetre d'echantillons)

    // // Scan tout le fichier
    // while(!feof(file)) {
    //     desc = sdscat(desc, "[");
    //     // Reset trame descripteur
    //     for(int j=0; j<NB_AMP_INTERVAL; ++j)
    //         desc_frame[j] = 0;

    //     // Scan fenetre d'echantillons
    //     for(int i=0; i<NB_SAMPLE_WINDOW; ++i) {
    //         fscanf(file, "%lf", &amp);

    //         // Segmentation par amplitude
    //         for(int j=0; j<NB_AMP_INTERVAL; ++j)
    //             if(-1+(j)*((float)2/NB_AMP_INTERVAL) < amp && amp < -1+(j+1)*((float)2/NB_AMP_INTERVAL))
    //                 desc_frame[j]++;
    //     }

    //     // Transfert la trame descripteur dans le descripteur
    //     for(int i=0; i<NB_AMP_INTERVAL; ++i) {
    //         sds tmp = sdsfromlonglong(desc_frame[i]);
    //         if(i != NB_AMP_INTERVAL-1)
    //             tmp = sdscat(tmp, " ");
    //         desc = sdscat(desc, tmp);
    //         sdsfree(tmp);
    //     }
    //     desc = sdscat(desc, "]");
    // }

    char c[50];
    while(fgets(c, 50, file) != NULL) {
        printf("%s", c);
    }
    printf("%d:%d\n", fileno(file), feof(file));

    // Close opened file
    fclose(file);

    return desc;
}
