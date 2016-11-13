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
    utils/canworkerthread.cpp \
    utils/canwrapper.cpp \
    widgets/qroundprogressbar.cpp \
    windows/mainwindow.cpp \
    windows/biotab.cpp \
    windows/gpstab.cpp \
    windows/dashtab.cpp \
    windows/settingstab.cpp \
    bitalino/bitalino.cpp

HEADERS  += utils/canworkerthread.h \
    utils/canwrapper.h \
    utils/qtUtils.h \
    utils/stdUtils.h \   
    virtualcan/canbus.h \
    widgets/bio.h \
    widgets/dash.h \
    widgets/gps.h \
    widgets/qroundprogressbar.h \
    widgets/settings.h \
    windows/mainwindow.h \
    windows/biotab.h \
    windows/gpstab.h \
    windows/dashtab.h \
    windows/settingstab.h \
    bitalino/bitalino.h

DISTFILES += \
    virtualcan/startCan.sh
