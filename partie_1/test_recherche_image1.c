#include "sauvegarde_descripteurs.h"
#include "indexation_image.h"

int main(){
	unsigned char flag;
	unsigned char a=3;
	Capsule caps=newCapsule(&flag);
	addElement(&caps,indexation_image("../documents/images/rgb/20.txt",50,1,1,a));
	addElement(&caps,indexation_image("../documents/images/rgb/17.txt",50,1,2,a));
	addElement(&caps,indexation_image("../documents/images/rgb/32.txt",50,1,3,a));
	addElement(&caps,indexation_image("../documents/images/rgb/36.txt",50,1,4,a));
	addElement(&caps,indexation_image("../documents/images/rgb/46.txt",50,1,5,a));
	addElement(&caps,indexation_image("../documents/images/rgb/37.txt",50,1,6,a));
	addElement(&caps,indexation_image("../documents/images/rgb/33.txt",50,1,7,a));
	saveDescripteurs(&flag,caps,"rechercheimage.desc");

}