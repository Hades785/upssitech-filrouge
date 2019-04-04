package controlleur;

import modele.Configuration;

public class CConfiguration {
	private Configuration configuration;

	public CConfiguration() {
		// TODO fectch existing configuration
		
		configuration = new Configuration();
	}

	public String getCheminBDTexte() {
		return configuration.getCheminBDTexte();
	}

	public void setCheminBDTexte(String cheminBDTexte) {
		configuration.setCheminBDTexte(cheminBDTexte);
	}

	public int getNbMotsMaxTexte() {
		return configuration.getNbMotsMaxTexte();
	}

	public void setNbMotsMaxTexte(int nbMotsMaxTexte) {
		configuration.setNbMotsMaxTexte(nbMotsMaxTexte);
	}

	public int getTailleMinMot() {
		return configuration.getTailleMinMot();
	}

	public int getNbrResTexte() {
		return configuration.getNbrResTexte();
	}

	public void setNbrResTexte(int nbrResTexte) {
		configuration.setNbrResTexte(nbrResTexte);
	}

	public String getCheminBDImage() {
		return configuration.getCheminBDImage();
	}

	public void setCheminBDImage(String cheminBDImage) {
		configuration.setCheminBDImage(cheminBDImage);
	}

	public int getNbBitsImage() {
		return configuration.getNbBitsImage();
	}

	public void setNbBitsImage(int nbBitsImage) {
		configuration.setNbBitsImage(nbBitsImage);
	}

	public int getNbCouleursMaxImage() {
		return configuration.getNbCouleursMaxImage();
	}

	public void setNbCouleursMaxImage(int nbCouleursMaxImage) {
		configuration.setNbCouleursMaxImage(nbCouleursMaxImage);
	}

	public float getSeuilCouleurImage() {
		return configuration.getSeuilCouleurImage();
	}

	public void setSeuilCouleurImage(float seuilCouleurImage) {
		configuration.setSeuilCouleurImage(seuilCouleurImage);
	}

	public int getNbResImage() {
		return configuration.getNbResImage();
	}

	public void setNbResImage(int nbResImage) {
		configuration.setNbResImage(nbResImage);
	}

	public String getCheminBDAudio() {
		return configuration.getCheminBDAudio();
	}

	public void setCheminBDAudio(String cheminBDAudio) {
		configuration.setCheminBDAudio(cheminBDAudio);
	}

	public int getNbEchantParFen() {
		return configuration.getNbEchantParFen();
	}

	public void setNbEchantParFen(int nbEchantParFen) {
		configuration.setNbEchantParFen(nbEchantParFen);
	}

	public int getNbInterAmp() {
		return configuration.getNbInterAmp();
	}

	public void setNbInterAmp(int nbInterAmp) {
		configuration.setNbInterAmp(nbInterAmp);
	}

	public int getNbrFenetres() {
		return configuration.getNbrFenetres();
	}

	public void setNbrFenetres(int nbrFenetres) {
		configuration.setNbrFenetres(nbrFenetres);
	}
}
