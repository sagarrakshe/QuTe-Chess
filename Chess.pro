

QT       += core gui

TARGET = Chess
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    tile.cpp \
    validation.cpp

HEADERS  += mainwindow.h \
    tile.h \
    validation.h

FORMS    += mainwindow.ui

RESOURCES += \
    Images.qrc
