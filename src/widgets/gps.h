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


#ifndef GPS_H
#define GPS_H


#include <QApplication>
#include <QPushButton>
#include <QLabel>
#include <QDebug>  // DEBUG ONLY

#include "../utils/qtUtils.h"

class Gpsboard : public QWidget
{

    Q_OBJECT

public:
    // layout
    QWidget *central;

    // circuit map
    QPixmap map;
    QLabel *map_label;
    QLabel *lap;
    QWidget *map_widget;

    // button to change tab
    QPushButton *changeTabButtonLeft;
    QPushButton *changeTabButtonRight;

    Gpsboard(QWidget *parent) : QWidget(parent) {
        this->central = new QWidget(parent);
        this->central->setFixedSize(parent->size());

        setupUI();
    }

    void setupUI() {
        setupChangeTab();
        setupMap();
    }

    void setupChangeTab() {
        // left button
        // pixmap to show in button
        QPixmap left("../res/left.png");
        left = left.scaled(QSize(40, 40), Qt::IgnoreAspectRatio);

        changeTabButtonLeft = new QPushButton(central);
        changeTabButtonLeft->setIcon(left);
        changeTabButtonLeft->setStyleSheet("background-color: black;");
        changeTabButtonLeft->setGeometry(10, 10, 40, 40);

        // right button
        // pixmap to show in button
        QPixmap right("../res/right.png");
        right = right.scaled(QSize(40, 40), Qt::IgnoreAspectRatio);

        changeTabButtonRight = new QPushButton(central);
        changeTabButtonRight->setIcon(right);
        changeTabButtonRight->setStyleSheet("background-color: black;");
        changeTabButtonRight->setGeometry(50, 10, 40, 40);

        QObject::connect(changeTabButtonLeft, SIGNAL(clicked()), this, SLOT(changeTabChildLeft()));
        QObject::connect(changeTabButtonRight, SIGNAL(clicked()), this, SLOT(changeTabChildRight()));
    }

    void setupMap() {
        // map
        map = QPixmap("../res/circuit/circuit.png").scaled(QSize(156, 165), Qt::KeepAspectRatio);
        map_label = new QLabel(central);
        map_label->setGeometry(594, 32, map.width(), map.height());
        map_label->setPixmap(map);

        // lap
        lap = new QLabel("LAP: 3", central);
        setupLabel(lap, 18);
        lap->setStyleSheet("QLabel {color : rgb(182,180,182); }");
        lap->setGeometry(680, 32, 80, 40);
        lap->raise();
    }


signals:
    void changeTabParent(int direction);

protected slots:
    void changeTabChildLeft() {
        emit changeTabParent(-1);
    }

    void changeTabChildRight() {
        emit changeTabParent(1);
    }
};


#endif //GPS
