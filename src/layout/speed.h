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


#ifndef SPEED
#define SPEED


#include <QtWidgets>


class Speed : public QWidget{
    Q_OBJECT

public:
    QWidget *central;
    QLabel *speed;
    QLabel *title;
    QFrame *frame;

    Speed(QWidget *parent){
        central = new QWidget(parent);
        central->setFixedSize(parent->size());

        frame = new QFrame(central);

        speed = new QLabel(central);
        title = new QLabel("SPEED", central);

        setupUI();
    }

    void setupUI(){
        //frame
        frame->setFrameStyle(QFrame::Box);
        frame->setLineWidth(3);
        frame->setFixedSize(central->size());
        frame->setGeometry(0, 0, frame->width(), frame->height());

        //label
        QFont font;
        font.setItalic(true);
        font.setPointSize(18);

        title->setAlignment(Qt::AlignCenter);
        title->setFont(font);
        title->setFixedSize(central->width(), 20);
        title->setGeometry(0, 2, title->width(), title->height());

        font.setPointSize(36);
        font.setItalic(false);
        font.setBold(true);

        speed->setAlignment(Qt::AlignCenter);
        speed->setFont(font);
        speed->setFixedSize(central->size());
        speed->setGeometry(0, 0, speed->width(), speed->height());
    }

    void setValue(double value){
        speed->setText(QString::number(value));
    }
};

#endif // SPEED
