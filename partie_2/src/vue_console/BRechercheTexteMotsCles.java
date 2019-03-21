package vue_console;

import java.util.ArrayList;
import java.util.Scanner;

import controlleur.CRechercheTexteMotsCles;

public class BRechercheTexteMotsCles {
	
	private static Scanner scanner = new Scanner(System.in);
	private CRechercheTexteMotsCles control;
	private Historique hist;
	private ArrayList<String> resultats;
	private String motsClés;
	
	
	
	public BRechercheTexteMotsCles(CRechercheTexteMotsCles control, Historique hist)
	{
		this.control = control;
		this.hist = hist;
		motsClés = new String();
	}
	
	
	
	public void Recherche(int nombreMax, int nbRes)
	{
		int nb = 0;
		
		do
		{
			System.out.print("Combien de mots-clés (" + nombreMax + " max) ?");
			nb = scanner.nextInt();
			System.out.println();
		}
		while(nb > nombreMax);
		
		
		for(int i = 0 ; i < nb ; i++)
		{
			System.out.print("Mot " + i + " : ");
			motsClés += scanner.next()+ ' ';
			System.out.println();
		}
		
		
		resultats = control.rechercherMotsCles(motsClés, nbRes);
		
		System.out.println("Résultats :");
		for(int i = 0 ; i < resultats.size() ; i++)
			System.out.println(resultats.get(i));
		
		hist.Historique(motsClés, resultats);
		
		resultats.clear();
	}
	
}
