#include "settingsdialog.h"
#include "ui_settingsdialog.h"

#include <QSerialPortInfo>

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
    //Initialize boxes
    QList<QSerialPortInfo> ports = QSerialPortInfo::availablePorts();
    for(QSerialPortInfo port : ports)
        ui->seriellesInterfaceComboBox->addItem(port.description());

    //Set default values
    ui->seriellesInterfaceComboBox->setCurrentText(
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
    Fallturm::settings->setValue("interface/serial/baudrate",ui->bautRateComboBox->currentText());

    Logger::log << L_INFO << "Saved following settings:\n";
    for(QString key : Fallturm::settings->allKeys())
        Logger::log << L_INFO << key << " : " << Main::settings->value(key).toString() << "\n";
    this->accept();

    emit settingsChanged();
}
