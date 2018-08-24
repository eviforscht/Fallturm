#include "parabola.h"

bool Point::compare_double(const double a, const double b, const double eps)
{
    return std::abs(a - b) < eps;
}

bool Point::operator==(Point& right)
{
    return compare_double(this->x, right.x) && compare_double(this->y, right.y);
}

bool Point::operator!=(Point& right)
{
    return !(*this == right);
}

Parabola::Parabola()
{

}

QVector<double> Parabola::getCoefficients() const
{
    return QVector<double> {a, b, c};
}

double Parabola::f(const double x) const
{
    return a*x*x + b*x + c;
}

Parabola::Parabola(const QVector<Point> points)
{
    //solve Ax=b for x
    //x is col vector with a,b and c

    //at least 3 points are required
    int n = points.length();
    if (n < 3)
            return;

    //xi^4
    double x4 = 0;
    for(int i = 0; i < n; i++)
        x4 += std::pow(points[i].x, 4);

    //xi^3
    double x3 = 0;
    for(int i = 0; i < n; i++)
        x3 += std::pow(points[i].x, 3);

    //xi^2
    double x2 = 0;
    for(int i = 0; i < n; i++)
        x2 += std::pow(points[i].x, 2);

    //xi
    double x = 0;
    for(int i = 0; i < n; i++)
        x += points[i].x;

    //create Matrix A
    arma::mat A(3, 3);
    A(0,0) = x4;
    A(0,1) = x3;
    A(0,2) = x2;
    A(1,0) = x3;
    A(1,1) = x2;
    A(1,2) = x;
    A(2,0) = x2;
    A(2,1) = x;
    A(2,2) = double(n);

    //column vector b

    double b_vec_el1 = 0;
    for(int i = 0; i < n; i++)
        b_vec_el1 += std::pow(points[i].x, 2) * points[i].y;

    double b_vec_el2 = 0;
    for(int i = 0; i < n; i++)
        b_vec_el2 += points[i].x * points[i].y;

    double b_vec_el3 = 0;
    for(int i = 0; i < n; i++)
        b_vec_el3 += points[i].y;

    arma::vec b_vec = {b_vec_el1, b_vec_el2, b_vec_el3};

    //calculate x
    try {
        arma::vec x_vec;
        bool success = arma::solve(x_vec, A, b_vec);
        if (success == false)
            throw success;
        setCoefficients(x_vec(0), x_vec(1), x_vec(2));
    } catch (std::runtime_error &e) {
        std::cerr << "runtime error: " << e.what();
    } catch(...){
        std::cerr << "error solving linear equation system";
    }
}

void Parabola::setCoefficients(double new_a, double new_b, double new_c)
{
    a = new_a;
    b = new_b;
    c = new_c;
}
