package vue_console;

import controlleur.CIndexation;

public class BIndexation {
	private CIndexation control;

	public BIndexation(CIndexation c)
	{
		control = c;
	}
	
	public void indexation(int nbMotsMax,int tailleMinMot,int nbCouleursMax, float seuilCouleur, int nbBits, int nbEchantillonPFenetre, int nbIntAmp)
	{
		control.indexation(nbMotsMax,tailleMinMot,nbCouleursMax, seuilCouleur, nbBits, nbEchantillonPFenetre, nbIntAmp);
	}
}
