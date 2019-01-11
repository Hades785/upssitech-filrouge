#include "recherche_audio.h"

int main() {
    sds path = sdsnew("/home/fuzuki/UPSSITECH/code/upssitech-filrouge/documents/audio/jingle_fi.txt");

    recherche_audio(path);

    sdsfree(path);
}