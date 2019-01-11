#include "indexation_audio.h"

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