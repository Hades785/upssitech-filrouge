package modele;

import java.util.ArrayList;
import java.util.List;

public class Recherche {
	private TypeFichier typeFichier;
	private String requete;
	private List<String> listResultatsRequete = new ArrayList<>();

	public Recherche(TypeFichier typeFichier) {
		this.typeFichier = typeFichier;
	}

	public TypeFichier getTypeFichier() {
		return typeFichier;
	}

	public void setRequete(String requete){
		this.requete=requete;
	}

	public void setListResultatsRequete(List<String> listResultatsRequete){
		this.listResultatsRequete=listResultatsRequete;
	}

	public String getRequete() {
		return requete;
	}

	public void setTypeFichier(TypeFichier typeFichier) {
		this.typeFichier = typeFichier;
	}
	
	public String ResultatsToString() {
		return listResultatsRequete.toString();
		
	}
}
