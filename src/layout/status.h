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


#ifndef STATUS
#define STATUS


#include <QtWidgets>


class Status : public QWidget{
    Q_OBJECT

public:
    QWidget *central;

    QLabel *fuel_label;
    QLabel *temp_label;


    Status(QWidget *parent){
        //layout
        central = new QWidget(parent);
        central->setFixedSize(200, 480);

        fuel_label = new QLabel(central);
        temp_label = new QLabel(central);

        setupUI();
    }

    void setupUI(){
        fuel_label->setAlignment(Qt::AlignCenter);
        fuel_label->setFixedSize(central->width(), central->height()/4);
        fuel_label->setGeometry(0, central->height()/2, fuel_label->width(), fuel_label->height());

        temp_label->setAlignment(Qt::AlignCenter);
        temp_label->setFixedSize(central->width(), central->height()/4);
        temp_label->setGeometry(0, double(0.75) * central->height(), temp_label->width(), temp_label->height());

        //images
        QPixmap fuel_image("../res/fuel.png");
        QPixmap temp_image("../res/temp.png");

        fuel_image = fuel_image.scaled(fuel_label->size(), Qt::KeepAspectRatio);
        temp_image = temp_image.scaled(temp_label->size(), Qt::KeepAspectRatio);

        //fuel_label->setPixmap(fuel_image);
        temp_label->setPixmap(temp_image);
    }

    void setValue(double fuel, double temperature){
        return;
    }

};

#endif // STATUS

