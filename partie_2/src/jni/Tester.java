package jni;

import controlleur.CIndexation;

public class Tester {
	static {
		System.loadLibrary("MoteurC");
	}

	public static void main(String[] args) {
		MoteurC.setTest(false);

		MoteurC.indexerTexte(CIndexation.CHEMIN_FICHIERS_TEXTE, 30, 3);
		MoteurC.indexerImage(CIndexation.CHEMIN_FICHIERS_IMAGE, 3, 255, 4);
		MoteurC.indexerAudio(CIndexation.CHEMIN_FICHIERS_AUDIO, 1000, 16);

		String a = MoteurC.rechercherTexte("FICHIER", 15);
		String b = MoteurC.rechercherMots("Chat Chien ", 15);
		String c = MoteurC.rechercherImage("FICHIER", 15, 4);
		String d = MoteurC.rechercherCouleur(4, 15, 4);
		String e = MoteurC.rechercherAudio("FICHIER", 1, 1000, 16);

		System.out.println(a);
		System.out.println(b);
		System.out.println(c);
		System.out.println(d);
		System.out.println(e);
	}

}
