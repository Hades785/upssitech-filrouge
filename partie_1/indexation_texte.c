#include "indexation_texte.h"
#include <ctype.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>



typedef struct
{
	unsigned int nbEle;
	unsigned int size;
	sds * mots;
	unsigned int * nbOcc;
}TabOcc;



void afficher_tabocc(TabOcc t)
{
	for (unsigned int i = 0 ; i < t.nbEle ; i++)
	{
		printf("%s : %u | ", t.mots[i], t.nbOcc[i]);
	}
}



sds indexation_texte(const sds accesFichier,int valId)
{
	// Cette fonction est chargée de créer le sds décrivant le fichier donné en paramètre.
	// Le descripteur ainsi créer est de la forme :
	// [valeur;valeur;valeur][mot :occurence;...;motN :occurenceN]
	// (Les 3 premières valeurs sont : id ; nombreDeMotsAuTotal ; nombreDeMotsRetenus)
	
	FILE* fichier = NULL;

    fichier = fopen(accesFichier, "r");
	
	printf("début de la fonction"); getchar();
	
	if (fichier != NULL)
	{
		sds motActuel;
		sds chaineTotale = sdsnew("[");
		int carActuel = 0;
        int nbDeCar = 0;
		int nbDeMots = 0;
		int nbDeMotsRetenus = 0;
		
		TabOcc tabocc;
		
		
		
		
		
		printf("Si on a pu ouvrir le fichier"); getchar();
		
		
		
		
		
		
		
		char tabMots[100];
		do
		{
			afficher_tabocc(tabocc);
			
			tabMots[0] = fgetc(fichier); // On lit le caractère
			
			if((tabMots[0] >= 'a' && tabMots[0] <= 'z') || (tabMots[0] >= 'A' && tabMots[0] <= 'Z')) // Si c'est une lettre
			{
				fscanf(fichier,"%98[äÄëËïÏöÖüÜÿâÂêÊîÎôÔûÛàÀèÈìÌòÒùÙéçÇæÆœŒa-zA-Z]", &tabMots[1]);
				motActuel = sdsnew(tabMots);
				
				// Traitement :
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
							
							printf("La 1ère lettre est la même"); getchar();
							
							// On vérifie que les lettres suivantes sont les mêmes
							while(motPresent && (i < (int)sdslen(motActuel)) && (cpt+i < (int)sdslen(chaineTotale)))
							{
								//printf("motActuel[i] : %c / chaineTotale[cpt+i] : %c", motActuel[i], chaineTotale[cpt+i]); getchar();
								
								if(motActuel[i] != chaineTotale[cpt+i])
									motPresent = 0;
								
								i++;
							}
							
							// On vérifie que le mot détecté n'est pas le début
							// d'un autre plus long. Ex : robot / robotique
							if(cpt+i+1 < (int)sdslen(chaineTotale))
							{
								if(chaineTotale[cpt+i] != ' ')
									motPresent = 0;
							}
						}
						
						cpt++;
					}
					
					
					if(motPresent)
					{
						printf("Le mot lu est déjà dans le descripteur"); getchar();
						
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
							nbOccurence += ((int)(chaineTotale[cpt-1-i] - '0')) * pow(10,i);
						}
						
						nbOccurence++; // On incrémente le nombre d'occurence du mot
						
						
						
						if(ilsSontTousANeuf) // On doit mettre un chiffre en plus (Ex : 99 -> 100)
						{
							sds newS = sdsempty();
							newS = sdscatsds(newS, chaineTotale);
							newS = sdscat(newS, " ");
							
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
				sdsfree(motActuel);
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
		
		return(s1);*/
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
}