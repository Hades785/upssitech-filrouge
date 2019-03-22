#include "utility.h"

sds getDirPathI(){
	return sdscat(sdscat(sdsnew(getenv("HOME")),"/"),STORAGE_FOLDER_NAME);
}