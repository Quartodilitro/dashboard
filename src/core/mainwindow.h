#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>

#include "connectionbridge.h"
#include "dashwindow.h"
#include "biowindow.h"
#include "geotimewindow.h"
#include "settingswindow.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void gotMessage(int code, int data);  // connections
    void setValue(double data, int code);

    void changeTabLeft();  // children windows
    void changeTabRight();

    void updateSettings();  // settings

private:
    QSize *DEFAULT_SIZE = new QSize(800, 480);  // geometry of the screen of the dashboard
    QString TITLE = QString::fromUtf8("Quartodilitro Dashboard");
    QPalette THEME_PALETTE = QPalette();
    QColor THEME_COLOR = QColor();
    QColor FONT_COLOR = QColor();

    Settings *settings;  // settings manager

    ConnectionBridge *connections;  // abstract model for incoming connections

    QStackedWidget *tabs;  // children windows
    BioWindow *bioWindow;
    DashWindow *dashWindow;
    GeoTimeWindow *geoTimeWindow;
    SettingsWindow *settingsWindow;
    void setupWindows();
};

#endif // MAINWINDOW_H
