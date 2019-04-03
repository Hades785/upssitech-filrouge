package testGraphique;

import javax.swing.UIManager;
import javax.swing.UnsupportedLookAndFeelException;

import controlleur.CRechercheAudio;
import controlleur.CRechercheImageCouleur;
import controlleur.CRechercheImageFichier;
import controlleur.CRechercheTexteFichier;
import controlleur.CRechercheTexteMotsCles;
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

		CRechercheTexteFichier controllerRechercheTexteFichier = new CRechercheTexteFichier();
		CRechercheTexteMotsCles controllerRechercheTexteMotsCles = new CRechercheTexteMotsCles();
		CRechercheImageFichier controllerRechercheImageFichier = new CRechercheImageFichier();
		CRechercheImageCouleur controllerRechercheImageCouleur = new CRechercheImageCouleur();
		CRechercheAudio controllerRechercheAudio = new CRechercheAudio();

		FrameUtilisateur frame = new FrameUtilisateur(controllerRechercheTexteFichier, controllerRechercheTexteMotsCles,
				controllerRechercheImageFichier, controllerRechercheImageCouleur, controllerRechercheAudio);
		frame.setVisible(true);
	}
}
