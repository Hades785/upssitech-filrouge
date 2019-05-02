package vuegraphique;

import java.awt.BorderLayout;
import java.awt.CardLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;

import javax.imageio.ImageIO;
import javax.sound.sampled.AudioInputStream;
import javax.sound.sampled.AudioSystem;
import javax.sound.sampled.Clip;
import javax.sound.sampled.LineUnavailableException;
import javax.sound.sampled.UnsupportedAudioFileException;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextPane;

public class PanPreview extends JPanel {
	private static final long serialVersionUID = -1155564394240546003L;

	private CardLayout cl;
	private JTextPane tp;
	private JLabel lb;

	private File audioFile;

	public PanPreview() {
		cl = new CardLayout();
		this.setLayout(cl);

		JPanel panTexte = new JPanel();
		panTexte.setLayout(new BorderLayout());
		tp = new JTextPane();
		panTexte.add(tp);
		this.add(panTexte, "texte");
		tp.setEditable(false);

		JPanel panImage = new JPanel();
		panImage.setLayout(new BorderLayout());
		lb = new JLabel();
		panImage.add(lb);
		this.add(panImage, "image");

		JPanel panAudio = new JPanel();
		panAudio.setLayout(new BorderLayout());
		JButton btn = new JButton("PLAY");
		panAudio.add(btn);
		btn.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				try (AudioInputStream audioInputStream = AudioSystem.getAudioInputStream(audioFile.getAbsoluteFile())) {
					// create clip reference
					Clip clip = AudioSystem.getClip();
					// open audioInputStream to the clip
					clip.open(audioInputStream);
				} catch (IOException e1) {
					e1.printStackTrace();
				} catch (UnsupportedAudioFileException e1) {
					e1.printStackTrace();
				} catch (LineUnavailableException e1) {
					e1.printStackTrace();
				}
			}
		});
		this.add(panAudio, "audio");
	}

	public void previewTexte(File file) {
		if (file.exists()) {
			cl.show(this, "texte");
			try {
				String contents = new String(Files.readAllBytes(Paths.get(file.getAbsolutePath())));
				tp.setText(contents);
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
	}

	public void previewImage(File file) {
		if (file.exists()) {
			cl.show(this, "image");
			if (file.getName().endsWith(".txt")) {
				String name = file.getAbsolutePath();
				File im = new File(name.substring(0, name.length() - 4) + ".jpg");
				if (im.exists()) {
					file = im;
				} else {
					
				}
				BufferedImage myPicture;
				try {
					myPicture = ImageIO.read(file);
					ImageIcon image = new ImageIcon(myPicture);
					lb.setIcon(image);
					lb.setText("");
				} catch (IOException e) {
					lb.setIcon(null);
					lb.setText("Unable to load image");
					e.printStackTrace();
				}
			}
		}
	}

	public void previewAudio(File file) {
		audioFile = file;
		cl.show(this, "audio");
	}
}
