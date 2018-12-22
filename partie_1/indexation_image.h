#ifndef __INDEXATION_IMAGE__
#define __INDEXATION_IMAGE__

#include <stdlib.h>
#include <stdio.h>
#include "sds.h"
#include <math.h>
#include<assert.h>

typedef struct{
	unsigned char R,G,B;
}Pixel;

typedef struct{
	unsigned int tailleX;
	unsigned int tailleY;
	Pixel **Image; //un pointeur vers un tableau à deux dimension (notre image) 
}Image;

//format du descripteur image:
//"[id,cheminAbsolu],[h0,h1,h2,...]"

unsigned int simplification(Pixel pixel,unsigned char nbBits);
//pixel : structure contenant les valeurs des trois couleurs
//nbBits nombre de bits de codage pour chaque couleur
//return : la concatenation des trois codes couleur simplifie
//		longueur binaire du return : 3*nbBits cales sur les poids faibles

unsigned int *histogramme(Image im,unsigned char nbBits);
//cette fonction renvoie un pointeur vers un tableau contenant le nombre d'occurences pour chaque valeur de l'intervalle [0 2^(3*nbBIts)]
// WARN : la fonction de vérifie pas ni n'agrandis le tableau, un depassement est possible.
//cette fonction va remlir ce tableau avec le nombre d'occurence de chaque valeur possible(indice du tableau) 
//image : l'image a traiter
//nbBits : la simplification a appliquer sur l'image

Image decodeImage(sds fichierImage);
//Cette fonction remplis une image de pixels a partir du contenu textuel des images proposees

Pixel newPixel(unsigned char R,unsigned char G,unsigned char B);
//renvoie un pixel avec les valeurs donnees

sds createDescripteur(unsigned int * histo,sds cheminAbsolu,int id);
//cette fonction renvoie un descripteur contenant les informations donnees
//ce string respecte le format donne en haut de ce fichier .h

sds indexation_image(sds cheminFichier);
//cette fonction cree un descripteur a partir du fichier dont le chemin est passe en parametre

//OPTION !
//Image visuSimplify(Image image,unsigned char nbBits);
//fonction simplifiant les couleurs avec nbBits et renvoyant une image.
//ne sert qu'a visualiser.
