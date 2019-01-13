#include <stdlib.h>
#include <stdio.h>
#include "sds.h"
#include "indexation_texte.h"

int main()
{
	sds s = indexation_texte("../documents/texte/05-Edition___les_mots_et.xml",42);
	printf("%s",s);
	return 0;
}