#include "recherche_texte.h"
#include "constantes.h"
#include "sauvegarde_descripteurs.h"

void recherche_texte_motscles(sds motscles, const sds[] liste_base_texte, const sds[] table_index_texte)
{
	sds[] resultats = new sds[NB_RESULTAT_RECHERCHE]; // resultats sous forme de chemin d acces
	int[] id = new int[NB_RESULTAT_RECHERCHE];
	id = lire_index(table_index_texte, motscles);
	
	for(int i = 0; i < NB_RESULTAT_RECHERCHE; i++)
	{
		resultats[i] = getNom(id[i], liste_base_texte)
		printf("%s\n", resultats[i]);
	}
}

void recherche_texte_fichier(sds fichier, const sds[] liste_base_texte, const sds fichierDescripteurs)
{
	sds descripteur; // le descripteur du fichier a rechercher
	unsigned char * flag;
	Capsule capsule;
	
	comparaison = sdsempty();
	descripteur = sdsnew(indexation_texte(fichier));
	capsule = loadDescripteurs(flag, fichierDescripteurs);
	
	for(int i = 0; i < capsule.nbDescripteurs; i++)
	{
		// comparaison de chaque descripteur dans fichier avec le descripteur
		// creer pour le fichier recherche
		//TODO
	}
}

// lit la table d index et retourne les identifiants des fichiers contenant le plus le mot
int[] lire_index(const sds[] table_index_texte, sds motscles)
{
	//TODO
}

// donne le nom d un fichier par rapport a son identidiant dans le fichier donne
sds getNom(int id, sds liste_base_texte)
{
	unsigned char * flag;
	Capsule capsule;
	int test_id;
	sds nom;
	
	capsule = loadDescripteurs(flag, liste_base_texte);
	nom = sdsempty();
	
	for(int i = 0; i < capsule.nbDescripteurs; i++)
	{
		// dans l optique ou dans le fichier liste_base_texte, la relation identifiant nom
		// est ecrite tel que "{identifiant:nom}" sans aucun autre caractere
		// (puisque le fichier n est a la base pas un fichiers de descripteurs, chaque
		// donnee traitant un fichier different seront separees par des accolade pour pouvoir
		// se servir du type capsule)
		sscanf(capsule.descripteurs[i], "%d:%s", &test_id, nom);
		if(id == test_id)
			break;
	}
	
	freeCapsule(capsule);
	return nom;
}