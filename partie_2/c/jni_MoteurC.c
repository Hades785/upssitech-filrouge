#include "jni_MoteurC.h"

#include <stdio.h>

#include "partie_1/constantes.h"
#include "partie_1/sds.h"
#include "partie_1/sauvegarde_descripteurs.h"
#include "partie_1/config_reader.h"

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
                                                      jint jNbMotsMax,
                                                      jint jTailleMinMot)
{
    int nbMotsMax;
    int tailleMinMot;

    nbMotsMax = (int) jNbMotsMax;
    tailleMinMot = (int) jTailleMinMot;

    printf("DEBUG : %d %d\n", nbMotsMax, tailleMinMot);
}

JNIEXPORT void JNICALL Java_jni_MoteurC_indexerImageC(JNIEnv* jniEnv,
                                                      jclass jClass,
                                                      jint jNbCouleursMax,
                                                      jfloat jSeuilCouleur,
                                                      jint jNbBits)
{
    int nbCouleursMax;
    int seuilCouleur;
    int nbBits;

    nbCouleursMax = (int) jNbCouleursMax;
    seuilCouleur = (int) jSeuilCouleur;
    nbBits = (int) jNbBits;

    printf("DEBUG : %d %d %d\n", nbCouleursMax, seuilCouleur, nbBits);
}

JNIEXPORT void JNICALL Java_jni_MoteurC_indexerAudioC(JNIEnv* jniEnv,
                                                      jclass jClass,
                                                      jint jNbSanplePFenetre,
                                                      jint jNbInterAmplitude)
{
    int nbEchantillonsParFenetre;
    int nbIntervallesAmplitude;

    nbEchantillonsParFenetre = (int) jNbSanplePFenetre;
    nbIntervallesAmplitude = (int) jNbInterAmplitude;

    printf("DEBUG : %d %d\n", nbEchantillonsParFenetre, nbIntervallesAmplitude);
}

JNIEXPORT jstring JNICALL Java_jni_MoteurC_rechercherTexteC(JNIEnv* jniEnv,
                                                            jclass jClass,
                                                            jstring jFilePath,
                                                            jint jNbResults)
{
    char* cheminFichier;
    int nbResultats;

    cheminFichier = (*jniEnv)->GetStringUTFChars(jniEnv, jFilePath, NULL);
    nbResultats = (int) jNbResults;

    printf("DEBUG : %s %d\n", cheminFichier, nbResultats);
    return (*jniEnv)->NewStringUTF(jniEnv, "DEBUG : RECHERCHE_TEXTE");
}

JNIEXPORT jstring JNICALL Java_jni_MoteurC_rechercherMotsC(JNIEnv* jniEnv,
                                                           jclass jClass,
                                                           jstring jMotsCles,
                                                           jint jNbResults)
{
    char* motsCles;
    int nbResultats;

    motsCles = (*jniEnv)->GetStringUTFChars(jniEnv, jMotsCles, NULL);
    nbResultats = (int) jNbResults;

    printf("DEBUG : %s %d\n", motsCles, nbResultats);
    return (*jniEnv)->NewStringUTF(jniEnv, "DEBUG : RECHERCHE_MOTS");
}

JNIEXPORT jstring JNICALL Java_jni_MoteurC_rechercherImageC(JNIEnv* jniEnv,
                                                            jclass jClass,
                                                            jstring jFilePath,
                                                            jint jNbResults,
                                                            jint jNbBits)
{
    char* cheminFichier;
    int nbResultats;
    int nbBits;

    cheminFichier = (*jniEnv)->GetStringUTFChars(jniEnv, jFilePath, NULL);
    nbResultats = (int) jNbResults;
    nbBits = (int) jNbBits;

    printf("DEBUG : %s %d %d\n", cheminFichier, nbResultats, nbBits);
    return (*jniEnv)->NewStringUTF(jniEnv, "DEBUG : RECHERCHE_IMAGE");
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

    codeCouleur = (int) jColorCode;
    nbResultats = (int) jNbResults;
    nbBits = (int) jNbBits;

    printf("DEBUG : %d %d %d\n", codeCouleur, nbResultats, nbBits);
    return (*jniEnv)->NewStringUTF(jniEnv, "DEBUG : RECHERCHE_COULEUR");
}

JNIEXPORT jstring JNICALL Java_jni_MoteurC_rechercherAudioC(JNIEnv* jniEnv,
                                                            jclass jClass,
                                                            jstring jFilePath,
                                                            jint jPasFenetre,
                                                            jint jNbSampleFen,
                                                            jint jNbInterAmp)
{
    char* cheminFichier;
    int pasFenetre;
    int nbEchantillonsParFenetre;
    int nbIntervallesAmplitude;

    cheminFichier = (*jniEnv)->GetStringUTFChars(jniEnv, jFilePath, NULL);
    pasFenetre = (int) jPasFenetre;
    nbEchantillonsParFenetre = (int) jNbSampleFen;
    nbIntervallesAmplitude = (int) jNbInterAmp;

    printf("DEBUG : %s %d %d %d\n", cheminFichier, pasFenetre, nbEchantillonsParFenetre, nbIntervallesAmplitude);
    return (*jniEnv)->NewStringUTF(jniEnv, "DEBUG : RECHERCHE_AUDIO");
}
