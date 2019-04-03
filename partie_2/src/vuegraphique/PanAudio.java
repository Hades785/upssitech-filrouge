package vuegraphique;

import javax.swing.JPanel;
import java.awt.GridBagLayout;
import javax.swing.JButton;
import javax.swing.JFileChooser;

import java.awt.GridBagConstraints;
import javax.swing.JTextField;
import javax.swing.filechooser.FileNameExtensionFilter;

import java.awt.Insets;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.awt.Dimension;
import javax.swing.JLabel;

@SuppressWarnings("serial")
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
		
		JLabel lblRechercheAudio = new JLabel("Recherche audio");
		GridBagConstraints gbc_lblRechercheAudio = new GridBagConstraints();
		gbc_lblRechercheAudio.anchor = GridBagConstraints.SOUTHWEST;
		gbc_lblRechercheAudio.insets = new Insets(0, 0, 5, 5);
		gbc_lblRechercheAudio.gridx = 0;
		gbc_lblRechercheAudio.gridy = 0;
		add(lblRechercheAudio, gbc_lblRechercheAudio);
		
		textField = new JTextField();
		textField.setMargin(new Insets(2, 0, 2, 2));
		GridBagConstraints gbc_textField = new GridBagConstraints();
		gbc_textField.insets = new Insets(0, 0, 5, 5);
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
		gbc_btnParcourir.insets = new Insets(0, 0, 5, 0);
		gbc_btnParcourir.fill = GridBagConstraints.BOTH;
		gbc_btnParcourir.gridx = 2;
		gbc_btnParcourir.gridy = 1;
		add(btnParcourir, gbc_btnParcourir);
		btnParcourir.addActionListener(new ActionListener() {
			
			@Override
			public void actionPerformed(ActionEvent e) {
				parcourir();
			}
		});
		
		JButton btnRechercher = new JButton("Rechercher");
		btnRechercher.setPreferredSize(new Dimension(150, 40));
		GridBagConstraints gbc_btnRechercher = new GridBagConstraints();
		gbc_btnRechercher.fill = GridBagConstraints.BOTH;
		gbc_btnRechercher.gridwidth = 2;
		gbc_btnRechercher.gridx = 1;
		gbc_btnRechercher.gridy = 3;
		add(btnRechercher, gbc_btnRechercher);
		btnRechercher.addActionListener(new ActionListener() {
			
			@Override
			public void actionPerformed(ActionEvent e) {
				rechercheAudio(textField.getText());
			}
		});

	}
	
	private void parcourir() {
		JFileChooser fc = new JFileChooser();
		FileNameExtensionFilter fnef = new FileNameExtensionFilter("Fichier audio en texte (.txt)", "txt");
		fc.setFileFilter(fnef);
		fc.setDialogTitle("Choix du fichier audio");
		File f = FrameUtilisateur.lastFile;
		if(f != null)
			fc.setCurrentDirectory(f);
		int rVal = fc.showOpenDialog(this);
		if(rVal == JFileChooser.APPROVE_OPTION) {
			f = fc.getSelectedFile();
			FrameUtilisateur.lastFile = f.getParentFile();
			textField.setText(f.getAbsolutePath());
		}
	}
	
	private void rechercheAudio(String chemin) {
		System.out.println("TODO Recherche audio\n"+chemin);
		//TODO Loic
	}

}
