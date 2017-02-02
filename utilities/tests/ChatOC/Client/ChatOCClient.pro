#-------------------------------------------------
#
# Project created by QtCreator 2016-11-18T00:31:44
#
#-------------------------------------------------

TEMPLATE  = app
QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4):
    QT  += widgets

TARGET   = ChatOCClient
TEMPLATE = app

HEADERS += FenClient.h

SOURCES += main.cpp \
    FenClient.cpp

FORMS   += FenClient.ui


