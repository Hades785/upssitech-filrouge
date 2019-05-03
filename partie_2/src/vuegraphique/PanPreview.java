package vuegraphique;

import java.awt.BorderLayout;
import java.awt.CardLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.stream.Stream;

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
			try {
				BufferedImage myPicture = decodeImTXT(file);
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

	public void previewAudio(File file) {
		audioFile = file;
		cl.show(this, "audio");
	}
	
	public void previewVoid() {
		cl.show(this, "texte");
		tp.setText("");
	}
	
	private static BufferedImage decodeImTXT(File file) throws IOException{
		StringBuilder build = new StringBuilder();
		try (Stream<String> stream = Files.lines( Paths.get(file.getAbsolutePath()), StandardCharsets.UTF_8))
	    {
	        stream.forEach(s -> build.append(s).append("\n"));
	    }
	    catch (IOException e)
	    {
	        e.printStackTrace();
	        throw e;
	    }
		String[] lines = build.toString().split("\n");
		if(lines.length < 2) throw new RuntimeException("Fichier vide.");
		String[] coords = lines[0].split(" ");
		if(coords.length != 3) throw new RuntimeException("Fichier invalide.");
		int x,y,z;
		x = Integer.parseInt(coords[0]);
		y = Integer.parseInt(coords[1]);
		z = Integer.parseInt(coords[2]);
		int[][][] resp = new int[z][x][y];
		if(lines.length < x) throw new RuntimeException("Fichier incomplet.");
		for(int zt = 0;zt < z;zt++) {
			for(int yt = 0;yt < y;yt++) {
				String numbers[] = lines[zt*y+yt+1].split(" ");
				if(numbers.length != x) throw new RuntimeException("Fichier invalide. Ligne "+(yt+zt*y));
				for(int xt = 0;xt < x;xt++) {
					resp[zt][xt][yt] = Integer.parseInt(numbers[xt]);
				}
			}
		}
		return getImage(resp);
	}
	
	private static BufferedImage getImage(int[][][] mapPix) throws IOException {
		BufferedImage image;
		if(mapPix.length == 1) {
			image = new BufferedImage(mapPix[0].length, mapPix[0][0].length, BufferedImage.TYPE_BYTE_GRAY);
			for(int y = 0;y < mapPix[0][0].length;y++) {
				for(int x = 0;x < mapPix[0].length;x++) {
					image.setRGB(x, y, mapPix[0][x][y]);
				}
			}
		}else {
			image = new BufferedImage(mapPix[0].length, mapPix[0][0].length, BufferedImage.TYPE_INT_RGB);
			for(int z = 0;z < mapPix.length;z++) {
				for(int y = 0;y < mapPix[0][0].length;y++) {
					for(int x = 0;x < mapPix[0].length;x++) {
						image.setRGB(x, y, (mapPix[0][x][y]<<16)+(mapPix[1][x][y]<<8)+(mapPix[2][x][y]));
					}
				}
			}
		}
		return image;
	}
}
