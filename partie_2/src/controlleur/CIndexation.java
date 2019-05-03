package controlleur;

import java.io.File;

import javax.swing.JFileChooser;

import jni.MoteurC;

public class CIndexation {
	private CConfiguration configuration;
	
	private static final String STORAGE_FOLDER_NAME = "PFilRouge";
	private static final String NOM_FICH_DESC_TEXT = "base_textes.desc";
	private static final String NOM_FICH_MAP_NOM_TEXT = "map_id_nom.desc";
	private static final String NOM_FICH_MAP_MOTS = "map_mots.desc";
	private static final String NOM_FICH_DESC_IMG = "base_images.desc";
	private static final String NOM_FICH_DESC_AUD = "base_audio.desc";

	public CIndexation(CConfiguration c) {
		configuration = c;
	}

	public void indexation() {
		int nbMotsMax = configuration.getNbMotsMaxTexte();
		int tailleMinMot = configuration.getTailleMinMot();
		int nbCouleursMax = configuration.getNbCouleursMaxImage();
		float seuilCouleur = configuration.getSeuilCouleurImage();
		int nbBits = configuration.getNbBitsImage();
		int nbEchantillonPFenetre = configuration.getNbEchantParFen();
		int nbIntAmp = configuration.getNbInterAmp();

		String cheminTexte = configuration.getCheminBDTexte();
		String cheminImage = configuration.getCheminBDImage();
		String cheminAudio = configuration.getCheminBDAudio();

		// TODO rajouter le nom de la classe pour les methodes statiques
		MoteurC.indexerTexte(cheminTexte, nbMotsMax, tailleMinMot);
		MoteurC.indexerImage(cheminImage, nbCouleursMax, seuilCouleur, nbBits);
		MoteurC.indexerAudio(cheminAudio, nbEchantillonPFenetre, nbIntAmp);
	}
	
	//teste si les dossiers existent, les crees et fait la premiere indexation
	public void setup() {
		boolean index = false;
		String homeDirPath = System.getenv("HOME")+"/"+STORAGE_FOLDER_NAME;
		File homeDir = new File(homeDirPath);
		if(homeDir.exists()) {
			if(!new File(homeDirPath+"/"+NOM_FICH_DESC_TEXT).exists() || !new File(homeDirPath+"/"+NOM_FICH_MAP_NOM_TEXT).exists()
					|| !new File(homeDirPath+"/"+NOM_FICH_MAP_MOTS).exists()
					|| !new File(homeDirPath+"/"+NOM_FICH_DESC_IMG).exists()
					|| !new File(homeDirPath+"/"+NOM_FICH_DESC_AUD).exists()) {
				index = true;
			}
		}else {
			homeDir.mkdir();
			index = true;
		}
		if(validateExistanceBaseFichiers()) index = true;
		if(index)
			indexation();
	}
	
	private boolean validateExistanceBaseFichiers() {
		boolean resp = false;
		if(!new File(configuration.getCheminBDTexte()).exists()) {
			File bdTexte;
			do {
				bdTexte = showFileChooser(new File("./"), "Selectionnez le dossier contenant les fichiers textes");
			}while(bdTexte == null);
			resp = true;
		}
		if(!new File(configuration.getCheminBDImage()).exists()) {
			File bdImage;
			do {
				bdImage = showFileChooser(new File("./"), "Selectionnez le dossier contenant les fichiers images");
			}while(bdImage == null);
			resp = true;
		}
		if(!new File(configuration.getCheminBDAudio()).exists()) {
			File bdAudio;
			do {
				bdAudio = showFileChooser(new File("./"), "Selectionnez le dossier contenant les fichiers audio");
			}while(bdAudio == null);
			resp = true;
		}
		return resp;
	}
	
	private File showFileChooser(File origin,String title) {
		JFileChooser fc = new JFileChooser();
		if(origin != null) {
			if(origin.isDirectory())
				fc.setCurrentDirectory(origin);
			else
				fc.setCurrentDirectory(origin.getParentFile());
		}
		fc.setDialogTitle(title);
		fc.setFileSelectionMode(JFileChooser.DIRECTORIES_ONLY);
		fc.setAcceptAllFileFilterUsed(false);
		if(fc.showOpenDialog(null) == JFileChooser.APPROVE_OPTION)
			return fc.getSelectedFile();
		else
			return null;
	}
}
