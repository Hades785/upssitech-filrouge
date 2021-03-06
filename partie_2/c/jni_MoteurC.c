#include "jni_MoteurC.h"
#include "utility.h"

#include <stdio.h>
#include <assert.h>

#include "partie_1/constantes.h"
#include "partie_1/sds.h"
#include "partie_1/sauvegarde_descripteurs.h"

#include "partie_1/indexation_texte.h"
#include "partie_1/indexation_image.h"
#include "partie_1/indexation_audio.h"

#include "partie_1/recherche_texte.h"
#include "partie_1/recherche_image.h"
#include "partie_1/recherche_audio.h"


JNIEXPORT void JNICALL Java_jni_MoteurC_initC(JNIEnv* jniEnv, jclass jClass)
{
    // Initialisation
}

JNIEXPORT void JNICALL Java_jni_MoteurC_indexerTexteC(JNIEnv* jniEnv,
                                                      jclass jClass,
                                                      jstring jBdd,
                                                      jint jNbMotsMax,
                                                      jint jTailleMinMot)
{
    const char* bdd;
    int nbMotsMax;
    int tailleMinMot;
    unsigned char flag;

    bdd = (*jniEnv)->GetStringUTFChars(jniEnv, jBdd, NULL);
    nbMotsMax = (int) jNbMotsMax;
    tailleMinMot = (int) jTailleMinMot;

    // debug print
    // printf("DEBUG : %s %d %d\n", bdd, nbMotsMax, tailleMinMot);
    
    Capsule descs = newCapsule(&flag);
    if(flag != SUCCES)
        return;

    Capsule mapNoms = newCapsule(&flag);
    if(flag != SUCCES)
        return;
    
    Capsule fichiers = newCapsule(&flag);
    if(flag != SUCCES)
        return;

    getAllFiles(bdd,".xml",&fichiers);

    for(unsigned int i = 0;i < fichiers.nbDescripteurs;i++){
        printf("Indexation texte : %s\n",fichiers.descripteurs[i]);
        addElement(&mapNoms, 
                   sdscatprintf(sdsempty(), "%u:%s", 
                                i, fichiers.descripteurs[i]));
        addElement(&descs,
                   indexation_texte(fichiers.descripteurs[i], i,
                                    nbMotsMax, tailleMinMot));
    }
    freeCapsule(fichiers);

    sds chemin = sdscat(sdscat(getDirPathI(),"/"), NOM_FICH_DESC_TEXT);
    saveDescripteurs(&flag,descs,chemin);
    sdsfree(chemin);
    if(flag != SUCCES){
        puts("Erreur seuvegarde descripteurs");
        assert(flag != ECHEC);
    }

    chemin = sdscat(sdscat(getDirPathI(),"/"), NOM_FICH_MAP_NOM_TEXT);
    saveDescripteurs(&flag,mapNoms,chemin);
    freeCapsule(mapNoms);
    sdsfree(chemin);
    if(flag != SUCCES){
        puts("Erreur seuvegarde descripteurs");
        assert(flag != ECHEC);
    }

    Capsule mapMots = genere_table(descs);
    freeCapsule(descs);

    chemin = sdscat(sdscat(getDirPathI(),"/"), NOM_FICH_MAP_MOTS);
    saveDescripteurs(&flag,mapMots,chemin);
    freeCapsule(mapMots);
    sdsfree(chemin);
    if(flag != SUCCES){
        puts("Erreur seuvegarde descripteurs");
        assert(flag != ECHEC);
    }
}

