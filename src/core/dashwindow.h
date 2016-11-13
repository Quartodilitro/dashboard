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
    void updateGPSMap();
    double getValue(int code);

    void updateSettings();

private:
    Ui::DashWindow *ui;

    ConnectionBridge *connectionBridge;
    Settings *settings;  // settings manager

    QPixmap map;
    double speedValue;
    double rpmValue;
    double gearValue;
    double gpsX;
    double gpsY;
};

#endif // DASHWINDOW_H
