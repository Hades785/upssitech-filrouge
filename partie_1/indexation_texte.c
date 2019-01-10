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

void ajout_mot(TabOcc *t, sds mot)
{
	long pos = position_mot_dans_tabocc(*t,mot);
	
	if(pos == -1)
	{
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
		t->nbOcc[t->nbEle] = 1;
		t->nbEle++;
	}
	else
	{
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
			
			if((tabMots[0] >= 'a' && tabMots[0] <= 'z') || (tabMots[0] >= 'A' && tabMots[0] <= 'Z')) // Si c'est une lettre
			{
				fscanf(fichier,"%30[äÄëËïÏöÖüÜÿâÂêÊîÎôÔûÛàÀèÈìÌòÒùÙéçÇæÆœŒa-zA-Z]", &tabMots[1]);
				motActuel = sdsnew(tabMots);
				
				if(sdslen(motActuel)>=TAILLE_MIN_MOT)
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
					/*	
					case ' ':
						printf("le char est un espace"); getchar();
						break;
						
					default:
						printf("le char n'est pas une lettre:%X",tabMots[0]); getchar();
						break;
					*/
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

/*TabOcc tri_occurence(TabOcc tab)
{
	TabOcc tab = newTabOcc();
	for()
}

sds renvoie_descripteur(TabOcc tabTrié)
{
	
}


sds indexation_texte(const sds accesFichier,int valId)
{
	// Cette fonction est chargée de créer le sds décrivant le fichier donné en paramètre.
	// Le descripteur ainsi créer est de la forme :
	// [valeur;valeur;valeur][mot :occurence;...;motN :occurenceN]
	// (Les 3 premières valeurs sont : id ; nombreDeMotsAuTotal ; nombreDeMotsRetenus)
	//[id;nbMotsTotal;nbMotsRetenus][mot1:occ1;mot2:occ2;...]
	
	FILE* fichier;

    fichier = fopen(accesFichier, "r");
	
	printf("début de la fonction"); getchar();
	
	if (fichier != NULL)
	{
		sds motActuel;
		sds chaineTotale = sdsnew("[");
		int carActuel = 0;
        int nbDeCar = 0;
		int nbDeMots = 0;
		//int nbDeMotsRetenus = 0;
		
		TabOcc tabocc = newTabOcc();
		
		
		
		
		
		printf("Si on a pu ouvrir le fichier"); getchar();
		
		
		
		
		
		
		
		char tabMots[TAILLE_MAX_MOT];//tableau de char
		do
		{
			afficher_tabocc(tabocc);
			
			tabMots[0] = fgetc(fichier); // On lit le caractère
			
			if((tabMots[0] >= 'a' && tabMots[0] <= 'z') || (tabMots[0] >= 'A' && tabMots[0] <= 'Z')) // Si c'est une lettre
			{
				fscanf(fichier,"%30[äÄëËïÏöÖüÜÿâÂêÊîÎôÔûÛàÀèÈìÌòÒùÙéçÇæÆœŒa-zA-Z]", &tabMots[1]);
				motActuel = sdsnew(tabMots);
				//petite simplification
				/*int num = position_mot_dans_tabocc(tabocc, motActuel);
				
				if(num == -1)
				{
					ajout_mot(&tabocc, motActuel);
					nbDeMotsRetenus++;
				}
				else
				{
					tabocc.nbOcc[i]++;
				}/////
				if(sdslen(motActuel)>=TAILLE_MIN_MOT)
					ajout_mot(&tabocc, motActuel);
				nbDeMots++;
				//sdsfree(motActuel);//surtout pas, il est gardé par tabocc
			}
			else
			{
				switch(tabMots[0])
				{
					case '<':
						printf("balise");getchar();
						fscanf(fichier, "%*[^>]");
						fgetc(fichier);
						break;
						
					case ' ':
						printf("le char est un espace"); getchar();
						break;
						
					default:
						printf("le char n'est pas une lettre:%X",tabMots[0]); getchar();
						break;
				}
			}
		}
		while (tabMots[0] != EOF); // fin de fichier
		
		fclose(fichier);
		
		
		/*
		sds s1 = sdsnew("[");
		s1 = sdscatprintf(s, "%d;%d;%d]", valId, nbDeMots, nbDeMotsRetenus);
		
		s1 = sdscatsds(s1, chaineTotale);
		
		// On libère l'espace mémoire :
		sdsfree(motActuel);
		sdsfree(chaineTotale);
		
		return(s1);*/
		
		
		
		
		/*
		// On lit le fichier
		do
        {
            carActuel = fgetc(fichier); // On lit le caractère
			
			
			
			if(carActuel == '<') // On entre dans une balise
			{
				while((carActuel != '>') && (carActuel != EOF))
				{
					carActuel = fgetc(fichier);
				}
				
				if(carActuel != EOF)
					carActuel = fgetc(fichier);
				else
					break;
				
				motActuel = sdsempty();
			}
			
			
			
			if(isalpha(carActuel)) // Si c'est une lettre
			{
				motActuel = sdscatprintf(motActuel, "%c", carActuel);
			}
			else
			{
				if((int)sdslen(motActuel) > 2) // Si le mot actuel fait au moins 3 lettres
				{
					int motPresent = 0;
					int cpt = 1;
					
					
					
					while(!motPresent && (cpt < (int)sdslen(chaineTotale)))
					{
						// Si la 1ère lettre est la même, et que c'est aussi la 1ère lettre
						// du mot dans chaineTotale. Pour éviter des mots avec des lettres en
						// plus au début. Ex : fondé / infondé
						if((chaineTotale[cpt] == motActuel[0]) && !isalpha(chaineTotale[cpt-1]))
						{
							motPresent = 1;
							int i = 0;
							
							// On vérifie que les lettres suivantes sont les mêmes
							while(motPresent && (i < (int)sdslen(motActuel)) && (cpt+i < (int)sdslen(chaineTotale)))
							{
								i++;
								
								if(motActuel[i] != chaineTotale[cpt+i])
									motPresent = 0;
							}
							
							// On vérifie que le mot détecté n'est pas le début
							// d'un autre plus long. Ex : robot / robotique
							if(cpt+i+1 < (int)sdslen(chaineTotale))
							{
								if(chaineTotale[cpt+i+1] != ' ')
									motPresent = 0;
							}
						}
						
						cpt++;
					}
					
					
					
					if(motPresent)
					{
						int nbChiffre = 0;
						int nbOccurence = 0;
						int ilsSontTousANeuf = 1;
						
						// On se place au début du nombre d'occurence
						cpt += (int)sdslen(motActuel) + 1;
						
						while(isdigit(chaineTotale[cpt]))
						{
							if(chaineTotale[cpt] != '9')
								ilsSontTousANeuf = 0;
							
							cpt++;
							nbChiffre++; // On compte le nombre de chiffres
						}
						
						for(int i = 0 ; i < nbChiffre ; i++) // On traduit le string en int
						{
							nbOccurence += ((int)(chaineTotale[cpt-1-i] - '0')) * math.pow(10,i);
						}
						
						nbOccurence++; // On incrémente le nombre d'occurence du mot
						
						
						
						if(ilsSontTousANeuf) // On doit mettre un chiffre en plus (Ex : 99 -> 100)
						{
							sds newS = sdsempty();
							newS = sdscatsds(newS, chaineTotale);
							newS = sdscat(newS, ' ');
							
							for(int i = cpt+1 ; i < (int)sdslen(newS) ; i++) // On décale d'un rang à droite
							{
								newS[i] = chaineTotale[i-1];
							}
							
							chaineTotale = newS;
							// On est passé par ex : de ...mot2 :99;mot3... à ...mot2 :99;;mot3...
							// A partir de ';', on a tout décalé à droite d'un rang
							
							
							chaineTotale[cpt-nbChiffre] = '1';
							
							for(int i = 1 ; i <= nbChiffre ; i++)
							{
								chaineTotale[cpt-nbChiffre+i] = '0';
							}
							// Finalement, on passe par ex : de ...mot2 :99;;mot3... à ...mot2 :100;mot3...
						}
						else
						{
							for(int i = 0 ; i < nbChiffre ; i++) // On insère le int dans le sds
							{
								int k = nbOccurence%10;
								nbOccurence -= k;
								nbOccurence /= 10;
								chaineTotale[cpt-1-i] = k + '0';
							}
						}
					}
					else
					{
						chaineTotale = sdscatsds(chaineTotale, motActuel);
						chaineTotale = sdscat(chaineTotale, " :1;");
						nbDeMotsRetenus++;
					}
				}
				
				nbDeMots++;
				
				motActuel = sdsempty();
			}
        }
		while (carActuel != EOF); // fin de fichier
		
        fclose(fichier);
		
		
		
		if((int)sdslen(chaineTotale) > 1) // Si on a trouvé au moins 1 mot
			chaineTotale[(int)sdslen(chaineTotale)-1] = ']'; // On remplace le dernier ';' par ']'
		else
			chaineTotale = sdscat(chaineTotale, ']');
		
		
		sds s1 = sdsnew("[");
		s1 = sdscatprintf(s, "%d;%d;%d]", valId, nbDeMots, nbDeMotsRetenus);
		
		s1 = sdscatsds(s1, chaineTotale);
		
		// On libère l'espace mémoire :
		sdsfree(motActuel);
		sdsfree(chaineTotale);
		
		return(s1);////
    }
	else
	{
		printf("Impossible d'ouvrir le fichier");
		
		sds retour = sdsempty();
		retour = sdscat(retour, "[ERREUR]");
		return(retour);
	}
}



void gestion_descripteurs()
{
	// A faire plus tard...
}*/