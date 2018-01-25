package de.progitOnline.Frame;

import java.awt.FileDialog;
import java.awt.FlowLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.image.BufferedImage;
import java.io.File;
import java.util.LinkedList;

import javax.imageio.ImageIO;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JDialog;

import de.progitOnline.Main.Koordinate;

public class Save {
	JDialog jd;
	JButton bild,settings;
	Diagramm d;
	LinkedList<Koordinate> data;
	BufferedImage bfg;
	JComboBox box;
	
	public Save(Diagramm d, LinkedList <Koordinate> data,BufferedImage bfg)
	{
		this.d = d;
		this.data = data;
		jd = new JDialog(d, "Speichern als...", true);
		jd.setLocationRelativeTo(d);
		bild = new JButton("Bild");
		bild.addActionListener(new ActionListener() {
			
			@Override
			public void actionPerformed(ActionEvent e) {
				if(e.getActionCommand().equals(bild.getActionCommand()))
				{
					String chose = (String) box.getSelectedItem();
					System.out.println(chose);
					System.err.println("Speichern als Bild!");
					String path = save(d);
					File f = new File(path + "." + chose);
					try {
						ImageIO.write(bfg, chose, f);
					} catch (Exception e1) {
						// TODO Auto-generated catch block
						e1.printStackTrace();
					} 
					System.err.println("Speichern erfolgreich!");
					jd.dispose();
					return;
				}
				
			}
		});
		
		settings = new JButton("Daten");
		settings.addActionListener(new ActionListener() {
			
			@Override
			public void actionPerformed(ActionEvent e) {
			if(e.getActionCommand().equals(settings.getActionCommand()))
			{
				System.err.println("Speichern als Settings!");
				Koordinate.saveList(data, d);
				jd.dispose();
				return;
			}
		
				
			}
		});
		box = new JComboBox(ImageIO.getWriterFormatNames());
		jd.setLayout(new FlowLayout());
		jd.add(bild);
		jd.add(box);
		jd.add(settings);
		jd.pack();
		jd.setDefaultCloseOperation(JDialog.HIDE_ON_CLOSE);
		jd.setVisible(true);
		
	}private String save(Diagramm d)
	{
		FileDialog save = new FileDialog(d, "Speichern unter...", FileDialog.SAVE);
		  save.setVisible(true);
		  
		  String saveName = save.getDirectory();
		  saveName +=save.getFile();
		  
		  return saveName;
	}
}
