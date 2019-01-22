#include "indexation_texte.h"
//#include <ctype.h>
//#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "constantes.h"
#include <assert.h>
#include "config_reader.h"

const char exclusions[] = "les des par une son que dans est ces ses pour sont faire pas Ces Sat Sep GMT ainsi sera Pour où afin même Cette vers vient qui aux cette Les";

//const char accents[] = "äÄëËïÏöÖüÜÿâÂêÊîÎôÔûÛàÀèÈìÌòÒùÙéçÇæÆœŒ";

void afficher_tabocc(TabOcc t)
{
	for (unsigned int i = 0 ; i < t.nbEle ; i++)
	{
		printf("%s : %u | ", t.mots[i], t.nbOcc[i]);
	}
	printf("\n");
}

long position_mot_dans_tabocc(TabOcc t, const char * mot)
{
	for(unsigned int i = 0;i < t.nbEle;i++){
		if(strcmp(t.mots[i], mot) == 0)
			return i;
	}
	return -1;
}

void addMotStrict(TabOcc *t,const char * mot,unsigned int nbOccur){
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
	t->mots[t->nbEle] = sdsnew(mot);
	t->nbOcc[t->nbEle] = nbOccur;
	t->nbEle++;
}

void ajout_mot(TabOcc *t, const char * mot)
{
	long pos = position_mot_dans_tabocc(*t,mot);
	if(pos == -1)
		addMotStrict(t,mot,1);
	else
		t->nbOcc[pos]++;
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
	for(unsigned int i = 0;i < t->nbEle;i++){
		sdsfree(t->mots[i]);
	}
	free(t->mots);
	free(t->nbOcc);
}

unsigned char test_alpha(int lettre)
{
	//printf("%c", lettre);
	
	if((lettre >= 'a' && lettre <= 'z') || (lettre >= 'A' && lettre <= 'Z')
		|| (lettre >= 192 && lettre <= 255)) // Si c'est une lettre
	{
		return 1;
	}
	else
	{/*
		char ch[2];
		ch[0] = lettre;
		ch[1] = 0;
		
		if(strstr(accents, ch) != NULL) // Si c'est une lettre accentuée
		{
			printf("trouvé !");
			return 1;
		}
		else*/
			return 0;
	}
}

int suppr_accent_et_maj(int lettre)
{
	if(lettre >= 'a' && lettre <= 'z') return lettre;
	else if(lettre >= 'A' && lettre <= 'Z') return (lettre+32);
	else if(lettre >= 192 && lettre <= 198) return ('a');
	else if(lettre == 199 || lettre == 231) return ('c');
	else if(lettre >= 200 && lettre <= 203) return ('e');
	else if(lettre >= 204 && lettre <= 207) return ('i');
	else if(lettre >= 210 && lettre <= 214) return ('o');
	else if(lettre >= 217 && lettre <= 220) return ('u');
	else if(lettre >= 224 && lettre <= 230) return ('a');
	else if(lettre >= 232 && lettre <= 235) return ('e');
	else if(lettre >= 236 && lettre <= 239) return ('i');
	else if(lettre == 241) return ('n');
	else if(lettre >= 242 && lettre <= 246) return ('o');
	else if(lettre >= 249 && lettre <= 252) return ('u');
	else if(lettre == 60) return ('<');
	else if(lettre == 62) return ('>');
	else return 32;
}


Capsule genere_table(Capsule caps)
{
	/*
	[declaration capsule]
	[declaration confmap]
	[remplissage confmap]
	[transfert map -> caspule]
	[renvoie capsule]
	*/
	
	unsigned char successFlag;
	Capsule cap_retour = newCapsule(&successFlag);
	assert(successFlag != ECHEC);
	ConfMap map_tempo = newConfMap(&successFlag);
	assert(successFlag != ECHEC);
	
	for(unsigned int i = 0 ; i < caps.nbDescripteurs ; i++)
	{
		int id;
		TabOcc tabocc = decode_descripteur(caps.descripteurs[i], &id);
		
		for(unsigned int ct = 0 ; ct < tabocc.nbEle ; ct++)
		{
			sds s = sdscat(sdsfromlonglong(id),":");
			sds s2 = sdscat(sdsfromlonglong(tabocc.nbOcc[ct]),";");
			s = sdscat(s,s2);
			postValue(&map_tempo, tabocc.mots[ct], s);
			sdsfree(s); sdsfree(s2);
		}
		freeTabOcc(&tabocc);
	}
	
	for(unsigned int i = 0 ; i < map_tempo.keys->nbDescripteurs ; i++)
	{
		sds s = sdscat(sdsdup(map_tempo.keys->descripteurs[i]), ";");
		s = sdscat(s, map_tempo.values->descripteurs[i]);
		addElementCopy(&cap_retour, s);
		sdsfree(s);
	}
	
	freeConfMap(map_tempo);
	
	return cap_retour;
}


