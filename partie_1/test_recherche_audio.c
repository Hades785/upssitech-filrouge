#include "recherche_audio.h"

int main() {
    sds path_f = sdsnew("../documents/audio/jingle_fi.txt");
    sds path_b = sdsnew("../documents/audio/test.desc");

    RESULT_RECHERCHE_AUDIO* resultats = recherche_audio(path_f, path_b, 1, 1000, 16);

    RESULT_RECHERCHE_AUDIO* ptr = resultats;
    while(ptr != NULL) {
        printf("%s : %fs (%d)\n", ptr->filename, ptr->match_time, ptr->score);
        ptr = ptr->next;
    }

    free_results_audio(resultats);
    sdsfree(path_b);
    sdsfree(path_f);
}