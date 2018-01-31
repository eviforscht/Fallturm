#include "funktion.h"

Parabel::Parabel(Koordinate a, Koordinate b, Koordinate c) : first(a), second(b), third(c)
{
    a = ((first.getY() - second.getY()) * (first.getX() - third.getX())
         - (first.getY() - third.getY()) * (first.getX() - second.getX())

         ) / ((Mathe::square(first.getX()) - Mathe::square(second.getX())) * (first.getX() - third.getX())
              - (Mathe::square(first.getX()) - Mathe::square(third.getX())) * (first.getX() - second.getX()));

    b = ((first.getY() - second.getY()) - a * (Mathe::square(first.getX()) - Mathe::square(second.getX()))

         ) / (first.getX() - second.getX());
    c = first.getY() - a * Mathe::square(first.getX()) - b * first.getX();
}

namespace Mathe
{
double round(double d, int stelle) {
    return QString::number(d,stelle).toDouble();
}

double hoch(double zahl, double exp)
{
    double temp = zahl;
    for(int i=1;i<exp;i++)
        zahl*=temp;

    return zahl;

}

double betrag(double value)
{
    if(value>0)
        return value;


    return -1*value;
}
double hoch(double zahl, int exp)
{
    return hoch(zahl,exp*1.0);
}

Funktion minS(LinkedList<Funktion>data)
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
    return ret;

}

double square(double zahl)
{
    return zahl * zahl;
}

}

//END_NAMESPACE_MATHE

double Koordinate::getX() const
{
    return x;
}

void Koordinate::setX(double value)
{
    x = value;
}

double Koordinate::getY() const
{
    return y;
}

void Koordinate::setY(double value)
{
    y = value;
}

double Parabel::getA() const
{
    return a;
}

double Parabel::getB() const
{
    return b;
}

double Parabel::getC() const
{
    return c;
}

Koordinate Parabel::getFirst() const
{
    return first;
}

Koordinate Parabel::getSecond() const
{
    return second;
}

Koordinate Parabel::getThird() const
{
    return third;
}

Funktion Funktion::init(QVector<Koordinate> data)
{
    collection.clear();
    Logger::log << L_INFO << "Starte Berechnung...\n";

    int p,q,r;
    p = 1;
    q = 2;
    r = data.size();
    while(p<r-1)
    {

        while(q<r)
        {
            Koordinate pk = data.at(p);
            Koordinate qk = data.at(q);
            Koordinate ursprung = data.first();

            Parabel pl(ursprung, pk, qk);

            double a1,b1,c1,t = 0;

            a1 = pl.getA();
            b1 = pl.getB();
            c1 = pl.getC();

            for(int i = 0;i<r;i++)
            {
                if(data.at(i).getX() == 0 || data.at(i).getY() == 0)
                    continue;
                double yR = data.at(i).getY();

                double yC = a1 * Mathe::hoch(data.at(i).getX(),2) + b1 * data.at(i).getX() + c1;

                if(yC == 0)
                    continue;

                t+= Mathe::betrag( ( 1 - yR/yC ) );

            }

            collection.add(Funktion(a1,b1,c1,t));

            q++;



        }

        p++;
        q = p+1;
    }
    Funktion sMin = Mathe::minS(collection);

    return sMin;

}

