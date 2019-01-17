#include <stdlib.h>
#include <stdio.h>
#include "sds.h"
#include "indexation_texte.h"

int main()
{
	sds s = indexation_texte("../documents/texte/10-Le_cyclone_Katrina_complique_le.xml",42);
	printf("\n%s\n",s);
	return 0;
}