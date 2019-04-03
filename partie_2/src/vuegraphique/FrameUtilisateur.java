package vuegraphique;

import java.awt.BorderLayout;
import java.awt.EventQueue;
import java.io.File;

import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;

import modele.Recherche;

import javax.swing.JMenuBar;
import javax.swing.JMenu;
import javax.swing.JMenuItem;
import javax.swing.JCheckBoxMenuItem;
import javax.swing.JTabbedPane;

public class FrameUtilisateur extends JFrame {

	//sert a positionner les popup parcourir dans le dernier dossier vise
	public static File lastFile;
	
	private JPanel contentPane;

	/**
	 * Create the frame.
	 */
	public FrameUtilisateur() {
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setBounds(100, 100, 450, 300);
		setLocationRelativeTo(null);
		
		JMenuBar menuBar = new JMenuBar();
		setJMenuBar(menuBar);
		
		JMenu mnMoteurs = new JMenu("Moteurs");
		menuBar.add(mnMoteurs);
		
		JCheckBoxMenuItem chckbxmntmMoteurG = new JCheckBoxMenuItem("Moteur G3");
		chckbxmntmMoteurG.setSelected(true);
		mnMoteurs.add(chckbxmntmMoteurG);
		
		JMenu mnConfiguration = new JMenu("Configuration");
		menuBar.add(mnConfiguration);
		
		JMenuItem mntmModifierConfiguration = new JMenuItem("Modifier configuration");
		mnConfiguration.add(mntmModifierConfiguration);
		
		JMenu menu = new JMenu("?");
		menuBar.add(menu);
		
		JMenuItem mntmAide = new JMenuItem("Aide");
		menu.add(mntmAide);
		
		JMenuItem mntmAPropos = new JMenuItem("A propos");
		menu.add(mntmAPropos);
		contentPane = new JPanel();
		contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
		setContentPane(contentPane);
		contentPane.setLayout(new BorderLayout(0, 0));
		
		PanResultat panResultat = new PanResultat();
		contentPane.add(panResultat, BorderLayout.EAST);
		
		JTabbedPane tabbedPane = new JTabbedPane(JTabbedPane.TOP);
		contentPane.add(tabbedPane, BorderLayout.CENTER);
		
		PanTexte panTexte = new PanTexte();
		tabbedPane.addTab("Texte", null, panTexte, "Recherche dans les fichiers de texte");
		
		PanImage panImage = new PanImage();
		tabbedPane.addTab("Image", null, panImage, "Recherche d'image");
		
		PanAudio panAudio = new PanAudio();
		tabbedPane.addTab("Audio", null, panAudio, "Recherche de fichiers son");
	}
	
	public void actionFromHistory(Recherche rech) {
		
	}

}
