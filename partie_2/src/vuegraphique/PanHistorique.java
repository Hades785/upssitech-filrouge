package vuegraphique;

import java.awt.BorderLayout;

import javax.swing.JList;
import javax.swing.JPanel;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;

import modele.Historique;
import modele.Recherche;

public class PanHistorique extends JPanel {

	private JList<Recherche> liste = new JList<>();
	private FrameUtilisateur f;
	private Historique hist;

	public PanHistorique(FrameUtilisateur frame, Historique hist) {
		super();
		setLayout(new BorderLayout());
		add(liste, BorderLayout.CENTER);
		this.f = frame;
		this.hist = hist;

		liste.setListData((Recherche[]) hist.getHistoriqueRecherches().toArray());

		liste.addListSelectionListener(new ListSelectionListener() {

			@Override
			public void valueChanged(ListSelectionEvent e) {
				f.actionFromHistory(liste.getModel().getElementAt(liste.getSelectedIndex()));
			}
		});
	}

}
