package vuegraphique;

import javax.swing.JPanel;
import javax.swing.JList;
import java.awt.GridBagLayout;
import java.awt.GridBagConstraints;
import java.awt.Insets;
import java.util.List;
import java.awt.Dimension;

public class PanResultat extends JPanel {
	private JList<String> list;

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
		
		list = new JList<>();
		list.setMinimumSize(new Dimension(50, 0));
		list.setPreferredSize(new Dimension(200, 0));
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
	
	public void setListContent(List<String> resultats) {
		this.list.setListData((String[]) resultats.toArray(new String[0]));
	}

}
