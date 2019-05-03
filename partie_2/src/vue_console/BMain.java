package vue_console;

import java.util.Scanner;

import controlleur.CConfiguration;
import controlleur.CHistorique;
import controlleur.CIdentification;
import controlleur.CIndexation;
import controlleur.CRechercheAudio;
import controlleur.CRechercheImageCouleur;
import controlleur.CRechercheImageFichier;
import controlleur.CRechercheTexteFichier;
import controlleur.CRechercheTexteMotsCles;

public class BMain {
	private static Scanner scanner = new Scanner(System.in);

	private static CConfiguration configuration = new CConfiguration();
	private static CHistorique historique = new CHistorique();
	private static CIndexation cindex = new CIndexation(configuration);
	
	private static BIdentification bIdentification = new BIdentification(new CIdentification());
	private static BIndexation bIndexation = new BIndexation(cindex);
	private static BRechercheImageCouleur bRechercheImageCouleur = new BRechercheImageCouleur(new CRechercheImageCouleur(configuration, historique));
	private static BRechercheImageFichier bRechercheImageFichier = new BRechercheImageFichier(new CRechercheImageFichier(configuration, historique));
	private static BRechercheTexteFichier bRechercheTexteFichier = new BRechercheTexteFichier(new CRechercheTexteFichier(configuration, historique));
	private static BRechercheTexteMotsCles bRechercheTexteMotsCles = new BRechercheTexteMotsCles(new CRechercheTexteMotsCles(configuration, historique));
	private static BRechercheAudio bRechercheAudio = new BRechercheAudio(new CRechercheAudio(configuration, historique));

	private static void afficherMenuConfig()
	{
		if(bIdentification.isIdentified())
		{
			// TODO
			System.out.println("Pas encore implemente...");
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
			System.out.println("2 - Recherche de fichiers textes par mots cles");
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
					bRechercheTexteMotsCles.Recherche();
					break;
				case 3:
					bRechercheImageFichier.Recherche();
					break;
				case 4:
					bRechercheImageCouleur.Recherche();
					break;
				case 5:
					bRechercheAudio.Recherche();
					break;
				case 6:
					return;
			}
		}
	}
	
	public static void main(String[] args) {
		//MoteurC.setTest(true);
		
		cindex.setup();
		
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
					bIndexation.indexation();
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
					System.out.println("Erreur de saisie, choisissez a nouveau :");
					break;
			}
		}
	}

}
