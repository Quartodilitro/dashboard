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


#ifndef DASH_H
#define DASH_H


#include <QApplication>
#include <QPushButton>
#include <QLabel>
#include <QFontDatabase>
#include <QTime>
#include <QPainter>
#include <QDebug>  // DEBUG ONLY

#include "qroundprogressbar.h"
#include "../utils/qtUtils.h"


class Timing : public QWidget
{

    Q_OBJECT

public:
    QWidget *central;
    QFont font;

    QLabel *title_1;
    QLabel *title_2;
    QLabel *title_3;
    QLabel *title_tot;

    QLabel *sect_1;
    QLabel *sect_2;
    QLabel *sect_3;
    QLabel *sect_tot;

    QLabel *best_1;
    QLabel *best_2;
    QLabel *best_3;
    QLabel *best_tot;

    Timing(QWidget *parent) : QWidget(parent) {
        this->central = new QWidget(parent);
        this->central->setFixedSize(parent->size());

        setupUI();
        setupGeometry();
    }

    void setupUI() {
        // setup font
        font = QFont("Arial", 8, QFont::Normal, false);
        this->setFont(font);

        // labels
        title_1 = new QLabel("I1", central);
        title_2 = new QLabel("I2",central);
        title_3 = new QLabel("I3",central);
        title_tot = new QLabel("TOT",central);

        sect_1 = new QLabel("29\"456", central);
        sect_2 = new QLabel("45\"961", central);
        sect_3 = new QLabel("19\"885", central);
        sect_tot = new QLabel("1\'45\"456", central);

        best_1 = new QLabel("29\"133", central);
        best_2 = new QLabel("45\"961", central);
        best_3 = new QLabel("18\"789", central);
        best_tot = new QLabel("1\'43\"994", central);

        setupTitle(title_1);
        setupTitle(title_2);
        setupTitle(title_3);
        setupTitle(title_tot);

        setupSect(sect_1);
        setupSect(sect_2);
        setupSect(sect_3);
        setupSect(sect_tot);

        setupBest(best_1);
        setupBest(best_2);
        setupBest(best_3);
        setupBest(best_tot);
    }

    void setupTitle(QLabel *label) {
        // QFont font;
        font.setPointSize(18);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);
        label->setStyleSheet("QLabel {color : rgb(182,180,182); }");
    }

    void setupSect(QLabel *label) {
        // QFont font;
        font.setPointSize(20);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);
        label->setStyleSheet("QLabel {color : rgb(182,180,182); }");
    }

    void setupBest(QLabel *label) {
        // QFont font;
        font.setPointSize(12);
        font.setBold(true);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);
        label->setStyleSheet("QLabel {color : rgb(255, 0, 255); }");
    }

    void setupGeometry() {
        /*int width_tot = 100;
        int level_title = 0;*/
        int height = 50;
        /*int height_title = 25;
        int level_sect = 25;
        int height_sect = 105;
        int level_best = 125;
        int height_best = 75;*/

        title_1->setGeometry(0, 0, 50, height);
        title_2->setGeometry(0, 50, 50, height);
        title_3->setGeometry(0, 100, 50, height);
        title_tot->setGeometry(0, 150, 50, height);

        sect_1->setGeometry(50, 0, 150, height);
        sect_2->setGeometry(50, 50, 150, height);
        sect_3->setGeometry(50, 100, 150, height);
        sect_tot->setGeometry(50, 150, 150, height);

        best_1->setGeometry(200, 0, 80, height);
        best_2->setGeometry(200, 50, 80, height);
        best_3->setGeometry(200, 100, 80, height);
        best_tot->setGeometry(200, 150, 80, height);
    }
};


class Dashboard : public QWidget
{

    Q_OBJECT

public:
    // layout
    QWidget *central;
    QFont font;

    // logo
    QPixmap logo;
    QLabel *logo_label;

    // widgets
    QLabel *rpm;
    QLabel *speed;
    QLabel *gear;
    QPalette bar_palette;
    QRoundProgressBar *bar;

    // temperatures
    QLabel *water;
    QLabel *air;
    QLabel *bpm;

    QLabel *water_title;
    QLabel *air_title;
    QLabel *bpm_title;

    // timing
    QWidget *timing_widget;
    Timing *timing;

    // button to change tab
    QPushButton *changeTabButtonRight;

    Dashboard(QWidget *parent) : QWidget(parent) {
        this->central = new QWidget(parent);
        this->central->setFixedSize(parent->size());

        setupUI();
    }

