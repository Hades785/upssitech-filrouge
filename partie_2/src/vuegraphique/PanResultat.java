package vuegraphique;

import javax.swing.JSplitPane;
import javax.swing.JList;
import java.util.List;
import java.awt.Dimension;

public class PanResultat extends JSplitPane {
	private static final long serialVersionUID = 9096459222103020402L;
	private JList<String> list;

	/**
	 * Create the panel.
	 */
	public PanResultat() {
		super(JSplitPane.VERTICAL_SPLIT);
		list = new JList<>();
		list.setMinimumSize(new Dimension(100, 100));
		list.setPreferredSize(new Dimension(200, 0));
		this.setTopComponent(list);
		
		PanPreview panPreview = new PanPreview();
		this.setBottomComponent(panPreview);
	}
	
	public void setListContent(List<String> resultats) {
		this.list.setListData((String[]) resultats.toArray(new String[0]));
	}

}
