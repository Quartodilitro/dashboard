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


#ifndef BIO_H
#define BIO_H


#include <QApplication>
#include <QPushButton>
#include <QLabel>

// DEBUG ONLY
#include <QDebug>


class Bioboard : public QWidget
{

    Q_OBJECT

public:
    // layout
    QWidget *central;

    // button to change tab
    QPushButton *changeTabButtonLeft;
    QPushButton *changeTabButtonRight;

    Bioboard(QWidget *parent) : QWidget(parent) {
        this->central = new QWidget(parent);
        this->central->setFixedSize(parent->size());

        setupUI();
    }

    void setupUI() {
        setupChangeTab();
    }

    void setupChangeTab() {
        // left button
        // pixmap to show in button
        QPixmap left("../res/left.png");
        left = left.scaled(QSize(40, 40), Qt::KeepAspectRatio);

        changeTabButtonLeft = new QPushButton(central);
        changeTabButtonLeft->setIcon(left);
        changeTabButtonLeft->setStyleSheet("background-color: black;");
        changeTabButtonLeft->setGeometry(10, 10, 40, 40);

        // right button
        // pixmap to show in button
        QPixmap right("../res/right.png");
        right = right.scaled(QSize(40, 40), Qt::KeepAspectRatio);

        changeTabButtonRight = new QPushButton(central);
        changeTabButtonRight->setIcon(right);
        changeTabButtonRight->setStyleSheet("background-color: black;");
        changeTabButtonRight->setGeometry(50, 10, 40, 40);

        QObject::connect(changeTabButtonLeft, SIGNAL(clicked()), this, SLOT(changeTabChildLeft()));
        QObject::connect(changeTabButtonRight, SIGNAL(clicked()), this, SLOT(changeTabChildRight()));
    }

signals:
    void changeTabParent(int direction);

protected slots:
    void changeTabChildLeft() {
        emit changeTabParent(-1);
    }

    void changeTabChildRight() {
        emit changeTabParent(1);
    }
};


#endif //BIO
