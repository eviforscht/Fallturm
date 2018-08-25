#ifndef PARABOLA_H
#define PARABOLA_H

#include <armadillo>
#include <cmath>
#include <limits>
#include <QVector>

namespace FallturmMath{
struct Point{
    double x;
    double y;

    static bool compare_double(const double a, const double b, const double eps = std::numeric_limits<double>::epsilon());
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

    double getA() const;
    void setA(double value);

    double getB() const;
    void setB(double value);

    double getC() const;
    void setC(double value);

private:
    // parabola has the form of y=ax^2 + bx +c
    double a = 0;
    double b = 0;
    double c = 0;
    void setCoefficients(double new_a, double new_b, double new_c);
};
}
#endif // PARABOLA_H
