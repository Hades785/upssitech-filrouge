package modele;

import java.util.ArrayList;
import java.util.List;

public class Recherche {
	private TypeFichier typefichier;
	private String requete;
	private List<String> listResultatsRequete=new ArrayList<>(); 
	
	public Recherche(TypeFichier typeFichier) {
		this.typefichier=typeFichier;
		}
	public TypeFichier getTypeFichier() {
		return typefichier;
	}
}
