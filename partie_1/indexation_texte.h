#ifndef __INDEXATION_TEXTE__
#define __INDEXATION_TEXTE__

#include <stdlib.h>
#include <stdio.h>
#include "sds.h"

/**
 * DESCRIPTION PLACEHOLDER
 *
 * @param  PLACEHOLDER
 * @return PLACEHOLDER
 */
sds ajout_nombre_dans_sds(int nbM, sds s);
sds indexation_texte(const sds accesFichier);
void gestion_descripteurs();

#endif
