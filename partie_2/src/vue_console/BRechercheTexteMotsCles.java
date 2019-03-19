package vue_console;

import java.util.ArrayList;
import java.util.Scanner;

public class BRechercheTexteMotsCles {
	
	private static Scanner scanner = new Scanner(System.in);
	private Controleur control;
	private Historique hist;
	private ArrayList<String> resultats;
	private ArrayList<String> motsClés;
	
	
	
	public BRechercheTexteMotsCles(Controleur control, Historique hist)
	{
		this.control = control;
		this.hist = hist;
		motsClés = new ArrayList<>();
	}
	
	
	
	public void Recherche(int nombreMax)
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
			motsClés.add(scanner.next());
			System.out.println();
		}
		
		
		resultats = control.Recherche(motsClés);
		
		System.out.println("Résultats :");
		for(int i = 0 ; i < resultats.size() ; i++)
			System.out.println(resultats.get(i));
		
		hist.Historique(motsClés, resultats);
		
		motsClés.clear();
		resultats.clear();
	}
	
}
