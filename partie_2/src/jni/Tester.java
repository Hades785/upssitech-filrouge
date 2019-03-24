package jni;

import controlleur.CIndexation;

public class Tester {
	static {
		System.loadLibrary("MoteurC");
	}

	public static void main(String[] args) {
		MoteurC.setTest(false);

		MoteurC.indexerTexte(CIndexation.CHEMIN_FICHIERS_TEXTE, 30, 3);
		MoteurC.indexerImage(CIndexation.CHEMIN_FICHIERS_IMAGE, 3, 2.5f, 4);
		MoteurC.indexerAudio(CIndexation.CHEMIN_FICHIERS_AUDIO, 1000, 16);

		String a = MoteurC.rechercherTexte("../documents/texte/03-Mimer_un_signal_nerveux_pour.xml", 15, 30, 3);
		String b = MoteurC.rechercherMots("sur ", 15, 30, 3);
		String c = MoteurC.rechercherImage("FICHIER", 15, 4, 3, 2.5f);
		String d = MoteurC.rechercherCouleur(4, 15, 4);
		String e = MoteurC.rechercherAudio("FICHIER", 1, 1000, 16);

		System.out.println("Recherche texte:\n" + a);
		System.out.println("Recherche mot-cle:\n" + b);
		System.out.println("Recherche image:\n" + c);
		System.out.println("Recherche couleur:\n" + d);
		System.out.println("Recherche audio:\n" + e);
	}

}
