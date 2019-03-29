package vuegraphique;

import javax.swing.JPanel;
import java.awt.GridBagLayout;
import javax.swing.JRadioButton;
import java.awt.GridBagConstraints;
import javax.swing.JTextField;
import java.awt.Insets;

import javax.swing.ButtonGroup;
import javax.swing.JButton;
import java.awt.Dimension;

public class PanTexte extends JPanel {
	private JTextField textField;
	private JTextField textField_1;

	/**
	 * Create the panel.
	 */
	public PanTexte() {
		GridBagLayout gridBagLayout = new GridBagLayout();
		gridBagLayout.columnWidths = new int[] {0, 0, 126, 0};
		gridBagLayout.rowHeights = new int[] {0, 0, 0, 0, 0, 0};
		gridBagLayout.columnWeights = new double[]{0.0, 0.8, 0.2, 0.0};
		gridBagLayout.rowWeights = new double[]{0.0, 0.0, 0.0, 0.0, 1.0, 0.0};
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
		
		textField = new JTextField();
		textField.setMargin(new Insets(2, 0, 2, 2));
		GridBagConstraints gbc_textField = new GridBagConstraints();
		gbc_textField.gridwidth = 3;
		gbc_textField.insets = new Insets(0, 0, 5, 5);
		gbc_textField.fill = GridBagConstraints.BOTH;
		gbc_textField.gridx = 0;
		gbc_textField.gridy = 1;
		add(textField, gbc_textField);
		textField.setColumns(10);
		
		JButton btnParcourir = new JButton("...");
		btnParcourir.setMargin(new Insets(2, 2, 2, 0));
		btnParcourir.setMaximumSize(new Dimension(20, 20));
		btnParcourir.setMinimumSize(new Dimension(20, 20));
		btnParcourir.setPreferredSize(new Dimension(20, 20));
		GridBagConstraints gbc_btnParcourir = new GridBagConstraints();
		gbc_btnParcourir.anchor = GridBagConstraints.WEST;
		gbc_btnParcourir.fill = GridBagConstraints.VERTICAL;
		gbc_btnParcourir.insets = new Insets(0, 0, 5, 0);
		gbc_btnParcourir.gridx = 3;
		gbc_btnParcourir.gridy = 1;
		add(btnParcourir, gbc_btnParcourir);
		
		JRadioButton rdbtnRechMotsCle = new JRadioButton("Recherche par mots clés");
		GridBagConstraints gbc_rdbtnRechMotsCle = new GridBagConstraints();
		gbc_rdbtnRechMotsCle.anchor = GridBagConstraints.WEST;
		gbc_rdbtnRechMotsCle.insets = new Insets(0, 0, 5, 5);
		gbc_rdbtnRechMotsCle.gridx = 0;
		gbc_rdbtnRechMotsCle.gridy = 2;
		add(rdbtnRechMotsCle, gbc_rdbtnRechMotsCle);
		radioBtnGroup.add(rdbtnRechMotsCle);
		
		textField_1 = new JTextField();
		textField_1.setMargin(new Insets(2, 0, 2, 0));
		GridBagConstraints gbc_textField_1 = new GridBagConstraints();
		gbc_textField_1.gridwidth = 4;
		gbc_textField_1.insets = new Insets(0, 0, 5, 5);
		gbc_textField_1.fill = GridBagConstraints.BOTH;
		gbc_textField_1.gridx = 0;
		gbc_textField_1.gridy = 3;
		add(textField_1, gbc_textField_1);
		textField_1.setColumns(10);
		
		JButton btnValider = new JButton("Rechercher");
		btnValider.setMargin(new Insets(2, 0, 0, 0));
		btnValider.setPreferredSize(new Dimension(150, 40));
		GridBagConstraints gbc_btnValider = new GridBagConstraints();
		gbc_btnValider.fill = GridBagConstraints.BOTH;
		gbc_btnValider.gridwidth = 2;
		gbc_btnValider.gridx = 2;
		gbc_btnValider.gridy = 5;
		add(btnValider, gbc_btnValider);

	}

}
