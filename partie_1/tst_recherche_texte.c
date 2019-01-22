#include "recherche_texte.h"
#include "sds.h"
#include "constantes.h"

int main()
{
	printf("Begin test recherche par mots cles\n\n");
	
	recherche_texte_motscles("chat ", "index.txt", "table_index.txt");
	
	printf("\nTest ended\n");
	
	printf("Begin test recherche par fichiers\n\n");
	
	recherche_texte_fichier("test.txt", "index.txt", "descripteurs.txt");
	
	printf("\nTest ended\n");
	return 0;
}