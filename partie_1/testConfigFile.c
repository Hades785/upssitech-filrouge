#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "config_reader.h"
#include "constantes.h"

int main(){
	//printf("%s\n",strcat(getenv("HOME"),CONFIG_FILE_PATH));
	unsigned char flag;
	ConfMap map;
	if(config_file_exists()){
		printf("it exists\n");
		map = read_config_file(&flag);
		assert(flag != ECHEC);
	}else{
		printf("it doesnt exists\n");
		map = newConfMap(&flag);
		assert(flag != ECHEC);
	}
	if(keyPosition(&map,"bonjour") == -1)
		printf("clef n'existe pas\n");
	flag = addValue(&map,"bonjour","aussi");
	if(flag == ECHEC){
		printf("echec add value\n");
	}
	printf("lecture");getchar();
	sds s = getConfigValue(&map,"bonjour");
	if(s != NULL){
		printf("%s\n",s);
		sdsfree(s);
	}
	printf("sauvegarde");getchar();
	flag = save_config_file(map);
	assert(flag != ECHEC);
	freeConfMap(map);
	return 0;
}