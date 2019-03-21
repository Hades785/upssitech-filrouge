package vue_console;

import java.util.ArrayList;
import java.util.Scanner;

import controlleur.CRechercheTexteMotsCles;

public class BRechercheTexteMotsCles {
	
	private static Scanner scanner = new Scanner(System.in);
	private CRechercheTexteMotsCles control;
	//private Historique hist;
	private ArrayList<String> resultats;
	private String motsCl�s;
	
	
	
	public BRechercheTexteMotsCles(CRechercheTexteMotsCles control)
	{
		this.control = control;
		motsCl�s = new String();
	}
	
	
	
	public void Recherche(int nbRes)
	{
		System.out.println("Entrez votre/vos mot(s)-cl�(s), s�par�(s) d'un espace :");
		motsCl�s = scanner.nextLine();
		
		resultats = control.rechercherMotsCles(motsCl�s, nbRes);
		
		System.out.println("R�sultats :");
		for(int i = 0 ; i < resultats.size() ; i++)
			System.out.println(resultats.get(i));
		
		//hist.Historique(motsCl�s, resultats);
		
		resultats.clear();
	}
	
}
