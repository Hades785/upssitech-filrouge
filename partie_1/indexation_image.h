#ifndef __INDEXATION_IMAGE__
#define __INDEXATION_IMAGE__

#include "sds.h"

typedef struct{
	unsigned char R,G,B;
}Pixel;

typedef struct{
	unsigned int tailleX;
	unsigned int tailleY;
	Pixel *image; //un pointeur vers un tableau à deux dimension (notre image) 
}Image;

//format du descripteur image:
//"[id,cheminAbsolu,nbCouleurs,nbPixelsTotal],[c0=nbOcc0,c1=nbOcc1,c2=nbOcc2,...]"

unsigned int simplification(Pixel pixel,unsigned char nbBits);
//pixel : structure contenant les valeurs des trois couleurs
//nbBits nombre de bits de codage pour chaque couleur
//return : la concatenation des trois codes couleur simplifie
//		longueur binaire du return : 3*nbBits cales sur les poids faibles

Pixel newPixel(unsigned char R,unsigned char G,unsigned char B);
//renvoie un pixel avec les valeurs donnees

unsigned int *histogramme(const Image im,unsigned char nbBits);
//cette fonction renvoie un pointeur vers un tableau contenant le nombre d'occurences pour chaque valeur de l'intervalle [0   2^(3*nbBIts)-1]
//image : l'image a traiter
//nbBits : la simplification a appliquer sur l'image

unsigned char decodeImage(Image * im, const char * fichierImage);
//Cette fonction remplis une image de pixels a partir du contenu textuel des images proposees

sds createDescripteur(const unsigned int * histo,unsigned char nbBits,const char * cheminAbsolu,int id,unsigned int nbCouleursMax,float seuilMin);
//cette fonction renvoie un descripteur contenant les informations donnees
//ce string respecte le format donne en haut de ce fichier .h
//nbCouleursMax et seuilMin sont passes par indexation_image

sds indexation_image(const char * cheminFichier,unsigned int nbCouleursMax,float seuilMin,int id ,unsigned char nbBits);
//cette fonction cree un descripteur a partir du fichier dont le chemin est passe en parametre
//nbCouleurMax definit le nombre de couleurs maximum enregistree,
//seuilMin [1 - 99] definit le pourcentage de couverture de l'image minimum requis pour etre enregistree
//la couleur majoritaire est toujours enregistree quelle que soit ces conditions

//OPTION !
//Image visuSimplify(Image image,unsigned char nbBits);
//fonction simplifiant les couleurs avec nbBits et renvoyant une image.
//ne sert qu'a visualiser.

#endif