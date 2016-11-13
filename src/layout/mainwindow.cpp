/**
 * Copyright 2016 Quartodilitro Team Unipd
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


#include <QMainWindow>
#include <QtWidgets>

#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    central = new QWidget(this);

    // background color
    // this->setStyleSheet("QMainWindow {background: 'white';}");

    setupAction();
    setupWidgets();
    // setupTabs();
    setupUI();

    // timer to sample data
    timeInterval = 100;
    connect(&dataTimer, SIGNAL(timeout()), this, SLOT(updateDataSlot()));
    dataTimer.start(timeInterval);

    // quartodilitro image
    /*QPixmap background_logo("../res/qdl_logo.png");
    background_logo = background_logo.scaled(this->size(), Qt::IgnoreAspectRatio);
    QLabel *background_label = new QLabel(this);
    background_label->setPixmap(background_logo);
    this->setCentralWidget(background_label);*/

    // no close-minimze buttons
    // this->setWindowFlags(Qt::FramelessWindowHint);
}


//UI

void MainWindow::setupAction(){
    newAct = new QAction("&New", this);
    newAct->setShortcuts(QKeySequence::New);
    QObject::connect(newAct, SIGNAL(triggered()), this, SLOT(newFile()));

    openAct = new QAction("&Open..", this);
    openAct->setShortcuts(QKeySequence::Open);
    QObject::connect(openAct, SIGNAL(triggered()), this, SLOT(openFile()));

    saveAct = new QAction(tr("&Save"), this);
    saveAct->setShortcuts(QKeySequence::Save);
    QObject::connect(saveAct, SIGNAL(triggered()), this, SLOT(save()));

    exitAct = new QAction(tr("Exit&.."), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    QObject::connect(exitAct, SIGNAL(triggered()), this, SLOT(quit()));


    editAct = new QAction("&Settings", this);
    QList<QKeySequence> edit_shortcut;
    edit_shortcut.append(QKeySequence(Qt::CTRL + Qt::Key_E));
    editAct->setShortcuts(edit_shortcut);
    QObject::connect(editAct, SIGNAL(triggered()), this, SLOT(editDialog()));

    aboutAct = new QAction("&About", this);
    QList<QKeySequence> about_shortcut;
    about_shortcut.append(QKeySequence(Qt::CTRL + Qt::Key_A));
    aboutAct->setShortcuts(about_shortcut);
    QObject::connect(aboutAct, SIGNAL(triggered()), this, SLOT(aboutDialog()));

    helpAct = new QAction("&Help", this);
    QList<QKeySequence> help_shortcut;
    help_shortcut.append(QKeySequence(Qt::CTRL + Qt::Key_H));
    helpAct->setShortcuts(help_shortcut);
    QObject::connect(helpAct, SIGNAL(triggered()), this, SLOT(helpDialog()));
}

void MainWindow::setupWidgets(){
    //rooms
    timing_widget = new QWidget(central);
    dashboard_widget = new QWidget(central);
    status_widget = new QWidget(central);

    // widgets
    timing = new Timing(timing_widget);
    dashboard = new Dashboard(dashboard_widget);
    status = new Status(status_widget);

    //layout
    central->setFixedSize(800, 480);
    central->setGeometry(0, 0, central->width(), central->height());

    //timing
    timing_widget->setFixedSize(200, 480);
    timing_widget->setGeometry(0, 0, timing_widget->width(), timing_widget->height());

    //dashboard
    dashboard_widget->setFixedSize(380, 480);
    dashboard_widget->setGeometry(210, 0, dashboard_widget->width(), dashboard_widget->height());

    //status
    status_widget->setFixedSize(190, 400);
    status_widget->setGeometry(610, 80, status_widget->width(), status_widget->height());
}

void MainWindow::setupTabs(){
    tabMenu = new QTabWidget(central);
    tabMenu->addTab(new QWidget(this), "Dash");
    tabMenu->addTab(new QWidget(this), "Plots");
    tabMenu->addTab(new QWidget(this), "Extra");
    tabMenu->addTab(new QWidget(this), "Settings");
}

void MainWindow::setupUI(){
    this->setWindowTitle(QString::fromUtf8("Quartodilitro Onboard GUI"));
    this->setFixedSize(800, 480);
}

void MainWindow::paintEvent(QPaintEvent* event) {
    QPainter p;
    p.begin(this);
    p.setPen(QPen(QColor(0, 0, 255), 5, Qt::SolidLine, Qt::SquareCap, Qt::BevelJoin));

    // sectors
    p.drawLine(195, 0, 195, 480);
    p.drawLine(0, 100, 195, 100);
    p.drawLine(0, 225, 195, 225);
    p.drawLine(0, 350, 195, 350);

    // oil
    p.drawLine(600, 75, 800, 75);

    // temperatures
    p.drawLine(600, 400, 800, 400);
    p.drawLine(600, 300, 800, 300);
    p.drawLine(600, 75, 600, 480);

    p.end();
}

//dialogs

void MainWindow::editDialog(){
    statusBar()->showMessage("Edit settings");

    //create dialog to input settings
    QWidget *dialog = new QWidget;
    dialog->setWindowTitle("Settings");

    //create spin box, entry value and button
    QSpinBox *spinner = new QSpinBox(dialog);
    spinner->setRange(0, 2000);
    spinner->setValue(150);

    QSlider *slider = new QSlider(Qt::Horizontal, dialog);
    slider->setRange(0, 2000);
    slider->setTickInterval(10);

    QLabel *istruction = new QLabel(dialog);
    istruction->setText("Set refresh rate;\n0 means as fast as possible.");

    //accept button
    QPushButton *accept = new QPushButton(dialog);
    accept->setText("Ok");

    //setting up layout
    QDesktopWidget desktop;
    istruction->setGeometry(20,30,200,90);
    spinner->setGeometry(40,120,60,60);
    slider->setGeometry(120,120,120,60);
    accept->setGeometry(80,210,40,30);
    dialog->setMinimumSize(200,270);
    dialog->show();
}

void MainWindow::aboutDialog(){
    statusBar()->showMessage("About this GUI");
    QString aboutText = "This software is a sample telemetry software developed for Quartodilitro UNIPD.\n"
                        "Copyright (C) 2016 Quartodilitro. All right Reserved.\n"
                        "Contact developers: quartodilitro@gmail.com";
    QMessageBox::about(this, "Quartodilitro Onboard GUI", aboutText);

}

void MainWindow::helpDialog(){
    statusBar()->showMessage("Help me");
    QString aboutText = "All you need is love";
    QMessageBox::about(this, "Is something wrong?", aboutText);
}


//actions

void MainWindow::newFile(){
    return;
}

void MainWindow::openFile(){
    return;
}

void MainWindow::save(){
    return;
}

void MainWindow::quit(){
    this->quit();
}

// sample rate

void MainWindow::updateDataSlot(){
    // getting random seed
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());

    // generating pseudo-random values
    int thousand_random = qrand() % 1000 + 1;  // integer in [1; 1000]
    int rpm = thousand_random * 15;
    int gear = thousand_random / 150;
    double speed = thousand_random / 3;
    double sector_0 = thousand_random % 30;
    double sector_1 = thousand_random % 20;
    double sector_2 = thousand_random % 40;
    double oil_pressure = thousand_random / 5;
    double engine_temp = thousand_random / 6;
    double water_temp = thousand_random / 10;

    this->dashboard->rpm_indicator->setValue(rpm, gear);
    this->dashboard->speed_indicator->setValue(speed);
    this->timing->setValue(sector_0, sector_1, sector_2);
    this->status->setValue(oil_pressure, engine_temp, water_temp);
}

void MainWindow::setRefreshRate(int ms){
    this->timeInterval = ms;
    this->dataTimer.start(this->timeInterval);
}
