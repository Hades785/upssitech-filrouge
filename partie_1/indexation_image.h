#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "String.h"

typedef struct{
	unsigned char R,G,B;
}Pixel;

typedef struct{
	unsigned int tailleX;
	unsigned int tailleY;
	Pixel [][] image;
}Image;

//format du descripteur image:
"[id,cheminAbsolu],[h0,h1,h2,...]"

unsigned int simplification(Pixel pixel,unsigned char nbBits);
//pixel : structure contenant les valeurs des trois couleurs
//nbBits nombre de bits de codage pour chaque couleur
//return : la concatenation des trois codes couleur simplifie
//		longueur binaire du return : 3*nbBits cales sur les poids faibles

void histogramme(unsigned int * histo,Image image,unsigned char nbBits);
//*histo est un pointeur vers un tableau de taille 2^nbBits (minimum).
// WARN : la fonction de vérifie pas ni n'agrandis le tableau, un depassement est possible.
//cette fonction va remlir ce tableau avec le nombre d'occurence de chaque valeur possible(indice du tableau)
//image : l'image a traiter
//nbBits : la simplification a appliquer sur l'image

Image decodeImage(String fichierImage);
//Cette fonction remplis une image de pixels a partir du contenu textuel des images proposees

Pixel newPixel(unsigned char R,unsigned char G,unsigned char B);
//renvoie un pixel avec les valeurs donnees

String createDescripteurString(unsigned int * histo,String cheminAbsolu,int id);
//cette fonction renvoie un descripteur contenant les informations donnees
//ce string respecte le format donne en haut de ce fichier.h

String indexation_image(String cheminFichier);
//cette fonction cree un descripteur a partir du fichier dont le chemin est passe en parametre

//OPTION !
//Image visuSimplify(Image image,unsigned char nbBits);
//fonction simplifiant les couleurs avec nbBits et renvoyant une image.
//ne sert qu'a visualiser.