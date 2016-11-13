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


#ifndef SETTINGS_H
#define SETTINGS_H


#include <QApplication>
#include <QPushButton>
#include <QLabel>
#include <QPainter>
#include <QMessageBox>
#include <QFontDatabase>

// DEBUG ONLY
#include <QDebug>


class Settingsboard : public QWidget
{

    Q_OBJECT

public:
    // layout
    QWidget *central;
    QPushButton *aboutButton;
    QFont font;

    // button to change tab
    QPushButton *changeTabButtonLeft;

    Settingsboard(QWidget *parent) : QWidget(parent) {
        this->central = new QWidget(parent);
        this->central->setFixedSize(parent->size());

        setupUI();
    }

    void setupUI() {
        // qdl logo
        QPixmap background_logo("../res/logobw.png");
        background_logo = background_logo.scaled(QSize(380, 60), Qt::KeepAspectRatio);
        QLabel *background_label = new QLabel(central);
        background_label->setGeometry(410, 70, 380, 60);
        background_label->setPixmap(background_logo);

        font = QFont("Arial", 8, QFont::Normal, false);
        font.setPointSize(12);
        this->setFont(font);

        setupHint();
        setupChangeTab();
    }

    void setupHint() {
            aboutButton = new QPushButton("About", central);
            aboutButton->setStyleSheet("background-color: black; color: white");
            aboutButton->setFont(font);
            aboutButton->setGeometry(710, 10, 80, 30);
            QObject::connect(aboutButton, SIGNAL(clicked()), this, SLOT(aboutDialog()));
    }

    void setupChangeTab() {
        // left button
        // pixmap to show in button
        QPixmap left("../res/left.png");
        left = left.scaled(QSize(40, 40), Qt::IgnoreAspectRatio);

        changeTabButtonLeft = new QPushButton(central);
        changeTabButtonLeft->setIcon(left);
        changeTabButtonLeft->setStyleSheet("background-color: black;");
        changeTabButtonLeft->setGeometry(10, 10, 40, 40);

        QObject::connect(changeTabButtonLeft, SIGNAL(clicked()), this, SLOT(changeTabChildLeft()));
    }

signals:
    void changeTabParent(int direction);

protected slots:
    void aboutDialog() {
        QString aboutText = "This software is a sample telemetry software developed for Quartodilitro (C).\n"
                            "Copyright (C) 2016. Created by the developers of Quartodilitro (C). All right Reserved.\n"
                            "Contact developers: quartodilitro@gmail.com";
        QMessageBox msg(this);
        msg.setWindowTitle("About this software");
        msg.setText(aboutText);
        msg.setFont(font);
        msg.exec();
    }

    void changeTabChildLeft() {
        emit changeTabParent(-1);
    }
};


#endif //SETTINGS
