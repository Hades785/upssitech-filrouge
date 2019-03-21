package vue_console;

import java.util.ArrayList;
import java.util.Scanner;

import controlleur.CRechercheImageCouleur;

public class BRechercheImageCouleur {
	
	private static Scanner scanner = new Scanner(System.in);
	private CRechercheImageCouleur control;
	//private Historique hist;
	private ArrayList<String> resultats;
	
	
	
	public BRechercheImageCouleur(CRechercheImageCouleur control, Historique hist)
	{
		this.control = control;
		this.hist = hist;
	}
	
	
	
	public void Recherche(int nbRes, int nbBits)
	{
		int r = 0;
		int g = 0;
		int b = 0;
		
		do
		{
			System.out.println("Rouge :");
			r = scanner.nextInt();
		}
		while(r < 0 || r > 255);
		
		do
		{
			System.out.println("Vert :");
			g = scanner.nextInt();
		}
		while(g < 0 || g > 255);
		
		do
		{
			System.out.println("Bleu :");
			b = scanner.nextInt();
		}
		while(b < 0 || b > 255);
		
		
		resultats = control.rechercherImageCouleur(couleur, nbRes, nbBits);
		
		System.out.println("Résultats :");
		for(int i = 0 ; i < resultats.size() ; i++)
			System.out.println(resultats.get(i));
		
		//hist.Historique(r, g, b, resultats);
		
		resultats.clear();
	}
	
}
