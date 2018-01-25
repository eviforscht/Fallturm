package round;

import java.util.LinkedList;

import de.progitOnline.Main.Koordinate;


public class Funktion {
	
	double a;
	double b;
	double c;
	double s;
	
	public LinkedList<Funktion> collection = new LinkedList<Funktion>();
	public static final int kerne = 2;//Runtime.getRuntime().availableProcessors();
	
	
	
	public Funktion(double a, double b, double c, double s)
	{
		this.a = a;
		this.b = b;
		this.c = c;
		this.s = s;
	}
	public Funktion(Parabel p,double s)
	{
		this.a = p.getA();
		this.b = p.getB();
		this.c  =p.getC();
		this.s = s;
	}
	/*public Funktion multiInit(LinkedList<Koordinate> data)
	{
		collection.clear();
		LinkedList<Thread> th = new LinkedList<Thread>();
		int part = (int) MatheZeugs.round(data.size()/kerne, 0);
		
		final int i = 1;
		
		Thread t = new Thread(new Runnable() {
			
			@Override
			public void run() {
				init(vonBis(0,part,data));
				
			}
		});
		
		th.add(t);
		
		Thread t1 = new Thread(new Runnable() {
			
			@Override
			public void run() {
				init(vonBis((part+1), data.size(),data));
				
			}
		});
		th.add(t1);
		
		for(int a=0;a<th.size();a++)
			th.get(a).start();
		
		
		System.out.println("Threads gestartet!");
		
		for(int a = 0;a<th.size();a++)
		{
			while(th.get(a).isAlive())
			{
				try {
					Thread.sleep(20);
				} catch (InterruptedException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}
		}
		System.out.println("Collection: " + collection.size());
		Funktion sMin = MatheZeugs.minS(collection);
		System.out.println("Berechnung beendet!");
		return sMin;
	}*/
	
	public Funktion init(LinkedList<Koordinate> data)
	{
		collection.clear();
		System.out.println("Starte Berechnung...");
		for(Koordinate k : data)
		{
			System.err.println(k);
		}
		int p,q,r;
		p = 1;
		q = 2;
		r = data.size();
		while(p<r-1)
		{
			
			while(q<r)
			{
				Koordinate pk = data.get(p);
				Koordinate qk = data.get(q);
				Koordinate ursprung = data.getFirst();
				
				Parabel pl = new Parabel(ursprung, pk, qk);
				
				double a1,b1,c1,t = 0;
				
				a1 = pl.getA();
				b1 = pl.getB();
				c1 = pl.getC();
				
				for(int i = 0;i<r;i++)
				{
					if(data.get(i).getX() == 0 || data.get(i).getY() == 0)
						continue;
					double yR = data.get(i).getY();
					
					double yC = a1 * MatheZeugs.hoch(data.get(i).getX(),2) + b1 * data.get(i).getX() + c1;
					
					if(yC == 0)
						continue;
					
					t+= MatheZeugs.betrag( ( 1 - yR/yC ) );
					
				}
				
				collection.add(new Funktion(a1,b1,c1,t));
				
				q++;
				
				
				
			}
			
		p++;
		q = p+1;
		}
		Funktion sMin = MatheZeugs.minS(collection);
		System.out.println("Berechnung beendet!");
		System.out.println("A: " + sMin.getA());
		System.out.println("B: " + sMin.getB());
		System.out.println("C: " + sMin.getC());
		return sMin;
		
		
		
	}
	public double getS() {
		// TODO Auto-generated method stub
		return s;
	}
	public double getA() {
		// TODO Auto-generated method stub
		return a;
	}
	public double getB() {
		// TODO Auto-generated method stub
		return b;
	}
	public double getC() {
		// TODO Auto-generated method stub
		return c;
	}
	public Funktion(LinkedList<Koordinate> data)
	{
		Funktion f = init(data);
		this.a = f.getA();
		this.b = f.getB();
		this.c = f.getC();
		this.s = f.getS();
	}

	public LinkedList<Koordinate> vonBis(int von, int bis,LinkedList<Koordinate> da)
	{
		LinkedList temp = new LinkedList<Koordinate>();
		
		for(int i = von;i<bis;i++)
		{
			temp.add(da.get(i));
		}
		
		return temp;
		
	}

	
	
}
