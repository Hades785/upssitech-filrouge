package jni;

public class Tester {
	static {
		System.loadLibrary("MoteurC");
	}

	public static void main(String[] args) {
		MoteurC.indexerTexte(15, 3);
		MoteurC.indexerImage(3, 255, 8);
		MoteurC.indexerAudio(1000, 10);
		
		String a = MoteurC.rechercherTexte("FICHIER", 5);
		String b = MoteurC.rechercherMots("+Chat -Chien", 5);
		String c = MoteurC.rechercherImage("FICHIER", 5, 8);
		String d = MoteurC.rechercherCouleur(4, 5, 8);
		String e = MoteurC.rechercherAudio("FICHIER", 5, 1000, 10);

		System.out.println(a);
		System.out.println(b);
		System.out.println(c);
		System.out.println(d);
		System.out.println(e);
	}

}
