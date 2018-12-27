
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

unsigned int *histogramme(const Image im,unsigned char nbBits){
	unsigned int p = pow(2,3*nbBits);
	unsigned int * histo = malloc(p*sizeof(unsigned int));
	assert(histo!=NULL);
	for(unsigned int i = 0;i < p;i++){
		histo[i] = 0;
	}
	for(unsigned int x=0;x<im.tailleX;x++){
		for(unsigned int y=0;y<im.tailleY;y++){
			histo[simplification((im.Image+(x*tailleY)+y),nbBits)]++;
		}
	}
	return histo;
}

sds createDescripteur(const unsigned int * histo,const sds cheminAbsolu,int id){
	sds s = sdscatprintf(sdsempty(),"%u,%s],[",id,cheminAbsolu);
	unsigned int p = pow(2,3*nbBits);
	for(unsigned int i = 0;i < (p-1);i++){
		s = sdscatprintf(s,"%u,",histo[i]);
	}
	s = sdscatprintf(s,"%u]",histo[p-1]);
	return s;
}



void decodeImage(Image * im,sds fichierImage) 
    {

    FILE * fichier=NULL;
    unsigned int nbr_matrice;
    unsigned int temp;
       
    fichier=fopen(fichierImage,"r");
    if(fichier!=NULL)
    {
        fscanf(fichier,"%u",&im->tailleX); //lecture des dimensions X & Yde l'image   
        fscanf(fichier,"%u",&im->tailleY);
        fscanf(fichier,"%u",&nbr_matrice);//lecture nombre matrice de pixel (1-> noir & blanc/3->couleur )

        
        im->image = malloc(im->tailleX * im->tailleY * sizeof(Pixel));

      if(nbr_matrice==1) //si l'image est noir & blanc 
       {
           for(unsigned int y = 0;y < im->tailleY;y++){
            for(unsigned int x = 0;x < im->tailleX;x++){
                fscanf(fichier,"%u",&temp);
                (*(im->image+(x*im->tailleY)+y)).R = (unsigned char) temp; //les 3 composantes RGB ont la même valeur
                (*(im->image+(x*im->tailleY)+y)).G = (unsigned char) temp;
                (*(im->image+(x*im->tailleY)+y)).B = (unsigned char) temp;
            }
        }  

      }
       else //si l'image est en couleur 
       { 
        for(unsigned int y = 0;y < im->tailleY;y++){
            for(unsigned int x = 0;x < im->tailleX;x++){
                fscanf(fichier,"%u",&temp);
                (*(im->image+(x*im->tailleY)+y)).R = (unsigned char) temp;
          

            }
        }
       

        
        for(unsigned int y = 0;y < im->tailleY;y++){
            for(unsigned int x = 0;x < im->tailleX;x++){
                fscanf(fichier,"%u",&temp);
               (*(im->image+(x*im->tailleY)+y)).G = (unsigned char) temp;
            }
        }
        
        for(unsigned int y = 0;y < im->tailleY;y++){
            for(unsigned int x = 0;x < im->tailleX;x++){
                fscanf(fichier,"%u",&temp);
                (*(im->image+(x*im->tailleY)+y)).B = (unsigned char) temp;
            }
        }
      }
    }
    fclose(fichier);
    
 }

