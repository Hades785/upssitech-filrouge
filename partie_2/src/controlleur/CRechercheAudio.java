package controlleur;

import java.util.ArrayList;

import jni.MoteurC;

public class CRechercheAudio {

	public ArrayList<String> rechercherAudio(String chemin, int winStep, int nbSampWin, int nbIntAmp)
	{
		String resultats;
		ArrayList<String> resFormattes = new ArrayList<>();
		
		//TODO ajouter nom classe de la methode statique
		resultats = MoteurC.rechercherAudio(chemin, winStep, nbSampWin, nbIntAmp);
		
		// separations des resultats
		String[] tmp = resultats.split("\n");
		
		// stockage sous forme de liste
		for(int i = 0; i < tmp.length; i++)
		{
			resFormattes.add(tmp[i]);
		}
		
		return resFormattes;
	}
}
