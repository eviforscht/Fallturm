package de.progitOnline.Import;

import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.LinkedList;

import javax.xml.parsers.ParserConfigurationException;

import org.xml.sax.SAXException;

import de.progitOnline.Main.Koordinate;

public class Test{
private static Connection con = null;
private static String dbHost = "192.168.2.113"; // Hostname
private static String dbPort = "3306";      // Port -- Standard: 3306
private static String dbName = "fallturm";   // Datenbankname
private static String dbUser = "user";     // Datenbankuser
private static String dbPass = "RvNcpzKMrbK3QaDN";      // Datenbankpasswort
public static final double einheitenLaenge = 24.;
private static int firstValue = 0;
private static LinkedList<Integer> alreadyInSystem = new LinkedList<Integer>();

private Test() throws Exception{
	System.out.println("Erstelle neue Instanz");
   try {
       Class.forName("com.mysql.jdbc.Driver"); // Datenbanktreiber für JDBC Schnittstellen laden.
       System.out.println("Baue Verbindung auf");
       // Verbindung zur JDBC-Datenbank herstellen.
       con = DriverManager.getConnection("jdbc:mysql://"+dbHost+":"+ dbPort+"/"+dbName+"?"+"user="+dbUser+"&"+"password="+dbPass);
   } catch (ClassNotFoundException e) {
       System.out.println("Treiber nicht gefunden");
   } catch (SQLException e) {
       System.out.println("Verbindung nicht moglich");
       System.out.println("SQLException: " + e.getMessage());
       System.out.println("SQLState: " + e.getSQLState());
       System.out.println("VendorError: " + e.getErrorCode());
       throw new Exception("Fehler bei der Verbindung!");
       
   }
 }

private static Connection getInstance() throws Exception{
	System.out.println("getInstance()");
   if(con == null)
       new Test();
   return con;
}

 //Gebe Tabelle in die Konsole aus
 public static LinkedList<Koordinate> getData(){
	 System.out.println("getData()");
	 double weg = 0;
	 int zeit = 0;
	 LinkedList <Koordinate> temp = new LinkedList <Koordinate>();
     try {
		con = getInstance();
	} catch (Exception e1) {
		try {
			temp = Koordinate.loadList(null);
			return temp;
		} catch (ParserConfigurationException | SAXException | IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
System.out.println("Starte Abfrage");
     if(con != null){
     // Abfrage-Statement erzeugen.
     Statement query;
     try {
         query = con.createStatement();

         // Tabelle anzeigen
         String sql =
               "SELECT time,pin FROM exp_tab";
         ResultSet result = query.executeQuery(sql);

       // Ergebnisstabelle durchforsten
         System.out.println("Starte Abfrage");
         int i = 0;
         while (result.next()) {
        	 
   
    int pin = result.getInt(2);
    if(alreadyInSystem.contains(pin))
    	continue;
    alreadyInSystem.add(pin);
    
    weg = getWay(pin);
    
    System.out.println("Weg: " + weg);
    if(i==0)
    {
    	firstValue = result.getInt(1);
    	
    }
    
    zeit  =(result.getInt(1) - firstValue)/1000;
    	
    System.out.println("Zeit: " + zeit);
    System.out.println("i: " +i);
    System.out.println("Pin:" + pin);
    i++;
    temp.add(new Koordinate(zeit,weg));
         }
     } catch (SQLException e) {
       e.printStackTrace();
     }
   }
     if(!(temp.size()>1))
    	 return null;
     else
    	 return temp;
 }

public static void insertValues() throws SQLException {
	double way = 98.76;
	double time = 44.99;
	 String sql = "INSERT INTO exp_tab(way, time) " +
             "VALUES(?, ?)";
	 PreparedStatement preparedStatement = con.prepareStatement(sql);
     // Erstes Fragezeichen durch "firstName" Parameter ersetzen
     preparedStatement.setDouble(1, way);
     // Zweites Fragezeichen durch "lastName" Parameter ersetzen
     preparedStatement.setDouble(2, time);
     // SQL ausführen.
     preparedStatement.executeUpdate();
	
}public static double getWay(int pin)
{
	switch(pin)
	{
	case 4: return 0;
	case 14: return 24;
	case 15: return 48;
	case 17: return 72;
	case 18: return 96;
	case 23: return 120;
	case 22: return 144;
	case 27: return 168;
	}
	System.err.println("\nIllegal argument!\n");
	
	return 0.;
}
}
