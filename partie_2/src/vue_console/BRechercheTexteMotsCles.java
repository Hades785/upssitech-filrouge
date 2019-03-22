package vue_console;

import java.util.ArrayList;
import java.util.Scanner;

import controlleur.CRechercheTexteMotsCles;

public class BRechercheTexteMotsCles {
	
	private static Scanner scanner = new Scanner(System.in);
	private CRechercheTexteMotsCles control;
	//private Historique hist;
	private ArrayList<String> resultats;
	private String motsCles;
	
	
	
	public BRechercheTexteMotsCles(CRechercheTexteMotsCles control)
	{
		this.control = control;
		motsCles = new String();
	}
	
	
	
	public void Recherche(int nbRes)
	{
		System.out.println("Entrez votre/vos mot(s)-clé(s), séparé(s) d'un espace :");
		motsCles = scanner.nextLine();
		
		resultats = control.rechercherMotsCles(motsCles, nbRes);
		
		System.out.println("R�sultats :");
		for(int i = 0 ; i < resultats.size() ; i++)
			System.out.println(resultats.get(i));
		
		//hist.Historique(motsCles, resultats);
		
		resultats.clear();
	}
	
}
