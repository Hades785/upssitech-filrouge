
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


unsigned int *histogramme(Image im,unsigned char nbBits){
	unsigned int p = pow(2,3*nbBits);
	unsigned int * histo = malloc(p*sizeof(unsigned int));
	assert(histo!=NULL);
	for(unsigned int i = 0;i < p;i++){
		histo[i] = 0;
	}
	for(unsigned int i=0;i<im.tailleX;i++){
		for(unsigned int j=0;j<im.tailleY;j++){
			histo[simplification(im.Image[i][j],nbBits)]++;
		}
	}
	return histo;
}