#ifndef MAIN_H
#define MAIN_H

#include "logger.h"
#include "fallturmexception.h"
#include "mainwindow.h"

#include <QApplication>
#include <QSettings>
#include <QErrorMessage>

class MainWindow;

namespace Fallturm {
void run(QApplication &app);
int init();
int shutdown();
void showGui();
int initSettings();

extern QSettings *settings;

extern Logger *log;

extern MainWindow* mainWindow;

class FallturmApp : public QApplication
{
public:
    FallturmApp(int &argc, char ** arg) : QApplication(argc, arg) {}
private:
    bool notify(QObject* receiver, QEvent* event) Q_DECL_OVERRIDE
    {
        try
        {
            return QApplication::notify(receiver, event);
        }
        catch (...)
        {
            QErrorMessage error;
            error.showMessage("Ein schwerer Fehler ist aufgetreten. Das Programm funktioniert evtl. nicht mehr richtig.");
        }

        return false;
    }
};
}

#endif // MAIN_H
