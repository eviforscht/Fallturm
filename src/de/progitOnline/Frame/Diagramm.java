package de.progitOnline.Frame;

import java.awt.Color;
import java.awt.Graphics;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.image.BufferedImage;
import java.awt.print.PageFormat;
import java.awt.print.Printable;
import java.awt.print.PrinterException;
import java.io.IOException;
import java.util.LinkedList;

import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JPanel;
import javax.swing.RepaintManager;
import javax.xml.parsers.ParserConfigurationException;

import org.xml.sax.SAXException;

//import WetterdiaManager.MainFrame.WindowHandler;
import de.progitOnline.Main.Koordinate;
import round.Funktion;
import round.MatheZeugs;

/**
 * Klasse zum Zeichnen einer Parabel aus mehreren Objekten vom Typ
 * de.progitOnline.Main.Koordinate
 * 
 * @author David Leeuwestein
 *
 */
public class Diagramm extends JFrame
{
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private String mode;
	public static final String sMode = "S", vMode = "V";
	private LinkedList<Koordinate> data = new LinkedList<Koordinate>();
	private double achseneinteilungX = 0, achseneinteilungY = 0;
	private static final Koordinate nullstelle = new Koordinate(150.0, 620.0);
	private static final double pixelProEinteilung = 60;
	private DiaPanel dia;
	private vPanel vp;
	JMenuBar menuleiste;
	JMenu datei;
	JMenu passwort;
	JMenuItem beenden, laden, speichern, drucken;
	private BufferedImage bfg;

	public Diagramm(LinkedList<Koordinate> data, String mode)
	{
		super("Fallturm");
		this.data = data;
		this.mode = mode;
		System.out.println("Anzahl empfangener Argumente: " + data.size());

		setSize(1024, 800);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setResizable(false);
		setLocationRelativeTo(null);
		setLayout(new GridLayout(1, 2, 10, 10));

		// addWindowListener(new WindowHandler());

		// Hinzufügen Panel
		if (mode == sMode)
		{
			dia = new DiaPanel();
			dia.repaint();
			add(dia);
		} else if (mode == vMode)
		{
			vp = new vPanel();
			vp.repaint();
			add(vp);
		} else
		{
			System.err.println("Ungültiger Modus!");
			System.exit(-1);
		}

		// Hinzufügen Info

		JPanel p = new JPanel(new GridLayout(3, 1, 10, 10));

		JLabel l = new JLabel();
		JLabel m = new JLabel("Achseneinteilung X: " + achseneinteilungX);
		JLabel n = new JLabel("Achseneinteilung Y: " + achseneinteilungY);

		p.add(l);
		p.add(n);
		p.add(m);

		// add(p);

		/**
		 * Hinzufuegen der Menueleiste
		 */

		menuleiste = new JMenuBar();
		setJMenuBar(menuleiste);

		datei = new JMenu("Datei");
		beenden = new JMenuItem("Beenden");
		beenden.addActionListener(new ActionHandler());

		laden = new JMenuItem("Laden");
		laden.addActionListener(new ActionHandler());
		speichern = new JMenuItem("Speichern");
		speichern.addActionListener(new ActionHandler());
		drucken = new JMenuItem("Drucken");
		drucken.addActionListener(new ActionHandler());

		menuleiste.add(datei);
		datei.add(speichern);
		datei.add(laden);
		datei.add(drucken);
		datei.add(beenden);

		// Sichtbar machen

		setVisible(true);

	}

	private class DiaPanel extends JPanel implements Printable
	{
		/**
		 * 
		 */
		private static final long serialVersionUID = 1L;
		// public double s = 0.;
		public double a = 0.;
		public double c = 0.;
		public double b = 0.;
		private double gravity = 9.81;
		// public double t = 0.;
		// public final double toleranz = 0.2;
		Koordinate maxValues = max(data);

