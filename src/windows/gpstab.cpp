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


#include "gpstab.h"

Gpstab::Gpstab(QWidget *parent) : QMainWindow(parent) {
    central = new QWidget(this);
    central->setGeometry(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    setupUI();
    setupTabChange();
}

void Gpstab::setupUI() {
    this->setStyleSheet("QMainWindow {background-color: 'black';}");

    // setup font
    font = QFont("Arial", 8, QFont::Normal, false);
    this->setFont(font);

    // background widgets
    gpsboard_widget = new QWidget(central);
    gpsboard_widget->setGeometry(0, 0, central->width(), central->height());

    // widgets
    gpsboard = new Gpsboard(gpsboard_widget);
}

void Gpstab::setupTabChange() {
    QObject::connect(gpsboard, SIGNAL(changeTabParent(int)), this, SLOT(changeTabChild(int)));
}

void Gpstab::changeTabChild(int direction) {
    emit changeTabParent(direction);
}

void Gpstab::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.setPen(QPen(QBrush(Qt::white), 10, Qt::SolidLine, Qt::SquareCap));
    font.setPointSize(28);
    painter.setFont(font);

    // ooops
    painter.drawText(120, 200, QString::fromUtf8("Ooops! - again - "));

    font.setPointSize(12);
    painter.setFont(font);

    // additional details
    painter.drawText(120, 220, QString::fromUtf8("It seems this tab is still under development ..."));
    painter.drawText(120, 235, QString::fromUtf8("Don't worry, Quartodilitro (C) developers are rushing to fix it!"));
    painter.drawText(120, 280, QString::fromUtf8("Well, at least you can take look at the values in the dashboard!"));


    // rectangle
    QRectF rectangle(100, 160, 600, 140);
    painter.setPen(QPen(QBrush(Qt::white), 10, Qt::SolidLine, Qt::SquareCap));
    painter.drawRoundedRect(rectangle, 20.0, 15.0);
}
