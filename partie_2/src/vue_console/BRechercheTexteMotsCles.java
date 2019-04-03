package vue_console;

import java.util.List;
import java.util.Scanner;

import controlleur.CRechercheTexteMotsCles;

public class BRechercheTexteMotsCles {
	
	private static Scanner scanner = new Scanner(System.in);
	private CRechercheTexteMotsCles control;
	//private Historique hist;
	private List<String> resultats;
	private String motsCles;
	
	
	
	public BRechercheTexteMotsCles(CRechercheTexteMotsCles control)
	{
		this.control = control;
		motsCles = new String();
	}
	
	
	
	public void Recherche(int nbRes,int nbMotsMax,int tailleminMot)
	{
		System.out.println("Entrez votre/vos mot(s)-cle(s), separe(s) d'un espace :");
		motsCles = scanner.nextLine();
		
		resultats = control.rechercherMotsCles(motsCles, nbRes,nbMotsMax,tailleminMot);
		
		System.out.println("Resultats :");
		for(int i = 0 ; i < resultats.size() ; i++)
			System.out.println(resultats.get(i));
		
		//hist.Historique(motsCles, resultats);
		
		resultats.clear();
	}
	
}
