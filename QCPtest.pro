#-------------------------------------------------
#
# Project created by QtCreator 2020-07-02T10:05:00
#
#-------------------------------------------------

QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = QCPtest
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


INCLUDEPATH += /home/slava/newclickhouse/clickhouse-cpp
INCLUDEPATH += /home/slava/paho.mqtt.cpp/src

LIBS += -L/home/slava/newclickhouse/build/clickhouse -lclickhouse-cpp-lib-static
LIBS += -L/home/slava/newclickhouse/build/contrib/lz4 -llz4-lib
LIBS += -L/home/slava/newclickhouse/build/contrib/cityhash -lcityhash-lib


SOURCES += \
        main.cpp \
        mainwindow.cpp \
            qcustomplot.cpp \
    fvnpclass.cpp \
    mqttclass.cpp

HEADERS += \
        mainwindow.h \
    qcustomplot.h \
    fvnpclass.h \
    mqttclass.h

FORMS += \
        mainwindow.ui
