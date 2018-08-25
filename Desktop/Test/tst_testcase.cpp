#include <QtTest>
#include <QCoreApplication>

// add necessary includes here
#include <QVector>
#include <limits>
#include "../Fallturm/parabola.h"

class testcase : public QObject
{
    Q_OBJECT

public:
    testcase();
    ~testcase();

private slots:
    void comparePoints();
    void initParabolaWithCoefficients();
    void calculateParabola();

};

testcase::testcase()
{

}

testcase::~testcase()
{

}

void testcase::comparePoints()
{
    FallturmMath::Point p1 = {1.0, 2.0};
    FallturmMath::Point p2;
    p2.x = 1.0;
    p2.y = 3;

    QCOMPARE((p1 == p2), false);
    QCOMPARE((p1 != p2), true);
}

void testcase::initParabolaWithCoefficients()
{
    FallturmMath::Parabola one(1,2,3);
    QVector<double> val = {1,2,3};
    QCOMPARE(one.getCoefficients(), val);
}

void testcase::calculateParabola()
{
    QVector<FallturmMath::Point> werte = {{0.5,0.5}, {1,2}, {2,8}};
    FallturmMath::Parabola p(werte);
    QVector<double> cof = {2, 0, 0};
    QVector<double> computed_cof = p.getCoefficients();
    for(int i = 0; i < cof.length(); i++)
        //QCOMPARE(Point::compare_double(computed_cof[i], cof[i]), true);
        QCOMPARE(FallturmMath::Point::compare_double(computed_cof[i], cof[i], 1e-13), true);
}

QTEST_MAIN(testcase)

#include "tst_testcase.moc"
