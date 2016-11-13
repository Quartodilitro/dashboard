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


#ifndef GPSTAB_H
#define GPSTAB_H


#include <QMainWindow>
#include <QPainter>
#include <QFontDatabase>

#include "../widgets/gps.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 480


class Gpstab : public QMainWindow
{
    Q_OBJECT

public:
    Gpstab(QWidget *parent = 0);

    QWidget *central;
    QWidget *gpsboard_widget;
    QFont font;
    Gpsboard *gpsboard;  // widget
    int gps_coord[60];
    QPixmap* map;

    void setupUI();
    void setupTabChange();
    void setValue(int id, int data);
    void setValueMap(int sect, int coordx, int coordy);

protected:
    void paintEvent(QPaintEvent *);

signals:
    void changeTabParent(int direction);

protected slots:
    void changeTabChild(int direction);
};


#endif // GPSTAB_H
