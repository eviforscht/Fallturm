#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QChart>

#include "main.h"
#include "logger.h"
#include "settingsdialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void updateToSettings();
private:
    void init();

    Ui::MainWindow *ui;
    SettingsDialog* settingsDialog;

};

#endif // MAINWINDOW_H
