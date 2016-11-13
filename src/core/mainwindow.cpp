#include <QLabel>
#include <stdexcept>

#include "mainwindow.h"
#include "../can/canbus.h"  // DEBUG
#include "core/settings.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    this->setFixedSize(DEFAULT_SIZE->width(), DEFAULT_SIZE->height());
    this->setWindowTitle(TITLE);
    this->setupWindows();
    this->setCentralWidget(tabs);
    this->tabs->setCurrentIndex(0);

    settings = new Settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());  // create settings manager

    connections = new ConnectionBridge();
    connect(connections->workerThread, SIGNAL(msgReceived(int, int)), this, SLOT(gotMessage(int,int)));
    connections->start();
}

MainWindow::~MainWindow()
{
    delete this;
}

void MainWindow::gotMessage(int code, int data) {
    setValue(data, (int) code);
}

/**
 * @brief MainWindow::setupWindows
 * @return setup gui tabs
 */
void MainWindow::setupWindows() {
    dashWindow = new DashWindow(this);  // create children windows
    bioWindow = new BioWindow(this);
    geoTimeWindow = new GeoTimeWindow(this);
    settingsWindow = new SettingsWindow(this);

    tabs = new QStackedWidget(this);  // create tab manager
    tabs->addWidget(dashWindow);  // add windows
    tabs->addWidget(bioWindow);
    tabs->addWidget(geoTimeWindow);
    tabs->addWidget(settingsWindow);
}

/**
 * @brief MainWindow::setValue
 * @param value new value to set in one of the tabs
 * @param code data field of value
 */
void MainWindow::setValue(double value, int code) {
    dashWindow->setValue(value, code);
    bioWindow->setValue(value, code);
}

/**
 * @brief MainWindow::changeTabLeft
 * @return change current tab to left one
 */
void MainWindow::changeTabLeft() {
    if (this->tabs->currentIndex() > 0) {
        this->tabs->setCurrentIndex(this->tabs->currentIndex() - 1);
    }
}

/**
 * @brief MainWindow::changeTabRight
 * @return change current tab to right one
 */
void MainWindow::changeTabRight() {
    if (this->tabs->currentIndex() < this->tabs->count() - 1) {
        this->tabs->setCurrentIndex(this->tabs->currentIndex() + 1);
    }
}

/**
 * @brief MainWindow::updateSettings
 * @return read default settings configuration and update layouts and user preferences
 */
void MainWindow::updateSettings() {
    bool isLightTheme = settings->hasLightTheme();  // retrieve theme preferences

    if (isLightTheme) {  // set light/dark theme
        THEME_COLOR = Qt::white;
        FONT_COLOR = Qt::black;
    } else {
        THEME_COLOR = Qt::black;
        FONT_COLOR = Qt::white;
    }
    THEME_PALETTE.setBrush(QPalette::Window, THEME_COLOR);
    THEME_PALETTE.setBrush(QPalette::WindowText, FONT_COLOR);
    THEME_PALETTE.setBrush(QPalette::Text, FONT_COLOR);
    THEME_PALETTE.setBrush(QPalette::Button, THEME_COLOR);
    THEME_PALETTE.setBrush(QPalette::ButtonText, FONT_COLOR);
    THEME_PALETTE.setBrush(QPalette::AlternateBase, THEME_COLOR);
    THEME_PALETTE.setBrush(QPalette::Base, THEME_COLOR);
    THEME_PALETTE.setBrush(QPalette::Shadow, THEME_COLOR);
    this->setPalette(THEME_PALETTE);

    this->dashWindow->updateSettings();  // update dashboard window
    this->bioWindow->updateSettings();  // update bio signals window
    this->geoTimeWindow->updateSettings();  // update geo-time window
    this->settingsWindow->displayUserPref();  // update settings window
}
