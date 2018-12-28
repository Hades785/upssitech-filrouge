#include "indexation_image.h"

unsigned int simplification(Pixel pixel,unsigned char nbBits){
	unsigned char simpR,simpG,simpB;
	unsigned char nbBitsD = (8-nbBits);
	simpR = pixel.R >> nbBitsD;
	simpG = pixel.G >> nbBitsD;
	simpB = pixel.B >> nbBitsD;
	return (((((unsigned int)simpR) << nbBits) + simpG) << nbBits) + simpB;
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
			histo[simplification(*(im.image+(x*im.tailleY)+y),nbBits)]++;
		}
	}
	return histo;
}

sds createDescripteur(const unsigned int * histo,unsigned char nbBits,const sds cheminAbsolu,int id,unsigned int nbCouleursMax,float seuilMin){
	sds s = sdscatprintf(sdsempty(),"[%u,%s,",id,cheminAbsolu);
	unsigned int p = pow(2,3*nbBits);
	unsigned int total = 0,seuil;
	for(unsigned int i = 0;i < p;i++){
		total += histo[i];
	}
	seuil = (unsigned int) (total * seuilMin/100);
	//printf("seuilMin: %u, percentage: %f, total: %u, seuil: %u\n",seuilMin,((float)seuilMin)/100,total,seuil);
	
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
		/*printf("liste:\n");
		printf("\t1:%u=%u\n",tabCouleur[0],tabOccur[0]);
		printf("\t2:%u=%u\n",tabCouleur[1],tabOccur[1]);
		printf("\t3:%u=%u\n",tabCouleur[2],tabOccur[2]);
		printf("\t4:%u=%u\n",tabCouleur[3],tabOccur[3]);
		printf("\t5:%u=%u\n",tabCouleur[4],tabOccur[4]);
		printf("\t6:%u=%u\n",tabCouleur[5],tabOccur[5]);*/
	}
	
	//on compte de nombre d'entree valides
	unsigned int nbVal = 0;
	for(unsigned int i = 0;i < nbCouleursMax;i++){
		if(tabOccur[i] >= seuil)
			nbVal++;
		else
			break;
	}
	
	if(nbVal == 0)nbVal = 1;//on en prends au moins une quoi qu'il arrive
	
	s = sdscatprintf(s,"%u],[",nbVal);
	
	for(unsigned int i = 0;i < (nbVal-1);i++){
		s = sdscatprintf(s,"%u=%u,",tabCouleur[i],tabOccur[i]);
	}
	
	s = sdscatprintf(s,"%u=%u]",tabCouleur[(nbVal-1)],tabOccur[(nbVal-1)]);
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