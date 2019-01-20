#include "config_reader.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "constantes.h"

sds getPath(){
	sds s = sdscat(sdsnew(getenv("HOME"),"/");
	s = sdscat(sdscat(s,STORAGE_FOLDER_NAME),"/");
	return sdscat(s,CONFIG_FILE_NAME);
}

unsigned char config_file_exists(){
	sds s = getPath();
	FILE * fichier = fopen(s,"r");
	sdsfree(s);
	if(fichier != NULL){
		fclose(fichier);
		return 1;
	}
	return 0;
}

ConfMap newConfMap(unsigned char * success_flag){
	ConfMap map;
	map.keys = malloc(sizeof(Capsule));
	if(map.keys == NULL){
		*success_flag = ECHEC;
		return map;
	}
	map.values = malloc(sizeof(Capsule));
	if(map.values == NULL){
		*success_flag = ECHEC;
		free(map.keys);
		return map;
	}
	*map.keys = newCapsule(success_flag);
	*map.values = newCapsule(success_flag);
	return map;
}

ConfMap read_config_file(unsigned char * success_flag){
	sds s = getPath();
	Capsule caps = loadDescripteurs(success_flag,s);
	sdsfree(s);
	ConfMap map = newConfMap(success_flag);
	if(*success_flag == ECHEC)
		return map;
	for(unsigned int i = 0;i < caps.nbDescripteurs;i++){
		char * pt = strchr(caps.descripteurs[i],':');
		*success_flag = addElement(map.keys, sdscpylen(sdsempty(),caps.descripteurs[i],pt-caps.descripteurs[i]));
		*success_flag = addElement(map.values, sdsnew(pt+1));
	}
	freeCapsule(caps);
	return map;
}

unsigned char save_config_file(ConfMap map){
	unsigned char flag;
	Capsule caps = newCapsule(&flag);
	for(unsigned int i = 0;i < map.keys->nbDescripteurs;i++){
		sds s = sdsdup(map.keys->descripteurs[i]);
		s = sdscat(s,":");
		flag = addElement(&caps,sdscat(s,map.values->descripteurs[i]));
	}
	sds s = getPath();
	saveDescripteurs(&flag,caps,s);
	sdsfree(s);
	freeCapsule(caps);
	return flag;
}

void freeConfMap(ConfMap map){
	freeCapsule(*map.keys);
	freeCapsule(*map.values);
	free(map.values);
	free(map.keys);
}

long keyPosition(ConfMap * map,const char * key){
	for(unsigned int i = 0;i < map->keys->nbDescripteurs;i++){
		if(strcmp(map->keys->descripteurs[i],key) == 0){
			return (long)i;
		}
	}
	return -1;
}

sds getConfigValue(ConfMap * map,const char * key){
	long pos = keyPosition(map,key);
	if(pos == -1)
		return NULL;
	return sdsdup(map->values->descripteurs[pos]);
}

long getConfigValueLong(ConfMap * map,const char * key,unsigned char * success_flag){
	sds s = getConfigValue(map,key);
	if(s == NULL){
		*success_flag = ECHEC;
		return 0;
	}
	long resp;
	sscanf(s,"%ld",&resp);
	sdsfree(s);
	return resp;
}

float getConfigValueFloat(ConfMap * map,const char * key,unsigned char * success_flag){
	sds s = getConfigValue(map,key);
	if(s == NULL){
		*success_flag = ECHEC;
		return 0;
	}
	float resp;
	sscanf(s,"%f",&resp);
	sdsfree(s);
	return resp;
}

unsigned char addValue(ConfMap * map,const char * key,const char * value){
	unsigned char flag = ECHEC;
	if(keyPosition(map,key) == -1){
		sds s = sdsnew(key);
		flag = addElement(map->keys,s);
		if(flag == ECHEC){
			sdsfree(s);
			return ECHEC;
		}
		s = sdsnew(value);
		flag = addElement(map->values,s);
		if(flag == ECHEC)
			sdsfree(s);
	}
	return flag;
}

unsigned char addValueLong(ConfMap * map,const char * key,long value){
	unsigned char flag = ECHEC;
	if(keyPosition(map,key) == -1){
		sds s = sdsnew(key);
		flag = addElement(map->keys,s);
		if(flag == ECHEC){
			sdsfree(s);
			return ECHEC;
		}
		s = sdsfromlonglong(value);
		flag = addElement(map->values,s);
		if(flag == ECHEC)
			sdsfree(s);
	}
	return flag;
}

unsigned char addValueFloat(ConfMap * map,const char * key,float value){
	unsigned char flag = ECHEC;
	if(keyPosition(map,key) == -1){
		sds s = sdsnew(key);
		flag = addElement(map->keys,s);
		if(flag == ECHEC){
			sdsfree(s);
			return ECHEC;
		}
		s = sdscatprintf(sdsempty(),"%f",value);
		flag = addElement(map->values,s);
		if(flag == ECHEC)
			sdsfree(s);
	}
	return flag;
}

unsigned char removeValue(ConfMap * map,const char * key){
	long pos = keyPosition(map,key);
	if(pos == -1) return ECHEC;
	removeDescripteur(map->keys,pos);
	removeDescripteur(map->values,pos);
	return SUCCES;
}

unsigned char changeValue(ConfMap * map,const char * key,const char * newValue){
	long pos = keyPosition(map,key);
	if(pos == -1) return ECHEC;
	sdsfree(map->values->descripteurs[pos]);
	map->values->descripteurs[pos] = sdsnew(newValue);
	return SUCCES;
}

unsigned char changeValueLong(ConfMap * map,const char * key,long newValue){
	sds s = sdsfromlonglong(newValue);
	unsigned char flag = changeValue(map,key,s);
	sdsfree(s);
	return flag;
}

unsigned char postValue(ConfMap * map,const char * key,const char * value){
	long pos = keyPosition(map,key);
	if(pos == -1)
		return addValue(map,key,value);
	else{
		map->values->descripteurs[pos] = sdscat(map->values->descripteurs[pos],value);
		return SUCCES;
	}
}