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
	
	private static native void indexerTexteC(String cheminBdd,String cheminMap,String cheminId,int nbMotsMax,int tailleminMot);
	private static void indexerTexteTest(String cheminBdd,String cheminMap,String cheminId,int nbMotsMax,int tailleminMot) {
		System.out.println("indexationTexteC");
		//TODO
	}
	public static void indexerTexte(String cheminBdd,String cheminMap,String cheminId,int nbMotsMax,int tailleminMot) {
		indexerTexteC(cheminBdd,cheminMap,cheminId,nbMotsMax,tailleminMot);
	}
	
	private static native void indexerImageC(String cheminBdd,int nbCouleursMax,float seuilCouleur,int nbBits);
	private static void indexerImageTest(String cheminBdd,int nbCouleursMax,float seuilCouleur,int nbBits) {
		System.out.println("indexationImageC");
		//TODO
	}
	public static void indexerImage(String cheminBdd,int nbCouleursMax,float seuilCouleur,int nbBits) {
		indexerImageC(cheminBdd,nbCouleursMax,seuilCouleur,nbBits);
	}

	private static native void indexerAudioC(String cheminBdd,int nbEchantillonPFenetre,int nbIntAmp);
	private static void indexerAudioTest(String cheminBdd,int nbEchantillonPFenetre,int nbIntAmp) {
		System.out.println("indexationAudioC");
		//TODO
	}
	public static void indexerAudio(String cheminBdd,int nbEchantillonPFenetre,int nbIntAmp) {
		indexerAudioC(cheminBdd,nbEchantillonPFenetre, nbIntAmp);
	}

	private static native String rechercherTexteC(String cheminMap,String cheminId,String cheminFichier,int nbRes);
	private static String rechercherTexteTest(String cheminMap,String cheminId,String cheminFichier,int nbRes) {
		System.out.println("rechercheTexteC");
		//TODO
		return "Attention\nFonction non faite";
	}
	public static String rechercherTexte(String cheminMap,String cheminId,String cheminFichier,int nbRes) {
		return rechercherTexteC(cheminMap,cheminId,cheminFichier, nbRes);
	}

	private static native String rechercherMotsC(String cheminMap,String cheminId,String mots,int nbRes);
	private static String rechercherMotsTest(String cheminMap,String cheminId,String mots,int nbRes) {
		System.out.println("RechercheMotsC");
		//TODO
		return "Attention\nFonction non faite";
	}
	public static String rechercherMots(String cheminMap,String cheminId,String mots,int nbRes) {
		return rechercherMotsC(cheminMap,cheminId,mots, nbRes);
	}

	private static native String rechercherImageC(String cheminBdd,String cheminImage,int nbRes,int nbBits);
	private static String rechercherImageTest(String cheminBdd,String cheminImage,int nbRes,int nbBits) {
		System.out.println("RechercheImageC");
		//TODO
		return "Attention\nFonction non faite";
	}
	public static String rechercherImage(String cheminBdd,String cheminImage,int nbRes,int nbBits) {
		return rechercherImageC(cheminBdd,cheminImage, nbRes, nbBits);
	}

	private static native String rechercherCouleurC(String cheminBdd,int colorCode,int nbRes,int nbBits);
	private static String rechercherCouleurTest(String cheminBdd,int colorCode,int nbRes,int nbBits) {
		System.out.println("RechercheCouleurC");
		//TODO
		return "Attention\nFonciton non faite";
	}
	public static String rechercherCouleur(String cheminBdd,int colorCode,int nbRes,int nbBits) {
		return rechercherCouleurC(cheminBdd,colorCode, nbRes, nbBits);
	}

	private static native String rechercherAudioC(String cheminBdd,String cheminFichier,int winStep,int nbSampWin,int nbIntAmp);
	private static String rechercherAudioTest(String cheminBdd,String cheminFichier,int winStep,int nbSampWin,int nbIntAmp) {
		System.out.println("RechercheAudioC");
		//TODO
		return "Attention\nFonction non faite";
	}
	public static String rechercherAudio(String cheminBdd,String cheminFichier,int winStep,int nbSampWin,int nbIntAmp) {
		return rechercherAudioC(cheminBdd,cheminFichier, winStep, nbSampWin, nbIntAmp);
	}
}