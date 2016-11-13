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

#include "dash.h"


Dash::Dash(QWidget *parent) : QMainWindow(parent)
{
    central = new QWidget(this);

    // background color
    // this->setStyleSheet("QMainWindow {background: 'white';}");

    setupWidgets();
    setupUI();

    // timer to sample data
    timeInterval = 100;
    connect(&dataTimer, SIGNAL(timeout()), this, SLOT(updateDataSlot()));
    dataTimer.start(timeInterval);
}


//UI

void Dash::setupWidgets(){
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
    dashboard_widget->setFixedSize(400, 480);
    dashboard_widget->setGeometry(200, 0, dashboard_widget->width(), dashboard_widget->height());

    //status
    status_widget->setFixedSize(200, 480);
    status_widget->setGeometry(600, 0, status_widget->width(), status_widget->height());
}

void Dash::setupUI(){
    this->setWindowTitle(QString::fromUtf8("Dash"));
    this->setFixedSize(800, 480);
}

// sample rate

void Dash::updateDataSlot(){
    // getting random seed
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());

    // generating pseudo-random values
    int rpm = qrand() % 15000 + 1;
    int gear = qrand() % 8;
    double speed = qrand() % 300 + double(qrand() % 1000) / 1000;
    double sector_0 = qrand() % 30 + double(qrand() % 1000) / 1000;
    double sector_1 = qrand() % 25 + double(qrand() % 1000) / 1000;
    double sector_2 = qrand() % 25 + double(qrand() % 1000) / 1000;

    this->dashboard->rpm_indicator->setValue(rpm, gear);
    this->dashboard->speed_indicator->setValue(speed);
    this->timing->setValue(sector_0, sector_1, sector_2);
}

void Dash::setRefreshRate(int ms){
    this->timeInterval = ms;
    this->dataTimer.start(this->timeInterval);
}
