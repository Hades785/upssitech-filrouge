package vuegraphique;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;

import javax.swing.JFrame;
import javax.swing.JSplitPane;

import controlleur.CIndexation;
import controlleur.CRechercheAudio;
import controlleur.CRechercheImageCouleur;
import controlleur.CRechercheImageFichier;
import controlleur.CRechercheTexteFichier;
import controlleur.CRechercheTexteMotsCles;

import javax.swing.JMenuBar;
import javax.swing.JMenu;
import javax.swing.JMenuItem;
import javax.swing.JCheckBoxMenuItem;
import javax.swing.JTabbedPane;

public class FrameUtilisateur extends JFrame {

	private static final long serialVersionUID = 4575907753415724077L;
	
	private CRechercheTexteFichier crtf;
	private CRechercheTexteMotsCles crtmc;
	private CRechercheImageFichier crif;
	private CRechercheImageCouleur cric;
	private CRechercheAudio cra;
	
	private CIndexation cindex;
	
	private PanResultat panRes;

	// sert a positionner les popup parcourir dans le dernier dossier vise
	public static File lastFile;
	
	private void setupMenuBar() {
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
		
		JMenuItem mntmReindexer = new JMenuItem("Reindexer les bases de fichiers");
		mnConfiguration.add(mntmReindexer);
		mntmReindexer.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				// TODO Auto-generated method stub
				
			}
		});

		JMenu menu = new JMenu("?");
		menuBar.add(menu);

		JMenuItem mntmAide = new JMenuItem("Aide");
		menu.add(mntmAide);

		JMenuItem mntmAPropos = new JMenuItem("A propos");
		menu.add(mntmAPropos);
	}
	
	private JTabbedPane setupTabPane() {
		if(panRes == null)
			throw new Error("Cannot instanciate Panels without panRes set (Arthur)");
		JTabbedPane tabbedPane = new JTabbedPane(JTabbedPane.TOP);
		
		PanTexte panTexte = new PanTexte(crtf, crtmc, panRes);
		tabbedPane.addTab("Texte", null, panTexte, "Recherche dans les fichiers de texte");

		PanImage panImage = new PanImage(crif, cric, panRes);
		tabbedPane.addTab("Image", null, panImage, "Recherche d'image");

		PanAudio panAudio = new PanAudio(cra, panRes);
		tabbedPane.addTab("Audio", null, panAudio, "Recherche de fichiers son");
		
		return tabbedPane;
	}

	/**
	 * Create the frame.
	 */
	public FrameUtilisateur(CRechercheTexteFichier crtf,
			CRechercheTexteMotsCles crtmc,
			CRechercheImageFichier crif,
			CRechercheImageCouleur cric,
			CRechercheAudio cra,
			CIndexation cindex) {
		
		this.crtf = crtf;
		this.crtmc = crtmc;
		this.crif = crif;
		this.cric = cric;
		this.cra = cra;
		this.cindex = cindex;
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setBounds(100, 100, 650, 300);
		setLocationRelativeTo(null);
		setTitle("Soft search");
		
		this.panRes = new PanResultat();

		setupMenuBar();
		
		JSplitPane sp = new JSplitPane(JSplitPane.HORIZONTAL_SPLIT);
		
		sp.setLeftComponent(setupTabPane());

		sp.setRightComponent(panRes);
		
		this.setContentPane(sp);
	}

}
