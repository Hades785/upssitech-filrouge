package controlleur;

import java.util.ArrayList;
import java.util.List;

import jni.MoteurC;
import modele.Recherche;
import modele.TypeFichier;

public class CRechercheAudio {
	private CConfiguration configuration;
	private CHistorique historique;
	
	public CRechercheAudio(CConfiguration c, CHistorique h)
	{
		configuration = c;
		historique = h;
	}

	public List<String> rechercherAudio(String chemin)
	{
		int winStep = configuration.getNbrFenetres();
		int nbSampWin = configuration.getNbEchantParFen();
		int nbIntAmp = configuration.getNbInterAmp();
		
		String resultats;
		List<String> resFormattes = new ArrayList<>();
		
		//TODO ajouter nom classe de la methode statique
		resultats = MoteurC.rechercherAudio(chemin, winStep, nbSampWin, nbIntAmp);
		
		// separations des resultats
		String[] tmp = resultats.split("\n");
		
		// stockage sous forme de liste
		for(int i = 0; i < tmp.length; i++)
		{
			resFormattes.add(tmp[i]);
		}
		
		// ajout dans l'historique
		Recherche recherche = new Recherche(TypeFichier.AUDIO);
		recherche.setRequete(chemin);
		recherche.setListResultatsRequete(resFormattes);
		historique.ajoutRecherche(recherche);
		
		return resFormattes;
	}
}
