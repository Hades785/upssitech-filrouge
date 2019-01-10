#include <stdlib.h>
#include <stdio.h>
#include "sds.h"
#include "indexation_texte.h"

int main()
{
	sds s = indexation_texte("../documents/texte/03-Mimer_un_signal_nerveux_pour.xml",42);
	printf("%s",s);
	return 0;
}