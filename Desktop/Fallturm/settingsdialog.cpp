#include "settingsdialog.h"
#include "ui_settingsdialog.h"

#include <QSerialPortInfo>
#include <QMessageBox>

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);
    init();
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::init()
{
    //check if any serial interfaces are available
    if(QSerialPortInfo::availablePorts().isEmpty())
    {
        Logger::log << L_ERROR << "No serial interface is  connected!\n";
        QMessageBox *msgBox = new QMessageBox(this);
        msgBox->setStandardButtons(QMessageBox::Cancel | QMessageBox::Ok);
        msgBox->setText("Es wurde kein serielles Interface gefunden. Bitte schließen Sie den Arduino an!");
        int answer = msgBox->exec();
        if (answer == QMessageBox::Cancel)
            exit(EXIT_SUCCESS);
        else
            return init();
    }

    //Initialize boxes
    QList<QSerialPortInfo> ports = QSerialPortInfo::availablePorts();
    for(QSerialPortInfo port : ports)
        ui->serialInterfaceComboBox->addItem(port.description());

    //Set default values
    ui->serialInterfaceComboBox->setCurrentText(
                Fallturm::settings->value("interface/serial",
                                          QSerialPortInfo::availablePorts().first().description()).toString());
    ui->baudRateComboBox->setCurrentText(Fallturm::settings->value("interface/serial/baudrate/","9600").toString());

    //connects
    QObject::connect(ui->buttonBox,&QDialogButtonBox::accepted,this,&SettingsDialog::updateSettings);
}

void SettingsDialog::updateSettings()
{
    Logger::log << L_INFO << "Updating settings...\n";
    Fallturm::settings->setValue("interface/serial",serialDescriptionToPortName(ui->serialInterfaceComboBox->currentText()));
    Fallturm::settings->setValue("interface/serial/baudrate",ui->baudRateComboBox->currentText());

    Logger::log << L_INFO << "Saved following settings:\n";
    for(QString key : Fallturm::settings->allKeys())
        Logger::log << L_INFO << key << " : " << Fallturm::settings->value(key).toString() << "\n";
    this->accept();

    emit settingsChanged();
}

QString SettingsDialog::serialDescriptionToPortName(QString description)
{
    for(QSerialPortInfo pI : QSerialPortInfo::availablePorts())
        if(pI.description() == description)
            return pI.portName();
    return "";
}
