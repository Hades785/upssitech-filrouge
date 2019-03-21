#include "jni_MoteurC.h"

#include <stdio.h>

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
                                                      jstring jMap,
                                                      jstring jId,
                                                      jint jNbMotsMax,
                                                      jint jTailleMinMot)
{
    const char* bdd;
    const char* map;
    const char* id;
    int nbMotsMax;
    int tailleMinMot;
    unsigned char flag;

    bdd = (*jniEnv)->GetStringUTFChars(jniEnv, jBdd, NULL);
    map = (*jniEnv)->GetStringUTFChars(jniEnv, jMap, NULL);
    id = (*jniEnv)->GetStringUTFChars(jniEnv, jId, NULL);
    nbMotsMax = (int) jNbMotsMax;
    tailleMinMot = (int) jTailleMinMot;

    printf("DEBUG : %s %s %s %d %d\n", bdd, map, id, nbMotsMax, tailleMinMot);
    /*
    Capsule descs = newCapsule(&flag);
    if(flag != SUCCES)
        return;

    Capsule mapNoms = newCapsule(&flag);
    if(flag != SUCCES)
        return;
    
    Capsule fichiers = newCapsule(&flag);
    if(flag != SUCCES)
        return;

    for(unsigned int i = 0;i < fichiers.nbDescripteurs;i++){
        printf("Indexation texte : %s\n",fichiers.descripteurs[i]);
        addElement(&mapNoms, 
                   sdscatprintf(sdsempty(), "%u:%s", 
                                i, fichiers.descripteurs[i]));
        addElement(&descs,
                   indexation_texte(fichiers.descripteurs[i], i,
                                    nb_mots_max, taille_min_mot));
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
    */
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
    int seuilCouleur;
    int nbBits;

    bdd = (*jniEnv)->GetStringUTFChars(jniEnv, jBdd, NULL);
    nbCouleursMax = (int) jNbCouleursMax;
    seuilCouleur = (int) jSeuilCouleur;
    nbBits = (int) jNbBits;

    printf("DEBUG : %s %d %d %d\n", bdd, nbCouleursMax, seuilCouleur, nbBits);
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

    bdd = (*jniEnv)->GetStringUTFChars(jniEnv, jBdd, NULL);
    nbEchantillonsParFenetre = (int) jNbSanplePFenetre;
    nbIntervallesAmplitude = (int) jNbInterAmplitude;

    printf("DEBUG : %s %d %d\n", bdd, nbEchantillonsParFenetre, nbIntervallesAmplitude);
}

JNIEXPORT jstring JNICALL Java_jni_MoteurC_rechercherTexteC(JNIEnv* jniEnv,
                                                            jclass jClass,
                                                            jstring jBdd,
                                                            jstring jMap,
                                                            jstring jFilePath,
                                                            jint jNbResults)
{
    const char* bdd;
    const char* map;
    const char* cheminFichier;
    int nbResultats;

    bdd = (*jniEnv)->GetStringUTFChars(jniEnv, jBdd, NULL);
    map = (*jniEnv)->GetStringUTFChars(jniEnv, jMap, NULL);
    cheminFichier = (*jniEnv)->GetStringUTFChars(jniEnv, jFilePath, NULL);
    nbResultats = (int) jNbResults;

    printf("DEBUG : %s %s %s %d\n", bdd, map, cheminFichier, nbResultats);
    return (*jniEnv)->NewStringUTF(jniEnv, "DEBUG : RECHERCHE_TEXTE");
}

JNIEXPORT jstring JNICALL Java_jni_MoteurC_rechercherMotsC(JNIEnv* jniEnv,
                                                           jclass jClass,
                                                           jstring jMap,
                                                           jstring jId,
                                                           jstring jMotsCles,
                                                           jint jNbResults)
{
    const char* map;
    const char* id;
    const char* motsCles;
    int nbResultats;

    map = (*jniEnv)->GetStringUTFChars(jniEnv, jMap, NULL);
    id = (*jniEnv)->GetStringUTFChars(jniEnv, jId, NULL);
    motsCles = (*jniEnv)->GetStringUTFChars(jniEnv, jMotsCles, NULL);
    nbResultats = (int) jNbResults;

    printf("DEBUG : %s %s %s %d\n", map, id, motsCles, nbResultats);
    return (*jniEnv)->NewStringUTF(jniEnv, "DEBUG : RECHERCHE_MOTS");
}

JNIEXPORT jstring JNICALL Java_jni_MoteurC_rechercherImageC(JNIEnv* jniEnv,
                                                            jclass jClass,
                                                            jstring jBdd,
                                                            jstring jFilePath,
                                                            jint jNbResults,
                                                            jint jNbBits)
{
    const char* bdd;
    const char* cheminFichier;
    int nbResultats;
    int nbBits;

    bdd = (*jniEnv)->GetStringUTFChars(jniEnv, jBdd, NULL);
    cheminFichier = (*jniEnv)->GetStringUTFChars(jniEnv, jFilePath, NULL);
    nbResultats = (int) jNbResults;
    nbBits = (int) jNbBits;

    printf("DEBUG : %s %s %d %d\n", bdd, cheminFichier, nbResultats, nbBits);
    return (*jniEnv)->NewStringUTF(jniEnv, "DEBUG : RECHERCHE_IMAGE");
}

JNIEXPORT jstring JNICALL Java_jni_MoteurC_rechercherCouleurC(JNIEnv* jniEnv,
                                                              jclass jClass,
                                                              jstring jBdd,
                                                              jint jColorCode,
                                                              jint jNbResults,
                                                              jint jNbBits)
{
    const char* bdd;
    int codeCouleur;
    int nbResultats;
    int nbBits;

    bdd = (*jniEnv)->GetStringUTFChars(jniEnv, jBdd, NULL);
    codeCouleur = (int) jColorCode;
    nbResultats = (int) jNbResults;
    nbBits = (int) jNbBits;

    printf("DEBUG : %s %d %d %d\n", bdd, codeCouleur, nbResultats, nbBits);
    return (*jniEnv)->NewStringUTF(jniEnv, "DEBUG : RECHERCHE_COULEUR");
}

JNIEXPORT jstring JNICALL Java_jni_MoteurC_rechercherAudioC(JNIEnv* jniEnv,
                                                            jclass jClass,
                                                            jstring jBdd,
                                                            jstring jFilePath,
                                                            jint jPasFenetre,
                                                            jint jNbSampleFen,
                                                            jint jNbInterAmp)
{
    const char* bdd;
    const char* cheminFichier;
    int pasFenetre;
    int nbEchantillonsParFenetre;
    int nbIntervallesAmplitude;

    bdd = (*jniEnv)->GetStringUTFChars(jniEnv, jBdd, NULL);
    cheminFichier = (*jniEnv)->GetStringUTFChars(jniEnv, jFilePath, NULL);
    pasFenetre = (int) jPasFenetre;
    nbEchantillonsParFenetre = (int) jNbSampleFen;
    nbIntervallesAmplitude = (int) jNbInterAmp;

    printf("DEBUG : %s %s %d %d %d\n", bdd, cheminFichier, pasFenetre, nbEchantillonsParFenetre, nbIntervallesAmplitude);
    return (*jniEnv)->NewStringUTF(jniEnv, "DEBUG : RECHERCHE_AUDIO");
}
