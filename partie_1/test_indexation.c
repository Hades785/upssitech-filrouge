#include "indexation.h"
#include <stdio.h>

int main(){
	Capsule caps = getAllFiles("../documents/images/rgb","");
	for(unsigned int i = 0;i < caps.nbDescripteurs;i++){
		printf("%u:%s\n",i,caps.descripteurs[i]);
	}
	return 0;
}