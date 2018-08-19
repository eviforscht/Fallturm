#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QChartView>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    init();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init()
{
    settingsDialog = new SettingsDialog(this);
    updateToSettings();

    QObject::connect(ui->actionBeenden,&QAction::triggered,this,&MainWindow::close);
    QObject::connect(ui->actionEinstellungen,&QAction::triggered,this,&MainWindow::changeSettings);
    QObject::connect(settingsDialog,&SettingsDialog::settingsChanged,this,&MainWindow::updateToSettings);
}

void MainWindow::updateToSettings()
{
    QString serialPortDesc = Fallturm::settings->value("interface/serial",
                                               QSerialPortInfo::availablePorts().first().portName()).toString();
    plot = new Plot(serialPortDesc);
    plot->setAnimationOptions(QChart::AllAnimations);
    plot->setTitle("Fallturm");

    QChartView* chartView = new QChartView();
    chartView->setChart(plot);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Maximum);
    chartView->repaint();
    this->setCentralWidget(chartView);
}


void MainWindow::changeSettings()
{
    settingsDialog->setWindowModality(Qt::ApplicationModal);
    settingsDialog->exec();
}
