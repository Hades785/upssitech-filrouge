package vuegraphique;

import javax.swing.JSplitPane;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;
import javax.swing.JList;
import java.util.List;
import java.awt.Dimension;
import java.io.File;

public class PanResultat extends JSplitPane {
	private static final long serialVersionUID = 9096459222103020402L;
	private JList<String> list;
	
	private TypeRecherche tr;

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
		
		list.addListSelectionListener(new ListSelectionListener() {
			@Override
			public void valueChanged(ListSelectionEvent e) {
				if(!list.isSelectionEmpty()) {
					File f = new File(list.getSelectedValue());
					switch(tr) {
					case AUDIO:
						String path = list.getSelectedValue().split(".txt ")[0]+".wav";
						panPreview.previewAudio(new File(path));
						break;
					case IMAGE:
						panPreview.previewImage(f);
						break;
					case TEXTE:
						panPreview.previewTexte(f);
						break;
					default:
						break;
					}
				}else {
					panPreview.previewVoid();
				}
			}
		});
		
	}
	
	public void setListContent(List<String> resultats,TypeRecherche tr) {
		this.list.setListData((String[]) resultats.toArray(new String[0]));
		this.tr = tr;
	}

}
