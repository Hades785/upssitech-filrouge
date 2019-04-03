package controlleur;

import java.util.ArrayList;

import jni.MoteurC;
import modele.Recherche;
import modele.TypeFichier;

public class CRechercheImageCouleur {
	private CHistorique historique;
	
	public CRechercheImageCouleur(CHistorique h)
	{
		historique = h;
	}

	public ArrayList<String> rechercherImageCouleur(int couleur, int nbRes, int nbBits)
	{
		String resultats;
		ArrayList<String> resFormattes = new ArrayList<>();
		
		//TODO ajouter nom classe de la methode statique
		resultats = MoteurC.rechercherCouleur(couleur, nbRes, nbBits);
		
		// separations des resultats
		String[] tmp = resultats.split("\n");
		
		// stockage sous forme de liste
		for(int i = 0; i < tmp.length; i++)
		{
			resFormattes.add(tmp[i]);
		}
		
		// ajout dans l'historique
		Recherche recherche = new Recherche(TypeFichier.IMAGES);
		recherche.setRequete(String.valueOf(couleur));
		recherche.setListResultatsRequete(resFormattes);
		historique.ajoutRecherche(recherche);
		
		return resFormattes;
	}
}
