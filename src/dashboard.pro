#-------------------------------------------------
#
# Project created by QtCreator 2016-09-01T16:36:33
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += printsupport

TARGET = dashboard
TEMPLATE = app


SOURCES += \
    main.cpp \  # application
    core/settings.cpp \
    core/mainwindow.cpp \
    core/connectionbridge.cpp \
    core/dashwindow.cpp \  # children windows
    core/biowindow.cpp \
    gui/chart.cpp \  # widgets
    gui/indicatorlabel.cpp \
    gui/qcustomplot.cpp \
    gui/qroundprogressbar.cpp \
    can/canworkerthread.cpp \  # can-bus
    can/canwrapper.cpp \
    bitalino/bitalino.cpp \  # bitalino
    core/geotimewindow.cpp \
    core/settingswindow.cpp


HEADERS  += \
    core/connectionbridge.h \  # application
    core/settings.h \
    core/mainwindow.h \  # children windows
    core/biowindow.h \
    core/dashwindow.h \
    gui/chart.h \  # widgets
    gui/indicatorlabel.h \
    gui/qcustomplot.h \
    gui/qroundprogressbar.h \
    can/canworkerthread.h \  # can-bus
    can/canwrapper.h \
    can/canbus.h \
    bitalino/bitalino.h \  # bitalino
    core/geotimewindow.h \
    core/settingswindow.h


FORMS    += \
    core/biowindow.ui \  # children windows
    core/dashwindow.ui \
    gui/chart.ui \  # widgets
    gui/indicatorlabel.ui \
    core/geotimewindow.ui \
    core/settingswindow.ui


RESOURCES += \
    resources.qrc  # embedded in application executable


DISTFILES += \
    can/startVirtualCan.sh  # DEBUG (virtual can starter)
