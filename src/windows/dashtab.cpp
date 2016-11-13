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


#include <QTime>

#include "dashtab.h"
#include <QFileInfo>

Dashtab::Dashtab(QWidget *parent) : QMainWindow(parent){
    central = new QWidget(this);
    central->setGeometry(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    setupUI();
    setupTabChange();
}

void Dashtab::setupUI() {
    this->setStyleSheet("QMainWindow {background-color: 'black';}");

    dashboard_widget = new QWidget(central);
    dashboard_widget->setGeometry(0, 0, central->width(), central->height());
    dashboard = new Dashboard(dashboard_widget);
}

void Dashtab::setValue(int id, int data) {
    dashboard->setValue(id, data);
    repaint();
}

void Dashtab::setValueMap(int sect, int coordx, int coordy) {
    repaint();
}

void Dashtab::setupTabChange() {
    QObject::connect(dashboard, SIGNAL(changeTabParent(int)), this, SLOT(changeTabChild(int)));
}

void Dashtab::changeTabChild(int direction) {
    emit changeTabParent(direction);
}

void Dashtab::paintEvent(QPaintEvent *event) {
    /*int second = QTime::currentTime().second() % 30;
    int gps_coord[60] = {134, 118, 131, 114, 130, 111, 127, 108, 125, 106, 122
                        , 101, 120, 98, 117, 95, 115, 92, 113, 89, 111, 86
                        , 108, 85, 104, 87, 101, 90, 98, 92, 94, 94, 91, 94
                        , 88, 94, 83, 93, 81, 91, 78, 88, 74, 86, 72, 84, 69
                        , 82, 67, 80, 66, 77, 65, 73, 66, 68, 66, 66, 65, 62};
    int coordx = gps_coord[second * 2];
    int coordy = gps_coord[second * 2 + 1];
    int sector = 0;  // get sector

    QPixmap *map = new QPixmap("../res/circuit/circuit_" + QString::number(sector) + QString::fromUtf8(".png"));    *map = map->scaled(QSize(156, 165), Qt::KeepAspectRatio);
    QPainter painter(map);
    painter.setPen(QPen(QBrush(QColor(255, 255, 255)), 10, Qt::SolidLine, Qt::RoundCap));
    painter.drawPoint(coordx, coordy);
    this->dashboard->map_label->setPixmap(*map);*/
}
