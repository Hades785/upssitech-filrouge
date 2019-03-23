package controlleur;

import java.util.ArrayList;

import jni.MoteurC;

public class CRechercheTexteFichier {

	public ArrayList<String> rechercherFichier(String chemin, int nbRes,int nbMotsMax,int tailleminMot)
	{
		String resultats;
		ArrayList<String> resFormattes = new ArrayList<>();
		
		//TODO ajouter nom classe de la methode statique
		resultats = MoteurC.rechercherTexte(chemin, nbRes,nbMotsMax,tailleminMot);
		
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
