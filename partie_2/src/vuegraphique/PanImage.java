package vuegraphique;

import javax.swing.JPanel;
import java.awt.GridBagLayout;
import javax.swing.JRadioButton;
import java.awt.GridBagConstraints;
import javax.swing.JTextField;
import java.awt.Insets;

import javax.swing.ButtonGroup;
import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JFormattedTextField;
import java.awt.Dimension;
import java.awt.BorderLayout;
import java.awt.Color;

public class PanImage extends JPanel {
	private JTextField champCheminImage;

	/**
	 * Create the panel.
	 */
	public PanImage() {
		GridBagLayout gridBagLayout = new GridBagLayout();
		gridBagLayout.columnWidths = new int[]{0, 0, 78, 12, 0, 0, 0, 0};
		gridBagLayout.rowHeights = new int[]{0, 0, 0, 0, 0, 0, 0, 0, 0};
		gridBagLayout.columnWeights = new double[]{0.0, 0.0, 0.0, 8.0, 1.0, 2.0, 0.0, Double.MIN_VALUE};
		gridBagLayout.rowWeights = new double[]{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, Double.MIN_VALUE};
		setLayout(gridBagLayout);
		
		ButtonGroup radioGroup = new ButtonGroup();
		
		JRadioButton rdbtnRechercheParComparaison = new JRadioButton("Recherche par comparaison d'image");
		rdbtnRechercheParComparaison.setSelected(true);
		GridBagConstraints gbc_rdbtnRechercheParComparaison = new GridBagConstraints();
		gbc_rdbtnRechercheParComparaison.anchor = GridBagConstraints.WEST;
		gbc_rdbtnRechercheParComparaison.gridwidth = 3;
		gbc_rdbtnRechercheParComparaison.insets = new Insets(0, 0, 5, 5);
		gbc_rdbtnRechercheParComparaison.gridx = 0;
		gbc_rdbtnRechercheParComparaison.gridy = 0;
		add(rdbtnRechercheParComparaison, gbc_rdbtnRechercheParComparaison);
		radioGroup.add(rdbtnRechercheParComparaison);
		
		champCheminImage = new JTextField();
		champCheminImage.setMargin(new Insets(2, 0, 2, 2));
		GridBagConstraints gbc_champCheminImage = new GridBagConstraints();
		gbc_champCheminImage.gridwidth = 6;
		gbc_champCheminImage.fill = GridBagConstraints.BOTH;
		gbc_champCheminImage.gridx = 0;
		gbc_champCheminImage.gridy = 1;
		add(champCheminImage, gbc_champCheminImage);
		champCheminImage.setColumns(10);
		
		JButton btnParcourir = new JButton("...");
		btnParcourir.setMargin(new Insets(2, 2, 2, 0));
		GridBagConstraints gbc_btnParcourir = new GridBagConstraints();
		gbc_btnParcourir.fill = GridBagConstraints.BOTH;
		gbc_btnParcourir.gridx = 6;
		gbc_btnParcourir.gridy = 1;
		add(btnParcourir, gbc_btnParcourir);
		
		JRadioButton rdbtnRechercheParCouleur = new JRadioButton("Recherche par couleur");
		GridBagConstraints gbc_rdbtnRechercheParCouleur = new GridBagConstraints();
		gbc_rdbtnRechercheParCouleur.anchor = GridBagConstraints.WEST;
		gbc_rdbtnRechercheParCouleur.gridwidth = 3;
		gbc_rdbtnRechercheParCouleur.insets = new Insets(0, 0, 5, 5);
		gbc_rdbtnRechercheParCouleur.gridx = 0;
		gbc_rdbtnRechercheParCouleur.gridy = 2;
		add(rdbtnRechercheParCouleur, gbc_rdbtnRechercheParCouleur);
		radioGroup.add(rdbtnRechercheParCouleur);
		
		JLabel lblRouge = new JLabel("Rouge :");
		GridBagConstraints gbc_lblRouge = new GridBagConstraints();
		gbc_lblRouge.anchor = GridBagConstraints.EAST;
		gbc_lblRouge.insets = new Insets(0, 5, 5, 5);
		gbc_lblRouge.gridx = 0;
		gbc_lblRouge.gridy = 3;
		add(lblRouge, gbc_lblRouge);
		
		JFormattedTextField fieldRouge = new JFormattedTextField();
		fieldRouge.setPreferredSize(new Dimension(40, 20));
		fieldRouge.setMinimumSize(new Dimension(40, 20));
		GridBagConstraints gbc_fieldRouge = new GridBagConstraints();
		gbc_fieldRouge.insets = new Insets(0, 0, 5, 5);
		gbc_fieldRouge.fill = GridBagConstraints.HORIZONTAL;
		gbc_fieldRouge.gridx = 1;
		gbc_fieldRouge.gridy = 3;
		add(fieldRouge, gbc_fieldRouge);
		
		JPanel panel = new JPanel();
		panel.setPreferredSize(new Dimension(50, 10));
		GridBagConstraints gbc_panel = new GridBagConstraints();
		gbc_panel.gridwidth = 3;
		gbc_panel.gridheight = 3;
		gbc_panel.insets = new Insets(0, 0, 5, 5);
		gbc_panel.fill = GridBagConstraints.BOTH;
		gbc_panel.gridx = 2;
		gbc_panel.gridy = 3;
		add(panel, gbc_panel);
		panel.setLayout(new BorderLayout(0, 0));
		
		JButton btnColorPicker = new JButton("Color picker");
		panel.add(btnColorPicker, BorderLayout.EAST);
		
		JPanel panel_1 = new JPanel();
		panel.add(panel_1, BorderLayout.CENTER);
		GridBagLayout gbl_panel_1 = new GridBagLayout();
		gbl_panel_1.columnWidths = new int[] {0, 0, 0, 0};
		gbl_panel_1.rowHeights = new int[]{0, 0};
		gbl_panel_1.columnWeights = new double[]{1.0, 0.0, 1.0, Double.MIN_VALUE};
		gbl_panel_1.rowWeights = new double[]{1.0, Double.MIN_VALUE};
		panel_1.setLayout(gbl_panel_1);
		
		JPanel panel_2 = new JPanel();
		panel_2.setBackground(Color.GREEN);
		panel_2.setPreferredSize(new Dimension(70, 10));
		GridBagConstraints gbc_panel_2 = new GridBagConstraints();
		gbc_panel_2.insets = new Insets(0, 0, 0, 5);
		gbc_panel_2.fill = GridBagConstraints.BOTH;
		gbc_panel_2.gridx = 1;
		gbc_panel_2.gridy = 0;
		panel_1.add(panel_2, gbc_panel_2);
		
		JLabel lblVert = new JLabel("Vert :");
		GridBagConstraints gbc_lblVert = new GridBagConstraints();
		gbc_lblVert.anchor = GridBagConstraints.EAST;
		gbc_lblVert.insets = new Insets(0, 0, 5, 5);
		gbc_lblVert.gridx = 0;
		gbc_lblVert.gridy = 4;
		add(lblVert, gbc_lblVert);
		
		JFormattedTextField fieldVert = new JFormattedTextField();
		fieldVert.setMinimumSize(new Dimension(40, 20));
		fieldVert.setPreferredSize(new Dimension(40, 20));
		GridBagConstraints gbc_fieldVert = new GridBagConstraints();
		gbc_fieldVert.insets = new Insets(0, 0, 5, 5);
		gbc_fieldVert.fill = GridBagConstraints.HORIZONTAL;
		gbc_fieldVert.gridx = 1;
		gbc_fieldVert.gridy = 4;
		add(fieldVert, gbc_fieldVert);
		
		JLabel lblBleu = new JLabel("Bleu :");
		GridBagConstraints gbc_lblBleu = new GridBagConstraints();
		gbc_lblBleu.anchor = GridBagConstraints.EAST;
		gbc_lblBleu.insets = new Insets(0, 0, 5, 5);
		gbc_lblBleu.gridx = 0;
		gbc_lblBleu.gridy = 5;
		add(lblBleu, gbc_lblBleu);
		
		JFormattedTextField fieldBleu = new JFormattedTextField();
		fieldBleu.setMinimumSize(new Dimension(40, 20));
		fieldBleu.setPreferredSize(new Dimension(40, 20));
		GridBagConstraints gbc_fieldBleu = new GridBagConstraints();
		gbc_fieldBleu.insets = new Insets(0, 0, 5, 5);
		gbc_fieldBleu.fill = GridBagConstraints.HORIZONTAL;
		gbc_fieldBleu.gridx = 1;
		gbc_fieldBleu.gridy = 5;
		add(fieldBleu, gbc_fieldBleu);
		
		JButton btnValider = new JButton("Rechercher");
		btnValider.setPreferredSize(new Dimension(150, 40));
		GridBagConstraints gbc_btnValider = new GridBagConstraints();
		gbc_btnValider.fill = GridBagConstraints.BOTH;
		gbc_btnValider.gridwidth = 3;
		gbc_btnValider.gridx = 4;
		gbc_btnValider.gridy = 7;
		add(btnValider, gbc_btnValider);

	}

}
