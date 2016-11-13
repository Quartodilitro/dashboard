#ifndef GEOTIMEWINDOW_H
#define GEOTIMEWINDOW_H

#include <QMainWindow>

#include "settings.h"
#include "connectionbridge.h"

namespace Ui {
class GeoTimeWindow;
}

class GeoTimeWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GeoTimeWindow(QWidget *parent = 0);
    ~GeoTimeWindow();

    void setValue(double value, int code);
    void updateGPSMap();
    void updateSettings();

private:
    Ui::GeoTimeWindow *ui;
    Settings *settings;  // settings manager
    ConnectionBridge *connectionBridge;  // data bus and connection manager

    QPixmap map;
    double gpsX;
    double gpsY;
};

#endif // GEOTIMEWINDOW_H
