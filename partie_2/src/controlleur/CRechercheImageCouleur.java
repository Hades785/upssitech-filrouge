package controlleur;

import java.util.ArrayList;

public class CRechercheImageCouleur {

	public ArrayList<String> rechercherImageCouleur(int couleur)
	{
		String resultats;
		ArrayList<String> resFormattes = new ArrayList<>();
		
		//TODO ajouter nom classe de la methode statique
		resultats = rechercherCouleur(couleur);
		
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
