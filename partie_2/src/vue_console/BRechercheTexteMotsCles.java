package vue_console;

import java.util.ArrayList;
import java.util.Scanner;

import controlleur.CRechercheTexteMotsCles;

public class BRechercheTexteMotsCles {
	
	private static Scanner scanner = new Scanner(System.in);
	private CRechercheTexteMotsCles control;
	private Historique hist;
	private ArrayList<String> resultats;
	private String motsCl�s;
	
	
	
	public BRechercheTexteMotsCles(CRechercheTexteMotsCles control, Historique hist)
	{
		this.control = control;
		this.hist = hist;
		motsCl�s = new String();
	}
	
	
	
	public void Recherche(int nombreMax, int nbRes)
	{
		int nb = 0;
		
		do
		{
			System.out.print("Combien de mots-cl�s (" + nombreMax + " max) ?");
			nb = scanner.nextInt();
			System.out.println();
		}
		while(nb > nombreMax);
		
		
		for(int i = 0 ; i < nb ; i++)
		{
			System.out.print("Mot " + i + " : ");
			motsCl�s += scanner.next()+ ' ';
			System.out.println();
		}
		
		
		resultats = control.rechercherMotsCles(motsCl�s, nbRes);
		
		System.out.println("R�sultats :");
		for(int i = 0 ; i < resultats.size() ; i++)
			System.out.println(resultats.get(i));
		
		hist.Historique(motsCl�s, resultats);
		
		resultats.clear();
	}
	
}
