package vue_console;

import java.util.ArrayList;
import java.util.Scanner;

import controlleur.CRechercheImageCouleur;

public class BRechercheImageCouleur {
	
	private static Scanner scanner = new Scanner(System.in);
	private CRechercheImageCouleur control;
	//private Historique hist;
	private ArrayList<String> resultats;
	
	
	
	public BRechercheImageCouleur(CRechercheImageCouleur control)
	{
		this.control = control;
	}
	
	
	
	public void Recherche(int nbRes, int nbBits)
	{
		int couleur = 0;
		
		do
		{
			System.out.println("Choisissez votre couleur :");
			System.out.println("1-noir     2-blanc");
			System.out.println("3-rouge    4-vert");
			System.out.println("5-bleu     6-cyan");
			System.out.println("7-magenta  8-jaune");
			couleur = scanner.nextInt();
		}
		while(couleur < 1 || couleur > 8);
		
		resultats = control.rechercherImageCouleur(couleur, nbRes, nbBits);
		
		System.out.println("Resultats :");
		for(int i = 0 ; i < resultats.size() ; i++)
			System.out.println(resultats.get(i));
		
		//hist.Historique(r, g, b, resultats);
		
		resultats.clear();
	}
	
}
