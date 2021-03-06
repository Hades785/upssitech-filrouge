package controlleur;

import java.util.ArrayList;
import java.util.List;

import jni.MoteurC;
import modele.Recherche;
import modele.TypeFichier;

public class CRechercheImageFichier {
	private CConfiguration configuration;
	private CHistorique historique;
	
	public CRechercheImageFichier(CConfiguration c, CHistorique h)
	{
		configuration = c;
		historique = h;
	}

	public List<String> rechercherImageFichier(String chemin)
	{
		int nbRes = configuration.getNbResImage();
		int nbBits = configuration.getNbBitsImage();
		int nbCouleursMax = configuration.getNbCouleursMaxImage();
		float seuil = configuration.getSeuilCouleurImage();
		
		String resultats;
		List<String> resFormattes = new ArrayList<>();
		
		//TODO ajouter nom classe de la methode statique
		resultats = MoteurC.rechercherImage(chemin, nbRes, nbBits,nbCouleursMax,seuil);
		
		// separations des resultats
		String[] tmp = resultats.split("\n");
		
		// stockage sous forme de liste
		for(int i = 0; i < tmp.length; i++)
		{
			resFormattes.add(tmp[i]);
		}
		
		// ajout dans l'historique
		Recherche recherche = new Recherche(TypeFichier.IMAGES);
		recherche.setRequete(chemin);
		recherche.setListResultatsRequete(resFormattes);
		historique.ajoutRecherche(recherche);
		
		return resFormattes;
	}
}
