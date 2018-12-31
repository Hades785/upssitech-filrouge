#include "recherche_image.h"
#include "indexation_image.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>

DescripteurImage decodeDescripteur(const sds descripteur){
	char chemin[200];
	DescripteurImage descIm;
	sscanf(descripteur,"[%d,%[^,],%u,%u",&(descIm.id),chemin,&(descIm.nbCouleurs),&(descIm.nbPixels));
	descIm.couleurs = malloc(sizeof(unsigned int)*descIm.nbCouleurs);
	descIm.nbOcc = malloc(sizeof(unsigned int)*descIm.nbCouleurs);
	assert(descIm.couleurs != NULL && descIm.nbOcc != NULL);
	char * debutNb = strchr(descripteur+1,'[');//+1 pour eviter celui de l'en tete
	assert(debutNb != NULL);
	//printf("gate0:%u",(debutNb-descripteur));getchar();
	for(unsigned int i = 0;i < descIm.nbCouleurs;i++){
		debutNb++;
		sscanf(debutNb,"%u=%u",&(descIm.couleurs[i]),&(descIm.nbOcc[i]));	//printf("gate1:%u,%u=%u",debutNb-descripteur,(descIm.couleurs[i]),(descIm.nbOcc[i]));getchar();
		if(i < (descIm.nbCouleurs-1)){
			debutNb = strchr(debutNb,',');
			//printf("gate2:%u",debutNb-descripteur);getchar();
			assert(debutNb != NULL);
		}
	}
	descIm.cheminAbs = sdsnew(chemin);
	return descIm;
}

//free tout les composants et la structure elle-meme
void freeDescIm(DescripteurImage * descIm){
	if(descIm != NULL){
		sdsfree(descIm->cheminAbs);
		free(descIm->couleurs);
		free(descIm->nbOcc);
		free(descIm);
	}
}

//cette fonction donne la difference (la somme des differences des trois couleurs)
unsigned int valDiff(unsigned int couleur1,unsigned int couleur2,unsigned char nbBits){
	//on commence par decomposer les trois composantes
	//on prepare les masques
	//unsigned int = 32 bits   0xffffffff
	unsigned int mask = 0xffffffff>>(32-nbBits);
	unsigned int r1 = couleur1>>(nbBits*2);
	unsigned int r2 = couleur2>>(nbBits*2);
	unsigned int v1 = (couleur1>>nbBits)&mask;
	unsigned int v2 = (couleur2>>nbBits)&mask;
	unsigned int b1 = couleur1&mask;
	unsigned int b2 = couleur2&mask;
	unsigned int sum;
	if(r1 > r2) sum = r1-r2;
	else sum = r2-r1;
	if(v1 > v2) sum += v1-v2;
	else sum = v2-v1;
	if(b1 > b2) sum = b1-b2;
	else sum = b2-b1;
	return sum;
}

sds * resultGenerator(unsigned int nbResMax,DescripteurImage ** tabDesc){
	sds * tabRes = malloc(sizeof(sds*)*nbResMax);
	assert(tabRes != NULL);
	for(unsigned int i = 0;i < nbResMax;i++){
		//pour chacun des resultats on extrait une copie du sds (car les originaux vont etre detruits)
		if(tabDesc[i] != NULL)
			tabRes[i] = sdsdup(tabDesc[i]->cheminAbs);
		else
			tabRes[i] = NULL;
	}
}

sds * recherche_image_col(const sds couleur,const Capsule caps,unsigned int nbResMax,unsigned char nbBits){
	if(strcmp(NOIR_T,couleur))
		return recherche_image(NOIR,caps,nbResMax,nbBits);
	if(strcmp(BLANC_T,couleur))
		return recherche_image(BLANC,caps,nbResMax,nbBits);
	if(strcmp(ROUGE_T,couleur))
		return recherche_image(ROUGE,caps,nbResMax,nbBits);
	if(strcmp(VERT_T,couleur))
		return recherche_image(VERT,caps,nbResMax,nbBits);
	if(strcmp(BLEU_T,couleur))
		return recherche_image(BLEU,caps,nbResMax,nbBits);
	if(strcmp(CYAN_T,couleur))
		return recherche_image(CYAN,caps,nbResMax,nbBits);
	if(strcmp(MAGENTA_T,couleur))
		return recherche_image(MAGENTA,caps,nbResMax,nbBits);
	if(strcmp(JAUNE_T,couleur))
		return recherche_image(JAUNE,caps,nbResMax,nbBits);
	return recherche_image(DEFAULT_COLOR,caps,nbResMax,nbBits);
}

