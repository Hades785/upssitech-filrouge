#include <stdio.h>
#include "sauvegarde_descripteurs.h"

int main(){
	unsigned char flag;
	printf("init capsule");getchar();
	Capsule caps = newCapsule(&flag);
	printf("remplissage capsule");getchar();
	sds s = sdsnew("bonjour");
	addElement(&caps,s);
	s = sdsnew("comment");
	addElement(&caps,s);
	s = sdsnew("va");
	addElement(&caps,s);
	s = sdsnew("1");
	addElement(&caps,s);
	s = sdsnew("v2a");
	addElement(&caps,s);
	printf("pointeur1:%p\t",caps.descripteurs);
	s = sdsnew("va3");
	addElement(&caps,s);
	s = sdsnew("va4");
	addElement(&caps,s);
	s = sdsnew("va5");
	addElement(&caps,s);
	s = sdsnew("va6");
	addElement(&caps,s);
	s = sdsnew("va7");
	addElement(&caps,s);
	s = sdsnew("va8");
	addElement(&caps,s);
	s = sdsnew("va9");
	addElement(&caps,s);
	s = sdsnew("va10");
	addElement(&caps,s);
	s = sdsnew("va11");
	addElement(&caps,s);
	s = sdsnew("va12");
	addElement(&caps,s);
	printf("pointeur2:%p\n",caps.descripteurs);
	
	//freeCapsule(caps);
	
	printf("sauvegarde");getchar();
	saveDescripteurs(&flag,caps,"fTestDesc1.desc");
	printf("affichage1");getchar();
	for(unsigned int i = 0;i < caps.nbDescripteurs;i++){
		printf("%u: %s\n",i,caps.descripteurs[i]);
	}
	printf("remove");getchar();
	removeDescripteur(&caps,10);
	printf("affichage2");getchar();
	for(unsigned int i = 0;i < caps.nbDescripteurs;i++){
		printf("%u: %s\n",i,caps.descripteurs[i]);
	}
	printf("free");getchar();
	freeCapsule(caps);
	printf("lecture");getchar();
	caps = loadDescripteurs(&flag,"fTestDesc1.desc");
	
	printf("fin lecture, affichage");getchar();
	
	for(unsigned int i = 0;i < caps.nbDescripteurs;i++){
		printf("%u: %s\n",i,caps.descripteurs[i]);
	}
	freeCapsule(caps);
	return 0;
}