package vue_console;

import java.util.ArrayList;
import java.util.Scanner;

public class BRechercheTexteMotsCles {
	
	private static Scanner scanner = new Scanner(System.in);
	private Controleur control;
	private Historique hist;
	private ArrayList<String> resultats;
	private ArrayList<String> motsCl�s;
	
	
	
	public BRechercheTexteMotsCles(Controleur control, Historique hist)
	{
		this.control = control;
		this.hist = hist;
		motsCl�s = new ArrayList<>();
	}
	
	
	
	public void Recherche(int nombreMax)
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
			motsCl�s.add(scanner.next());
			System.out.println();
		}
		
		
		resultats = control.Recherche(motsCl�s);
		
		System.out.println("R�sultats :");
		for(int i = 0 ; i < resultats.size() ; i++)
			System.out.println(resultats.get(i));
		
		hist.Historique(motsCl�s, resultats);
		
		motsCl�s.clear();
		resultats.clear();
	}
	
}