JNIEXPORT void JNICALL Java_jni_MoteurC_indexerImageC(JNIEnv* jniEnv,
                                                      jclass jClass,
                                                      jstring jBdd,
                                                      jint jNbCouleursMax,
                                                      jfloat jSeuilCouleur,
                                                      jint jNbBits)
{
    const char* bdd;
    int nbCouleursMax;
    float seuilCouleur;
    int nbBits;
    unsigned char flag;

    bdd = (*jniEnv)->GetStringUTFChars(jniEnv, jBdd, NULL);
    nbCouleursMax = (int) jNbCouleursMax;
    seuilCouleur = (float) jSeuilCouleur;
    nbBits = (int) jNbBits;

    // debug print
    // printf("DEBUG : %s %d %f %d\n", bdd, nbCouleursMax, seuilCouleur, nbBits);
    
    Capsule descs = newCapsule(&flag);
    if (flag != SUCCES)
        return;

    Capsule fichiers = newCapsule(&flag);
    if (flag != SUCCES)
        return;

    getAllFiles(bdd,".txt",&fichiers);

    for(unsigned int i = 0;i < fichiers.nbDescripteurs;i++){
        printf("Indexation image : %s\n",fichiers.descripteurs[i]);
        addElement(&descs,
                   indexation_image(fichiers.descripteurs[i], nbCouleursMax,
                                    seuilCouleur, i, nbBits));
    }

    sds chemin = sdscat(sdscat(getDirPathI(),"/"),NOM_FICH_DESC_IMG);
    saveDescripteurs(&flag,descs,chemin);
    sdsfree(chemin);
    freeCapsule(descs);
    freeCapsule(fichiers);
    if(flag != SUCCES){
        puts("Erreur seuvegarde descripteurs");
        assert(flag != ECHEC);
    }
}

JNIEXPORT void JNICALL Java_jni_MoteurC_indexerAudioC(JNIEnv* jniEnv,
                                                      jclass jClass,
                                                      jstring jBdd,
                                                      jint jNbSanplePFenetre,
                                                      jint jNbInterAmplitude)
{
    const char* bdd;
    int nbEchantillonsParFenetre;
    int nbIntervallesAmplitude;
    unsigned char flag;

    bdd = (*jniEnv)->GetStringUTFChars(jniEnv, jBdd, NULL);
    nbEchantillonsParFenetre = (int) jNbSanplePFenetre;
    nbIntervallesAmplitude = (int) jNbInterAmplitude;

    // debug print
    // printf("DEBUG : %s %d %d\n", bdd, nbEchantillonsParFenetre, nbIntervallesAmplitude);

    Capsule descs = newCapsule(&flag);
    if(flag != SUCCES)
        return;

    Capsule fichiers = newCapsule(&flag);
    if(flag != SUCCES)
        return;

    getAllFiles(bdd,".txt",&fichiers);

    for(unsigned int i = 0;i < fichiers.nbDescripteurs;i++){
        printf("Indexation audio : %s\n",fichiers.descripteurs[i]);
        sds s = sdsdup(fichiers.descripteurs[i]);
        sds t = indexation_audio(fichiers.descripteurs[i],
                                 nbEchantillonsParFenetre,
                                 nbIntervallesAmplitude);
        s = sdscat(s, ";");
        s = sdscat(s, t);
        addElementCopy(&descs, s);
        
        sdsfree(t);
        sdsfree(s);
    }

    sds chemin = sdscat(sdscat(getDirPathI(),"/"),NOM_FICH_DESC_AUD);
    saveDescripteurs(&flag,descs,chemin);
    sdsfree(chemin);
    freeCapsule(descs);
    freeCapsule(fichiers);
    if(flag != SUCCES){
        puts("Erreur seuvegarde descripteurs");
        assert(flag != ECHEC);
    }
}

JNIEXPORT jstring JNICALL Java_jni_MoteurC_rechercherTexteC(JNIEnv* jniEnv,
                                                            jclass jClass,
                                                            jstring jFilePath,
                                                            jint jNbResults,
                                                            jint jNbMotsMax,
                                                            jint jTailleMinMot)
{
    const char* cheminFichier;
    int nbResultats;
    int nbMotsMax;
    int tailleMinMot;
    unsigned char flag;

    cheminFichier = (*jniEnv)->GetStringUTFChars(jniEnv, jFilePath, NULL);
    nbResultats = (int) jNbResults;
    nbMotsMax = (int) jNbMotsMax;
    tailleMinMot = (int) jTailleMinMot;

    // debug print
    // printf("DEBUG : %s %d %d %d\n", cheminFichier, nbResultats, nbMotsMax, tailleMinMot);

    sds dirPath = sdscat(getDirPath(),"/");

    sds temp = sdscat(sdsdup(dirPath),NOM_FICH_MAP_MOTS);
    Capsule base_mots = loadDescripteurs(&flag,temp);
    sdsfree(temp);

    temp = sdscat(sdsdup(dirPath),NOM_FICH_MAP_NOM_TEXT);
    Capsule mapNoms = loadDescripteurs(&flag,temp);
    sdsfree(temp);

    sdsfree(dirPath);
    
    sds * resultats = malloc(sizeof(sds*)*nbResultats);
    assert(resultats != NULL);
    for(unsigned int i = 0;i < nbResultats;i++){
        resultats[i] = NULL;
    }

    sds descripteur = indexation_texte(cheminFichier, 0, nbMotsMax, tailleMinMot);
    recherche_texte_fichier(descripteur, mapNoms, base_mots, nbResultats, resultats);
    sdsfree(descripteur);
    
    // Traitement resultats
	sds s = sdsempty();
    for(int i = 0; i < nbResultats && resultats[i] != NULL; i++)
    {
        // Formatage chaine de retour
		s = sdscat(s, resultats[i]);
		s = sdscat(s, "\n");

        sdsfree(resultats[i]);
    }
    free(resultats);
    freeCapsule(base_mots);
    freeCapsule(mapNoms);

    // Retour resultats
	jstring res = (*jniEnv)->NewStringUTF(jniEnv,s);
	sdsfree(s);
	return res;
}

