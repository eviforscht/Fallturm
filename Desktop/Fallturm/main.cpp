#include "main.h"


#include <QApplication>
#include <QErrorMessage>

int main(int argc, char *argv[])
{
    Fallturm::FallturmApp app(argc, argv);
    Fallturm::run(app);

    return EXIT_SUCCESS;
}


namespace Fallturm {
    QSettings *settings;
    Logger* log;
    MainWindow *mainWindow;

    void run(QApplication &app)
    {
        try
        {
            //Initialisierung
            if(init() != EXIT_SUCCESS)
                throw FallturmException(QString("Initialisierung fehlgeschlagen!"));

            //Ausführung
            showGui();
            app.exec();

        } catch(FallturmException e)
        {
            QErrorMessage error;
            error.showMessage(e.what());
        }
        catch(...)
        {
            QErrorMessage error;
            error.showMessage("Ein fataler Fehler ist aufgetreten! Es kann sein, dass das Program nun nicht mehr richtig funktiniert.");
        }

        //Shutting down
        shutdown();
    }

    /**
     * Initializes the program
     *
     * @brief init
     * @return
     */
    int init()
    {
        //Initializing logger
        Logger::log.init(Logger::All);
        if(initSettings() != EXIT_SUCCESS)
            throw FallturmException(QString("Failed to initialize settings!"));

        mainWindow= new MainWindow(Q_NULLPTR);

        Logger::log << L_INFO << "Program initialized.\n";

        return EXIT_SUCCESS;
    }

    int shutdown()
    {
        Logger::log << L_INFO << "Shutting down program.\n";

        Fallturm::settings->sync();
        if (Fallturm::settings->status() != 0) {
            Logger::log << L_ERROR << "failed to write the settings to" << Fallturm::settings->fileName().toStdString() << "\n";
            return EXIT_FAILURE;
        }
        else
            Logger::log << L_INFO << "wrote the settings to" << Fallturm::settings->fileName().toStdString() << "\n";

        delete settings;

        return EXIT_SUCCESS;
    }

    /**
     * Displays the gui
     *
     * @brief showGui
     */
    void showGui()
    {
        mainWindow->showMaximized();
    }

    int initSettings()
    {
        settings = new QSettings("Evangelische_Schule_Neuruppin", "Fallturm");
        settings->setIniCodec("UTF-8");
        Logger::log << L_INFO << "reading config file from " << Fallturm::settings->fileName() << "\n";
        settings->sync();
        Logger::log << L_INFO << "Settings initialized!\n";

        Logger::log << L_INFO << "Read following settings:\n";
        for(QString key : Fallturm::settings->allKeys())
            Logger::log << L_INFO << key << " : " << Fallturm::settings->value(key).toString() << "\n";

        return EXIT_SUCCESS;
    }
}
