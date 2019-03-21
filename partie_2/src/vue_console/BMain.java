package vue_console;

import java.util.Scanner;

import controlleur.CIdentification;
import controlleur.CRechercheImageCouleur;
import controlleur.CRechercheImageFichier;
import controlleur.CRechercheTexteFichier;
import controlleur.CRechercheTexteMotsCles;

public class BMain {
	private static Scanner scanner = new Scanner(System.in);
	private static Historique historique = Historique.getInstance(); // TODO en supposant qu'il s'agisse d'un singleton
	
	private static BIdentification bIdentification = new BIdentification(CIdentification.getInstance());
	private static BRechercheImageCouleur bRechercheImageCouleur = new BRechercheImageCouleur(new CRechercheImageCouleur(), historique);
	private static BRechercheImageFichier bRechercheImageFichier = new BRechercheImageFichier(new CRechercheImageFichier(), historique);
	private static BRechercheTexteFichier bRechercheTexteFichier = new BRechercheTexteFichier(new CRechercheTexteFichier(), historique);
	private static BRechercheTexteMotsCles bRechercheTexteMotsCles = new BRechercheTexteMotsCles(new CRechercheTexteMotsCles(), historique);
	
	// TODO variables de configurations a deplacer
	private static final int NB_RES;

	private static void afficherMenuConfig()
	{
		if(bIdentification.isIdentified())
		{
			// TODO
			System.out.println("Pas encore implementé...");
		}
		else
		{
			System.out.println("Veuillez vous identifier.");
		}
	}
	
	private static void afficherMenuRecherche()
	{
		int choix = 0;
		
		while(choix != 6)
		{
			System.out.println("1 - Recherche de fichiers textes par fichier");
			System.out.println("2 - Recherche de fichiers textes par mots clés");
			System.out.println("3 - Recherche de fichiers images par fichier");
			System.out.println("4 - Recherche de fichiers images par couleurs");
			System.out.println("5 - Recherche de fichiers audio par jingle");
			System.out.println("6 - Retour");
			
			choix = scanner.nextInt();
			switch(choix)
			{
				case 1:
					bRechercheTexteFichier.Recherche();
					break;
				case 2:
					bRechercheTexteMotsCles.Recherche(NB_RES);
					break;
				case 3:
					bRechercheImageFichier.Recherche();
					break;
				case 4:
					bRechercheImageCouleur.Recherche();
					break;
				case 5:
					// TODO
					System.out.println("Pas encore implementé...");
					break;
				case 6:
					return;
			}
		}
	}
	
	public static void main(String[] args) {
		int choix = 0;
		
		System.out.println("Bienvenu sur notre moteur de recherche.\nVeuillez choisir une option :");
		
		while(choix != 5)
		{
			System.out.println("1 - Lancer une recherche");
			System.out.println("2 - Indexer des fichiers");
			System.out.println("3 - Configurer l'application");
			System.out.println("4 - S'identifier");
			System.out.println("5 - Quitter");
			
			choix = scanner.nextInt();
			switch(choix)
			{
				case 1:
					afficherMenuRecherche();
					break;
				case 2:
					// TODO
					System.out.println("Pas encore implementé...");
					break;
				case 3:
					afficherMenuConfig();
					break;
				case 4:
					bIdentification.identification();
					break;
				case 5:
					return;
				default:
					System.out.println("Erreur de saisie, choisissez à nouveau :");
					break;
			}
		}
	}

}
