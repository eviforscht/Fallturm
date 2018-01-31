#ifndef PLOT_H
#define PLOT_H

#include "main.h"

#include <QObject>
#include <QtCharts/QAbstractAxis>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QValueAxis>
#include <QtCore/QRandomGenerator>
#include <QtCore/QDebug>
#include <QtCore/qtimer.h>
#include <QtSerialPort\qserialport.h>
#include <QtCore\qtimer.h>
#include <QtCharts\qchart.h>
#include <QSerialPort>
#include <QSerialPortInfo>

#include <mutex>

QT_CHARTS_BEGIN_NAMESPACE
class QSplineSeries;
class QValueAxis;
QT_CHARTS_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE

class Plot : public QChart
{
public:
    Plot(QString serialPortName);
private:
    void init();

};

#endif // PLOT_H
