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


#include <QtWidgets>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <sys/uio.h>
#include <net/if.h>
#include <linux/can.h>
#include <linux/can/raw.h>
#include <assert.h>
#include <stdio.h>
#include <QMessageBox>
#include <QString>
#include <QDebug>  // !!! TESTING PURPOSE ONLY
#include <stdio.h>  // splash screen
#include <stdlib.h>
#include <unistd.h>

#include "../utils/canworkerthread.h"
#include "mainwindow.h"


#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 480


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    this->setFixedSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    setupTab();
    setupCan();
    this->setCentralWidget(tabMenu);
}

MainWindow::~MainWindow() {
    m_workerThread->shutDown();  // Tell worker thread to shut down
    can->Close();  // Close can connection
    if(!m_workerThread->wait(3000)) {  // wait for worker thread to shut down, force if problem
        m_workerThread->terminate();
    }

    delete m_workerThread;
    delete can;
}

void MainWindow::setupTab() {
    // create tabmenu
    tabMenu = new QStackedWidget(this);

    // create and add tabs
    dashtab = new Dashtab(this);
    biotab = new Biotab(this);
    gpstab = new Gpstab(this);
    settingstab = new Settingstab(this);

    tabMenu->addWidget(dashtab);
    tabMenu->addWidget(biotab);
    tabMenu->addWidget(gpstab);
    tabMenu->addWidget(settingstab);

    changeTab(0);  // go to first tab
    // arrows to navigate through tabs
    QObject::connect(dashtab, SIGNAL(changeTabParent(int)), this, SLOT(changeTab(int)));
    QObject::connect(biotab, SIGNAL(changeTabParent(int)), this, SLOT(changeTab(int)));
    QObject::connect(gpstab, SIGNAL(changeTabParent(int)), this, SLOT(changeTab(int)));
    QObject::connect(settingstab, SIGNAL(changeTabParent(int)), this, SLOT(changeTab(int)));
}

void MainWindow::changeTab(int direction) {
    int current_tab = tabMenu->currentIndex();
    tabMenu->setCurrentIndex(current_tab + direction);

    // update title
    current_tab = tabMenu->currentIndex();
    if (current_tab == 0) {
        this->setWindowTitle(QString::fromUtf8("Quartodilitro GUI :: Dashboard"));
    } else if (current_tab == 1) {
        this->setWindowTitle(QString::fromUtf8("Quartodilitro GUI :: Bio"));
    } else if (current_tab == 2) {
        this->setWindowTitle(QString::fromUtf8("Quartodilitro GUI :: GPS"));
    } else {
        this->setWindowTitle(QString::fromUtf8("Quartodilitro GUI :: Settings"));
    }
}

void MainWindow::setupCan() {
    int ret;

    // create class to handle CAN communication
    can = new CanWrapper();

    // create a worker thread that listens to CAN messages and sends data to GUI with signal/slot mecanism
    m_workerThread = new CanWorkerThread();

    int errorCode;

    // connect signal from worker thread to slot in GUI
    // close old connection (if there is one) and shut down worker threads
    can->Close();

    // tell thread to shut down, force if problem
    m_workerThread->shutDown();

    if(!m_workerThread->wait(3000)) {
        m_workerThread->terminate();
    }

    // init new connection  // !!! TESTING PURPOSE ONLY
    ret = can->Init("vcan0", errorCode);
    if(!ret) {
        QMessageBox msgBox;
        msgBox.setText("Could not initialize CAN net. Error code: " + QString::number(errorCode) + "\nHave you run \"startCan.sh <interface name>\" as root?");
        msgBox.exec();
        return;
    }

    can->EnableErrorMessages();  // initialize worker thread and connect it to mainwindow
    m_workerThread->Init(can);
    m_workerThread->start();
    connect(m_workerThread, SIGNAL(msgReceived(int, int)), this, SLOT(msgReceived(int, int)));
}

void MainWindow::msgReceived(int id, int data) {
    dashtab->setValue(id, data);
}