		public DiaPanel()
		{
			try
			{
				/*
				 * Koordinate first1 = data.getFirst(); Koordinate second1 =
				 * data.get((int) MatheZeugs.round((data.size() - 1.0) / 2, 0));
				 * Koordinate third1 = data.get(data.size() - 1);
				 */
				Funktion p = new Funktion(data);
				/**
				 * Berechnen nach Marvin
				 */
				a = p.getA();
				b = p.getB();
				c = p.getC();

			} catch (Exception e)
			{
				e.printStackTrace();
				System.exit(-1);
			}

		}

		@Override
		public void paintComponent(Graphics g)
		{
			super.paintComponent(g);

			System.out.println("y = " + a + "*" + "t^2" + "+" + b + "*" + "t");
			System.out.println("Bedingungen erfüllt!");
			System.out.println("Aufruf paintComponent");

			g.setColor(Color.BLACK);
			g.drawLine((int) nullstelle.getX(), (int) nullstelle.getY(),
					(int) (nullstelle.getX() + pixelProEinteilung * 10), (int) nullstelle.getY());
			g.drawLine((int) nullstelle.getX(), (int) nullstelle.getY(), (int) nullstelle.getX(),
					(int) (nullstelle.getY() - pixelProEinteilung * 10));
			LinkedList<Koordinate> temp_list = new LinkedList<Koordinate>();
			/*
			 * Achseneinteilung berechnen
			 */
			achseneinteilungX = maxValues.getX() / 10;
			achseneinteilungY = maxValues.getY() / 10;

			/**
			 * Erdbeschleunigung berechnen
			 */
			gravity = MatheZeugs.round(a * 20000, 3);
			// Zeichnen Koordinaten
			for (double i = 0.; i <= maxValues.getX(); i++)
			{
				double x = i;
				double y = 0;
				y = (a * (x * x)) + (b * x) + c;

				/**
				 * Zeichnen mithilfe des Proportionalitätsfaktors
				 */
				Koordinate temp = new Koordinate(nullstelle.getX() + (x / achseneinteilungX * pixelProEinteilung * 1.0),
						nullstelle.getY() * 1.0 - (y / achseneinteilungY * pixelProEinteilung * 1.0));
				System.out.println("Zeichne Punkt: " + temp.getX() + " " + temp.getY());
				temp_list.add(temp);
			}
			for (int i = 0; i < temp_list.size() - 1; i++)
			{
				System.out.println(i + ". Schleifendurchlauf");
				Koordinate first = temp_list.get(i);
				Koordinate second = temp_list.get(i + 1);

				g.drawLine((int) first.getX(), (int) first.getY(), (int) second.getX(), (int) second.getY());
				System.out.printf("Zeichne Linie von %f %f nach %f %f.", first.getX(), first.getY(), second.getX(),
						second.getY());
			}
			for (int i = 0; i < 10; i++)
			{
				g.drawString("" + Math.round((achseneinteilungX * i * 100.0)) / 100.0,
						(int) (nullstelle.getX() + pixelProEinteilung * i),
						(int) (nullstelle.getY() + pixelProEinteilung));
			}
			for (int y = 0; y < 10; y++)
				g.drawString("" + (Math.round(100.0 * (achseneinteilungY * y)) / 100.0),
						(int) (nullstelle.getX() - pixelProEinteilung),
						(int) (nullstelle.getY() - (y * pixelProEinteilung)));

			/**
			 * Zeichnen von unnötigen Formalien
			 */
			g.drawString("t in Microsekunden/1000", (int) (nullstelle.getX() + pixelProEinteilung * 10 + 50),
					(int) nullstelle.getY());
			g.drawString("s in Zentimetern", (int) nullstelle.getX(),
					(int) (nullstelle.getY() - (pixelProEinteilung * 10) - 5));

			g.drawLine((int) (nullstelle.getX() + pixelProEinteilung * 10 - 5), (int) (nullstelle.getY() - 5),
					(int) (nullstelle.getX() + pixelProEinteilung * 10), (int) nullstelle.getY());
			g.drawLine((int) (nullstelle.getX() + pixelProEinteilung * 10 - 5), (int) (nullstelle.getY() + 5),
					(int) (nullstelle.getX() + pixelProEinteilung * 10), (int) nullstelle.getY());

			g.drawLine((int) (nullstelle.getX() - 5), (int) (nullstelle.getY() - (10 * pixelProEinteilung) + 5),
					(int) nullstelle.getX(), (int) (nullstelle.getY() - (pixelProEinteilung * 10)));
			g.drawLine((int) (nullstelle.getX() + 5), (int) (nullstelle.getY() - (10 * pixelProEinteilung) + 5),
					(int) nullstelle.getX(), (int) (nullstelle.getY() - (pixelProEinteilung * 10)));

			/**
			 * Zeichnen der Erdbeschleunigung
			 */
			g.drawString("Erdbeschleunigung: " + gravity, (int) nullstelle.getX() + 5,
					(int) (nullstelle.getY() - pixelProEinteilung * 10 + 25));

			/**
			 * Zeichnen der ursprünglichen Punkte
			 */
			System.out.println("\nZeichnen der ursprünglichen Punkte...\n");
			for (int i = 0; i < data.size(); i++)
			{
				Koordinate k = data.get(i);
				Koordinate temp = new Koordinate(
						nullstelle.getX() + (k.getX() / achseneinteilungX * pixelProEinteilung),
						nullstelle.getY() - (k.getY() / achseneinteilungY * pixelProEinteilung));
				// System.out.println(temp);

				g.drawLine((int) (temp.getX() - 5), (int) (temp.getY() - 5), (int) (temp.getX() + 5),
						(int) (temp.getY() + 5));
				g.drawLine((int) (temp.getX() - 5), (int) (temp.getY() + 5), (int) (temp.getX() + 5),
						(int) (temp.getY() - 5));
			}

		}

