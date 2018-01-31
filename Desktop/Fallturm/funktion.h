#ifndef FUNKTION_H
#define FUNKTION_H

#include <QString>
#include <QVector>

#include "logger.h"
#include "main.h"
class Koordinate
{
public:
    Koordinate() = default;
    double getX() const;
    void setX(double value);

    double getY() const;
    void setY(double value);

private:
    double x;
    double y;

};

class Parabel
{
public:
    Parabel(Koordinate a, Koordinate b, Koordinate c) : first(a), second(b), third(c) {}
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

private:

    Funktion init(QVector<Koordinate> data);
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
    Funktion minS(LinkedList<Funktion>data);

}

#endif // FUNKTION_H
