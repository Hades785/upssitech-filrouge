#include <stdlib.h>
#include "indexation.h"
#include "recherche.h"

int main(int argc, const char* argv[]) {
    indexer(MODE_INDEX_TEXTE);
    rechercher(MODE_RECH_TEXTE);
    printf("TEST SUCCESS\n");
    return EXIT_SUCCESS;
}
