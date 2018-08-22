#include "plot.h"
#include "funktion.h"

#include <QStringList>
#include <QString>
#include <QPoint>

#include <mutex>

//global variables
std::mutex renderInProgress;
std::mutex updateData;
const unsigned int STEP_SIZE = 10;

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

    //Initializing serial interface
    try
    {

        if(!port->open(QIODevice::ReadWrite))
            throw FallturmException(QString("Failed to open serial interface!"));

        port->setBaudRate(Fallturm::settings->value("interface/serial/baudrate","9600").toInt());
        port->setDataBits(QSerialPort::Data8);
        port->setParity(QSerialPort::NoParity);
        port->setStopBits(QSerialPort::OneStop);
        port->setFlowControl(QSerialPort::NoFlowControl);


        Logger::log << L_INFO << "Initialized serial interface " << port->portName() << " with baudrate " << port->baudRate() << "\n";
    }catch(...)
    {
        QErrorMessage error;
        error.showMessage("Failed to open serial interface!");
        Logger::log << L_ERROR << "Failed to open serial interface!\n";
    }


    intervalTimer.start();
}

void Plot::renderNewPlot()
{
    std::lock_guard<std::mutex> guard(renderInProgress);
    Logger::log << L_DEBUG << "Rendering new plot...\n";
    //Doing math...
    long startTime = 0;
    int startDistance = 0;
    for(Entry e : entries)
        if(e.led == 0)
        {
            startTime = e.timeInMillis;
            startDistance = e.height;
            break;
        }

    QVector<Koordinate> coordinates;
    for(Entry e : entries)
    {
        Koordinate k(e.timeInMillis-startTime,e.height-startDistance);
        Logger::log << L_DEBUG << k.getX() << " : " << k.getY() << "\n";
        coordinates.push_back(k);
    }
    Funktion f = Funktion::init(coordinates);
    double a = f.a();
    double b = f.b();
    double c = f.c();

    //Drawing data
    Logger::log << L_DEBUG << "Drawing data...\n";
    const unsigned int PLOT_WIDTH = plotArea().width();

    //exakte Messwerte
    QLineSeries *exact = new QLineSeries(this);
    exact->setName("Exakte Messwerte");
    int pixelToDraw = 0;
    int pixelDistancePerStep = PLOT_WIDTH / coordinates.size();
    for(Koordinate k : coordinates)
    {
        pixelToDraw+= pixelDistancePerStep;
        exact->append(k.getX(),k.getY());
    }

    QLineSeries *mathIdeal = new QLineSeries(this);
    mathIdeal->setName("idealisierte Messwerte");
    Logger::log << L_DEBUG << "Drawing " << PLOT_WIDTH << " with " << STEP_SIZE <<" pixels distance...\n";
    for(unsigned int pixelToDraw=0;pixelToDraw<PLOT_WIDTH;pixelToDraw+=STEP_SIZE)
    {
        double x = pixelToDraw;
        double y = (a * (x * x)) + (b * x) + c;
        mathIdeal->append(x,y);
    }

    //formatting plot
    Logger::log <<L_DEBUG << "Formatting plot...\n";
    addSeries(exact);
    //addSeries(mathIdeal);
    createDefaultAxes();
    axisX()->setTitleText("t[ms]");
    axisY()->setTitleText("s[cm]");
    setTitle("Fallturm-Auswertung");
    Logger::log << L_DEBUG << "Rendering completed.\n";

}

void Plot::handleTimeout()
{
    std::lock_guard<std::mutex> guard(updateData);
    if(!(port->isOpen() && port->isReadable()))
    {
        Logger::log << L_WARN << "Serial interface not available!\n";
        return;
    }

    int bytes_available = port->bytesAvailable();
    if(bytes_available > 4)
        emit dataAvailable();
}

void Plot::showNewPlot()
{
    QByteArray lineInBytes = buffer + port->readLine();
    if(lineInBytes.length() <= 0)
        return;
    QString  line = QString::fromUtf8(lineInBytes);
    if(!line.endsWith("\n"))
    {
        buffer.append(line);
        return;
    }
    buffer.clear();
    Logger::log << L_DEBUG << "Read: " << line << "\n";
    QStringList lineSplits = line.split(";");
    Entry entry;
    entry.height = lineSplits.at(0).toInt();
    entry.led = lineSplits.at(1).toInt();
    entry.timeInMillis = lineSplits.at(2).toLong();
    for(Entry e : entries)
        if(e.led == entry.led)
            return;
    entries.push_back(entry);
    Logger::log << L_DEBUG << "Extracted: " << entry.led << ";" << entry.height << ";" << entry.timeInMillis << "\n";
    if(entries.size() == LED_COUNT)
        renderNewPlot();
}
