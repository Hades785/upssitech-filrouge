#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "config_reader.h"

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
		ConfMap map = newConfMap(&flag);
		assert(flag != ECHEC);
	}
	addValue(&map,"bonjour","aussi");
	
	sds s = getConfigValue(&map,"bonjour");
	printf("%s\n",s);
	sdsfree(s);
	flag = save_config_file(map);
	assert(flag != ECHEC);
	freeConfMap(map);
	return 0;
}