		@Override
		public int print(Graphics g, PageFormat pageFormat, int pageIndex) throws PrinterException
		{
			if (pageIndex > 0)
			{
				return (NO_SUCH_PAGE);
			} else
			{
				int x = (int) pageFormat.getImageableX() + 1;
				int y = (int) pageFormat.getImageableY() + 1;
				g.translate(x, y);
				RepaintManager currentManager = RepaintManager.currentManager(this);
				currentManager.setDoubleBufferingEnabled(false);
				this.paint(g);
				currentManager.setDoubleBufferingEnabled(true);
				return (PAGE_EXISTS);
			}
		}
	}

	private class vPanel extends JPanel implements Printable
	{
		/**
		 * 
		 */
		private static final long serialVersionUID = 1L;
		public double s = 0.;
		public double a = 0.;
		public double c = 0.;
		public double b = 0.;
		public double t = 0.;
		public final double toleranz = 0.2;
		LinkedList<Koordinate> values;
		Koordinate maxValues;

		public vPanel()
		{
			System.out.println("Zeichnen der Koordinaten v/t");
			try
			{
				values = new LinkedList<Koordinate>();
				for (int i = 0; i < data.size(); i++)
				{
					if (i == 0)
					{
						values.add(new Koordinate(data.get(i).getX(), 0.));
						continue;
					}
					Koordinate k = data.get(i);

					double x, y;

					if (data.get(i).getX() - data.get(i - 1).getX() == 0)
						continue;

					x = data.get(i).getX();

					y = (data.get(i).getY() - data.get(i - 1).getY()) / (data.get(i).getX() - data.get(i - 1).getX());

					values.add(new Koordinate(x, y));
					System.out.println(values.getLast());

				}
				System.out.println("data.size() == values.size(): " + (data.size() == values.size()));

				Funktion p = new Funktion(values);
				/**
				 * Berechnen nach Marvin
				 */
				a = p.getA();
				b = p.getB();
				c = p.getC();
				System.out.println("A: " + a);
				System.out.println("B: " + b);
				System.out.println("C: " + c);
				maxValues = max(values);
			} catch (Exception e)
			{
				e.printStackTrace();
				System.exit(-1);
			}

		}

