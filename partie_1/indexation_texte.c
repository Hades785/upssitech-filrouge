#include "indexation_texte.h"

sds indexation_texte(const sds accesFichier)
{
	FILE* fichier = NULL;

    fichier = fopen(accesFichier, "r");
	
	if (fichier != NULL)
	{
		sds motActuel = sdsempty();
		sds chaineTotale = sdsempty();
        int nbDeCar = 0;
		
		// On lit le fichier
		do
        {
            int caractereActuel = fgetc(fichier); // On lit le caractère
			nbDeCar++;
			/*
			if(caractereActuel==pasunelettre) // Savoir si c'est pas une lettre (voir ascii)
			{
				// /!\ Détecter les balises des xml : de la forme <mot>
			}
			else
				*/
			motActuel = sdscat(motActuel, caractereActuel);
			
        }
		while (caractereActuel != EOF); // fin de fichier

        fclose(fichier);
		
		sdsfree(motActuel);
		
		//return(); // Pour le retour, voir ludichat sur discord
    }
	else
	{
		printf("Impossible d'ouvrir le fichier test.txt");
		
		sds retour =
		return()
	}
}