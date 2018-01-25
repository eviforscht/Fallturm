package de.progitOnline.Frame;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.image.BufferedImage;
import java.awt.print.PageFormat;
import java.awt.print.Printable;
import java.awt.print.PrinterException;
import java.awt.print.PrinterJob;

import javax.swing.JOptionPane;
      
public class BildDruckenScale implements Printable{
     
 private BufferedImage img;
 Diagramm dia;
 
 public int print(Graphics graphics, PageFormat pageFormat, int pageIndex) throws PrinterException {
  
  if(pageIndex > 0)  //Nur eine Seite drucken
   return NO_SUCH_PAGE;
   
  Graphics2D g2d = (Graphics2D) graphics;
  pageFormat.setOrientation(PageFormat.LANDSCAPE);
   
  g2d.translate(pageFormat.getImageableX(), pageFormat.getImageableY());
   
  double scaleX = pageFormat.getImageableWidth()/img.getWidth();  //Die Skalierung für die X und Y Achse ausrechnen
  double scaleY = pageFormat.getImageableHeight()/img.getHeight();
 
     double scale = Math.min(scaleX,scaleY);  //Damit das Bild nicht verzogen wird, den kleinsten Skalierungsfaktor verwenden
     
     g2d.scale(scale,scale); //Die Skalierung auf das Graphics Objekt zeichnen
      
     g2d.drawImage(img, 0, 0, null);  //Das Bild darf erst auf das Graphics Objekt gezeichnet werden,
              //wenn es bereits Skaliert wurde
           
     return PAGE_EXISTS;
 }
  
 public void setImg(BufferedImage img) {
  this.img = img;
 }
 
  
 public BildDruckenScale(BufferedImage bfgI,Diagramm diagramm) {
	 this.dia=diagramm;
     try {
    	 PageFormat pageFormat = new PageFormat();
         pageFormat.setOrientation(PageFormat.LANDSCAPE);
            PrinterJob pjob = PrinterJob.getPrinterJob();
           
            if (pjob.printDialog() == false)
                return;  //Abbruch durch Benutzer
            
            
            BildDruckenScale bds = new BildDruckenScale();
            bds.setImg(bfgI);
 
         pjob.setPrintable(bds,pageFormat);
         pjob.print();
     } catch (Exception e) {
    	 JOptionPane.showInternalMessageDialog(dia, "Beim Drucken ist ein Fehler aufgetreten, bitte versuchen Sie es erneut.", "Fehler", JOptionPane.OK_OPTION);
     }
    }public BildDruckenScale(){}
}