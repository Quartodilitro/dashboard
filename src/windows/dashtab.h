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


#ifndef DASHTAB_H
#define DASHTAB_H


#include <QMainWindow>
#include <QPainter>

#include "../widgets/dash.h"


#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 480


class Dashtab : public QMainWindow
{
    Q_OBJECT

public:
    Dashtab(QWidget *parent=0);

    QWidget *central;
    QWidget *dashboard_widget;
    Dashboard *dashboard;  // widget

    void setupUI();
    void setupTabChange();
    void setValue(int id, int data);
    void setValueMap(int sect, int coordx, int coordy);

protected:
    void paintEvent(QPaintEvent *event);

signals:
    void changeTabParent(int direction);

protected slots:
    void changeTabChild(int direction);
};


#endif // DASHTAB_H
