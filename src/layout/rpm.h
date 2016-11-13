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


#ifndef RPM
#define RPM


#include <QtWidgets>
#include "qroundprogressbar.h"
#include "gear.h"


class Rpm : public QWidget{
    Q_OBJECT

public:
    QWidget *central;
    QRoundProgressBar *bar;
    Gear *gear;

    //palette to color high/low RPM values
    QPalette high_rpm;
    QPalette mid_rpm;
    QPalette low_rpm;


    Rpm(QWidget *parent){
        central = new QWidget(parent);
        central->setFixedSize(parent->size());
        bar = new QRoundProgressBar(central);
        gear = new Gear(central);

        //palette
        high_rpm.setColor(QPalette::Highlight, Qt::red);
        mid_rpm.setColor(QPalette::Highlight, Qt::yellow);
        low_rpm.setColor(QPalette::Highlight, Qt::black);

        setupUI();
    }

    void setupUI(){
        setupBar();
    }

    void setupBar(){
        //bar settings
        bar->setRange(0, 20000);
        bar->setFormat("");
        bar->setDataPenWidth(0);
        bar->setBarStyle(QRoundProgressBar::StyleDonut);
        bar->setDecimals(0);

        //palette
        bar->setValue(0);
        bar->setNullPosition(225);

        //geometry
        bar->setGeometry(0, 0, central->width(), central->height());
    }

    void setValue(int rpm, int gear){
        //change color of bar to red
        if (rpm > 10500){
            bar->setPalette(this->high_rpm);
        }else if (rpm > 7500){
            bar->setPalette(this->mid_rpm);
        }else{
            bar->setPalette(this->low_rpm);
        }
        bar->setValue(rpm);
        this->gear->setValue(gear);
    }
};

#endif //RPM