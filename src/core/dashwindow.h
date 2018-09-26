#ifndef DASHWINDOW_H
#define DASHWINDOW_H

#include <limits>
#include <QMainWindow>
#include <QBitArray>

#include "connectionbridge.h"
#include "settings.h"
#include "ui_dashwindow.h"


namespace Ui {
class DashWindow;
}

class DashWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit DashWindow(QWidget *parent = 0);
    ~DashWindow();

    void setValue(double value, int code);
    double getValue(int code);

    void updateSettings();

private:
    Ui::DashWindow *ui;

    ConnectionBridge *connectionBridge;
    Settings *settings;  // settings manager

    double speedValue;
    double rpmValue;
    double gearValue;
};

#endif // DASHWINDOW_H
