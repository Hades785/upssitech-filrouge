package vue_console;

import java.io.File;
import java.util.List;
import java.util.Scanner;

import controlleur.CRechercheImageFichier;

public class BRechercheImageFichier {
	
	private static Scanner scanner = new Scanner(System.in);
	private CRechercheImageFichier control;
	//private Historique hist;
	private List<String> resultats;
	
	
	
	public BRechercheImageFichier(CRechercheImageFichier control)
	{
		this.control = control;
	}
	
	
	public void Recherche(int nbRes, int nbBits,int nbCouleursMax,float seuil)
	{
		String chemin = "";
		File f;
		
		do
		{
			if(chemin != "")
				System.out.println("Fichier introuvable !");
			
			System.out.println("Entrez le chemin d'acces de l'image a comparer :");
			chemin = scanner.next();
			
			f = new File(chemin);
		}
		while(!f.exists() || f.isDirectory());
		
		
		resultats = control.rechercherImageFichier(chemin, nbRes, nbBits,nbCouleursMax,seuil);
		
		System.out.println("Resultats :");
		for(int i = 0 ; i < resultats.size() ; i++)
			System.out.println(resultats.get(i));
		
		//hist.Historique(chemin, resultats);
		
		resultats.clear();
	}
	
}
