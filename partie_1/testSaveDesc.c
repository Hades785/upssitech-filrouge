#include <stdio.h>
#include "sauvegarde_descripteurs.h"

int main(){
	Capsule caps;
	printf("init capsule");
	getchar();
	initCapsule(&caps,3);
	caps.nbDescripteurs = 3;
	printf("remplissage capsule");
	getchar();
	sds s = sdsnew("bonjour");
	caps.descripteurs[0] = s;
	s = sdsnew("comment");
	caps.descripteurs[1] = s;
	s = sdsnew("va");
	caps.descripteurs[2] = s;
	
	unsigned char flag;
	printf("sauvegarde");
	getchar();
	saveDescripteurs(&flag,caps,"fTestDesc1.desc");
	printf("free");
	getchar();
	freeCapsule(&caps);
	printf("done");
	getchar();
	
	printf("lecture");
	getchar();
	caps = loadDescripteurs(&flag,"fTestDesc1.desc");
	
	printf("fin lecture, affichage");
	getchar();
	
	printf("0: %s\n",caps.descripteurs[0]);
	printf("1: %s\n",caps.descripteurs[1]);
	printf("2: %s\n",caps.descripteurs[2]);
	return 0;
}