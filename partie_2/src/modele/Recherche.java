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
}