JNIEXPORT jstring JNICALL Java_jni_MoteurC_rechercherMotsC(JNIEnv* jniEnv,
                                                           jclass jClass,
                                                           jstring jMotsCles,
                                                           jint jNbResults,
                                                           jint jNbMotsMax,
                                                           jint jTailleMinMot)
{
    const char* motsCles;
    int nbResultats;
    unsigned char flag;

    motsCles = (*jniEnv)->GetStringUTFChars(jniEnv, jMotsCles, NULL);
    nbResultats = (int) jNbResults;

    // debug print
    // printf("DEBUG : %s %d\n", motsCles, nbResultats);

    sds dirPath = sdscat(getDirPath(),"/");

    sds temp = sdscat(sdsdup(dirPath),NOM_FICH_MAP_MOTS);
    Capsule base_mots = loadDescripteurs(&flag,temp);
    sdsfree(temp);

    temp = sdscat(sdsdup(dirPath),NOM_FICH_MAP_NOM_TEXT);
    Capsule mapNoms = loadDescripteurs(&flag,temp);
    sdsfree(temp);

    sdsfree(dirPath);
    
    sds * resultats = malloc(sizeof(sds*)*nbResultats);
    assert(resultats != NULL);
    for(unsigned int i = 0;i < nbResultats;i++){
        resultats[i] = NULL;
    }
    
    sds sMotsCles = sdsnew(motsCles);
    recherche_texte_motscles(sMotsCles, mapNoms, base_mots,
                             nbResultats, resultats);
    sdsfree(sMotsCles);
    
    // Traitement resultats
    sds s = sdsempty();
    for(int i = 0; i < nbResultats && resultats[i] != NULL; i++)
    {
        // Formatage chaine de retour
        s = sdscat(s, resultats[i]);
        s = sdscat(s, "\n");

        sdsfree(resultats[i]);
    }
    free(resultats);
    freeCapsule(base_mots);
    freeCapsule(mapNoms);

    // Retour resultats
    jstring res = (*jniEnv)->NewStringUTF(jniEnv,s);
    sdsfree(s);
    return res;
}

JNIEXPORT jstring JNICALL Java_jni_MoteurC_rechercherImageC(JNIEnv* jniEnv,
                                                            jclass jClass,
                                                            jstring jFilePath,
                                                            jint jNbResults,
                                                            jint jNbBits,
                                                            jint jNbCouleursMax,
                                                            jfloat jSeuilCouleur)
{
    const char* cheminFichier;
    int nbResultats;
    int nbBits;
    int nbCouleursMax;
    float seuilCouleur;
    unsigned char flag;

    cheminFichier = (*jniEnv)->GetStringUTFChars(jniEnv, jFilePath, NULL);
    nbResultats = (int) jNbResults;
    nbBits = (int) jNbBits;
    nbCouleursMax = (int) jNbCouleursMax;
    seuilCouleur = (int) jSeuilCouleur;

    // debug print
    // printf("DEBUG : %s %d %d %d %f\n", cheminFichier, nbResultats, nbBits, nbCouleursMax, seuilCouleur);

    sds dirPath = sdscat(sdscat(getDirPath(),"/"),NOM_FICH_DESC_IMG);
    Capsule base = loadDescripteurs(&flag,dirPath);
    if(flag != SUCCES){
        printf("Echec ouverture base descripteurs : %s\n",dirPath);
        sdsfree(dirPath);
        assert(flag != ECHEC);
    }
    sdsfree(dirPath);

    sds * reponse;    
    reponse = recherche_image_file(cheminFichier, base, nbResultats, nbBits, nbCouleursMax, seuilCouleur);
    
    freeCapsule(base);

    // Traitement resultats
    sds s = sdsempty();
    if(reponse == NULL){
        puts("Chemin invalide.");
    }else{
        for(int i = 0; reponse[i] != NULL; i++){
            s = sdscat(s, reponse[i]);
            s = sdscat(s, "\n");

            sdsfree(reponse[i]);
        }
        free(reponse);
    }

    // Retour resultats
    jstring res = (*jniEnv)->NewStringUTF(jniEnv,s);
    sdsfree(s);
    return res;
}

