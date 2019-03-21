package vue_console;

import java.io.File;
import java.util.ArrayList;
import java.util.Scanner;

import controlleur.CRechercheImageFichier;

public class BRechercheImageFichier {
	
	private static Scanner scanner = new Scanner(System.in);
	private CRechercheImageFichier control;
	private Historique hist;
	private ArrayList<String> resultats;
	
	
	
	public BRechercheImageFichier(CRechercheImageFichier control, Historique hist)
	{
		this.control = control;
		this.hist = hist;
	}
	
	
	public void Recherche()
	{
		String chemin = "";
		File f;
		
		do
		{
			if(chemin != "")
				System.out.println("Fichier introuvable !");
			
			System.out.println("Entrez le chemin d'accès de l'image à comparer :");
			chemin = scanner.next();
			
			f = new File(chemin);
		}
		while(!f.exists() || f.isDirectory());
		
		
		resultats = control.rechercherImageFichier(chemin, nbRes, nbBits);
		
		System.out.println("Résultats :");
		for(int i = 0 ; i < resultats.size() ; i++)
			System.out.println(resultats.get(i));
		
		hist.Historique(chemin, resultats);
		
		resultats.clear();
	}
	
}
