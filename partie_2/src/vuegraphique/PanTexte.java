package vuegraphique;

import javax.swing.JPanel;
import java.awt.GridBagLayout;
import javax.swing.JRadioButton;
import java.awt.GridBagConstraints;
import javax.swing.JTextField;
import javax.swing.filechooser.FileNameExtensionFilter;

import controlleur.CRechercheTexteFichier;
import controlleur.CRechercheTexteMotsCles;

import java.awt.Insets;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.util.List;

import javax.swing.ButtonGroup;
import javax.swing.JButton;
import javax.swing.JFileChooser;

import java.awt.Dimension;

public class PanTexte extends JPanel {
	private static final long serialVersionUID = -2028779124140208538L;
	private CRechercheTexteFichier controllerRechercheFichier;
	private CRechercheTexteMotsCles controllerRechercheMots;
	private PanResultat panResultat;

	private JTextField champNomFichier;
	private JTextField champMotsCle;

	/**
	 * Create the panel.
	 */
	public PanTexte(CRechercheTexteFichier controllerTexteRechercheFichier,
			CRechercheTexteMotsCles controllerTexteRechercheMotsCles, PanResultat panResultat) {
		this.controllerRechercheFichier = controllerTexteRechercheFichier;
		this.controllerRechercheMots = controllerTexteRechercheMotsCles;
		this.panResultat = panResultat;

		GridBagLayout gridBagLayout = new GridBagLayout();
		gridBagLayout.columnWidths = new int[] { 0, 0, 126, 0 };
		gridBagLayout.rowHeights = new int[] { 0, 0, 0, 0, 0, 0 };
		gridBagLayout.columnWeights = new double[] { 0.0, 0.8, 0.2, 0.0 };
		gridBagLayout.rowWeights = new double[] { 0.0, 0.0, 0.0, 0.0, 1.0, 0.0 };
		setLayout(gridBagLayout);

		ButtonGroup radioBtnGroup = new ButtonGroup();

		JRadioButton rdbtnRechFichiersTextes = new JRadioButton("Recherche par fichiers texte");
		rdbtnRechFichiersTextes.setSelected(true);
		GridBagConstraints gbc_rdbtnRechFichiersTextes = new GridBagConstraints();
		gbc_rdbtnRechFichiersTextes.anchor = GridBagConstraints.WEST;
		gbc_rdbtnRechFichiersTextes.insets = new Insets(0, 0, 5, 5);
		gbc_rdbtnRechFichiersTextes.gridx = 0;
		gbc_rdbtnRechFichiersTextes.gridy = 0;
		add(rdbtnRechFichiersTextes, gbc_rdbtnRechFichiersTextes);
		radioBtnGroup.add(rdbtnRechFichiersTextes);

		champNomFichier = new JTextField();
		champNomFichier.setMargin(new Insets(2, 0, 2, 2));
		GridBagConstraints gbc_champNomFichier = new GridBagConstraints();
		gbc_champNomFichier.gridwidth = 3;
		gbc_champNomFichier.fill = GridBagConstraints.BOTH;
		gbc_champNomFichier.gridx = 0;
		gbc_champNomFichier.gridy = 1;
		add(champNomFichier, gbc_champNomFichier);
		champNomFichier.setColumns(10);

		JButton btnParcourir = new JButton("...");
		btnParcourir.setMargin(new Insets(2, 2, 2, 0));
		btnParcourir.setMaximumSize(new Dimension(20, 20));
		btnParcourir.setMinimumSize(new Dimension(20, 20));
		btnParcourir.setPreferredSize(new Dimension(20, 20));
		GridBagConstraints gbc_btnParcourir = new GridBagConstraints();
		gbc_btnParcourir.anchor = GridBagConstraints.WEST;
		gbc_btnParcourir.fill = GridBagConstraints.VERTICAL;
		gbc_btnParcourir.gridx = 3;
		gbc_btnParcourir.gridy = 1;
		add(btnParcourir, gbc_btnParcourir);
		btnParcourir.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent e) {
				parcourir();
			}
		});

		JRadioButton rdbtnRechMotsCle = new JRadioButton("Recherche par mots clés");
		GridBagConstraints gbc_rdbtnRechMotsCle = new GridBagConstraints();
		gbc_rdbtnRechMotsCle.anchor = GridBagConstraints.WEST;
		gbc_rdbtnRechMotsCle.insets = new Insets(0, 0, 5, 5);
		gbc_rdbtnRechMotsCle.gridx = 0;
		gbc_rdbtnRechMotsCle.gridy = 2;
		add(rdbtnRechMotsCle, gbc_rdbtnRechMotsCle);
		radioBtnGroup.add(rdbtnRechMotsCle);

		champMotsCle = new JTextField();
		champMotsCle.setMargin(new Insets(2, 0, 2, 0));
		GridBagConstraints gbc_champMotsCle = new GridBagConstraints();
		gbc_champMotsCle.gridwidth = 4;
		gbc_champMotsCle.fill = GridBagConstraints.BOTH;
		gbc_champMotsCle.gridx = 0;
		gbc_champMotsCle.gridy = 3;
		add(champMotsCle, gbc_champMotsCle);
		champMotsCle.setColumns(10);

		JButton btnValider = new JButton("Rechercher");
		btnValider.setMargin(new Insets(2, 0, 0, 0));
		btnValider.setPreferredSize(new Dimension(150, 40));
		GridBagConstraints gbc_btnValider = new GridBagConstraints();
		gbc_btnValider.fill = GridBagConstraints.BOTH;
		gbc_btnValider.gridwidth = 2;
		gbc_btnValider.gridx = 2;
		gbc_btnValider.gridy = 5;
		add(btnValider, gbc_btnValider);
		btnValider.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent e) {
				if (rdbtnRechFichiersTextes.isSelected())
					rechercheFichier(champNomFichier.getText());
				else
					rechercheMotsCle(champMotsCle.getText());
			}
		});

	}

	private void parcourir() {
		JFileChooser fc = new JFileChooser();
		FileNameExtensionFilter fnef = new FileNameExtensionFilter("Fichier texte (.xml)", "xml");
		fc.setFileFilter(fnef);
		fc.setDialogTitle("Choix du fichier texte");
		File f = FrameUtilisateur.lastFile;
		if (f != null)
			fc.setCurrentDirectory(f);
		int rVal = fc.showOpenDialog(this);
		if (rVal == JFileChooser.APPROVE_OPTION) {
			f = fc.getSelectedFile();
			FrameUtilisateur.lastFile = f.getParentFile();
			champNomFichier.setText(f.getAbsolutePath());
		}
	}

	private void rechercheFichier(String path) {
		List<String> resultats = controllerRechercheFichier.rechercherFichier(path);
		panResultat.setListContent(resultats,TypeRecherche.TEXTE);
	}

	private void rechercheMotsCle(String mots) {
		List<String> resultats = controllerRechercheMots.rechercherMotsCles(mots);
		panResultat.setListContent(resultats,TypeRecherche.TEXTE);
	}

}
