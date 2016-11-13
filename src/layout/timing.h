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


#ifndef TIMING
#define TIMING


#include <QtWidgets>


class Timing : public QWidget{
    Q_OBJECT

public:
    QWidget *central;

    QFrame *frame_0;
    QFrame *frame_1;
    QFrame *frame_2;
    QFrame *frame_tot;

    QLabel *sector_title_0;
    QLabel *sector_title_1;
    QLabel *sector_title_2;
    QLabel *sector_title_tot;

    QLabel *sector_0;
    QLabel *sector_1;
    QLabel *sector_2;
    QLabel *sector_tot;


    Timing(QWidget *parent){
        central = new QWidget(parent);
        central->setFixedSize(200, 480);

        frame_0 = new QFrame(central);
        frame_1 = new QFrame(central);
        frame_2 = new QFrame(central);
        frame_tot = new QFrame(central);

        sector_title_0 = new QLabel("SECTOR 1", central);
        sector_title_1 = new QLabel("SECTOR 2",central);
        sector_title_2 = new QLabel("SECTOR 3",central);
        sector_title_tot = new QLabel("TOTAL",central);

        sector_0 = new QLabel(central);
        sector_1 = new QLabel(central);
        sector_2 = new QLabel(central);
        sector_tot = new QLabel(central);

        setupUI();
    }

    void setupUI(){
        // frames
        frame_0->setFrameStyle(QFrame::Box);
        frame_0->setLineWidth(3);
        frame_0->setFixedSize(central->width(), 75);
        frame_0->setGeometry(0, 0, frame_0->width(), frame_0->height());

        frame_1->setFrameStyle(QFrame::Box);
        frame_1->setLineWidth(3);
        frame_1->setFixedSize(central->width(), 75);
        frame_1->setGeometry(0, central->height()/4, frame_1->width(), frame_1->height());

        frame_2->setFrameStyle(QFrame::Box);
        frame_2->setLineWidth(3);
        frame_2->setFixedSize(central->width(), 75);
        frame_2->setGeometry(0, central->height()/2, frame_2->width(), frame_2->height());

        frame_tot->setFrameStyle(QFrame::Box);
        frame_tot->setLineWidth(3);
        frame_tot->setFixedSize(central->width(), 75);
        frame_tot->setGeometry(0, double(0.75) * central->height(), frame_tot->width(), frame_tot->height());

        //labels
        QFont font;
        font.setItalic(true);
        font.setPointSize(18);

        //titles
        sector_title_0->setAlignment(Qt::AlignCenter);
        sector_title_0->setFont(font);
        sector_title_0->setFixedSize(central->width(), central->height()/20);
        sector_title_0->setGeometry(0, 0, sector_title_0->width(), sector_title_0->height());

        sector_title_1->setAlignment(Qt::AlignCenter);
        sector_title_1->setFont(font);
        sector_title_1->setFixedSize(central->width(), central->height()/20);
        sector_title_1->setGeometry(0, central->height()/4, sector_title_1->width(), sector_title_1->height());

        sector_title_2->setAlignment(Qt::AlignCenter);
        sector_title_2->setFont(font);
        sector_title_2->setFixedSize(central->width(), central->height()/20);
        sector_title_2->setGeometry(0, central->height()/2, sector_title_2->width(), sector_title_2->height());

        sector_title_tot->setAlignment(Qt::AlignCenter);
        sector_title_tot->setFont(font);
        sector_title_tot->setFixedSize(central->width(), central->height()/20);
        sector_title_tot->setGeometry(0, double(0.75) * central->height(), sector_title_tot->width(), sector_title_tot->height());

        //values
        font.setPointSize(36);
        font.setItalic(false);
        font.setBold(true);

        sector_0->setAlignment(Qt::AlignCenter);
        sector_0->setFont(font);
        sector_0->setFixedSize(frame_0->size());
        sector_0->setGeometry(0, 0, sector_0->width(), sector_0->height());

        sector_1->setAlignment(Qt::AlignCenter);
        sector_1->setFont(font);
        sector_1->setFixedSize(frame_0->size());
        sector_1->setGeometry(0, central->height()/4, sector_1->width(), sector_1->height());

        sector_2->setAlignment(Qt::AlignCenter);
        sector_2->setFont(font);
        sector_2->setFixedSize(frame_0->size());
        sector_2->setGeometry(0, central->height()/2, sector_2->width(), sector_2->height());

        sector_tot->setAlignment(Qt::AlignCenter);
        sector_tot->setFont(font);
        sector_tot->setFixedSize(frame_0->size());
        sector_tot->setGeometry(0, double(0.75) * central->height(), sector_tot->width(), sector_tot->height());
    }

    void setValue(double sector0, double sector1, double sector2){
        sector_0->setText(QString::number(sector0));
        sector_1->setText(QString::number(sector1));
        sector_2->setText(QString::number(sector2));
        sector_tot->setText(QString::number(sector0 + sector1 + sector2));
    }
};

#endif // TIMING

