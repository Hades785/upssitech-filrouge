#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>

ConfMap defaultConfMap(){
	unsigned char flag;
	ConfMap map = newConfMap(&flag);
	assert(flag != ECHEC);
	/*flag = addValue(&map,"chemin_bdd","");
	assert(flag != ECHEC);*/
	flag = addValueLong(&map,"nb_res_image",15);
	assert(flag != ECHEC);
	flag = addValueLong(&map,"nb_bits_image",4);
	assert(flag != ECHEC);
}

void config_menu(ConfMap * map){
	printf("\tMENU DE CONFIGURATION\n");
	printf("Configuration de la recherche :\n");
	printf("Nombre de résultats texte : %ld",map->)
}

int main(){
	printf("Moteur de recherche de fichier équipe 3\n");
	printf("Chargement");
	ConfMap map;
	unsigned char flag;
	if(config_file_exists()){
		map = read_config_file(&flag);
		printf(".");
	}else{
		map = defaultConfMap();
		printf(".");
		flag = save_config_file(map);
		assert(flag != ECHEC);
	}
	printf(".");
	long pos(keyPosition(&map,"chemin_bdd");
	if(pos == -1){
		printf(".\nChemin de la base de fichiers non connu.\nVeuillez entrer le chemin : ");
		
	}
}