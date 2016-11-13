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


#include "settingstab.h"

Settingstab::Settingstab(QWidget *parent) : QMainWindow(parent) {
    central = new QWidget(this);
    central->setGeometry(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    setupUI();
    setupTabChange();
}

void Settingstab::setupUI() {
    this->setStyleSheet("QMainWindow {background-color: 'black';}");

    // setup font
    font = QFont("Arial", 8, QFont::Normal, false);
    this->setFont(font);

    // background widgets
    settingsboard_widget = new QWidget(central);
    settingsboard_widget->setGeometry(0, 0, central->width(), central->height());

    // widgets
    settingsboard = new Settingsboard(settingsboard_widget);
}

void Settingstab::setupTabChange() {
    QObject::connect(settingsboard, SIGNAL(changeTabParent(int)), this, SLOT(changeTabChild(int)));
}

void Settingstab::changeTabChild(int direction) {
    emit changeTabParent(direction);
}

void Settingstab::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.setFont(font);

    painter.setPen(QPen(QBrush(Qt::white), 10, Qt::SolidLine, Qt::SquareCap));
    painter.drawText(20, 70, QString::fromUtf8("Dashboard"));
    painter.drawText(410, 255, QString::fromUtf8("Gps"));
    painter.drawText(20, 255, QString::fromUtf8("Bio"));

    painter.setPen(QPen(QBrush(Qt::white), 2, Qt::SolidLine, Qt::SquareCap));
    painter.drawLine(20, 80, 400, 80);
    painter.drawLine(410, 265, 780, 265);
    painter.drawLine(20, 265, 400, 265);
}
