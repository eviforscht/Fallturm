#ifndef PARABOLA_H
#define PARABOLA_H

#include <cmath>
#include <armadillo>
#include <QVector>

struct Point{
    double x;
    double y;
};

class Parabola
{
public:
    Parabola();
    Parabola(double a, double b, double c): a(a), b(b), c(c) {}
    Parabola(QVector<Point> points);

    QVector<double> getCoefficients();

    double f(double x);

private:
    // parabola has the form of y=ax^2 + bx +c
    double a = 0;
    double b = 0;
    double c = 0;
    void setCoefficients(double new_a, double new_b, double new_c);
};

#endif // PARABOLA_H
