package round;

import de.progitOnline.Main.Koordinate;

public class Parabel
{
	private Koordinate first, second, third;
	private double a;
	private double b;
	private double c;

	public Parabel(Koordinate first, Koordinate second, Koordinate third)
	{
		this.first = first;
		this.second = second;
		this.third = third;

		a = ((first.getY() - second.getY()) * (first.getX() - third.getX())
				- (first.getY() - third.getY()) * (first.getX() - second.getX())

		) / ((square(first.getX()) - square(second.getX())) * (first.getX() - third.getX())
				- (square(first.getX()) - square(third.getX())) * (first.getX() - second.getX()));

		b = ((first.getY() - second.getY()) - a * (square(first.getX()) - square(second.getX()))

		) / (first.getX() - second.getX());
		c = first.getY() - a * square(first.getX()) - b * first.getX();

		// System.err.println("A: " + 10000 * a);
		/*
		 * System.err.println("B: " + b); System.err.println("C: " + c);
		 */

	}

	public Koordinate getFirst()
	{
		return first;
	}

	public Koordinate getSecond()
	{
		return second;
	}

	public Koordinate getThird()
	{
		return third;
	}

	public double getA()
	{
		return a;
	}

	public double getB()
	{
		return b;
	}

	public double getC()
	{
		return c;
	}

	private static double square(double x)
	{
		return x * x;
	}
}
