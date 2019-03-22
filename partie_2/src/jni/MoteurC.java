package jni;

public class MoteurC {
	private MoteurC() {};
	
	private static boolean test = false;
	
	public static void setTest(boolean t) {
		test = t;
	}
	
	private static native void initC();
	private static void initTest() {
		System.out.println("InitC");
	}
	public static void init() {
		if(test)
			initTest();
		else
			initC();
	}
	
	private static native void indexerTexteC(String cheminBdd,int nbMotsMax,int tailleminMot);
	private static void indexerTexteTest(String cheminBdd,int nbMotsMax,int tailleminMot) {
		System.out.println("indexationTexteC:");
		System.out.println("CheminBDD : "+cheminBdd);
		System.out.println("NbMotsMax : "+nbMotsMax);
		System.out.println("tailleminMot : "+tailleminMot);
	}
	public static void indexerTexte(String cheminBdd,int nbMotsMax,int tailleminMot) {
		if(test)
			indexerTexteTest(cheminBdd,nbMotsMax,tailleminMot);
		else
			indexerTexteC(cheminBdd, nbMotsMax, tailleminMot);
	}
	
	private static native void indexerImageC(String cheminBdd,int nbCouleursMax,float seuilCouleur,int nbBits);
	private static void indexerImageTest(String cheminBdd,int nbCouleursMax,float seuilCouleur,int nbBits) {
		System.out.println("indexationImageC:");
		System.out.println("CheminBDD : "+cheminBdd);
		System.out.println("nbCouleursMax : "+nbCouleursMax);
		System.out.println("seuilCouleur : "+seuilCouleur);
		System.out.println("nbBits : "+nbBits);
	}
	public static void indexerImage(String cheminBdd,int nbCouleursMax,float seuilCouleur,int nbBits) {
		if(test)
			indexerImageTest(cheminBdd,nbCouleursMax,seuilCouleur,nbBits);
		else
			indexerImageC(cheminBdd, nbCouleursMax, seuilCouleur, nbBits);
	}

	private static native void indexerAudioC(String cheminBdd,int nbEchantillonPFenetre,int nbIntAmp);
	private static void indexerAudioTest(String cheminBdd,int nbEchantillonPFenetre,int nbIntAmp) {
		System.out.println("indexationAudioC:");
		System.out.println("cheminBdd : "+cheminBdd);
		System.out.println("nbEchantillonPFenetre : "+nbEchantillonPFenetre);
		System.out.println("nbIntAmp : "+nbIntAmp);
	}
	public static void indexerAudio(String cheminBdd,int nbEchantillonPFenetre,int nbIntAmp) {
		if(test)
			indexerAudioTest(cheminBdd,nbEchantillonPFenetre, nbIntAmp);
		else
			indexerAudioC(cheminBdd, nbEchantillonPFenetre, nbIntAmp);
	}

	private static native String rechercherTexteC(String cheminFichier,int nbRes);
	private static String rechercherTexteTest(String cheminFichier,int nbRes) {
		System.out.println("rechercheTexteC");
		System.out.println("cheminFichier : "+cheminFichier);
		System.out.println("nbRes : "+nbRes);
		return "Attention\nFonction non faite";
	}
	public static String rechercherTexte(String cheminFichier,int nbRes) {
		if(test)
			return rechercherTexteTest(cheminFichier, nbRes);
		else
			return rechercherTexteC(cheminFichier, nbRes);
	}

	private static native String rechercherMotsC(String mots,int nbRes);
	private static String rechercherMotsTest(String mots,int nbRes) {
		System.out.println("RechercheMotsC");
		System.out.println("mots : "+mots);
		System.out.println("nbRes : "+nbRes);
		return "Attention\nFonction non faite";
	}
	public static String rechercherMots(String mots,int nbRes) {
		if(test)
			return rechercherMotsTest(mots, nbRes);
		else
			return rechercherMotsC(mots, nbRes);
	}

	private static native String rechercherImageC(String cheminImage,int nbRes,int nbBits);
	private static String rechercherImageTest(String cheminImage,int nbRes,int nbBits) {
		System.out.println("RechercheImageC");
		System.out.println("cheminImage : "+cheminImage);
		System.out.println("nbRes : "+nbRes);
		System.out.println("nbBits : "+nbBits);
		return "Attention\nFonction non faite";
	}
	public static String rechercherImage(String cheminImage,int nbRes,int nbBits) {
		if(test)
			return rechercherImageTest(cheminImage, nbRes, nbBits);
		else
			return rechercherImageC(cheminImage, nbRes, nbBits);
	}

	private static native String rechercherCouleurC(int colorCode,int nbRes,int nbBits);
	private static String rechercherCouleurTest(int colorCode,int nbRes,int nbBits) {
		System.out.println("RechercheCouleurC");
		System.out.println("colorCode : "+colorCode);
		System.out.println("nbRes : "+nbRes);
		System.out.println("nbBits : "+nbBits);
		return "Attention\nFonciton non faite";
	}
	public static String rechercherCouleur(int colorCode,int nbRes,int nbBits) {
		if(test)
			return rechercherCouleurTest(colorCode, nbRes, nbBits);
		else
			return rechercherCouleurC(colorCode, nbRes, nbBits);
	}

	private static native String rechercherAudioC(String cheminFichier,int winStep,int nbSampWin,int nbIntAmp);
	private static String rechercherAudioTest(String cheminFichier,int winStep,int nbSampWin,int nbIntAmp) {
		System.out.println("RechercheAudioC");
		System.out.println("cheminFichier : "+cheminFichier);
		System.out.println("winStep : "+winStep);
		System.out.println("nbSampWin : "+nbSampWin);
		System.out.println("nbIntAmp : "+nbIntAmp);
		return "Attention\nFonction non faite";
	}
	public static String rechercherAudio(String cheminFichier,int winStep,int nbSampWin,int nbIntAmp) {
		if(test)
			return rechercherAudioTest(cheminFichier, winStep, nbSampWin, nbIntAmp);
		else
			return rechercherAudioC(cheminFichier, winStep, nbSampWin, nbIntAmp);
	}
}