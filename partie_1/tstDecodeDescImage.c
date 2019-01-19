#include "sds.h"
#include "recherche_image.h"

#include <stdio.h>
#include <stdlib.h>

int main(){
	sds s = sdsnew("[42,bonjourAussi,3,200],[12=13,45=20,25=6]");
	printf("Origine:    %s\n",s);
	DescripteurImage desc = decodeDescripteur(s);
	sdsfree(s);
	printf("Id:         %d\n",desc.id);
	printf("Chemin:     %s\n",desc.cheminAbs);
	printf("nbCouleurs: %u\n",desc.nbCouleurs);
	printf("nbPixels:   %u\n",desc.nbPixels);
	printf("Liste des couleurs:\n");
	for(unsigned int i = 0;i < desc.nbCouleurs;i++){
		printf("\t%u,\t%u\n",desc.couleurs[i],desc.nbOcc[i]);
	}
	sdsfree(desc.cheminAbs);
	free(desc.couleurs);
	free(desc.nbOcc);
	return 0;
}