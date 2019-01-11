#include "sauvgarde_descripteurs.h"
#include "indexation_image.h"

int main(){
	unsigned char flag;
	Capsule caps=newCapsule(&flag);
	addElement(&caps,indexation_image("../documents/images/rgb/20.txt",10,1,1,2));
	addElement(&caps,indexation_image("../documents/images/rgb/17.txt",10,1,2,2));
	addElement(&caps,indexation_image("../documents/images/rgb/32.txt",10,1,3,2));
	addElement(&caps,indexation_image("../documents/images/rgb/36.txt",10,1,4,2));
	addElement(&caps,indexation_image("../documents/images/rgb/46.txt",10,1,5,2));
	addElement(&caps,indexation_image("../documents/images/rgb/37.txt",10,1,6,2));
	addElement(&caps,indexation_image("../documents/images/rgb/33.txt",10,1,7,2));
	saveDescripteurs(&flag,caps,"rechercheimage.desc");

}