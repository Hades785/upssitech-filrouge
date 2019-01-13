#include <stdio.h>
#include "indexation_texte.h"
#include "sds.h"

int main(){
	TabOcc t = newTabOcc();
	ajout_mot(&t,sdsnew("bonjour"));
	ajout_mot(&t,sdsnew("comment"));
	ajout_mot(&t,sdsnew("sava"));
	ajout_mot(&t,sdsnew("aujourdui"));
	ajout_mot(&t,sdsnew("fzefzref"));
	ajout_mot(&t,sdsnew("fzefzefzef"));
	ajout_mot(&t,sdsnew("efsefzef"));
	ajout_mot(&t,sdsnew("efzrejfo"));
	ajout_mot(&t,sdsnew("kjefozkf"));
	ajout_mot(&t,sdsnew("efozijefoz"));
	ajout_mot(&t,sdsnew("oezijfoz"));
	ajout_mot(&t,sdsnew("comment"));
	ajout_mot(&t,sdsnew("bonjour"));
	ajout_mot(&t,sdsnew("efozijefoz"));
	ajout_mot(&t,sdsnew("efozijefoz"));
	ajout_mot(&t,sdsnew("efozijefoz"));
	afficher_tabocc(t);
	printf("\n");
	triTabOcc(&t);
	afficher_tabocc(t);
}