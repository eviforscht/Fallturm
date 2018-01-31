#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>

#include "logger.h"
#include "main.h"

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent = 0);
    ~SettingsDialog();
signals:
    void settingsChanged();

public slots:
    void updateSettings();

private:
    void init();

    Ui::SettingsDialog *ui;
};

#endif // SETTINGSDIALOG_H
