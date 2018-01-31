#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QChart>

#include "main.h"
#include "logger.h"
#include "settingsdialog.h"
#include "plot.h"

namespace Ui {
class MainWindow;
}

class Plot;
class SettingsDialog;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void updateToSettings();
    void changeSettings();
private:
    void init();

    Ui::MainWindow *ui;
    SettingsDialog* settingsDialog;
    Plot *plot;

};

#endif // MAINWINDOW_H
