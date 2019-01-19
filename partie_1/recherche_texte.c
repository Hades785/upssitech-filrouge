#include "recherche_texte.h"
#include "constantes.h"
#include <string.h>

// donne le nom d un fichier par rapport a son identidiant dans le fichier donne
sds getNom(int id, sds liste_base_texte)
{
	unsigned char flag;
	Capsule capsule;
	int test_id;
	sds nom;
	
	capsule = loadDescripteurs(&flag, liste_base_texte);
	nom = sdsempty();
	
	for(int i = 0; i < nombreDescripteurs(capsule); i++)
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

// renvoie la liste des mots retenus dans un fichier depuis un descripteur
void listeMots(sds descripteur, sds * listeMots)
{
	int nbMotsRetenus;
	char * ptr;
	sds mot;
	
	sscanf(descripteur, "[%*d;%*d;%d]", &nbMotsRetenus);
	
	ptr = strchr(descripteur, ']');
	ptr += 2; // on se place sur le premier mot
	mot = sdsempty();
	
	for(int i = 0; i < nbMotsRetenus; i++)
	{
		sscanf(ptr, "%[^:%*d]", mot);
		listeMots[i] = sdsnew(mot);
		if (i < nbMotsRetenus-1)
		{
			ptr = strchr(ptr, ';');
			ptr++;
		}
	}
	sdsfree(mot);
}

void freeListeMots(int nbMots, sds * listeMots)
{
	for(int i = 0; i < nbMots; i++)
	{
		sdsfree(listeMots[i]);
	}
}

// prend deux liste de mots et leur taille et les compare
// plus le nombre renvoyé est grand, plus les fichiers sont similaires.
int motscmp(const sds * liste1, const sds * liste2, int taille1, int taille2)
{
	int compteur = 0; // on compte le nombre de mots identiques
	
	for(int i = 0; i < taille1; i++)
	{
		for(int j = 0; j < taille2; j++)
		{
			if(strcmp(liste1[i], liste2[j]) == 0)
			{
				compteur++;
				break;
			}
		}
	}
	
	return compteur;
}

// lit la table d index et retourne les identifiants des fichiers contenant le plus les mots
int* lire_index(Capsule table_index, sds motscles, int id[])
{
	// format : mot1;fichier1:nbocc;fichier2...
	char * ptr_mc; // pointeur de parcours des mots cles
	char * ptr_index; // pointeur de lecture de la table d index
	sds mot, comp;
	int identifiant, occurence;
	
	mot = sdsempty();
	comp = sdsempty();
	
	// parcours des mots cles
	ptr_mc = motscles;
	while(strlen(ptr_mc) != 0)
	{
		sscanf(ptr_mc, "%s", mot);
		
		for(int i = 0; i < nombreDescripteurs(table_index); i++)
		{
			sscanf(table_index.descripteurs[i], "%[^;]", comp);
			printf("%s\n", comp);
			if(strcmp(mot, comp) == 0)
			{
				ptr_index = strchr(table_index.descripteurs[i], ';');
				break;
			}
		}
		while(strlen(ptr_index) != 0)
		{
			sscanf(ptr_index, "%d:%d", &identifiant, &occurence);
			// TODO
			
			ptr_index = strchr(ptr_index, ';');
			ptr_index++;
		 }
		
		ptr_mc = strchr(ptr_mc, ' ');
		ptr_mc++;
	}
	
	sdsfree(mot);
	sdsfree(comp);
	
	return id;
}

void recherche_texte_motscles(const sds motscles, const sds liste_base_texte, const sds table_index_texte)
{
	sds resultats[NB_RESULTAT_RECHERCHE]; // resultats sous forme de chemin d acces
	int id[NB_RESULTAT_RECHERCHE];
	unsigned char flag;
	Capsule capsule = loadDescripteurs(&flag, liste_base_texte);
	//id = lire_index(table_index_texte, motscles);
	
	for(int i = 0; i < NB_RESULTAT_RECHERCHE; i++)
	{
		resultats[i] = getNom(id[i], liste_base_texte);
		printf("%s\n", resultats[i]);
	}
	
	freeCapsule(capsule);
}

// Pour le moment, cette fonction recherche un fichier identique a celui passe en parametre
void recherche_texte_fichier(const sds fichier, const sds liste_base_texte, const sds fichierDescripteurs)
{
	// format d un descripteur
	// [id;nombreDeMotsAuTotal;nombreDeMotsRetenus][mot:occurence;mot2:occurence2]
	
	sds descripteur; // le descripteur du fichier a rechercher
	sds resultats[NB_RESULTAT_RECHERCHE];
	unsigned char flag;
	Capsule capsule;
	int id;
	// variables utilisees pour comparer les descripteurs
	int  nbMotsRetenusF, nbMotsRetenusC, nbMotsRetenusR;
	
	//descripteur = indexation_texte(fichier);
	descripteur = sdsnew("[18;6;2][nununu :34;tin :23]");
	capsule = loadDescripteurs(&flag, fichierDescripteurs);
	//printf("%d\n", flag);
	sscanf(descripteur, "[%*d;%*d;%d]", &nbMotsRetenusF);
	
	// liste des mots pour chaque descripteur
	// sds listeMotsF[nbMotsRetenusF];
	sds * listeMotsF = (sds*) malloc(sizeof(sds)*nbMotsRetenusF);
	listeMots(descripteur, listeMotsF);
	
	sds * listeMotsC;
	sds * listeMotsR;
	for(int i = 0; i < nombreDescripteurs(capsule); i++)
	{
		// Les premiers descripteurs trouves seront toujours enregistrees
		// dans le tableau de resultats
		if(i < NB_RESULTAT_RECHERCHE)
		{
			resultats[i] = capsule.descripteurs[i];
		}
		// On compare la similitude du descripteur courant au fichier recherche
		// et la similitude des resultats avec le fichier recherche
		else
		{
			sscanf(capsule.descripteurs[i], "[%*d;%*d;%d]", &nbMotsRetenusC);
			listeMotsC = (sds*) malloc(sizeof(sds)*nbMotsRetenusC);
			listeMots(capsule.descripteurs[i], listeMotsC);
			// parcours des resultats pour les comparer au descripteur courant dans la
			// capsule
			for(int j = 0; j < NB_RESULTAT_RECHERCHE; j++)
			{
				sscanf(resultats[j], "[%*d;%*d;%d]", &nbMotsRetenusR);
				listeMotsR = (sds*) malloc(sizeof(sds)*nbMotsRetenusR);
				listeMots(resultats[j], listeMotsR);
				if (motscmp(listeMotsC, listeMotsF, nbMotsRetenusC, nbMotsRetenusF) > motscmp(listeMotsR, listeMotsF, nbMotsRetenusR, nbMotsRetenusF))
				{
					resultats[j] = capsule.descripteurs[i]; // a ameliorer, peut supprimer un resultat plus pertinent qu un autre
					break;
				}
				freeListeMots(nbMotsRetenusR, listeMotsR);
				free(listeMotsR);
			}
			freeListeMots(nbMotsRetenusC, listeMotsC);
			free(listeMotsC);
		}
	}
	freeListeMots(nbMotsRetenusF, listeMotsF);
	free(listeMotsF);
	
	// Le tableau des resultats contients les descripteurs des fichiers les plus
	// similaires au fichiers recherche.
	// Cette boucle sert a passer des descripteurs au nom des fichiers
	for(int i = 0; i < NB_RESULTAT_RECHERCHE; i++)
	{
		sscanf(resultats[i], "[%d", &id);
		resultats[i] = getNom(id, liste_base_texte);
		printf("%s\n", resultats[i]);
		sdsfree(resultats[i]);
	}
	
	freeCapsule(capsule);
	sdsfree(descripteur);
}