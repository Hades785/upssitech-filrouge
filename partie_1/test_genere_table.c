#include <stdlib.h>
#include <stdio.h>
#include "sds.h"
#include "indexation_texte.h"
#include "constantes.h"
#include "config_reader.h"

int main()
{
	unsigned char successFlag;
	Capsule cap = newCapsule(&successFlag);
	
	addElement(&cap, indexation_texte("../documents/texte/05-Photographie___Philip_Blenkinsop_a.xml", 0));
	addElement(&cap, indexation_texte("../documents/texte/05-Rock___l_Illinois_magique_de.xml", 1));
	addElement(&cap, indexation_texte("../documents/texte/06-US_Open___Mauresmo_et.xml", 2));
	
	Capsule cap2 = genere_table(cap);
	//saveDescripteurs(&successFlag, cap2, "table_index_texte.txt");
	
	//freeCapsule(cap); freeCapsule(cap2);
	
	return 0;
}