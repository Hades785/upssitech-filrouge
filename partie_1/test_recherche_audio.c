#include "recherche_audio.h"

int main() {
    sds path_f = sdsnew("../documents/audio/jingle_fi.txt");
    sds path_b = sdsnew("../documents/audio/test.desc");

    recherche_audio(path_f, path_b, 1, 1000, 16);

    sdsfree(path_b);
    sdsfree(path_f);
}