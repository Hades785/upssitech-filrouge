#include "indexation_texte.h"
#include <ctype.h>

sds indexation_texte(const sds accesFichier)
{
	FILE* fichier = NULL;

    fichier = fopen(accesFichier, "r");
	
	if (fichier != NULL)
	{
		sds motActuel = sdsempty();
		sds chaineTotale = sdsempty();
		int carActuel = 0;
        int nbDeCar = 0;
		
		// On lit le fichier
		do
        {
            carActuel = fgetc(fichier); // On lit le caractère
			motActuel = sdscat(motActuel, carActuel);
			
			if(carActuel == '<') // On entre dans une balise
			{
				while((carActuel != '>') && (carActuel != EOF))
				{
					carActuel = fgetc(fichier);
				}
				
				carActuel = fgetc(fichier);
				
				motActuel = sdsempty();
			}
			
			if(isalpha(carActuel)) // Si c'est une lettre
			{
				motActuel = sdscat(motActuel, carActuel);
			}
			else
			{
				if((int)sdslen(motActuel) > 2) // Si le mot actuel fait au moins 3 lettres
				{
					int motPresent = 0;
					int cpt = 0;
					
					while(!motPresent && (cpt < (int)sdslen(chaineTotale)))
					{
						// Si la 1ère lettre est la même
						if(chaineTotale[cpt] == motActuel[0])
						{
							motPresent = 1;
							int i = 0;
							
							for(i = 0 ; i < (int)sdslen(motActuel) ; i++)
							{
								if(motActuel[i] != chaineTotale[cpt+i])
									motPresent = 0;
							}
							
							// On vérifie que le mot détecté n'est pas le début
							// d'un autre plus long. Ex : robot / robotique
							if(chaineTotale[cpt+i+1] != ':')
								motPresent = 0;
							
							// Si le mot est trouvé, on sort de la boucle
							if(motPresent) break;
						}
						
						cpt++;
					}
					
					if(motPresent)
					{
						
					}
					else
					{
						
					}
				}
				
				motActuel = sdsempty();
			}
        }
		while (carActuel != EOF); // fin de fichier

        fclose(fichier);
		
		sdsfree(motActuel); // On supprime les strings
		sdsfree(chaineTotale);
		
		//return(); // Pour le retour, voir ludichat sur discord //TODO
    }
	else
	{
		printf("Impossible d'ouvrir le fichier test.txt");
		
		//sds retour =
		return()
	}
}