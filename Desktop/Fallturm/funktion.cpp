#include "funktion.h"

#include <cmath>

Parabel::Parabel(Koordinate ka, Koordinate kb, Koordinate kc) : first(ka), second(kb), third(kc)
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
    return (std::round(d*hoch(10,stelle))/hoch(10,stelle));
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

Funktion minS(QVector<Funktion>data)
{
    double d = std::numeric_limits<double>::max();
    Funktion ret;
    for(int i = 0;i<data.size();i++)
    {
        try
        {
            Funktion f = data.at(i);

            if(f.s()<d)
            {
                d= f.s();
                ret = f;
            }

        }catch(FallturmException e)
        {
            Logger::log << L_ERROR << e.what() << "\n";
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

unsigned long Koordinate::getX() const
{
    return x;
}

void Koordinate::setX(unsigned long value)
{
    x = value;
}

unsigned long Koordinate::getY() const
{
    return y;
}

void Koordinate::setY(unsigned long value)
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
    QVector<Funktion> collection;
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

            collection.push_back(Funktion(a1,b1,c1,t));

            q++;



        }

        p++;
        q = p+1;
    }
    Funktion sMin = Mathe::minS(collection);

    return sMin;

}

double Funktion::s() const
{
    return m_s;
}

double Funktion::c() const
{
    return m_c;
}

double Funktion::b() const
{
    return m_b;
}

double Funktion::a() const
{
    return m_a;
}

