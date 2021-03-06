package controlleur;

import java.util.ArrayList;
import java.util.List;

import jni.MoteurC;
import modele.Recherche;
import modele.TypeFichier;

public class CRechercheImageCouleur {
	private CConfiguration configuration;
	private CHistorique historique;
	
	public CRechercheImageCouleur(CConfiguration c, CHistorique h)
	{
		configuration = c;
		historique = h;
	}

	public List<String> rechercherImageCouleur(int couleur)
	{
		int nbRes = configuration.getNbResImage();
		int nbBits = configuration.getNbBitsImage();
		
		String resultats;
		List<String> resFormattes = new ArrayList<>();
		
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
