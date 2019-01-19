#ifndef __CONFIGREADER__
#define __CONFIGREADER__
#include "sds.h"
#include "sauvegarde_descripteurs.h"

typedef struct{
	Capsule * keys;
	Capsule * values;
}ConfMap;

unsigned char config_file_exists();

ConfMap newConfMap(unsigned char * success_flag);

ConfMap read_config_file(unsigned char * success_flag);

unsigned char save_config_file(ConfMap map);

void freeConfMap(ConfMap map);

long keyPosition(ConfMap * map,const char * key);

sds getConfigValue(ConfMap * map,const char * key);

long getConfigValueLong(ConfMap * map,const char * key,unsigned char * success_flag);

float getConfigValueFloat(ConfMap * map,const char * key,unsigned char * success_flag);

unsigned char addValue(ConfMap * map,const char * key,const char * value);

unsigned char addValueLong(ConfMap * map,const char * key,long value);

unsigned char addValueFloat(ConfMap * map,const char * key,float value);

unsigned char removeValue(ConfMap * map,const char * key);

unsigned char changeValue(ConfMap * map,const char * key,const char * newValue);

unsigned char changeValueLong(ConfMap * map,const char * key,long newValue);

unsigned char postValue(ConfMap * map,const char * key,const char * value);
#endif