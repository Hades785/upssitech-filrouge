#include <stdio.h>
#include "sauvegarde_descripteurs.h"

int main(){
	Capsule caps;
	freeCapsule(&caps);
	caps.nbDescripteurs = 3;
	sds s = sdsnew("bonjour");
	caps.descripteurs[0] = s;
	s = sdsnew("comment");
	caps.descripteurs[1] = s;
	s = sdsnew("va");
	caps.descripteurs[2] = s;
	
	unsigned char flag;
	saveDescripteurs(&flag,caps,sdsnew("fTestDesc1.desc"));
	printf("done");
}