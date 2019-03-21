package vue_console;

import java.util.ArrayList;
import java.util.Scanner;

import controlleur.CRechercheTexteMotsCles;

public class BRechercheTexteMotsCles {
	
	private static Scanner scanner = new Scanner(System.in);
	private CRechercheTexteMotsCles control;
	//private Historique hist;
	private ArrayList<String> resultats;
	private String motsClés;
	
	
	
	public BRechercheTexteMotsCles(CRechercheTexteMotsCles control)
	{
		this.control = control;
		motsClés = new String();
	}
	
	
	
	public void Recherche(int nbRes)
	{
		System.out.println("Entrez votre/vos mot(s)-clé(s), séparé(s) d'un espace :");
		motsClés = scanner.nextLine();
		
		resultats = control.rechercherMotsCles(motsClés, nbRes);
		
		System.out.println("Résultats :");
		for(int i = 0 ; i < resultats.size() ; i++)
			System.out.println(resultats.get(i));
		
		//hist.Historique(motsClés, resultats);
		
		resultats.clear();
	}
	
}
