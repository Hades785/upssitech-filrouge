package controlleur;

import java.util.ArrayList;
import java.util.List;

import jni.MoteurC;
import modele.Recherche;
import modele.TypeFichier;

public class CRechercheTexteMotsCles {
	private CConfiguration configuration;
	private CHistorique historique;
	
	public CRechercheTexteMotsCles(CConfiguration c, CHistorique h)
	{
		configuration = c;
		historique = h;
	}

	public List<String> rechercherMotsCles(String motsCles)
	{
		int nbRes = configuration.getNbrResTexte();
		int nbMotsMax = configuration.getNbMotsMaxTexte();
		int tailleminMot = configuration.getTailleMinMot();
		
		String resultats;
		List<String> resFormattes = new ArrayList<>();
		
		//TODO ajouter nom classe de la methode statique
		resultats = MoteurC.rechercherMots(motsCles+" ", nbRes,nbMotsMax,tailleminMot);
		
		// separations des resultats
		String[] tmp = resultats.split("\n");
		
		// stockage sous forme de liste
		for(int i = 0; i < tmp.length; i++)
		{
			resFormattes.add(tmp[i]);
		}
		
		// ajout dans l'historique
		Recherche recherche = new Recherche(TypeFichier.IMAGES);
		recherche.setRequete(motsCles);
		recherche.setListResultatsRequete(resFormattes);
		historique.ajoutRecherche(recherche);
		
		return resFormattes;
	}
}
