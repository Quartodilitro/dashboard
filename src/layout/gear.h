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


#ifndef GEAR
#define GEAR


#include <QtWidgets>


class Gear : public QWidget{
    Q_OBJECT

public:
    QWidget *central;
    QLCDNumber *gear;

    Gear(QWidget *parent){
        central = new QWidget(parent);
        central->setFixedSize(parent->size());
        gear = new QLCDNumber(central);

        setupUI();
    }

    void setupUI(){
        gear->setDigitCount(1);

        gear->display(0);

        //gear->setFixedSize(this->size());
        gear->setGeometry(125, 125, 150, 150);
    }

    void setValue(int value){
        gear->display(value);
    }
};

#endif // GEAR
