#include "parabola.h"

Parabola::Parabola()
{

}

QVector<double> Parabola::getCoefficients()
{
    return QVector<double> {a, b, c};
}

double Parabola::f(double x)
{
    return a*x*x + b*x + c;
}

Parabola::Parabola(QVector<Point> points)
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
    arma::mat A(n, n);
    A(1,1) = x4;
    A(1,2) = x3;
    A(1,3) = x2;
    A(2,1) = x3;
    A(2,2) = x2;
    A(2,3) = x;
    A(3,1) = x2;
    A(3,2) = x;
    A(3,3) = double(n);

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
        setCoefficients(x_vec(1), x_vec(2), x_vec(3));
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
