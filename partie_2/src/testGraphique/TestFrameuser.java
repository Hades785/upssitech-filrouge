package testGraphique;

import javax.swing.UIManager;
import javax.swing.UnsupportedLookAndFeelException;

import controlleur.CConfiguration;
import controlleur.CHistorique;
import controlleur.CIndexation;
import controlleur.CRechercheAudio;
import controlleur.CRechercheImageCouleur;
import controlleur.CRechercheImageFichier;
import controlleur.CRechercheTexteFichier;
import controlleur.CRechercheTexteMotsCles;
import vue_console.BIndexation;
import vuegraphique.FrameUtilisateur;

public class TestFrameuser {
	public static void main(String[] args) {
		if (args.length > 0 && args[0] == "-s") {
			try {
				UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
				System.out.println("GKT skin not found, using system skin instead");
			} catch (ClassNotFoundException | InstantiationException | IllegalAccessException
					| UnsupportedLookAndFeelException e1) {
				System.out.println("GTK and system skin cannot be found. You are stuck with this ugly thing, sorry !");
			}
		} else if (args.length == 0) {
			try {

				UIManager.setLookAndFeel("com.sun.java.swing.plaf.gtk.GTKLookAndFeel");
			} catch (ClassNotFoundException | InstantiationException | IllegalAccessException
					| UnsupportedLookAndFeelException e) {
				try {
					UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
					System.out.println("GKT skin not found, using system skin instead");
				} catch (ClassNotFoundException | InstantiationException | IllegalAccessException
						| UnsupportedLookAndFeelException e1) {
					System.out.println(
							"GTK and system skin cannot be found. You are stuck with this ugly thing, sorry !");
				}
			}
		}
		

		CConfiguration controllerConfiguration = new CConfiguration();
		CIndexation cindex = new CIndexation(controllerConfiguration);
		BIndexation bIndexation = new BIndexation(cindex);
		CHistorique controllerHistorique = new CHistorique();
		CRechercheTexteFichier controllerRechercheTexteFichier = new CRechercheTexteFichier(controllerConfiguration, controllerHistorique);
		CRechercheTexteMotsCles controllerRechercheTexteMotsCles = new CRechercheTexteMotsCles(controllerConfiguration, controllerHistorique);
		CRechercheImageFichier controllerRechercheImageFichier = new CRechercheImageFichier(controllerConfiguration, controllerHistorique);
		CRechercheImageCouleur controllerRechercheImageCouleur = new CRechercheImageCouleur(controllerConfiguration, controllerHistorique);
		CRechercheAudio controllerRechercheAudio = new CRechercheAudio(controllerConfiguration, controllerHistorique);

		//cindex.setup();
		
		FrameUtilisateur frame = new FrameUtilisateur(controllerRechercheTexteFichier, controllerRechercheTexteMotsCles,
				controllerRechercheImageFichier, controllerRechercheImageCouleur, controllerRechercheAudio, cindex);
		frame.setVisible(true);
	}
}
