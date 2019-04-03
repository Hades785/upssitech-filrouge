package vue_console;

import java.util.Scanner;

import controlleur.CHistorique;
import controlleur.CIdentification;
import controlleur.CIndexation;
import controlleur.CRechercheAudio;
import controlleur.CRechercheImageCouleur;
import controlleur.CRechercheImageFichier;
import controlleur.CRechercheTexteFichier;
import controlleur.CRechercheTexteMotsCles;
import jni.MoteurC;

public class BMain {
	private static Scanner scanner = new Scanner(System.in);

	private static CHistorique historique = new CHistorique();
	
	private static BIdentification bIdentification = new BIdentification(new CIdentification());
	private static BIndexation bIndexation = new BIndexation(new CIndexation());
	private static BRechercheImageCouleur bRechercheImageCouleur = new BRechercheImageCouleur(new CRechercheImageCouleur(historique));
	private static BRechercheImageFichier bRechercheImageFichier = new BRechercheImageFichier(new CRechercheImageFichier(historique));
	private static BRechercheTexteFichier bRechercheTexteFichier = new BRechercheTexteFichier(new CRechercheTexteFichier(historique));
	private static BRechercheTexteMotsCles bRechercheTexteMotsCles = new BRechercheTexteMotsCles(new CRechercheTexteMotsCles(historique));
	private static BRechercheAudio bRechercheAudio = new BRechercheAudio(new CRechercheAudio(historique));
	
	// TODO variables de configurations a deplacer
	private static final int NB_RES = 10;
	private static final int TAILLE_MIN_MOTS = 3;
	private static final int NB_MOTS_MAX = 50;
	private static final int NB_COULEURS_MAX = 50;
	private static final float SEUIL_COULEUR = 2.5f;
	private static final int NB_BITS = 4;
	private static final int PAS_DECALAGE_FENETRE = 1;
	private static final int NB_ECHANTILLON_FENETRE = 1000;
	private static final int NB_INT_AMP = 16;

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
					bRechercheTexteFichier.Recherche(NB_RES,NB_MOTS_MAX,TAILLE_MIN_MOTS);
					break;
				case 2:
					bRechercheTexteMotsCles.Recherche(NB_RES,NB_MOTS_MAX,TAILLE_MIN_MOTS);
					break;
				case 3:
					bRechercheImageFichier.Recherche(NB_RES, NB_BITS, NB_COULEURS_MAX,SEUIL_COULEUR);
					break;
				case 4:
					bRechercheImageCouleur.Recherche(NB_RES, NB_BITS);
					break;
				case 5:
					bRechercheAudio.Recherche(PAS_DECALAGE_FENETRE, NB_ECHANTILLON_FENETRE, NB_INT_AMP);
					break;
				case 6:
					return;
			}
		}
	}
	
	public static void main(String[] args) {
		//MoteurC.setTest(true);
		
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
					bIndexation.indexation(NB_MOTS_MAX,TAILLE_MIN_MOTS,NB_COULEURS_MAX, SEUIL_COULEUR, NB_BITS, NB_ECHANTILLON_FENETRE, NB_INT_AMP);
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
