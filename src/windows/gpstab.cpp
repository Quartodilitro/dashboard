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

void Gpstab::setValue(int id, int data) {
    qDebug() << "GPS: set value\n";
}

void Gpstab::setValueMap(int sect, int coordx, int coordy) {
    repaint();
}

void Gpstab::setupTabChange() {
    QObject::connect(gpsboard, SIGNAL(changeTabParent(int)), this, SLOT(changeTabChild(int)));
}

void Gpstab::changeTabChild(int direction) {
    emit changeTabParent(direction);
}

void Gpstab::paintEvent(QPaintEvent *) {
    int second = QTime::currentTime().second() % 30;

    int coordx = 0;  // this->gps_coord[second * 2];
    int coordy = 0;  // this->gps_coord[second * 2 + 1];
    int sector = 0;  // get sector

    /* this->map = new QPixmap("../res/circuit/circuit_" + QString::number(sector) + QString::fromUtf8(".png"));
    this->map->scaled(QSize(156, 165), Qt::KeepAspectRatio);*/
    /*QPainter painter(this->map);
    painter.setPen(QPen(QBrush(QColor(255, 255, 255)), 10, Qt::SolidLine, Qt::RoundCap));
    painter.drawPoint(coordx, coordy);
    this->gpsboard->map_label->setPixmap(*map);*/
}
