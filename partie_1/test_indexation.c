#include "indexation.h"
#include <stdio.h>

int main(){
	unsigned char flag;
	Capsule caps = newCapsule(&flag);
	getAllFiles("../documents",".txt",&caps);
	for(unsigned int i = 0;i < caps.nbDescripteurs;i++){
		printf("%u:%s\n",i,caps.descripteurs[i]);
	}
	return 0;
}