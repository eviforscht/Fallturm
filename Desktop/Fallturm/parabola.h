#ifndef PARABOLA_H
#define PARABOLA_H

#include <armadillo>
#include <cmath>
#include <limits>
#include <QVector>

struct Point{
    double x;
    double y;

    bool compare_double(const double a, const double b, const double eps);
    bool operator!=(Point& right);
    bool operator==(Point& right);
};



class Parabola
{
public:
    Parabola();
    Parabola(double a, double b, double c): a(a), b(b), c(c) {}
    Parabola(const QVector<Point> points);

    QVector<double> getCoefficients() const;

    double f(const double x) const;

private:
    // parabola has the form of y=ax^2 + bx +c
    double a = 0;
    double b = 0;
    double c = 0;
    void setCoefficients(double new_a, double new_b, double new_c);
};

#endif // PARABOLA_H
