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
    QLCDNumber *rpm_label;

    // palette to color high/low RPM values
    QPalette high_rpm;
    QPalette mid_rpm;
    QPalette low_rpm;


    Rpm(QWidget *parent){
        central = new QWidget(parent);
        central->setFixedSize(parent->size());
        bar = new QRoundProgressBar(central);
        rpm_label = new QLCDNumber(central);
        gear = new Gear(central);

        // palette
        high_rpm.setColor(QPalette::Highlight, Qt::red);
        high_rpm.setBrush(QPalette::Base, Qt::NoBrush);
        high_rpm.setBrush(QPalette::Shadow, QColor(237, 237, 237));

        mid_rpm.setColor(QPalette::Highlight, Qt::yellow);
        mid_rpm.setBrush(QPalette::Base, Qt::NoBrush);
        mid_rpm.setBrush(QPalette::Shadow, QColor(237, 237, 237));

        low_rpm.setColor(QPalette::Highlight, Qt::black);
        low_rpm.setBrush(QPalette::Base, Qt::NoBrush);
        low_rpm.setBrush(QPalette::Shadow, QColor(237, 237, 237));

        setupUI();
    }

    void setupUI(){
        setupBar();

        QFont font;
        font.setItalic(false);
        font.setPointSize(32);

        rpm_label->setDigitCount(5);
        rpm_label->setGeometry(100, 250, 200, 100);
    }

    void setupBar(){
        // bar settings
        bar->setRange(0, 20000);
        bar->setFormat("");
        bar->setDataPenWidth(0);
        bar->setBarStyle(QRoundProgressBar::StyleDonut);
        bar->setDecimals(0);

        // palette
        bar->setValue(0);
        bar->setNullPosition(225);

        // geometry
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
        rpm_label->display(rpm);

        this->gear->setValue(gear);
    }
};

#endif //RPM
