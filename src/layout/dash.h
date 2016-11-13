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


#include <QMainWindow>
#include "timing.h"
#include "dashboard.h"
#include "status.h"

class Dash : public QMainWindow
{
    Q_OBJECT

public:
    explicit Dash(QWidget *parent = 0);

    //layout
    QWidget *central;
    QWidget *timing_widget;
    QWidget *dashboard_widget;
    QWidget *status_widget;

    //widgets
    Timing *timing;
    Dashboard *dashboard;
    Status *status;

    //layoutsetup
    void setupWidgets();
    void setupUI();

    //realtime data
    int timeInterval;

private: //realtime data
    QTimer dataTimer;

private slots:
    //sample rate
    void updateDataSlot();
    void setRefreshRate(int ms);
};

#endif // DASH_H
