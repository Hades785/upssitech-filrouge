package controlleur;

import java.util.ArrayList;

import jni.MoteurC;
import modele.Recherche;
import modele.TypeFichier;

public class CRechercheTexteFichier {
	private CHistorique historique;
	
	public CRechercheTexteFichier(CHistorique h)
	{
		historique = h;
	}

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
		
		// ajout dans l'historique
		Recherche recherche = new Recherche(TypeFichier.TEXTE);
		recherche.setRequete(chemin);
		recherche.setListResultatsRequete(resFormattes);
		historique.ajoutRecherche(recherche);
		
		return resFormattes;
	}
}
