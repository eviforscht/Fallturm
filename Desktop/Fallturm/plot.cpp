#include "plot.h"
#include "funktion.h"

#include <QStringList>
#include <QString>
#include <QPoint>

Plot::Plot(QString serialPortName)
{
    port = new QSerialPort(serialPortName);
    init();
}


Plot::~Plot()
{

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
    //Doing math...
    long startTime = 0;
    for(Entry e : entries)
        if(e.led == 0)
            startTime = e.timeInMillis;

    QVector<Koordinate> coordinates;
    for(Entry e : entries)
    {
        Koordinate k(e.height,e.timeInMillis-startTime);
        coordinates.push_back(k);
    }
    Funktion f = Funktion::init(coordinates);
    double a = f.a();
    double b = f.b();
    double c = f.c();

    //Drawing data
    QLineSeries *exact = new QLineSeries(this);
    for(Koordinate k : coordinates)
        exact->append(k.getX(),k.getY());

    QLineSeries *mathIdeal = new QLineSeries(this);
    for(int i=0;i+=10;i<plotArea().width())
    {
        double x = i;
        double y = (a * (x * x)) + (b * x) + c;
        mathIdeal->append(x,y);
    }

    //formatting plot
    addSeries(exact);
    addSeries(mathIdeal);
    createDefaultAxes();
    setTitle("Fallturm-Auswertung");

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
