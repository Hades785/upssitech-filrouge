package controlleur;

import jni.MoteurC;

public class CIndexation {

	public void indexation(int nbCouleursMax, float seuilCouleur, int nbBits, int nbEchantillonPFenetre, int nbIntAmp)
	{
		// TODO rajouter le nom de la classe pour les methodes statiques
		MoteurC.indexerTexte();
		MoteurC.indexerImage(nbCouleursMax, seuilCouleur, nbBits);
		MoteurC.indexerAudio(nbEchantillonPFenetre, nbIntAmp);
	}
}
