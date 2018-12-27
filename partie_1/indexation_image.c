
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

sds createDescripteur(const unsigned int * histo,unsigned char nbBits,const sds cheminAbsolu,int id,unsigned int nbCouleursMax,unsigned int seuilMin){
	sds s = sdscatprintf(sdsempty(),"[%u,%s,",id,cheminAbsolu);
	unsigned int p = pow(2,3*nbBits);
	unsigned int total = 0,seuil;
	for(unsigned int i = 0;i < p;i++){
		total += histo[i];
	}
	seuil = (unsigned int) (total * ((float)seuilMin)/100);
	
	unsigned int * tabCouleur = malloc(sizeof(unsigned int)*nbCouleursMax);//tableau de stockage des codes couleurs
	unsigned int * tabOccur = malloc(sizeof(unsigned int)*nbCouleursMax);//tableau de stockage des nombres d'occurence
	assert(tabCouleur != NULL && tabOccur != NULL);
	
	//on vide le tableau
	for(unsigned int i = 0;i < nbCouleursMax;i++){
		tabOccur[i] = 0;
	}
	
	//on tri tout ce bazar
	for(unsigned int i = 0;i < p;i++){//on balaye l'histogramme
		//pour chaque valeur dans l'histogramme
		//on cherche ou la mettre dans le tableau
		unsigned int couleur = i, occ = histo[i];
		unsigned int temp;
		//et on pousse tout une fois trouve
		for(unsigned int u = 0;u < nbCouleursMax;u++){
			if(occ > tabOccur[u]){
				temp = tabOccur[u];
				tabOccur[u] = occ;
				occ = temp;
				
				temp = tabCouleur[u];
				tabCouleur[u] = couleur;
				couleur = temp;
			}
			//si on a atteint un 0 on s'en va
			if(occ == 0)
				break;
		}
	}
	
	//on compte de nombre d'entree valides
	unsigned int nbVal = 0;
	for(unsigned int i = 0;i < nbCouleursMax;i++){
		if(tabOccur[i] >= seuil)
			nbVal++;
		else
			break;
	}
	
	if(nbVal = 0)nbVal = 1;//on en prends au moins une quoi qu'il arrive
	
	s = sdscatprintf(s,"%u],[",nbVal);
	
	for(unsigned int i = 0;i < (nbVal-1);i++){
		s = sdscatprintf(s,"%u=%u,",tabCouleur[i],tabOccur[i]);
	}
	s = sdscatprintf(s,"%u=%u]",tabCouleur[i],tabOccur[i]);
	return s;
}