#ifndef FUNKTION_H
#define FUNKTION_H

#include <QString>
#include <QVector>

#include "main.h"

class Koordinate
{
public:
    Koordinate() = default;
    Koordinate(unsigned long xk,unsigned long yk) : x(xk), y(yk) {}
    unsigned long getX() const;
    void setX(unsigned long value);

    unsigned long getY() const;
    void setY(unsigned long value);

private:
    unsigned long x;
    unsigned long y;

};

class Parabel
{
public:
    Parabel(Koordinate a, Koordinate b, Koordinate c);
    Parabel() = default;
    double getA() const;
    double getB() const;
    double getC() const;
    Koordinate getFirst() const;
    Koordinate getSecond() const;
    Koordinate getThird() const;

private:

    double a;
    double b;
    double c;
    Koordinate first;
    Koordinate second;
    Koordinate third;
};

class Funktion
{
public:
    Funktion() = default;
    Funktion(Parabel p, double s) : m_a(p.getA()),m_b(p.getB()),m_c(p.getC()),m_s(s) {}
    Funktion(double a, double b, double c, double s) : m_a(a), m_b(b), m_c(c),m_s(s) {}
    static Funktion init(QVector<Koordinate> data);

    double a() const;

    double b() const;

    double c() const;

    double s() const;

private:

    double m_a;
    double m_b;
    double m_c;
    double m_s;
    QVector<Funktion> collection;

};

namespace Mathe {
    double square(double zahl);
    double hoch(double zahl, double exp);
    double betrag(double value);
    double hoch(double zahl, int exp);
    Funktion minS(QVector<Funktion>data);

}

#endif // FUNKTION_H
