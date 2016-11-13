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


#ifndef STATUS
#define STATUS


#include <QtWidgets>
#include "qroundprogressbar.h"


class Status : public QWidget{
    Q_OBJECT

public:
    QWidget *central;

    QLabel *oil_temperature_title;
    QLabel *engine_temp_title;
    QLabel *water_temp_title;

    QRoundProgressBar *oil_temperature_bar;
    QLCDNumber *oil_temperature_lcd;
    QLabel *engine_temp_label;
    QLabel *water_temp_label;


    Status(QWidget *parent){
        // layout
        central = new QWidget(parent);
        central->setFixedSize(190, 400);

        oil_temperature_title = new QLabel("", central);
        engine_temp_title = new QLabel("", central);
        water_temp_title = new QLabel("", central);

        oil_temperature_bar = new QRoundProgressBar(central);
        oil_temperature_lcd = new QLCDNumber(central);
        engine_temp_label = new QLabel(central);
        water_temp_label = new QLabel(central);

        setupUI();
    }

    void setupUI(){
        // titles
        QFont font;
        font.setItalic(true);
        font.setPointSize(12);

        oil_temperature_title->setAlignment(Qt::AlignCenter);
        oil_temperature_title->setFont(font);
        oil_temperature_title->setGeometry(0, 175, central->width(), 100);

        oil_temperature_lcd->setDigitCount(2);
        oil_temperature_lcd->setGeometry(50, 50, 75, 75);

        engine_temp_title->setAlignment(Qt::AlignCenter);
        engine_temp_title->setFont(font);
        engine_temp_title->setFixedSize(central->width(), 100);
        engine_temp_title->setGeometry(0, 195, engine_temp_title->width(), engine_temp_title->height());

        water_temp_title->setAlignment(Qt::AlignCenter);
        water_temp_title->setFont(font);
        water_temp_title->setFixedSize(central->width(), 100);
        water_temp_title->setGeometry(0, 295, water_temp_title->width(), water_temp_title->height());

        // oil bar
        oil_temperature_bar->setRange(0, 200);
        oil_temperature_bar->setFormat("");
        oil_temperature_bar->setDataPenWidth(0);
        oil_temperature_bar->setBarStyle(QRoundProgressBar::StyleDonut);
        oil_temperature_bar->setDecimals(0);
        oil_temperature_bar->setNullPosition(225);
        oil_temperature_bar->setGeometry(0, 0, 180, 200);

        QPalette palette_oil;
        palette_oil.setBrush(QPalette::Base, Qt::NoBrush);
        palette_oil.setBrush(QPalette::Shadow, QColor(237, 237, 237));
        oil_temperature_bar->setPalette(palette_oil);

        font.setItalic(false);
        font.setBold(true);
        font.setPointSize(32);

        // engine label
        engine_temp_label->setFont(font);
        engine_temp_label->setAlignment(Qt::AlignCenter);
        engine_temp_label->setFixedSize(200, 100);
        engine_temp_label->setGeometry(0, 220, 200, 100);

        // water label
        water_temp_label->setFont(font);
        water_temp_label->setAlignment(Qt::AlignCenter);
        water_temp_label->setFixedSize(central->width(), central->height()/4);
        water_temp_label->setGeometry(0, 320, 200, 100);
    }

    void setValue(double oil_temperature, double engine_temperature, double water_temperature){
        oil_temperature_bar->setValue((int) oil_temperature);
        oil_temperature_lcd->display((int) oil_temperature);
        engine_temp_label->setText(QString::number(engine_temperature) + QString::fromUtf8("C°"));
        water_temp_label->setText(QString::number(water_temperature) + QString::fromUtf8("C°"));
    }

};

#endif // STATUS

