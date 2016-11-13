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


#ifndef BIOTAB_H
#define BIOTAB_H


#include <QMainWindow>
#include <QPainter>
#include <QFontDatabase>

#include "../widgets/bio.h"


#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 480


class Biotab : public QMainWindow
{
    Q_OBJECT

public:
    Biotab(QWidget *parent = 0);

    //layout
    QWidget *central;
    QWidget *bioboard_widget;
    QFont font;

    //widgets
    Bioboard *bioboard;

    void setupUI();
    void setupTabChange();

protected:
    void paintEvent(QPaintEvent *);

signals:
    void changeTabParent(int direction);

protected slots:
    void changeTabChild(int direction);
};


#endif // BIOTAB_H
