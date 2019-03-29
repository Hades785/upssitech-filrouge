package vuegraphique;

import javax.swing.JPanel;
import javax.swing.JList;
import java.awt.GridBagLayout;
import java.awt.GridBagConstraints;
import java.awt.Insets;

public class PanResultat extends JPanel {

	/**
	 * Create the panel.
	 */
	public PanResultat() {
		GridBagLayout gridBagLayout = new GridBagLayout();
		gridBagLayout.columnWidths = new int[]{0, 0};
		gridBagLayout.rowHeights = new int[]{0, 0, 0};
		gridBagLayout.columnWeights = new double[]{1.0, Double.MIN_VALUE};
		gridBagLayout.rowWeights = new double[]{1.0, 1.0, Double.MIN_VALUE};
		setLayout(gridBagLayout);
		
		JList list = new JList();
		GridBagConstraints gbc_list = new GridBagConstraints();
		gbc_list.insets = new Insets(0, 0, 5, 0);
		gbc_list.fill = GridBagConstraints.BOTH;
		gbc_list.gridx = 0;
		gbc_list.gridy = 0;
		add(list, gbc_list);
		
		PanPreview panPreview = new PanPreview();
		GridBagConstraints gbc_panPreview = new GridBagConstraints();
		gbc_panPreview.fill = GridBagConstraints.BOTH;
		gbc_panPreview.gridx = 0;
		gbc_panPreview.gridy = 1;
		add(panPreview, gbc_panPreview);

	}

}
