package modele;

import java.util.ArrayList;
import java.util.List;

public class Historique {
	private List<Recherche> historiqueRecherches=new ArrayList<>();

	public Historique() {
		
	}
	
	public void ajoutRecherche(Recherche recherche){ 
		historiqueRecherches.add(recherche);
		}
	
	public void supprimerRecherche(Recherche recherche) {
		historiqueRecherches.remove(recherche);
	}
	
	public void ViderHistorique() {
		historiqueRecherches.clear();
	}
	
	
}
