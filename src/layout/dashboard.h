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


#ifndef DASHBOARD
#define DASHBOARD


#include <QtWidgets>
#include "rpm.h"
#include "speed.h"


class Dashboard : public QWidget{
    Q_OBJECT

public:
    // widgets
    Rpm *rpm_indicator;
    Speed *speed_indicator;

    // layout
    QWidget *central;
    QWidget *speed_room;
    QWidget *rpm_room;

    Dashboard (QWidget *parent){
        //layout
        central = new QWidget(parent);
        central->setFixedSize(400, 480);

        speed_room = new QWidget(central);
        speed_room->setFixedSize(300, 75);

        rpm_room = new QWidget(central);
        rpm_room->setFixedSize(400, 400);

        //widgets
        rpm_indicator = new Rpm(rpm_room);
        speed_indicator = new Speed(speed_room);

        setupUI();
    }

    void setupUI(){
        //layout
        speed_room->setGeometry(50, 0, speed_room->width(), speed_room->height());
        speed_indicator->setGeometry(0, 0, speed_room->width(), speed_room->height());

        rpm_room->setGeometry(0, 80, rpm_room->width(), rpm_room->height());
        rpm_indicator->setGeometry(0, 0, rpm_room->width(), rpm_room->height());
    }    

    void setValue(int rpm, int gear, double speed){
        rpm_indicator->setValue(rpm, gear);
        speed_indicator->setValue(speed);
    }
};

#endif // DASHBOARD