    void setupUI() {
        font = QFont("Arial", 8, QFont::Normal, false);
        this->setFont(font);

        setupBar();
        setupLabels();
        setupChangeTab();
        setupLogo();
        setupTiming();
    }

    void setupChangeTab() {
        // pixmap to show in button
        QPixmap right("../res/right.png");
        right = right.scaled(QSize(40, 40), Qt::KeepAspectRatio);

        changeTabButtonRight = new QPushButton(central);
        changeTabButtonRight->setIcon(right);
        changeTabButtonRight->setStyleSheet("background-color: black;");
        changeTabButtonRight->setGeometry(50, 10, 40, 40);

        QObject::connect(changeTabButtonRight, SIGNAL(clicked()), this, SLOT(changeTabChildRight()));
    }

    void setupBar() {
        bar = new QRoundProgressBar(central);

        bar->setRange(0, 9334);  // in order to have max rpm (20000) at (360 - 45)° degree
        bar->setDecimals(0);
        bar->setValue(0);
        bar->setNullPosition(225);

        bar->setFormat("");
        bar->setDataPenWidth(30);
        bar->setOutlinePenWidth(30);
        bar->setBarStyle(QRoundProgressBar::StyleDonut);

        bar_palette.setBrush(QPalette::Window, Qt::black);
        bar_palette.setBrush(QPalette::AlternateBase, Qt::black);
        bar_palette.setBrush(QPalette::Base, Qt::black);
        bar_palette.setBrush(QPalette::Shadow, Qt::black);
        bar->setPalette(bar_palette);

        bar->setGeometry(26, 30, 470, 470);
    }

    void setupLabels() {
        rpm = new QLabel(central);
        speed = new QLabel(central);
        gear = new QLabel(central);
        water = new QLabel(central);
        air = new QLabel(central);
        bpm = new QLabel(central);
        water_title = new QLabel("T body °C", central);
        air_title = new QLabel("T oil °C", central);
        bpm_title = new QLabel("BPM", central);

        // stylesheet
        setupLabel(rpm, 30);
        setupLabel(gear, 54);
        setupLabel(speed, 30);
        setupLabel(water, 24);
        setupLabel(air, 24);
        setupLabel(bpm, 24);
        setupLabel(water_title, 12); water_title->setStyleSheet("QLabel {color : rgb(182,180,182); }");
        setupLabel(air_title, 12); air_title->setStyleSheet("QLabel {color : rgb(182,180,182); }");
        setupLabel(bpm_title, 12); bpm_title->setStyleSheet("QLabel {color : rgb(182,180,182); }");

        // geometry
        rpm->setGeometry(187, 275, 140, 52);
        gear->setGeometry(227, 187, 67, 82);
        speed->setGeometry(187, 127, 140, 52);
        water->setGeometry(488, 394, 80, 36);
        air->setGeometry(594, 394, 80, 36);
        bpm->setGeometry(692, 394, 80, 36);
        water_title->setGeometry(480, 420, 96, 36);
        air_title->setGeometry(594, 420, 80, 36);
        bpm_title->setGeometry(692, 420, 80, 36);
    }

    void setupLogo() {
        logo = QPixmap("../res/logobw.png").scaled(QSize(288, 52), Qt::KeepAspectRatio);
        logo_label = new QLabel(central);
        logo_label->setGeometry(116, 376, logo.width(), logo.height());
        logo_label->setPixmap(logo);
    }

    void setupTiming() {
        timing_widget = new QWidget(central);
        timing_widget->setGeometry(500, 190, 280, 200);

        timing = new Timing(timing_widget);
    }

    void setValue(int can_code, int data) {
        if (can_code == 0x0C){
            bar->setValue(data);
            rpm->setText(QString::number(data));

            // update palette
            if (data > 5000) {
                bar_palette.setBrush(QPalette::Highlight, Qt::red);
            }else{
                bar_palette.setBrush(QPalette::Highlight, Qt::white);
            }
            bar->setPalette(bar_palette);
        } else if (can_code == 0x0D){
            speed->setText(QString::number(data));
        } else if (can_code == 0xD4){
            gear->setText(QString::number(data));
        }

        // bitalino
        if (can_code == 0x0B) {
            bpm->setText(QString::number(data));
        }

        water->setText(QString::number(37.3)); // water->setText(QString::number(data * 8 % 300));
        air->setText(QString::number(data * 6 % 300));
    }

signals:
    void changeTabParent(int direction);

protected slots:
    void changeTabChildRight() {
        emit changeTabParent(1);
    }
};

#endif //DASH
