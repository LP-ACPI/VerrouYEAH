
QT       += network core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app

SOURCES += main.cpp \
    ftp.cpp

HEADERS += \
    ftp.h

FORMS += \
    Dialog.ui

RESOURCES += \
    res.qrc

