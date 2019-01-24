#include "recherche_texte.h"
#include "sds.h"
#include "constantes.h"
#include "sauvegarde_descripteurs.h"
#include "indexation.h"
#include <string.h>

int main()
{
	unsigned char flag;
	Capsule liste_base_texte = loadDescripteurs(&flag, "/home/fuzuki/PFilRouge/map_id_nom.desc");
	Capsule table_index = loadDescripteurs(&flag, "/home/fuzuki/PFilRouge/map_mots.desc");
	sds res[10];
	for(int i = 0; i < 10; i++)
	{
		res[i] = NULL;
	}
	
	printf("Begin test recherche par mots cles\n\n");
	
	recherche_texte_motscles("prix ", liste_base_texte, table_index, 10, res);
	
	for(int i = 0; i < 10; i++)
	{
		if(res[i] != NULL)
			printf("%d\t%s\n", i+1, res[i]);
	}
	
	printf("\nTest ended\n");
	
	// réinitialisation du tableau
	for(int i = 0; i < 10; i++)
	{
		res[i] = 0;
	}
	
	printf("Begin test recherche par fichiers\n\n");
	
	sds descripteur = indexation_texte("test.txt", 0, 20, 3);
	recherche_texte_fichier(descripteur, liste_base_texte, table_index, 10, res);
	
	for(int i = 0; i < 10; i++)
	{
		if(strlen(res[i]) > 0)
			printf("%s\n", res[i]);
	}
	
	printf("\nTest ended\n");
	
	freeCapsule(liste_base_texte);
	freeCapsule(table_index);
	sdsfree(descripteur);
	
	return 0;
}