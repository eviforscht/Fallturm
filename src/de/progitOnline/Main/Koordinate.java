package de.progitOnline.Main;

import java.awt.FileDialog;
import java.awt.Frame;
import java.io.File;
import java.io.IOException;
import java.util.LinkedList;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;

import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;
import org.xml.sax.SAXException;

import de.progitOnline.Frame.Diagramm;


public class Koordinate {

	double x;
	double y;
	private static FileDialog save;
	private static String saveName;
	
	private static FileDialog load;
	private static String loadName;
	public static String endung = ".ff";
	
	
	public Koordinate(double x , double y)
	{
		this.x = x;
		this.y = y;
	}
	
	public double getX()
	{
		return x;
	}
	public double getY()
	{
		return y;
	}
	public void setX(double x)
	{
		this.x = x;
	}
	public void setY(double y)
	{
		this.y=y;
	}
	@Override
	public String toString() {
		return "de.progitOnline.Koordinate\nX : " + getX() + "\nY: " + getY();
	}
	
	 public static LinkedList<Koordinate> loadList(Diagramm di) throws ParserConfigurationException, SAXException, IOException{
		  
		  load = new FileDialog(di, "Werte laden...", FileDialog.LOAD);
		  load.setVisible(true);
		  
		  LinkedList<Koordinate> data = new LinkedList<Koordinate>();
		  
		  loadName = load.getDirectory();
		  loadName += load.getFile();
		  
		  
		  System.out.println("Dateiname: "+loadName);
		  
		  
		  
		  
		  
		  
		  
		  
		  
		  
		  DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
			DocumentBuilder builder = factory.newDocumentBuilder();
			Document document = builder.parse(new File(loadName));
			
			NodeList sList = document.getElementsByTagName("settings");
			Node settings = sList.item(0);
			Element el = (Element)settings;
			/*setTownName(el.getElementsByTagName("twonName").item(0).getTextContent().trim());
			System.out.println("Stadtname: "+townNameTag);
			setWidthPosition(el.getElementsByTagName("WidthPosition").item(0).getTextContent().trim());
			System.out.println("Breitenposition: "+Breitenposition);
			setlengthPosition(el.getElementsByTagName("LengthPosition").item(0).getTextContent().trim());
			System.out.println("LÃ¤ngenposition: "+getLengthPosition());
			setAboutZero(el.getElementsByTagName("aboutZero").item(0).getTextContent().trim());
			System.out.println("Ãœber null: "+getAboutZero());*/
			
			NodeList nList = document.getElementsByTagName("Koordinate");
			data.clear();
			
			
			for (int NodeAtPosition = 0; NodeAtPosition < nList.getLength(); NodeAtPosition++) {
				Node kooNode = nList.item(NodeAtPosition);
				Element e = (Element) kooNode;

				data.add(new Koordinate(
				Double.parseDouble(e.getElementsByTagName("time").item(0).getTextContent().trim() ),
				Double.parseDouble(e.getElementsByTagName("way").item(0).getTextContent().trim() ) ) );
				System.out.println(data.getLast());
				
			}
		  
		  

		  
		  
		  
		  System.out.println("Listengroeße nach dem Laden: "+data.size());
		  
		  
		return data;
	  }public static boolean saveList(LinkedList <Koordinate> data,Diagramm di){
		  
		  
		  save = new FileDialog(di, "Speichern unter...", FileDialog.SAVE);
		  save.setVisible(true);
		  
		  saveName = save.getDirectory();
		  saveName +=save.getFile();
		  
		  System.out.println("Speichern unter: "+saveName);
		  System.out.println("Aktuelle Listengröße: "+data.size());
		  try {
				DocumentBuilderFactory docFactory = DocumentBuilderFactory.newInstance();
				DocumentBuilder docBuilder = docFactory.newDocumentBuilder();
				Document doc = docBuilder.newDocument();

				Element rootElement = doc.createElement("example");
				doc.appendChild(rootElement);
				
				Element settings = doc.createElement("settings");
				rootElement.appendChild(settings);
				
				/*Element townName = doc.createElement("twonName");
				townName.appendChild(doc.createTextNode(townNameTag));
				settings.appendChild(townName);
				
				Element WidthPosition = doc.createElement("WidthPosition");
				WidthPosition.appendChild(doc.createTextNode(Breitenposition));
				settings.appendChild(WidthPosition);
				
				Element LengthPosition = doc.createElement("LengthPosition");
				LengthPosition.appendChild(doc.createTextNode(LÃ¤ngenposition));
				settings.appendChild(LengthPosition);
				
				Element aboutZero = doc.createElement("aboutZero");
				aboutZero.appendChild(doc.createTextNode(ueberNull));
				settings.appendChild(aboutZero);*/
				
				

				for (int i = 0; i < data.size(); i++) {
					Koordinate k = data.get(i);

					Element ko = doc.createElement("Koordinate");
					rootElement.appendChild(ko);

					Element time = doc.createElement("time");
					time.appendChild(doc.createTextNode(""+k.getX()));
					ko.appendChild(time);

					Element way = doc.createElement("way");
					way.appendChild(doc.createTextNode(""+k.getY()));
					ko.appendChild(way);
					

				}

				// als XML schreiben
				TransformerFactory transformerFactory = TransformerFactory
						.newInstance();
				Transformer transformer = transformerFactory.newTransformer();
				DOMSource source = new DOMSource(doc);
				StreamResult result = new StreamResult(new File(saveName  + endung));
				
				System.out.println("speichern...");
				
				
				transformer.transform(source, result);
				System.out.println("Speichern abgeschlossen!");

			} catch (Exception e) {
				e.printStackTrace();
				return false;
			}
		  
		  
		  
		  
		  
		  
		  
		  
		return true;
		  
	  }
	
}
