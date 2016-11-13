# Copyright 2016 Quartodilitro Team Unipd
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.


QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = gui
TEMPLATE = app


SOURCES += main.cpp \
    layout/mainwindow.cpp \
    layout/qroundprogressbar.cpp \
    layout/dash.cpp

HEADERS  += mainwindow.h \
    layout/mainwindow.h \
    utils/qt_utils.h \
    utils/std_utils.h \
    layout/dashboard.h \
    layout/qroundprogressbar.h \
    layout/rpm.h \
    layout/speed.h \
    layout/gear.h \
    layout/timing.h \
    layout/status.h \
    layout/dash.h
