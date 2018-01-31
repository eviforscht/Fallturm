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
#include <QVector>

#include <mutex>

#define LISTENER_INTERVALL 100
#define LED_COUNT 8

QT_CHARTS_BEGIN_NAMESPACE
class QSplineSeries;
class QValueAxis;
QT_CHARTS_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE

class Plot : public QChart
{
public:

    struct Entry {
        unsigned int led;
        unsigned int height;
        unsigned long timeInMillis;
    };

    Plot(QString serialPortName);

public slots:
    void handleTimeout();
    void showNewPlot();
signals:
    void dataAvailable();
private:
    void init();
    void renderNewPlot();
    QSerialPort* port;
    QTimer intervalTimer;
    QVector<Entry> entries;

};

#endif // PLOT_H
