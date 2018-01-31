#include "plot.h"

#include <QStringList>
#include <QString>
#include <QPoint>

Plot::Plot(QString serialPortName)
{
    port = new QSerialPort(serialPortName);
    init();
}

void Plot::init()
{
    QObject::connect(&intervalTimer, &QTimer::timeout, this, &Plot::handleTimeout);
    QObject::connect(this,&Plot::dataAvailable,this,&Plot::showNewPlot);
    intervalTimer.setInterval(LISTENER_INTERVALL);



    intervalTimer.start();
}

void Plot::renderNewPlot()
{
    QPoint p1,p2,p3;

    entries.clear();
}

void Plot::handleTimeout()
{
    if(!(port->isOpen() && port->isReadable()))
    {
        Logger::log << L_WARN << "Serial interface not readable!\n";
        return;
    }

    int bytes_available = port->bytesAvailable();
    if(bytes_available > 4)
        emit dataAvailable();
}

void Plot::showNewPlot()
{
    QStringList entries;
    while(true)
    {
        QByteArray lineInBytes = port->readLine();
        if(lineInBytes.length() <= 0)
            break;
        QString  line = QString::fromUtf8(lineInBytes);
        QStringList lineSplits = line.split(";");
        Entry entry;
        entry.height = lineSplits.at(0).toInt();
        entry.led = lineSplits.at(1).toInt();
        entry.timeInMillis = lineSplits.at(2).toLong();
        for(Entry e : entries)
            if(e.led == entry.led)
                return;
        entries.push_back(entry);
        if(entries.size() == LED_COUNT)
            renderNewPlot();
    }
}