		@Override
		public void paintComponent(Graphics g)
		{
			super.paintComponent(g);
			System.out.println("Aufruf paintComponent");

			g.setColor(Color.BLACK);
			g.drawLine((int) nullstelle.getX(), (int) nullstelle.getY(),
					(int) (nullstelle.getX() + pixelProEinteilung * 10), (int) nullstelle.getY());
			g.drawLine((int) nullstelle.getX(), (int) nullstelle.getY(), (int) nullstelle.getX(),
					(int) (nullstelle.getY() - pixelProEinteilung * 10));
			LinkedList<Koordinate> temp_list = new LinkedList<Koordinate>();

			// Zeichnen Koordinaten
			for (double i = 0.; i <= maxValues.getX(); i++)
			{
				double x = i;
				double y = 0;

				y = (a * (x * x)) + (b * x) + c;

				Koordinate temp = new Koordinate(nullstelle.getX() + (x / achseneinteilungX * pixelProEinteilung * 1.0),
						nullstelle.getY() * 1.0 - (y / achseneinteilungY * pixelProEinteilung * 1.0));
				// System.out.println("Zeichne Punkt: " + temp.getX() + " " +
				// temp.getY());
				temp_list.add(temp);
			}
			for (int i = 0; i < temp_list.size() - 1; i++)
			{
				// System.out.println(i + ". Schleifendurchlauf");
				Koordinate first = temp_list.get(i);
				Koordinate second = temp_list.get(i + 1);

				g.drawLine((int) first.getX(), (int) first.getY(), (int) second.getX(), (int) second.getY());
			}

			/*
			 * Achseneinteilung berechnen
			 */
			achseneinteilungX = maxValues.getX() / 10;
			achseneinteilungY = maxValues.getY() / 10;
			for (int i = 0; i < 10; i++)
			{
				g.drawString("" + Math.round((achseneinteilungX * i * 100.0)) / 100.0,
						(int) (nullstelle.getX() + pixelProEinteilung * i),
						(int) (nullstelle.getY() + pixelProEinteilung));
			}
			for (int y = 0; y < 10; y++)
				g.drawString("" + (Math.round(100.0 * (achseneinteilungY * y)) / 100.0),
						(int) (nullstelle.getX() - pixelProEinteilung),
						(int) (nullstelle.getY() - (y * pixelProEinteilung)));

			/**
			 * Zeichnen von unnötigen Formalien
			 */
			g.drawString("t in Microsekunden/1000", (int) (nullstelle.getX() + pixelProEinteilung * 10 + 50),
					(int) nullstelle.getY());
			g.drawString("v in cm/s*1000", (int) nullstelle.getX(),
					(int) (nullstelle.getY() - (pixelProEinteilung * 10) - 5));

			g.drawLine((int) (nullstelle.getX() + pixelProEinteilung * 10 - 5), (int) (nullstelle.getY() - 5),
					(int) (nullstelle.getX() + pixelProEinteilung * 10), (int) nullstelle.getY());
			g.drawLine((int) (nullstelle.getX() + pixelProEinteilung * 10 - 5), (int) (nullstelle.getY() + 5),
					(int) (nullstelle.getX() + pixelProEinteilung * 10), (int) nullstelle.getY());

			g.drawLine((int) (nullstelle.getX() - 5), (int) (nullstelle.getY() - (10 * pixelProEinteilung) + 5),
					(int) nullstelle.getX(), (int) (nullstelle.getY() - (pixelProEinteilung * 10)));
			g.drawLine((int) (nullstelle.getX() + 5), (int) (nullstelle.getY() - (10 * pixelProEinteilung) + 5),
					(int) nullstelle.getX(), (int) (nullstelle.getY() - (pixelProEinteilung * 10)));

			/**
			 * Zeichnen der ursprünglichen Punkte
			 */
			System.out.println("\nZeichnen der ursprünglichen Punkte...\n");
			for (int i = 0; i < values.size(); i++)
			{
				Koordinate k = values.get(i);
				Koordinate temp = new Koordinate(
						nullstelle.getX() + (k.getX() / achseneinteilungX * pixelProEinteilung),
						nullstelle.getY() - (k.getY() / achseneinteilungY * pixelProEinteilung));
				// System.out.println(temp);

				g.drawLine((int) (temp.getX() - 5), (int) (temp.getY() - 5), (int) (temp.getX() + 5),
						(int) (temp.getY() + 5));
				g.drawLine((int) (temp.getX() - 5), (int) (temp.getY() + 5), (int) (temp.getX() + 5),
						(int) (temp.getY() - 5));
			}

		}

