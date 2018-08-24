#include <QtTest>
#include <QCoreApplication>

// add necessary includes here
#include <QVector>
#include "../Fallturm/parabola.h"

class testcase : public QObject
{
    Q_OBJECT

public:
    testcase();
    ~testcase();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_case1();

};

testcase::testcase()
{

}

testcase::~testcase()
{

}

void testcase::initTestCase()
{

}

void testcase::cleanupTestCase()
{

}

void testcase::test_case1()
{
    Parabola one(1,2,3);
    QVector<double> val = {1,2,3};
    QCOMPARE(one.getCoefficients(), val);

    QVector<Point> werte = {{0.5,0.5}, {1,2}, {2,8}};
    Parabola p(werte);
    QVector<double> cof = {2, 0, 0};
    QCOMPARE(p.getCoefficients(), cof);
}

QTEST_MAIN(testcase)

#include "tst_testcase.moc"
