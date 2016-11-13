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


#ifndef QT_UTILS
#define QT_UTILS


#include <QDesktopWidget>
#include <QtGui>
#include <QLabel>

inline int getScreenWidth(){
    QDesktopWidget widget;
    QRect mainScreenSize = widget.availableGeometry(widget.primaryScreen());
    return mainScreenSize.width();
}

inline int getScreenHeight(){
    QDesktopWidget widget;
    QRect mainScreenSize = widget.availableGeometry(widget.primaryScreen());
    return mainScreenSize.height();
}

inline void setSize(QWidget *widget, int height, int width){
    widget->setMinimumWidth(width);  // min width = max width
    widget->setMaximumWidth(width);
    widget->setMinimumHeight(height);  // min height = max height
    widget->setMaximumHeight(height);
}

inline void setupLabel(QLabel *label, int pointSize) {
    QFont font;
    font.setPointSize(pointSize);
    label->setFont(font);
    label->setAlignment(Qt::AlignCenter);
    label->setStyleSheet("QLabel {color : white; }");
}


#endif // QT_UTILS
