#ifndef GEOTIMEWINDOW_H
#define GEOTIMEWINDOW_H

#include <QMainWindow>

#include "settings.h"

namespace Ui {
class GeoTimeWindow;
}

class GeoTimeWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GeoTimeWindow(QWidget *parent = 0);
    ~GeoTimeWindow();

    void updateSettings();

private:
    Ui::GeoTimeWindow *ui;
    Settings *settings;  // settings manager
};

#endif // GEOTIMEWINDOW_H