TabOcc lecture_fichier(const char * accesFichier, unsigned int * nbMotsTotal,unsigned int tailleMinMot)
{
	FILE* fichier;

    fichier = fopen(accesFichier, "r");
	
	if (fichier != NULL)
	{
		sds motActuel;
		TabOcc tabocc = newTabOcc();
		
		char tabMots[30];//tableau de char
		int lettreInt = 0;
		
		do // Tant qu'on est pas arrivé à la fin du fichier
		{
			lettreInt = fgetc(fichier);
			tabMots[0] = suppr_accent_et_maj(lettreInt);
			
			//printf(" %d/%d ", lettreInt, tabMots[0]);
			
			if(test_alpha(lettreInt) == 1) // Si c'est une lettre
			{
				//fscanf(fichier,"%30[äÄëËïÏöÖüÜÿâÂêÊîÎôÔûÛàÀèÈìÌòÒùÙéçÇæÆœŒ'a-zA-Z]", &tabMots[1]);
				
				int ct = 1;
				while((ct < 30) && test_alpha(lettreInt) == 1)
				{
					lettreInt = fgetc(fichier);
					tabMots[ct] = suppr_accent_et_maj(lettreInt);
					
					if(tabMots[ct] == '<')
					{
						fscanf(fichier, "%*[^>]"); // On va jusqu'à la fin de la balise
						fgetc(fichier);
						break;
					}
					
					ct++;
				}
				tabMots[ct] = 0;
				
				
				if(tabMots[1] == '\'')
					motActuel = sdsnew(&tabMots[2]);
				else
					motActuel = sdsnew(tabMots);
				
				
				if((int)sdslen(motActuel)-1>=tailleMinMot && strstr(exclusions,motActuel) == NULL)
					ajout_mot(&tabocc, motActuel);
				sdsfree(motActuel);
				
				(*nbMotsTotal)++;
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
		while (lettreInt != EOF); // fin de fichier
		fclose(fichier);
		return tabocc;
    }
	else
	{
		printf("Impossible d'ouvrir le fichier"); getchar();
		
		TabOcc tabocc = newTabOcc();
		return tabocc;
	}
}

TabOcc tri_occurence(TabOcc tab,unsigned int nbMotsMax)
{
	triTabOcc(&tab);
	TabOcc resp = newTabOcc();
	
	for(unsigned int i = 0;i < nbMotsMax && i < tab.nbEle;i++){
		addMotStrict(&resp,tab.mots[i],tab.nbOcc[i]);
	}
	
	return resp;
}

sds renvoie_descripteur(TabOcc tabTrie,int id,unsigned int nbMotsTotal)
{
	sds s = sdsempty();
	//unsigned int nbMotsRetenus = totalOccurences(tabTrie);
	//[id;nbMotsTotal;nbMotsRetenus][mot1:occ1;mot2:occ2;...]
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

TabOcc decode_descripteur(const char * descripteur, int * idFichier){
	//[id;nbMotsTotal;nbMotsRetenus][mot1:occ1;mot2:occ2;...]
	TabOcc tab = newTabOcc();
	unsigned int nbMotsRetenus;
	sscanf(descripteur,"[%d;%*u;%u",idFichier,&nbMotsRetenus);
	char * debutNb = strchr(descripteur+1,'[');//+1 pour eviter celui de l'en tete
	assert(debutNb != NULL);
	char mot[30];
	unsigned int nbOcc;
	for(unsigned int i = 0;i < nbMotsRetenus;i++){
		debutNb++;
		sscanf(debutNb,"%30[^ :] :%u",mot,&nbOcc);
		addMotStrict(&tab,mot,nbOcc);
		if(i < nbMotsRetenus-1){
			debutNb = strchr(debutNb,';');
			assert(debutNb != NULL);
		}
	}
	return tab;
}

sds indexation_texte(const char * accesFichier,int valId,unsigned int nbMotsMax,unsigned int tailleMinMot)
{
	unsigned int nbMotsTotal = 0;
	TabOcc fichier = lecture_fichier(accesFichier, &nbMotsTotal, tailleMinMot);
	TabOcc desc = tri_occurence(fichier,nbMotsMax);
	freeTabOcc(&fichier);
	sds resp = renvoie_descripteur(desc,valId,nbMotsTotal);
	freeTabOcc(&desc);
	return resp;
}