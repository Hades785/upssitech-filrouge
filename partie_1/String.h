typedef struct{
	int tailleStr;
	char * chaine;
}String;

#define REUSSITE 0
#define ECHEC 1

String newString(int taille);
int tailleMaxString(String str);
int agrandirString(String * str,int nbPlus);//nbPlus = le nombre de cases supplementaires
void reduireString(String * str,int nbMoins);//nbMoins = le nombre de cases a enlever
