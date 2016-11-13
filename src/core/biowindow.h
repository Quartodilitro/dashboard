#ifndef BIOWINDOW_H
#define BIOWINDOW_H

#include <QMainWindow>

#include "connectionbridge.h"
#include "settings.h"
#include "ui_biowindow.h"


namespace Ui {
class BioWindow;
}

class BioWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit BioWindow(QWidget *parent=0);
    ~BioWindow();

    double getValue(int code);
    void updateSettings();

private:
    Ui::BioWindow *ui;

    ConnectionBridge *connectionBridge;
    Settings *settings;

public slots:
    void setValue(int value, int code);
};

#endif // BIOWINDOW_H
