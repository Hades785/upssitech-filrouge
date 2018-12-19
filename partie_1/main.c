#include <stdlib.h>
#include <dirent.h>
#include "indexation.h"
#include "recherche.h"

/**
 * Indexation du repertoire
  */
void indexation_main()
{
	char[] chemin;
	
	// Indexation
	// Une condition sera ajoutee pour qu elle ne soit pas re effectuee
	// a chaque demarrage du logiciel.
	chemin = new char[300];
	do
	{
	printf("Saisissez le chemin absolu du repertoire contenant les fichiers a indexer limite a 300 caracteres):\n")
	scanf("%s", chemin);
	DIR* dir = opendir(chemin); // verification de l existence
	} while(!dir)
		
	indexer(MODE_INDEX_TEXTE, chemin);
	indexer(MODE_INDEX_IMAGE, chemin);
	indexer(MODE_INDEX_AUDIO, chemin);
}

/**
* Menu - Recherche
 */
 void recherche_main()
 {
	int choix;
	while(choix)
	{
		printf("3 - Recherche de texte\n");
		printf("2 - Recherche d image\n");
		printf("1 - Recherche de son\n");
		printf("0 - Precedent\n");
		
		scanf("%d", &choix);
		printf("\n\n------------------------\n\n");
		
		switch(choix)
		{
			case 0:
				return;
			case 1:
				recherche_main_a();
				break;
			case 2:
				recherche_main_i();
				break;
			case 3:
				recherche_main_t();
				break;
			default:
				continue;
		}
	}
 }
 
 void recherche_main_t()
 {
	 int choix;
	 while(choix)
	 {
		printf("2 - Recherche par fichier\n"); 
		printf("1 - Recherche par mot-cles\n");
		printf("0 - Precedent\n");
		
		switch(choix)
		{
			case 0:
				return;
			case 1:
				// rechercher(MODE_RECH_TEXTE_MOT);
				break;
			case 2:
				// rechercher(MODE_RECH_TEXTE_FICHIER);
				break;
			default:
				continue;
	 }
 }
 
 void recherche_main_i()
 {
	 
 }
 
 void recherche_main_a()
 {
	 char[] fichier_jingle; // extrait de son recherche
	 // TODO
 }

/**
 * Affichage du menu principal.
 */
void display_main_menu() {
	int choix;
	while(choix)
	{
		printf("2 - Recherche\n");
		printf("1 - Reindexer\n");
		printf("0 - Quitter\n");
		
		scanf("%d", &choix);
		printf("\n\n------------------------\n\n");
		
		switch(choix)
		{
			case 1:
				recherche_main();
				break;
			case 2:
				indexation();
				break;
			default:
				continue;
		}
	}
}

int main(int argc, const char* argv[]) {
	indexation();
    display_main_menu();
    return EXIT_SUCCESS;
}
