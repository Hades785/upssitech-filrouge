package controlleur;

import java.util.List;

import modele.Historique;
import modele.Recherche;

public class CHistorique {
	private Historique historique = new Historique();

	public List<Recherche> consulterHistorique()
	{
		return historique.getHistoriqueRecherches();
	}
	
	public void ajoutRecherche(Recherche recherche) {
		historique.ajoutRecherche(recherche);
	}

	public void supprimerRecherche(Recherche recherche) {
		historique.supprimerRecherche(recherche);
	}

	public void viderHistorique() {
		historique.viderHistorique();
	}
}
