package vuegraphique;

import javax.swing.JPanel;
import java.awt.GridBagLayout;
import javax.swing.JButton;
import java.awt.GridBagConstraints;
import javax.swing.JTextField;
import java.awt.Insets;
import java.awt.Dimension;

public class PanAudio extends JPanel {
	private JTextField textField;

	/**
	 * Create the panel.
	 */
	public PanAudio() {
		GridBagLayout gridBagLayout = new GridBagLayout();
		gridBagLayout.columnWidths = new int[] {30, 30, 0};
		gridBagLayout.rowHeights = new int[] {0, 0, 0, 0};
		gridBagLayout.columnWeights = new double[]{8.0, 2.0, 0.0};
		gridBagLayout.rowWeights = new double[]{1.0, 0.0, 1.0, 0.0};
		setLayout(gridBagLayout);
		
		textField = new JTextField();
		textField.setMargin(new Insets(2, 0, 2, 2));
		GridBagConstraints gbc_textField = new GridBagConstraints();
		gbc_textField.gridwidth = 2;
		gbc_textField.fill = GridBagConstraints.BOTH;
		gbc_textField.gridx = 0;
		gbc_textField.gridy = 1;
		add(textField, gbc_textField);
		textField.setColumns(10);
		
		JButton btnParcourir = new JButton("...");
		btnParcourir.setMargin(new Insets(2, 2, 2, 0));
		btnParcourir.setPreferredSize(new Dimension(45, 23));
		GridBagConstraints gbc_btnParcourir = new GridBagConstraints();
		gbc_btnParcourir.fill = GridBagConstraints.BOTH;
		gbc_btnParcourir.gridx = 2;
		gbc_btnParcourir.gridy = 1;
		add(btnParcourir, gbc_btnParcourir);
		
		JButton btnRechercher = new JButton("Rechercher");
		btnRechercher.setPreferredSize(new Dimension(150, 40));
		GridBagConstraints gbc_btnRechercher = new GridBagConstraints();
		gbc_btnRechercher.fill = GridBagConstraints.BOTH;
		gbc_btnRechercher.gridwidth = 2;
		gbc_btnRechercher.gridx = 1;
		gbc_btnRechercher.gridy = 3;
		add(btnRechercher, gbc_btnRechercher);

	}

}
