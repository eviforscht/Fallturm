package de.progitOnline.Main;

import java.util.LinkedList;

import de.progitOnline.Frame.Diagramm;
import de.progitOnline.Import.Test;

public class Main
{

	static LinkedList data = new LinkedList<Koordinate>();

	public static void main(String[] args)
	{
		System.out.println("Starte Programm...");

		/*
		 * Random r = new Random();
		 * 
		 * for(int i = 0;i<100;i++) { data.add(new Koordinate(r.nextInt(1000),
		 * r.nextInt(1000))); }
		 */

		// Koordinate.saveList(data, null);

		/*
		 * Test.printNameList(); try { Test.insertValues(); } catch
		 * (SQLException e) { System.out.println(
		 * "Fehler beim Schreiben in Datenbank!\n\n"); // TODO Auto-generated
		 * catch block e.printStackTrace(); }
		 */

		data = Test.getData();
		/// Test.printNameList();

		Diagramm d = new Diagramm(data, Diagramm.sMode);

		System.out.println("Beende Programm...");

	}
}
