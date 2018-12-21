#include <math.h>
#include "indexation_image.h"

unsigned int simplification(Pixel pixel,unsigned char nbBits){
	unsigned char simpR,simpG,simpB;
	unsigned char nbBitsD = (8-nbBits)
	simpR = pixel.R >> nbBitsD;
	simpG = pixel.G >> nbBitsD;
	simpB = pixel.B >> nbBitsD;
	return = (((((unsigned int)simpR) << nbBits) + simpG) << nbBits) + simpB;
}

Pixel newPixel(unsigned char R,unsigned char G,unsigned char B){
	Pixel pix;
	pix.R = R;
	pix.G = G;
	pix.B = B;
	return pix;
}


unsigned int *histogramme(Image im,unsigned char nbBits)
{   int a,k=0;
	int * histo=malloc(pow(2,3*nbBits)*sizeof(*histo));
	{ *(histo+k)=0;
	for(int i=0;i<im.tailleX;i++)
		for(int j=0;j<im.tailleY;j++)
			if(k==simplification(im.Image[i][j],nbBits))
			(*(histo+k))++;
			k++;
	} while(k!=pow(2,3*nbBits));
	while(k)
	
	
 return histo;
}


 

