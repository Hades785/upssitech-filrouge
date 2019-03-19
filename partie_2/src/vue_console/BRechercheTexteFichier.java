package vue_console;

import java.io.File;
import java.util.ArrayList;
import java.util.Scanner;

public class BRechercheTexteFichier {
	
	private static Scanner scanner = new Scanner(System.in);
	private Controleur control;
	private Historique hist;
	private ArrayList<String> resultats;
	
	
	
	public BRechercheTexteFichier(Controleur control, Historique hist)
	{
		this.control = control;
		this.hist = hist;
	}
	
	
	
	public void Recherche()
	{
		private String chemin = "";
		File f;
		
		do
		{
			if(chemin != "")
				System.out.println("Fichier introuvable !");
			
			System.out.println("Entrez le chemin d'accès du fichier à comparer :");
			chemin = scanner.next();
			
			f = new File(chemin);
		}
		while(!f.exists() || f.isDirectory());
		
		
		resultats = control.Recherche(chemin);
		
		System.out.println("Résultats :");
		for(int i = 0 ; i < resultats.size() ; i++)
			System.out.println(resultats.get(i));
		
		hist.Historique(chemin, resultats);
		
		resultats.clear();
	}
	
}
