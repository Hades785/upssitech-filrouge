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

    printf("DEBUG : %s %d %d\n", bdd, nbMotsMax, tailleMinMot);
    
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
    int seuilCouleur;
    int nbBits;
    unsigned char flag;

    bdd = (*jniEnv)->GetStringUTFChars(jniEnv, jBdd, NULL);
    nbCouleursMax = (int) jNbCouleursMax;
    seuilCouleur = (int) jSeuilCouleur;
    nbBits = (int) jNbBits;

    printf("DEBUG : %s %d %d %d\n", bdd, nbCouleursMax, seuilCouleur, nbBits);
    
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

    printf("DEBUG : %s %d %d\n", bdd, nbEchantillonsParFenetre, nbIntervallesAmplitude);

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
                                                            jint jNbResults)
{
    const char* cheminFichier;
    int nbResultats;
    int tailleMinMot;
    int nbMotsMax;
    unsigned char flag;

    cheminFichier = (*jniEnv)->GetStringUTFChars(jniEnv, jFilePath, NULL);
    nbResultats = (int) jNbResults;

    printf("DEBUG : %s %d\n", cheminFichier, nbResultats);

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
    
    // TODO traitement resultats
    //fin_rech_texte(resultats,nb_res_max);
    
    for(int i = 0; i < nbResultats; i++)
    {
        sdsfree(resultats[i]);
    }
    free(resultats);
    freeCapsule(base_mots);
    freeCapsule(mapNoms);

    return (*jniEnv)->NewStringUTF(jniEnv, "DEBUG : RECHERCHE_TEXTE");
}

JNIEXPORT jstring JNICALL Java_jni_MoteurC_rechercherMotsC(JNIEnv* jniEnv,
                                                           jclass jClass,
                                                           jstring jMotsCles,
                                                           jint jNbResults)
{
    const char* motsCles;
    int nbResultats;
    unsigned char flag;

    motsCles = (*jniEnv)->GetStringUTFChars(jniEnv, jMotsCles, NULL);
    nbResultats = (int) jNbResults;

    printf("DEBUG : %s %d\n", motsCles, nbResultats);

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
    
    // TODO traitement du resultat
    // fin_rech_texte(resultats,nb_res_max);
    
    int i = 0;
    while(resultats[i] != NULL && i < nbResultats)
    {
        sdsfree(resultats[i]);
        i++;
    }
    free(resultats);
    freeCapsule(base_mots);
    freeCapsule(mapNoms);

    return (*jniEnv)->NewStringUTF(jniEnv, "DEBUG : RECHERCHE_MOTS");
}

JNIEXPORT jstring JNICALL Java_jni_MoteurC_rechercherImageC(JNIEnv* jniEnv,
                                                            jclass jClass,
                                                            jstring jFilePath,
                                                            jint jNbResults,
                                                            jint jNbBits)
{
    const char* cheminFichier;
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
    const char* cheminFichier;
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
