package jni;

public class MoteurC {
	private MoteurC() {};
	
	private static native void initC();
	private static void initTest() {
		System.out.println("InitC");
	}
	public static void init() {
		initTest();
	}
	
	private static native void indexerTexteC(int nbMotsMax,int tailleminMot);
	private static void indexerTexteTest() {
		System.out.println("indexationTexteC");
		//TODO
	}
	public static void indexerTexte() {
		indexerTexteTest();
	}
	
	private static native void indexerImageC(int nbCouleursMax,float seuilCouleur,int nbBits);
	private static void indexerImageTest(int nbCouleursMax,float seuilCouleur,int nbBits) {
		System.out.println("indexationImageC");
		//TODO
	}
	public static void indexerImage(int nbCouleursMax,float seuilCouleur,int nbBits) {
		indexerImageTest(nbCouleursMax,seuilCouleur,nbBits);
	}

	private static native void indexerAudioC(int nbEchantillonPFenetre,int nbIntAmp);
	private static void indexerAudioTest(int nbEchantillonPFenetre,int nbIntAmp) {
		System.out.println("indexationAudioC");
		//TODO
	}
	public static void indexerAudio(int nbEchantillonPFenetre,int nbIntAmp) {
		indexerAudioTest(nbEchantillonPFenetre, nbIntAmp);
	}

	private static native String rechercherTexteC(String cheminFichier,int nbRes);
	private static String rechercherTexteTest(String cheminFichier,int nbRes) {
		System.out.println("rechercheTexteC");
		//TODO
		return "Attention\nFonction non faite";
	}
	public static String rechercherTexte(String cheminFichier,int nbRes) {
		return rechercherTexteTest(cheminFichier, nbRes);
	}

	private static native String rechercherMotsC(String mots,int nbRes);
	private static String rechercherMotsTest(String mots,int nbRes) {
		System.out.println("RechercheMotsC");
		//TODO
		return "Attention\nFonction non faite";
	}
	public static String rechercherMots(String mots,int nbRes) {
		return rechercherMotsTest(mots, nbRes);
	}

	private static native String rechercherImageC(String cheminImage,int nbRes,int nbBits);
	private static String rechercherImageTest(String cheminImage,int nbRes,int nbBits) {
		System.out.println("RechercheImageC");
		//TODO
		return "Attention\nFonction non faite";
	}
	public static String rechercherImage(String cheminImage,int nbRes,int nbBits) {
		return rechercherImageTest(cheminImage, nbRes, nbBits);
	}

	private static native String rechercherCouleurC(int colorCode,int nbRes,int nbBits);
	private static String rechercherCouleurTest(int colorCode,int nbRes,int nbBits) {
		System.out.println("RechercheCouleurC");
		//TODO
		return "Attention\nFonciton non faite";
	}
	public static String rechercherCouleur(int colorCode,int nbRes,int nbBits) {
		return rechercherCouleurTest(colorCode, nbRes, nbBits);
	}

	private static native String rechercherAudioC(String cheminFichier,int winStep,int nbSampWin,int nbIntAmp);
	private static String rechercherAudioTest(String cheminFichier,int winStep,int nbSampWin,int nbIntAmp) {
		System.out.println("RechercheAudioC");
		//TODO
		return "Attention\nFonction non faite";
	}
	public static String rechercherAudio(String cheminFichier,int winStep,int nbSampWin,int nbIntAmp) {
		return rechercherAudioTest(cheminFichier, winStep, nbSampWin, nbIntAmp);
	}
}