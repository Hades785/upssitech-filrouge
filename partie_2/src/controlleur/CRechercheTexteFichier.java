package controlleur;

import java.util.ArrayList;
import java.util.List;

import jni.MoteurC;
import modele.Recherche;
import modele.TypeFichier;

public class CRechercheTexteFichier {
	private CConfiguration configuration;
	private CHistorique historique;
	
	public CRechercheTexteFichier(CConfiguration c, CHistorique h)
	{
		configuration = c;
		historique = h;
	}

	public List<String> rechercherFichier(String chemin)
	{
		int nbRes = configuration.getNbrResTexte();
		int nbMotsMax = configuration.getNbMotsMaxTexte();
		int tailleminMot = configuration.getTailleMinMot();
		
		String resultats;
		List<String> resFormattes = new ArrayList<>();
		
		//TODO ajouter nom classe de la methode statique
		resultats = MoteurC.rechercherTexte(chemin, nbRes,nbMotsMax,tailleminMot);
		
		// separations des resultats
		String[] tmp = resultats.split("\n");
		
		// stockage sous forme de liste
		for(int i = 0; i < tmp.length; i++)
		{
			resFormattes.add(tmp[i]);
		}
		
		// ajout dans l'historique
		Recherche recherche = new Recherche(TypeFichier.TEXTE);
		recherche.setRequete(chemin);
		recherche.setListResultatsRequete(resFormattes);
		historique.ajoutRecherche(recherche);
		
		return resFormattes;
	}
}
