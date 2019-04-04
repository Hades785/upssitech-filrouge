package controlleur;

import jni.MoteurC;

public class CIndexation {
	private CConfiguration configuration;

	public CIndexation(CConfiguration c) {
		configuration = c;
	}

	public void indexation() {
		int nbMotsMax = configuration.getNbMotsMaxTexte();
		int tailleMinMot = configuration.getTailleMinMot();
		int nbCouleursMax = configuration.getNbCouleursMaxImage();
		float seuilCouleur = configuration.getSeuilCouleurImage();
		int nbBits = configuration.getNbBitsImage();
		int nbEchantillonPFenetre = configuration.getNbEchantParFen();
		int nbIntAmp = configuration.getNbInterAmp();

		String cheminTexte = configuration.getCheminBDTexte();
		String cheminImage = configuration.getCheminBDImage();
		String cheminAudio = configuration.getCheminBDAudio();

		// TODO rajouter le nom de la classe pour les methodes statiques
		MoteurC.indexerTexte(cheminTexte, nbMotsMax, tailleMinMot);
		MoteurC.indexerImage(cheminImage, nbCouleursMax, seuilCouleur, nbBits);
		MoteurC.indexerAudio(cheminAudio, nbEchantillonPFenetre, nbIntAmp);
	}
}
