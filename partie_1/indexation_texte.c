#include "indexation_texte.h"
#include <ctype.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "constantes.h"
#include <assert.h>

void afficher_tabocc(TabOcc t)
{
	for (unsigned int i = 0 ; i < t.nbEle ; i++)
	{
		printf("%s : %u | ", t.mots[i], t.nbOcc[i]);
	}
	printf("\n");
}

long position_mot_dans_tabocc(TabOcc t, sds mot)
{
	for(unsigned int i = 0;i < t.nbEle;i++){
		if(strcmp(t.mots[i], mot) == 0)
			return i;
	}
	return -1;
}

void addMotStrict(TabOcc *t, sds mot,unsigned int nbOccur){
	if(t->nbEle == t->size)
	{
		sds * newTabS = malloc(sizeof(sds)*(t->size+20));
		unsigned int * newTabU = malloc(sizeof(unsigned int)*(t->size+20));
		assert(newTabS != NULL && newTabU != NULL);
		memcpy(newTabS,t->mots,sizeof(sds)*t->size);
		memcpy(newTabU,t->nbOcc,sizeof(unsigned int)*t->size);
		t->size+=20;
		free(t->mots);
		free(t->nbOcc);
		t->mots = newTabS;
		t->nbOcc = newTabU;
	}
	t->mots[t->nbEle] = mot;
	t->nbOcc[t->nbEle] = nbOccur;
	t->nbEle++;
}

void ajout_mot(TabOcc *t, sds mot)
{
	long pos = position_mot_dans_tabocc(*t,mot);
	if(pos == -1)
		addMotStrict(t,mot,1);
	else{
		t->nbOcc[pos]++;
		sdsfree(mot);
	}
}

TabOcc newTabOcc()
{
	TabOcc t;
	t.nbEle = 0;
	t.size = 20;
	t.mots = malloc(sizeof(sds)*20);
	t.nbOcc = malloc(sizeof(unsigned int)*20);
	assert(t.mots != NULL && t.nbOcc != NULL);
	return t;
}

unsigned int totalOccurences(TabOcc t)
{
	unsigned int tt = 0;
	for(unsigned int i = 0;i < t.nbEle;i++)
	{
		tt+=t.nbOcc[i];
	}
	return tt;
}

void triTabOcc(TabOcc * t){
	sds temps;
	unsigned int tempu;
	for(unsigned int i = 1;i < t->nbEle;i++){
		for(unsigned int u = 0;u < (t->nbEle-i);u++){
			if(t->nbOcc[u] < t->nbOcc[u+1]){
				temps = t->mots[u];
				tempu = t->nbOcc[u];
				t->mots[u] = t->mots[u+1];
				t->nbOcc[u] = t->nbOcc[u+1];
				t->mots[u+1] = temps;
				t->nbOcc[u+1] = tempu;
			}
		}
	}
}

void freeTabOcc(TabOcc * t)
{
	free(t->mots);
	free(t->nbOcc);
}

unsigned char test_alpha(char lettre)
{
	if((lettre >= 'a' && lettre <= 'z') || (lettre >= 'A' && lettre <= 'Z')) // Si c'est une lettre "classique"
		return 1;
	else
	{
		char ch[2];
		ch[0] = lettre;ch[1] = 0;
		
		if(strstr(accents, ch) != NULL) // Si c'est une lettre accentuée
			return 0;
		else
			return 2;
	}
}

TabOcc lecture_fichier(const sds accesFichier, unsigned int * nbMotsTotal)
{
	FILE* fichier;

    fichier = fopen(accesFichier, "r");
	
	if (fichier != NULL)
	{
		sds motActuel;
		TabOcc tabocc = newTabOcc();
		
		char tabMots[TAILLE_MAX_MOT];//tableau de char
		
		do // Tant qu'on est pas arrivé à la fin du fichier
		{
			tabMots[0] = fgetc(fichier); // On lit le caractère
			
			if(test_alpha(tabMots[0]) != 2) // Si c'est une lettre
			{
				fscanf(fichier,"%30[äÄëËïÏöÖüÜÿâÂêÊîÎôÔûÛàÀèÈìÌòÒùÙéçÇæÆœŒ'a-zA-Z]", &tabMots[test_alpha(tabMots[0])]);
				
				if(tabMots[1] == '\'')
					motActuel = sdsnew(&tabMots[2]);
				else
					motActuel = sdsnew(tabMots);
				
				
				if(sdslen(motActuel)>=TAILLE_MIN_MOT && strstr(exclusions,motActuel) == NULL)
					ajout_mot(&tabocc, motActuel);
				else
					sdsfree(motActuel);
				
				nbMotsTotal++;
			}
			else
			{
				switch(tabMots[0])
				{
					case '<':
						fscanf(fichier, "%*[^>]"); // On va jusqu'à la fin de la balise
						fgetc(fichier);
						break;
				}
			}
		}
		while (tabMots[0] != EOF); // fin de fichier
		fclose(fichier);
		return tabocc;
    }
	else
	{
		printf("On a pas pu ouvrir le fichier"); getchar();
		
		TabOcc tabocc = newTabOcc();
		return tabocc;
	}
}

TabOcc tri_occurence(TabOcc tab)
{
	triTabOcc(&tab);
	TabOcc resp = newTabOcc();
	
	for(unsigned int i = 0;i < NB_RESULTAT_RECHERCHE;i++){
		addMotStrict(&resp,tab.mots[i],tab.nbOcc[i]);
	}
	
	return resp;
}

sds renvoie_descripteur(TabOcc tabTrie,int id,unsigned int nbMotsTotal)
{
	sds s = sdsempty();
	//unsigned int nbMotsRetenus = totalOccurences(tabTrie);

	s = sdscatprintf(s,"[%d;%u;%u][",id,nbMotsTotal,tabTrie.nbEle);

	for(unsigned int i = 0;i < tabTrie.nbEle;i++)
	{
		s = sdscatprintf(s,"%s:%u",tabTrie.mots[i],tabTrie.nbOcc[i]);

		if(i < tabTrie.nbEle-1)
			s = sdscatprintf(s,";");
	}
	
	s = sdscatprintf(s,"]");
	
	return s;
}

sds indexation_texte(const sds accesFichier,int valId)
{
	unsigned int nbMotsTotal;
	TabOcc fichier = lecture_fichier(accesFichier, &nbMotsTotal);
	TabOcc desc = tri_occurence(fichier);
	freeTabOcc(&fichier);
	sds resp = renvoie_descripteur(desc,valId,nbMotsTotal);
	freeTabOcc(&desc);
	return resp;
}