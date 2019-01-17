#include <stdio.h>
#include "config_reader.h"

int main(){
	if(config_file_exists()){
		printf("it exists");
	}else{
		printf("it doesnt exists");
	}
}