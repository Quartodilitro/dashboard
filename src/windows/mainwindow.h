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


#include <QStackedWidget>
#include <QMainWindow>

#include "dashtab.h"
#include "biotab.h"
#include "gpstab.h"
#include "settingstab.h"
#include "../utils/canworkerthread.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QWidget *central;  // layout
    QStackedWidget *tabMenu;  //tabs
    Dashtab *dashtab;
    Biotab *biotab;
    Gpstab *gpstab;
    Settingstab *settingstab;

    void setupTab();
    void setupCan();

private:
    CanWrapper *can;  // canbus
    int m_receivedMessages;  // Number of received messages
    CanWorkerThread *m_workerThread;  // Thread that listens for CAN messages

protected slots:
    void changeTab(int direction);
    void msgReceived(int id, int data);
};

#endif // MAINWINDOW_H
