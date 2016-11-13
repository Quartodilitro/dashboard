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


#include <QtGui>

int getScreenWidth(){
    QDesktopWidget widget;
    QRect mainScreenSize = widget.availableGeometry(widget.primaryScreen());
    return mainScreenSize.width();
}

int getScreenHeight(){
    QDesktopWidget widget;
    QRect mainScreenSize = widget.availableGeometry(widget.primaryScreen());
    return mainScreenSize.height();
}

void setSize(QWidget *widget, int height, int width){
    //min width = max width
    widget->setMinimumWidth(width);
    widget->setMaximumWidth(width);

    //min height = max height
    widget->setMinimumHeight(height);
    widget->setMaximumHeight(height);
}

#endif // QT_UTILS
