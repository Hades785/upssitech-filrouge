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

// Pour le moment, cette fonction recherche un fichier identique a celui passe en parametre
void recherche_texte_fichier(sds fichier, const sds[] liste_base_texte, const sds fichierDescripteurs)
{
	// format d un descripteur
	// [id;nombreDeMotsAuTotal;nombreDeMotsRetenus][mot :occurence;mot2 :occurence2]
	
	sds descripteur, comparaison, resultat; // le descripteur du fichier a rechercher
	unsigned char * flag;
	Capsule capsule;
	int comparaison, id;
	
	resultat = sdsnew("Fichier recherche non trouve.");
	descripteur = sdsnew(indexation_texte(fichier));
	capsule = loadDescripteurs(flag, fichierDescripteurs);
	
	for(int i = 0; i < capsule.nbDescripteurs; i++)
	{
		comparaison = int sdscmp(capsule.descripteurs[i], descripteur);
		if (comparaison == 0)
		{
			sscanf(descripteur, "[%d;", &id);
			resultats = getNom(id[i], liste_base_texte);
		}
	}
	printf(resultat);
}

// lit la table d index et retourne les identifiants des fichiers contenant le plus le mot
int[] lire_index(const sds[] table_index_texte, const sds[] motscles)
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