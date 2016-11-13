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


#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include "timing.h"
#include "dashboard.h"
#include "status.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    //actions
    QAction *newAct;
    QAction *openAct;
    QAction *saveAct;
    QAction *exitAct;

    QAction *editAct;

    QAction *aboutAct;
    QAction *helpAct;

    //tabs
    QTabWidget *tabMenu;

    //layout
    QWidget *central;
    QWidget *timing_widget;
    QWidget *dashboard_widget;
    QWidget *status_widget;
    QStatusBar *statusbar;

    //widgets
    Timing *timing;
    Dashboard *dashboard;
    Status *status;

    //layoutsetup
    void setupAction();
    void setupWidgets();
    void setupTabs();
    void setupUI();
    void paintEvent(QPaintEvent* event);

    //realtime data
    int timeInterval;

private: //realtime data
    QTimer dataTimer;

private slots:
    //menubar actions and dialogs
    void newFile();
    void openFile();
    void save();
    void quit();

    void editDialog();

    void aboutDialog();
    void helpDialog();

    //sample rate
    void updateDataSlot();
    void setRefreshRate(int ms);
};

#endif // MAINWINDOW_H
