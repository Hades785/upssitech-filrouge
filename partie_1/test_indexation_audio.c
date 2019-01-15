#include <string.h>
#include "indexation_audio.h"
#include "sauvegarde_descripteurs.h"

// DEBUG!!!!!!
#define NB_FILES 10
#define NB_CHAR_FILENAME 50


int get_files(const sds path, char** files) {
    sds cmd = sdsempty();
    cmd = sdscat(cmd, "ls ");
    cmd = sdscat(cmd, path);
    cmd = sdscat(cmd, " | grep \\.txt");
    FILE* fp;

    if ((fp = popen(cmd, "r")) == NULL) {
        // printf("Error opening pipe!\n");
        return -1;
    }

    int i = 0;
    while (!feof(fp)) {
        fscanf(fp, "%s", files[i]);
        sdsupdatelen(files[i]);
        i++;
    }

    if(pclose(fp))  {
        // printf("Command not found or exited with error status\n");
        return -1;
    }

    sdsfree(cmd);
    return 0;
}

int main() {
    sds path = sdsnew("../documents/audio/");

    // Recuperation des noms des fichiers a indexer
    int file_count = 0;
    sds* files = (sds*) malloc(sizeof(sds)*NB_FILES);
    for(int i = 0; i < NB_FILES; i++)
        files[i] = sdsnewlen("", NB_CHAR_FILENAME);
    get_files(path, files);
    for(int i = 0; i < NB_FILES; i++)
        if(strcmp(files[i], "\0") != 0)
            file_count++;

    // Generation de la capsule dse descripteurs
    char flag;
    Capsule capsule = newCapsule(&flag);
    if(flag == SUCCES)
        for(int i = 0; i < file_count; i++) {
            sds tmp = sdsdup(path);
            tmp = sdscat(tmp, files[i]);

            printf("%s\n", tmp);

            sds s = indexation_audio(tmp);
            addElementCopy(&capsule, s);

            sdsfree(s);
            sdsfree(tmp);
        }
    freeCapsule(capsule);

    // sds s = indexation_audio(path);

    // // Log file
    // FILE* log = fopen("/home/fuzuki/UPSSITECH/code/upssitech-filrouge/documents/audio/log", "w");

    // fprintf(log, "%s", s);

    // // Close log file
    // fclose(log);

    // sdsfree(s);

    for(int i = 0; i < NB_FILES; i++)
        sdsfree(files[i]);
    free(files);

    sdsfree(path);
}
