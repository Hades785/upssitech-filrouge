package vue_console;

import java.io.File;
import java.util.List;
import java.util.Scanner;

import controlleur.CRechercheAudio;

public class BRechercheAudio {
	
	private static Scanner scanner = new Scanner(System.in);
	private CRechercheAudio control;
	//private Historique hist;
	private List<String> resultats;
	
	
	
	public BRechercheAudio(CRechercheAudio control)
	{
		this.control = control;
	}
	
	
	
	public void Recherche()
	{
		String chemin = "";
		File f;
		
		do
		{
			if(chemin != "")
				System.out.println("Fichier introuvable !");
			
			System.out.println("Entrez le chemin d'acces du jingle a comparer :");
			chemin = scanner.next();
			
			f = new File(chemin);
		}
		while(!f.exists() || f.isDirectory());
		
		
		resultats = control.rechercherAudio(chemin);
		
		System.out.println("Resultats :");
		for(int i = 0 ; i < resultats.size() ; i++)
			System.out.println(resultats.get(i));
		
		//hist.Historique(chemin, resultats);
		
		resultats.clear();
	}
	
}
