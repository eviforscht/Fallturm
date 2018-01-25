package round;

import java.util.LinkedList;

public class MatheZeugs 
{
	public static double round(double d, int stelle) {
		return (Math.round(d*hoch(10,stelle))/hoch(10,stelle));
	}
	public static double hoch(double zahl, double exp)
	{
		double temp = zahl;
		for(int i=1;i<exp;i++)
			zahl*=temp;
		
		return zahl;

	}
	
	public static double betrag(double value)
	{
		if(value>0)
			return value;
		
		
		return -1*value;
	}
	public static double hoch(double zahl, int exp)
	{
		return hoch(zahl,exp*1.0);
	}
	
	public static Funktion minS(LinkedList<Funktion>data)
	{
		double d = Double.MAX_VALUE;
		Funktion ret = null;
		for(int i = 0;i<data.size();i++)
		{
		try
		{
			Funktion f = data.get(i);
			
			if(f.getS()<d&&f!=null)
			{
				d= f.getS();
				ret = f;
			}
			
		}catch(Exception e)
		{
			System.err.println(i);
			e.printStackTrace();
		}
			
		}
		System.out.println(ret.getA());
		return ret;
			
	}
}
