package jni;

public class Tester {
	static {
		System.loadLibrary("MoteurC");
	}

	public static void main(String[] args) {
		MoteurC.indexerTexte("BDD", "MAP", "ID", 15, 3);
		MoteurC.indexerImage("BDD", 3, 255, 8);
		MoteurC.indexerAudio("BDD", 1000, 10);
		
		String a = MoteurC.rechercherTexte("BDD", "MAP", "FICHIER", 5);
		String b = MoteurC.rechercherMots("MAP", "ID", "+Chat -Chien", 5);
		String c = MoteurC.rechercherImage("BDD", "FICHIER", 5, 8);
		String d = MoteurC.rechercherCouleur("BDD", 4, 5, 8);
		String e = MoteurC.rechercherAudio("BDD", "FICHIER", 5, 1000, 10);

		System.out.println(a);
		System.out.println(b);
		System.out.println(c);
		System.out.println(d);
		System.out.println(e);
	}

}
