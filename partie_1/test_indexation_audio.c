#include <string.h>
#include "indexation_audio.h"
#include "sauvegarde_descripteurs.h"

// DEBUG!!!!!!
#define NB_FILES 10
#define NB_CHAR_FILENAME 50


int get_files(char** files) {
    char* cmd = "ls ../documents/audio/ | grep \\.txt";    
    FILE* fp;

    if ((fp = popen(cmd, "r")) == NULL) {
        // printf("Error opening pipe!\n");
        return -1;
    }

    int i = 0;
    while (!feof(fp)) {
        fscanf(fp, "%s", files[i]);
        i++;
    }

    if(pclose(fp))  {
        // printf("Command not found or exited with error status\n");
        return -1;
    }

    return 0;
}

int main() {
    // Recuperation des noms des fichiers a indexer
    int file_count = 0;
    char** files = (char**) malloc(sizeof(char*)*NB_FILES);
    for(int i = 0; i < NB_FILES; i++)
        files[i] = (char*) malloc(sizeof(char)*NB_CHAR_FILENAME);
    get_files(files);
    for(int i = 0; i < NB_FILES; i++)
        if(strcmp(files[i], "\0") != 0)
            file_count++;

    // Generation de la capsule dse descripteurs
    sds path = sdsnew("../documents/audio/");
    char flag;
    Capsule capsule = newCapsule(&flag);
    if(flag == SUCCES)
        for(int i = 0; i < file_count; i++) {
            sds tmp = sdsdup(path);
            tmp = sdscat(tmp, files[i]);

            printf("%s\n", tmp);

            sds s = indexation_audio(path); //infinite loop....
            // addElementCopy(&capsule, s);

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
        free(files[i]);
    free(files);

    sdsfree(path);
}
