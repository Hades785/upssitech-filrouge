package controlleur;

import java.util.ArrayList;

public class CRechercheImageFichier {

	public ArrayList<String> rechercherImageFichier(String chemin)
	{
		String resultats;
		ArrayList<String> resFormattes = new ArrayList<>();
		
		//TODO ajouter nom classe de la methode statique
		resultats = rechercherImage(chemin);
		
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