		@Override
		public int print(Graphics g, PageFormat pageFormat, int pageIndex) throws PrinterException
		{
			if (pageIndex > 0)
			{
				return (NO_SUCH_PAGE);
			} else
			{
				int x = (int) pageFormat.getImageableX() + 1;
				int y = (int) pageFormat.getImageableY() + 1;
				g.translate(x, y);
				RepaintManager currentManager = RepaintManager.currentManager(this);
				currentManager.setDoubleBufferingEnabled(false);
				this.paint(g);
				currentManager.setDoubleBufferingEnabled(true);
				return (PAGE_EXISTS);
			}
		}
	}

	/*
	 * private class werteTabelle extends JPanel { Koordinate start = new
	 * Koordinate(nullstelle.getX(),nullstelle.getY()+pixelProEinteilung); int
	 * pixelProZeile = 50,pixelProSpalte=60; Koordinate endPos = new
	 * Koordinate(start.getX()*data.size()*pixelProSpalte,start.getY()+3*
	 * pixelProZeile);
	 * 
	 * public werteTabelle() {
	 * 
	 * }
	 * 
	 * @Override public void paintComponent(Graphics g) { for(int i=1;i<4;i++)
	 * g.drawLine(start.getX(),start.getY()+(i*pixelProZeile). , x2, y2); } }
	 */
	/**
	 * Berechnet die Maximalwerte einer uebergebenen LinkedList<Koordinate>
	 * 
	 * @param temp
	 * @return
	 */
	public Koordinate max(LinkedList<Koordinate> temp)
	{
		Koordinate max = new Koordinate(0, 0);
		for (Object k : temp)
		{
			Koordinate k1 = (Koordinate) k;
			if (k1.getX() > max.getX())
				max.setX(k1.getX());
			if (k1.getY() > max.getY())
				max.setY(k1.getY());
		}
		return max;

	}

	private class ActionHandler implements ActionListener
	{

		@Override
		public void actionPerformed(ActionEvent e)
		{

			if (e.getActionCommand().equals(laden.getActionCommand()))
			{

				System.out.println("laden neuer Koordinaten...");
				LinkedList<Koordinate> temp = null;
				try
				{
					temp = Koordinate.loadList(Diagramm.this);
				} catch (ParserConfigurationException | SAXException | IOException e1)
				{
					// TODO Auto-generated catch block
					e1.printStackTrace();
					return;
				}
				Diagramm.this.dispose();
				new Diagramm(temp, mode);
				return;
			}
			if (e.getActionCommand().equals(speichern.getActionCommand()))
			{
				bfg = new BufferedImage(dia.getWidth(), dia.getHeight(), BufferedImage.TYPE_INT_RGB);
				dia.paint(bfg.getGraphics());
				new Save(Diagramm.this, data, bfg);
				return;
			}
			if (e.getActionCommand().equals(beenden.getActionCommand()))
			{
				System.out.println("Beenden...");
				System.exit(0);
			}
			if (e.getActionCommand().equals(drucken.getActionCommand()))
			{
				System.out.println("Drucken...");
				bfg = new BufferedImage(dia.getWidth(), dia.getHeight(), BufferedImage.TYPE_INT_RGB);
				dia.paint(bfg.getGraphics());
				new BildDruckenScale(bfg, Diagramm.this);
			}
		}

	}

}
