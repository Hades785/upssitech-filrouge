#include "recherche_texte.h"
#include "sds.h"
#include "constantes.h"
#include "sauvegarde_descripteurs.h"
#include "indexation.h"

int main()
{
	unsigned char flag;
	Capsule liste_base_texte = loadDescripteurs(&flag, "index.txt");
	Capsule table_index = loadDescripteurs(&flag, "table_index.txt");
	printf("Begin test recherche par mots cles\n\n");
	
	recherche_texte_motscles("chat fichier texte indexer patate ", liste_base_texte, table_index, 10);
	
	printf("\nTest ended\n");
	
	printf("Begin test recherche par fichiers\n\n");
	
	sds descripteur = indexation_texte("test.txt", 0);
	recherche_texte_fichier(descripteur, liste_base_texte, table_index, 10);
	
	printf("\nTest ended\n");
	
	freeCapsule(liste_base_texte);
	freeCapsule(table_index);
	sdsfree(descripteur);
	
	return 0;
}