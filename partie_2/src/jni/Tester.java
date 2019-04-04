package jni;

import controlleur.CConfiguration;
import controlleur.CIndexation;

public class Tester {

	public static void main(String[] args) {
		MoteurC.setTest(false);
		
		CConfiguration config = new CConfiguration();

		MoteurC.indexerTexte(config.getCheminBDTexte(), 30, 3);
		MoteurC.indexerImage(config.getCheminBDImage(), 3, 2.5f, 4);
		MoteurC.indexerAudio(config.getCheminBDAudio(), 1000, 16);

		String a = MoteurC.rechercherTexte("../documents/texte/03-Mimer_un_signal_nerveux_pour.xml", 15, 30, 3);
		String b = MoteurC.rechercherMots("sur ", 15, 30, 3);
		String c = MoteurC.rechercherImage("../documents/images/rgb/16.txt", 15, 4, 3, 2.5f);
		String d = MoteurC.rechercherCouleur(0xff0000, 15, 4);
		String e = MoteurC.rechercherAudio("../documents/audio/jingle_fi.txt", 1, 1000, 16);

		System.out.println("Recherche texte:\n" + a);
		System.out.println("Recherche mot-cle:\n" + b);
		System.out.println("Recherche image:\n" + c);
		System.out.println("Recherche couleur:\n" + d);
		System.out.println("Recherche audio:\n" + e);
	}

}