JNIEXPORT jstring JNICALL Java_jni_MoteurC_rechercherCouleurC(JNIEnv* jniEnv,
                                                              jclass jClass,
                                                              jint jColorCode,
                                                              jint jNbResults,
                                                              jint jNbBits)
{
    int codeCouleur;
    int nbResultats;
    int nbBits;
    unsigned char flag;

    codeCouleur = (int) jColorCode;
    nbResultats = (int) jNbResults;
    nbBits = (int) jNbBits;

    // debug print
    // printf("DEBUG : %d %d %d\n", codeCouleur, nbResultats, nbBits);

    sds dirPath = sdscat(sdscat(getDirPath(),"/"),NOM_FICH_DESC_IMG);

    Capsule base = loadDescripteurs(&flag,dirPath);
    if(flag != SUCCES){
        printf("Echec ouverture base descripteurs : %s\n",dirPath);
        sdsfree(dirPath);
        assert(flag != ECHEC);
    }

    sdsfree(dirPath);

    sds * reponse;
    reponse = recherche_image(simpColor(codeCouleur, nbBits), 
                              base, nbResultats, nbBits);
    
    freeCapsule(base);

    // Traitement resultats
    sds s = sdsempty();
    for(int i = 0; reponse[i] != NULL; i++){
        s = sdscat(s, reponse[i]);
        s = sdscat(s, "\n");

        sdsfree(reponse[i]);
    }
    free(reponse);

    // Retour resultats
    jstring res = (*jniEnv)->NewStringUTF(jniEnv,s);
    sdsfree(s);
    return res;
}

JNIEXPORT jstring JNICALL Java_jni_MoteurC_rechercherAudioC(JNIEnv* jniEnv,
                                                            jclass jClass,
                                                            jstring jFilePath,
                                                            jint jPasFenetre,
                                                            jint jNbSampleFen,
                                                            jint jNbInterAmp)
{
    const char* cheminFichier;
    int pasFenetre;
    int nbEchantillonsParFenetre;
    int nbIntervallesAmplitude;
    unsigned char flag;

    cheminFichier = (*jniEnv)->GetStringUTFChars(jniEnv, jFilePath, NULL);
    pasFenetre = (int) jPasFenetre;
    nbEchantillonsParFenetre = (int) jNbSampleFen;
    nbIntervallesAmplitude = (int) jNbInterAmp;

    // debug print
    // printf("DEBUG : %s %d %d %d\n", cheminFichier, pasFenetre, nbEchantillonsParFenetre, nbIntervallesAmplitude);

    sds dirPath = sdscat(sdscat(getDirPath(),"/"),NOM_FICH_DESC_AUD);
    Capsule base = loadDescripteurs(&flag,dirPath);
    if(flag != SUCCES){
        printf("Echec ouverture base descripteurs : %s\n",dirPath);
        sdsfree(dirPath);
        assert(flag != ECHEC);
    }
    sdsfree(dirPath);

    RESULT_RECHERCHE_AUDIO* resultats = recherche_audio((char*) cheminFichier, 
                                                        base, 
                                                        pasFenetre, 
                                                        nbEchantillonsParFenetre,
                                                        nbIntervallesAmplitude);

    // Traitement resultats
    sds s = sdsempty();
    for(RESULT_RECHERCHE_AUDIO* ptr = resultats; ptr != NULL; ptr = ptr->next)
        s = sdscatprintf(s, "%s : %fs (%d)\n", ptr->filename, ptr->match_time, ptr->score);

    free_results_audio(resultats);
    
    freeCapsule(base);

    // Retour resultats
    jstring res = (*jniEnv)->NewStringUTF(jniEnv,s);
    sdsfree(s);
    return res;
}
