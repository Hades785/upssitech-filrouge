#ifndef __INDEXATION__
#define __INDEXATION__

#include "sauvegarde_descripteurs.h"
#include "config_reader.h"
/*#include "indexation_texte.h"
#include "indexation_image.h"
#include "indexation_audio.h"*/

/**
 * DESCRIPTION PLACEHOLDER
 *
 * @param  PLACEHOLDER
 * @return PLACEHOLDER
 */
//void indexer(int mode /*TODO*/);

void getAllFiles(const char * chemin_fichiers,const char * extension,Capsule * caps);

void indexer_texte(const char * chemin_desc,const ConfMap * map);

void indexer_image(const char * chemin_desc,const ConfMap * map);

void indexer_audio(const char * chemin_desc,const ConfMap * map);
#endif