sds * recherche_image(unsigned int couleur,const Capsule caps,unsigned int nbResMax,unsigned char nbBits){
	//le classement des resultats se fait selon un systeme de points,
	//attribues en fonction de la proximite des couleurs
	//on prepare un tableau pour stocker les points du haut du classement
	//(si un descripteur est en dessous c'est que suffisamment d'autres sont plus proches)
	
	float * tabPoints = malloc(sizeof(float)*nbResMax);
	
	//et un tableau pour stocker les descripteurs decodes du top du classement (y faut bien savoir qui a gagne)
	DescripteurImage ** tabDesc = malloc(sizeof(DescripteurImage*)*nbResMax);
	assert(tabPoints != NULL && tabDesc != NULL);
	
	for(unsigned int i = 0;i < nbResMax;i++){
		tabDesc[i] = NULL;
		tabPoints[i] = 0;
	}
	
	//on balaye les descripteurs pour trouver leur nombre de points
	//on fait le calcul du total de points pour pouvoir faire le classement en meme temps, et ainsi ne pas avoir a stocker un total par descripteur de la base.
	
	//pour chaque element de la base
	unsigned int points;
	for(unsigned int i = 0;i < caps.nbDescripteurs;i++){
		//on en extrait le descripteur
		DescripteurImage tempdes = decodeDescripteur(caps.descripteurs[i]);
		DescripteurImage * descIm = &tempdes;
		points = 0;
		//pour chaque couleur de l'image de la base
		for(unsigned int c = 0;c < descIm->nbCouleurs;c++){
			//ici on compare directement a une couleur, donc on fait le meme calcul mais en considérant une image unie de la couleur donnee (100% de la couleur)
			float prop = descIm->nbOcc[c]/(float)descIm->nbPixels;
			unsigned int valDif = valDiff(couleur,descIm->couleurs[c],nbBits);
			float factDiff = pow(DIVISEUR_PAR_BIT,valDif);
			points+= prop*NB_POINTS_SIM*factDiff;
		}
		
		//on injecte ce resultat dans le classement
		//pour cela on balaye le classement en descendant et en injectant
		
		for(unsigned int u = 0;u < nbResMax;u++){
			//ici on ne lit que les points donc pas de veriication si le descripteur existe
			if(tabPoints[u] <= points){
				float temp = tabPoints[u];
				tabPoints[u] = points;
				points = temp;
				
				DescripteurImage * tempd = tabDesc[u];
				tabDesc[u] = descIm;
				descIm = tempd;
			}
			//temp et tempd ne contiennent que des copies de pointeurs temporairement, donc pas de free (aucune memoire n'est allouee)
		}
		freeDescIm(descIm);
		//points est un type primitif, donc pas de free
	}
	
	//on a maintenant notre classement, reste a composer le resultat de recherche
	sds * result = resultGenerator(nbResMax,tabDesc);
	//on free tout ce bazar
	for(unsigned int i = 0;i < nbResMax;i++){
		freeDescIm(tabDesc[i]);
	}
	free(tabDesc);
	free(tabPoints);
	return result;
}

sds * recherche_image_file(const sds fichier,const Capsule caps,unsigned int nbResMax,unsigned char nbBits,unsigned int nbCouleursMax,float seuilMin){
	
	float * tabPoints = malloc(sizeof(float)*nbResMax);
	DescripteurImage ** tabDesc = malloc(sizeof(DescripteurImage*)*nbResMax);
	assert(tabPoints != NULL && tabDesc != NULL);
	
	for(unsigned int i = 0;i < nbResMax;i++){
		tabDesc[i] = NULL;
		tabPoints[i] = 0;
	}
	
	//on cree le descripteur de l'image donnee
	DescripteurImage cible = decodeDescripteur(indexation_image(fichier,nbCouleursMax,seuilMin));
	
	//on fait le calcul du total de points pour pouvoir faire le classement en meme temps, et ainsi ne pas avoir a stocker un total par descripteur de la base.
	
	//on prepare les valeurs qui serviront au calcul
	//la proportion dans l'image de chaque couleur
	float * propCible = malloc(sizeof(float)*cible.nbCouleurs);
	assert(propCible != NULL);
	for(unsigned int i = 0;i < cible.nbCouleurs;i++){
		propCible[i] = cible.nbOcc[i]/(float)cible.nbPixels;
	}
	
	//pour chaque element de la base
	unsigned int points;
	for(unsigned int i = 0;i < caps.nbDescripteurs;i++){
		//on en extrait le descripteur
		DescripteurImage tempdes = decodeDescripteur(caps.descripteurs[i]);
		DescripteurImage * descIm = &tempdes;
		points = 0;
		//pour chaque couleur de l'image de la base
		for(unsigned int c = 0;c < descIm->nbCouleurs;c++){
			//ici on compare toutes les couleurs de l'image cible
			//on commence par preparer les valeurs de l'image a tester
			float prop = descIm->nbOcc[c]/(float)descIm->nbPixels;
			//pour chaque couleur de la cible
			for(unsigned int u = 0;u < cible.nbCouleurs;u++){
				unsigned int valDif = valDiff(cible.couleurs[u],descIm->couleurs[c],nbBits);
				float factDiff = pow(DIVISEUR_PAR_BIT,valDif);
				points+= propCible[u] * prop * NB_POINTS_SIM * factDiff;
			}
		}
		
		free(propCible);
		
		//on injecte ce resultat dans le classement
		//pour cela on balaye le classement en descendant et en injectant
		
		for(unsigned int u = 0;u < nbResMax;u++){
			//ici on ne lit que les points donc pas de veriication si le descripteur existe
			if(tabPoints[u] <= points){
				float temp = tabPoints[u];
				tabPoints[u] = points;
				points = temp;
				
				DescripteurImage * tempd = tabDesc[u];
				tabDesc[u] = descIm;
				descIm = tempd;
			}
			//temp et tempd ne contiennent que des copies de pointeurs temporairement, donc pas de free (aucune memoire n'est allouee)
		}
		freeDescIm(descIm);
		//points est un type primitif, donc pas de free
	}
	
	//on a maintenant notre classement, reste a composer le resultat de recherche
	sds * result = resultGenerator(nbResMax,tabDesc);
	//on free tout ce bazar
	for(unsigned int i = 0;i < nbResMax;i++){
		freeDescIm(tabDesc[i]);
	}
	free(tabDesc);
	free(tabPoints);
	return result;
}