package controlleur;

import jni.MoteurC;

public class CIndexation {
	
	public static final String CHEMIN_FICHIERS_TEXTE = "../documents/texte";
	public static final String CHEMIN_FICHIERS_IMAGE = "../documents/images/rgb";
	public static final String CHEMIN_FICHIERS_AUDIO = "../documents/audio";

	public void indexation(int nbMotsMax,int tailleMinMot,int nbCouleursMax, float seuilCouleur, int nbBits, int nbEchantillonPFenetre, int nbIntAmp)
	{
		// TODO rajouter le nom de la classe pour les methodes statiques
		MoteurC.indexerTexte(CHEMIN_FICHIERS_TEXTE,nbMotsMax,tailleMinMot);
		MoteurC.indexerImage(CHEMIN_FICHIERS_IMAGE,nbCouleursMax, seuilCouleur, nbBits);
		MoteurC.indexerAudio(CHEMIN_FICHIERS_AUDIO,nbEchantillonPFenetre, nbIntAmp);
	}
}
