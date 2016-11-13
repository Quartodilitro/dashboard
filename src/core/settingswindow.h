#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <QApplication>
#include <QMainWindow>
#include <QDebug>

#include "settings.h"


namespace Ui {
class SettingsWindow;
}

class SettingsWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SettingsWindow(QWidget *parent = 0);
    ~SettingsWindow();
    void displayUserPref();

private:
    Ui::SettingsWindow *ui;
    Settings *settings;

    void setUserPref(const QString &key, const QVariant &value);
    QVariant getUserPrefValue(const QString &key);

private slots:
    void updateUserPref();

signals:
    void updateSettings();
};

#endif // SETTINGSWINDOW_H
