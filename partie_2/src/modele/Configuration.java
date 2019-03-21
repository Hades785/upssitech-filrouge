package modele;

public class Configuration {

	// param�tres de configuration texte

	private String cheminBDTexte;
	private int nbMotsMaxTexte; // Nombre de mots maximum retenus par fichier
	private int tailleMinMot; // Taille minimale des mots retenus
	private int nbrResTexte; // -Nombre de r�sultats de recherche texte

	// param�tres de configuration image

	private String cheminBDImage;
	private int nbBitsImage; // Nombre de bits de quantification par couleur
	private int nbCouleursMaxImage; // Nombre de couleurs maximum m�moris�es par image
	private float seuilCouleurImage; // Seuil minimal de consid�ration d'une couleur (en % de couverture de l'image)
	private int nbResImage; // Nombre de r�sultats de recherche image

	//// param�tres de configuration audio

	private String cheminBDAudio;
	private int nbEchantParFen; // Nombre d'�chantillons par fen�tre
	private int nbInterAmp; // Nombre d'intervalles en amplitude
	private int nbrFenetres; // Nombre de fen�tres de d�calage entre mesure

	public Configuration() {

		// Initialisation des param�tres par d�faut
		cheminBDTexte = "/mnt/e/upssitech-filrouge/documents/texte";
		cheminBDImage = "/mnt/e/upssitech-filrouge/documents/images";
		cheminBDAudio = "/mnt/e/upssitech-filrouge/documents/audio";

		nbMotsMaxTexte = 30;
		tailleMinMot = 3;
		nbrResTexte = 15;

		nbBitsImage = 4;
		nbCouleursMaxImage = 50;
		seuilCouleurImage = (float) 0.1;
		nbResImage = 15;

		nbEchantParFen = 1000;
		nbInterAmp = 16;
		nbrFenetres = 1;

	}

	public String getCheminBDTexte() {
		return cheminBDTexte;
	}

	public void setCheminBDTexte(String cheminBDTexte) {
		this.cheminBDTexte = cheminBDTexte;
	}

	public int getNbMotsMaxTexte() {
		return nbMotsMaxTexte;
	}

	public void setNbMotsMaxTexte(int nbMotsMaxTexte) {
		this.nbMotsMaxTexte = nbMotsMaxTexte;
	}

	public int getTailleMinMot() {
		return tailleMinMot;
	}

	public void setTailleMinMot(int tailleMinMot) {
		this.tailleMinMot = tailleMinMot;
	}

	public int getNbrResTexte() {
		return nbrResTexte;
	}

	public void setNbrResTexte(int nbrResTexte) {
		this.nbrResTexte = nbrResTexte;
	}

	public String getCheminBDImage() {
		return cheminBDImage;
	}

	public void setCheminBDImage(String cheminBDImage) {
		this.cheminBDImage = cheminBDImage;
	}

	public int getNbBitsImage() {
		return nbBitsImage;
	}

	public void setNbBitsImage(int nbBitsImage) {
		this.nbBitsImage = nbBitsImage;
	}

	public int getNbCouleursMaxImage() {
		return nbCouleursMaxImage;
	}

	public void setNbCouleursMaxImage(int nbCouleursMaxImage) {
		this.nbCouleursMaxImage = nbCouleursMaxImage;
	}

	public float getSeuilCouleurImage() {
		return seuilCouleurImage;
	}

	public void setSeuilCouleurImage(float seuilCouleurImage) {
		this.seuilCouleurImage = seuilCouleurImage;
	}

	public int getNbResImage() {
		return nbResImage;
	}

	public void setNbResImage(int nbResImage) {
		this.nbResImage = nbResImage;
	}

	public String getCheminBDAudio() {
		return cheminBDAudio;
	}

	public void setCheminBDAudio(String cheminBDAudio) {
		this.cheminBDAudio = cheminBDAudio;
	}

	public int getNbEchantParFen() {
		return nbEchantParFen;
	}

	public void setNbEchantParFen(int nbEchantParFen) {
		this.nbEchantParFen = nbEchantParFen;
	}

	public int getNbInterAmp() {
		return nbInterAmp;
	}

	public void setNbInterAmp(int nbInterAmp) {
		this.nbInterAmp = nbInterAmp;
	}

	public int getNbrFenetres() {
		return nbrFenetres;
	}

	public void setNbrFenetres(int nbrFenetres) {
		this.nbrFenetres = nbrFenetres;
	}

}
