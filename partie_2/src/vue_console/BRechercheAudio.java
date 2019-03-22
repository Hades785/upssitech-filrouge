package vue_console;

import java.io.File;
import java.util.ArrayList;
import java.util.Scanner;

import controlleur.CRechercheAudio;
import controlleur.CRechercheTexteFichier;

public class BRechercheAudio {
	
	private static Scanner scanner = new Scanner(System.in);
	private CRechercheAudio control;
	//private Historique hist;
	private ArrayList<String> resultats;
	
	
	
	public BRechercheAudio(CRechercheAudio control)
	{
		this.control = control;
	}
	
	
	
	public void Recherche(int winStep, int nbSampWin, int nbIntAmp)
	{
		String chemin = "";
		File f;
		
		do
		{
			if(chemin != "")
				System.out.println("Fichier introuvable !");
			
			System.out.println("Entrez le chemin d'acces du jingle e comparer :");
			chemin = scanner.next();
			
			f = new File(chemin);
		}
		while(!f.exists() || f.isDirectory());
		
		
		resultats = control.rechercherAudio(chemin, winStep, nbSampWin, nbIntAmp);
		
		System.out.println("R�sultats :");
		for(int i = 0 ; i < resultats.size() ; i++)
			System.out.println(resultats.get(i));
		
		//hist.Historique(chemin, resultats);
		
		resultats.clear();
	}
	
}
