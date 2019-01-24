#include "recherche_texte.h"
#include "constantes.h"
#include <string.h>

typedef struct Cel_Occ
{
	struct Cel_Occ * precedent;
	int identifiant;
	int occurences;
	struct Cel_Occ * suivant;
} TabOccurences;

// donne le nom d un fichier par rapport a son identifiant dans le fichier donne
sds getNom(int id, Capsule liste_base_texte)
{
	int test_id;
	
	if(id != -1) {
		char buf[300];
		for(int i = 0; i < nombreDescripteurs(liste_base_texte); i++)
		{
			// dans l optique ou dans le fichier liste_base_texte, la relation identifiant nom
			// est ecrite tel que "{identifiant:nom}" sans aucun autre caractere
			// (puisque le fichier n est a la base pas un fichiers de descripteurs, chaque
			// donnee traitant un fichier different seront separees par des accolade pour pouvoir
			// se servir du type capsule)
			sscanf(liste_base_texte.descripteurs[i], "%d:%300s", &test_id, buf);
			if(id == test_id)
				return sdsnew(buf);
		}
	}

	return NULL;
}

// renvoie la liste des mots retenus dans un fichier depuis un descripteur
sds listeMots(sds descripteur)
{
	int nbMotsRetenus;
	char * ptr;
	char mot[35];
	sds listeMots = sdsempty();
	
	sscanf(descripteur, "[%*d;%*d;%d]", &nbMotsRetenus);
	
	ptr = strchr(descripteur, ']');
	ptr += 2; // on se place sur le premier mot
	
	for(int i = 0; i < nbMotsRetenus; i++)
	{
		sscanf(ptr, "%32[^:]", mot);
		listeMots = sdscat(listeMots, mot);
		ptr = strchr(ptr, ';');
		ptr++;
	}
	
	return listeMots;
}

// lit la table d index et retourne les identifiants des fichiers contenant le plus les mots
void lire_index(Capsule table_index, sds motscles, int id[], int nb_res)
{
	// format : mot1;fichier1:nbocc;fichier2...
	char * ptr_mc; // pointeur de parcours des mots cles
	char * ptr_index; // pointeur de lecture de la table d index
	char mot[35], comp[35];
	int identifiant, occurence, compteur;
	int occurences[nb_res];
	TabOccurences * listeOccurences;
	TabOccurences * courant;
	
	listeOccurences = (TabOccurences*) malloc(sizeof(TabOccurences));
	listeOccurences->precedent = NULL;
	listeOccurences->identifiant = -1;
	listeOccurences->occurences = -1;
	listeOccurences->suivant = NULL;
	
	// parcours des mots cles
	ptr_mc = motscles;
	ptr_index = "";
	while(strlen(ptr_mc) != 0)
	{
		sscanf(ptr_mc, "%32s", mot);
		
		// on recupere le mot de la table d index
		for(int i = 0; i < nombreDescripteurs(table_index); i++)
		{
			sscanf(table_index.descripteurs[i], "%32[^;]", comp);
			if(strcmp(mot, comp) == 0)
			{
				ptr_index = strchr(table_index.descripteurs[i], ';');
				ptr_index++;
				break;
			}
		}
		
		// pour chaque mot cle, on recupere son nombre d occurence dans chaque fichier
		// on additionne les occurences a chaque fois
		courant = listeOccurences;
		while(strlen(ptr_index) != 0)
		{
			sscanf(ptr_index, "%d:%d", &identifiant, &occurence);
			if(courant->identifiant == -1)
			{
				courant->identifiant = identifiant;
				courant->occurences = occurence;
			}
			else
			{
				while(courant)//while(1) securise
				{
					if(courant->identifiant == identifiant)
					{
						courant->occurences += occurence;
						/*if(courant->suivant == NULL)
						{
							courant->suivant = (TabOccurences*) malloc(sizeof(TabOccurences));
							courant->suivant->precedent = courant;
							courant->suivant->suivant = NULL;
							courant->suivant->identifiant = -2;
						} Pas de sens*/
						break;
					}
					if(courant->suivant == NULL)
					{
						courant->suivant = (TabOccurences*) malloc(sizeof(TabOccurences));
						courant->suivant->precedent = courant;
						courant->suivant->suivant = NULL;
						courant = courant->suivant;
						courant->identifiant = identifiant;
						courant->occurences = occurence;
						courant->suivant = NULL;
						break;
					}
					courant = courant->suivant;
				}
			}
			ptr_index = strchr(ptr_index, ';');
			ptr_index++;
		}
		
		ptr_mc = strchr(ptr_mc, ' ');
		ptr_mc++;
	}
	
	// on recupere les identifiants avec un meilleur score
	compteur = 0;
	courant = listeOccurences;
	//printf("%p : %d : %d : %p\n", courant->precedent, courant->identifiant, courant->occurences, courant->suivant);
	while(courant != NULL)
	{
		if(compteur < nb_res)
		{
			id[compteur] = courant->identifiant;
			occurences[compteur] = courant->occurences;
			compteur++;
		}
		else
		{
			for(int i = 0; i < nb_res; i++)
			{
				if(courant->occurences > occurences[i])
				{
					id[compteur] = courant->identifiant;
					occurences[compteur] = courant->occurences;
					break;
				}
			}
		}
		if(courant->precedent)
			free(courant->precedent);//et si le courant n'a pas de precedent ?
		if(courant->suivant == NULL)
		{
			free(courant);
			break;
		}
		courant = courant->suivant;
	}
}

void recherche_texte_motscles(const sds motscles, Capsule liste_base_texte, Capsule table_index_texte, int nb_res, sds resultats[])
{
	int id[nb_res];
	
	for(int i = 0; i < nb_res; i++)
	{
		id[i] = -1;
	}
	
	lire_index(table_index_texte, motscles, id, nb_res);
	
	int i = 0;
	//for(int i = 0; i < nb_res; i++)
	while(id[i] != -1 && i < nb_res){
		resultats[i] = getNom(id[i], liste_base_texte);
		//fprintf(stderr, "%d:%s\n", id[i], resultats[i]);
		i++;
	}
}

void recherche_texte_fichier(const sds descripteur, Capsule liste_base_texte, Capsule table_index_texte, int nb_res, sds resultats[])
{
	sds motscles = listeMots(descripteur);
	
	recherche_texte_motscles(motscles, liste_base_texte, table_index_texte, nb_res, resultats);
	
	sdsfree(motscles);
}
