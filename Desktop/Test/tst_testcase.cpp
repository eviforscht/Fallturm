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
    Parabola p(1,2,3);
    QVector<double> test = {1,2,3};
    QCOMPARE(p.getCoefficients(), test);
}

QTEST_MAIN(testcase)

#include "tst_testcase.moc"
