#include "indexation_texte.h"

void indexation_texte(char[] repertoire)
{
	FILE* fichier = NULL;

    fichier = fopen("test.txt", "r");
	
	if (fichier != NULL)
	{
		String motActuel = newString(int taille); //TODO
        // On lit le fichier
		do
        {
            int caractereActuel = fgetc(fichier); // On lit le caractère

            printf("%c", caractereActuel); // On l'affiche

        } while (caractereActuel != EOF); // On continue tant que fgetc n'a pas retourné EOF (fin de fichier)

        fclose(fichier);
    }
	else
	{
		printf("Impossible d'ouvrir le fichier test.txt");
	}
}