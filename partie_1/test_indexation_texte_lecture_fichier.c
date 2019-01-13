#include <stdlib.h>
#include <stdio.h>
#include "sds.h"
#include "indexation_texte.h"

int main()
{
	TabOcc tabocc = newTabOcc();
	unsigned int nb = 0;
	
	tabocc = lecture_fichier("../documents/texte/03-Mimer_un_signal_nerveux_pour.xml", &nb);
	
	triTabOcc(&tabocc);
	
	afficher_tabocc(tabocc);
	
	return 0;
}