#include <stdio.h>
#include <stdlib.h>
#include "indexation_image.h"

int main ()
{
	Image im;
	unsigned int * histo;
	unsigned int nbCouleursMax;
	float seuilMin;
	int id;
	char chemin[200];
	unsigned char nbBits;
	printf("veuillez introduire le chemin de votre image\n");
	scanf("%s",chemin);
	printf("veuillez introduire le nbCouleursMax, le seuilMin,le id et le nbBits respectivement\n");
	scanf(" %u %f %d %hhu",&nbCouleursMax,&seuilMin,&id,&nbBits);
	printf("%s",indexation_image(chemin,nbCouleursMax,seuilMin,id,nbBits));

	/*unsigned n; 
	decodeImage(&im,"/mnt/e/upssitech-filrouge/documents/images/rgb/01.txt"); //on donne le chemin absolu de n'importe quel fichier pour faire le test
    
    printf("matrice des pixel RGB (décodage de l'image)\n");
	for(unsigned int y = 0;y < im.tailleY;y++){
		for(unsigned int x = 0;x < im.tailleX;x++){ //affichage de la matrice des pixel RGB (décodage de l'image)
			printf("%u  %u  %u    ", (*(im.image+(x*im.tailleY)+y)).R,(*(im.image+(x*im.tailleY)+y)).G,(*(im.image+(x*im.tailleY)+y)).B);
		} 
		printf("\n");
	}
     
	printf("veuillez préciser le nombre de bits de poids fort à prendre en compte \n"); 
	scanf("%u",&n);

	histo=histogramme(im,n); //génération de l'histogramme 

	printf("\n");

	for(unsigned int y = 0;y < pow(2,3*n);y++) /* n paramètre de configuration permet de choisir 
		                                          le nombre de bits de poids fort à prendre pour la quantification
		printf(" %u   %u  \n",y,*(histo+y)); //affichage de l'histogramme 
		*/


	return 0;
}

