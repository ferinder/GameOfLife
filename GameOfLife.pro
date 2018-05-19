#-------------------------------------------------
#
# Project created by QtCreator 2018-04-24T09:09:31
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GameOfLife
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

SOURCES += \
        src\main.cpp \
        src\mainwindow.cpp\
        src\cell.cpp\
        src\gameboard.cpp\
        src\game.cpp\
        src\newboarddialog.cpp \
        src\getruledialog.cpp \
        src\rulesdialog.cpp
        src\propertiesdialog.cpp

HEADERS += \
        src\mainwindow.h\
        src\cell.h\
        src\gameboard.h\
        src\game.h\
        src\newboarddialog.h \
        src\getruledialog.h \
        src\rulesdialog.h
        src\propertiesdialog.h

FORMS += \
        src\mainwindow.ui\
        src\newboarddialog.ui \
        src\getruledialog.ui \
        src\rulesdialog.ui
        src\propertiesdialog.ui


RESOURCES += \
        icons.qrc
