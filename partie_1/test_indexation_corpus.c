#include "indexation_texte.h"
#include <stdio.h>
#include "sauvegarde_descripteurs.h"
#include "constantes.h"

int main(){
	unsigned char flag;
	Capsule caps = newCapsule(&flag);
	addElement(&caps,indexation_texte("03-Mimer_un_signal_nerveux_pour.xml",1));
	addElement(&caps,indexation_texte("05-Edition___les_mots_et.xml",2));
	addElement(&caps,indexation_texte("05-Le_Colombien_Juan_Pablo_Montoya.xml",3));
	addElement(&caps,indexation_texte("05-Photographie___Philip_Blenkinsop_a.xml",4));
	addElement(&caps,indexation_texte("05-Rock___l_Illinois_magique_de.xml",5));
	addElement(&caps,indexation_texte("06-US_Open___Mauresmo_et.xml",6));
	addElement(&caps,indexation_texte("08-Carlos_do_Carmo____Le.xml",7));
	addElement(&caps,indexation_texte("08-La_mission_Deep_Impact_permet.xml",8));
	addElement(&caps,indexation_texte("09-Miracle___le_cricket_est.xml",9));
	addElement(&caps,indexation_texte("10-Le_cyclone_Katrina_complique_le.xml",10));
	addElement(&caps,indexation_texte("12-Agassi_plie_face_au_meilleur.xml",11));
	saveDescripteurs(&flag,caps,"corpustexte.desc");
	assert(flag!=ECHEC);
	
	
}