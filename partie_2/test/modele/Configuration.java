package modele;

public class Configuration {
	
	//paramètres de configuration texte
	
	String cheminBDTexte;
	int nbMotsMaxTexte;  //Nombre de mots maximum retenus par fichier
	int tailleMinMot;  //Taille minimale des mots retenus
	int nbrResTexte;  //-Nombre de résultats de recherche texte
	
	//paramètres de configuration image
	
	String cheminBDImage;
	int nbBitsImage;  //Nombre de bits de quantification par couleur
	int nbCouleursMaxImage; //Nombre de couleurs maximum mémorisées par image
	float seuilCouleurImage; //Seuil minimal de considération d'une couleur (en % de couverture de l'image)
	int nbResImage;  //Nombre de résultats de recherche image
	
	////paramètres de configuration audio
	
	String cheminBDAudio;
	int nbEchantParFen;  //Nombre d'échantillons par fenêtre
	int nbInterAmp;  //Nombre d'intervalles en amplitude
	int nbrFenetres;  //Nombre de fenêtres de décalage entre mesure
	
	
	public Configuration() {
		 
	//Initialisation des paramètres par défaut 
		 cheminBDTexte="/mnt/e/upssitech-filrouge/documents/texte";
		 cheminBDImage="/mnt/e/upssitech-filrouge/documents/images";
		 cheminBDAudio="/mnt/e/upssitech-filrouge/documents/audio";
		 
		 
		 nbMotsMaxTexte=30; 
		 tailleMinMot=3;  
		 nbrResTexte=15; 
		
		 nbBitsImage=4;  
		 nbCouleursMaxImage=50; 
		 seuilCouleurImage=(float) 0.1; 
		 nbResImage=15;  
		
		 nbEchantParFen=1000; 
		 nbInterAmp=16;  
		 nbrFenetres=1;
	
	}
	
	//Fonctions de Configuration Texte
	
	public void configCheminTexte(String nouveauChemin) {
		cheminBDTexte=nouveauChemin;
	}
		
	public void configNbMotsMaxTexte(int nbMotsMaxTexte) {
		this.nbMotsMaxTexte=nbMotsMaxTexte;
	}
	
	public void configTailleMinMot(int tailleMinMot) {
		this.tailleMinMot=tailleMinMot;
	}
	
	public void configNbResTexte(int nbResTexte) {
		this.nbrResTexte=nbResTexte;
	}
	
	//Fonctions de Configuration image
	
	public void configCheminImage(String nouveauChemin) {
		cheminBDImage=nouveauChemin;
	}
	
	public void configNBitsImage(int nbBitsImage) {
		this.nbBitsImage=nbBitsImage;
	}
	
	public void configNbCouleursMaxImage(int nbCouleurMaxImage) {
		this.nbCouleursMaxImage=nbCouleurMaxImage;
	}
	
	public void configSeuilCouleurImage(float  seuilCouleurImage) {
		this.seuilCouleurImage=this.seuilCouleurImage;
	}
	

	public void configNbResImage(int nbResImage) {
		this.nbResImage=nbResImage;
	}
	
	//Fonctions de Configuration audio
	
	public void configCheminAudio(String nouveauChemin) {
		cheminBDAudio=nouveauChemin;
	}
	
	public void nbEchantParFen(int nbEchantParFen) {
		this.nbEchantParFen=nbEchantParFen;
	}
	
	public void nbInterAmp(int nbInterAmp) {
		this.nbInterAmp=nbInterAmp;
	}
	
	public void nbrFenetres(int nbrFenetre) {
		this.nbInterAmp=nbInterAmp;
	}
	
	
	
}
