package vue_console;

import java.util.Scanner;

import controlleur.CIndexation;

public class BIndexation {
	private CIndexation control;

	public BIndexation(CIndexation c)
	{
		control = c;
	}
	
	public void indexation(int nbCouleursMax, float seuilCouleur, int nbBits, int nbEchantillonPFenetre, int nbIntAmp)
	{
		control.indexation(nbCouleursMax, seuilCouleur, nbBits, nbEchantillonPFenetre, nbIntAmp);
	}
}
