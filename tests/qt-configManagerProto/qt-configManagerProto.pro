#-------------------------------------------------
#
# Project created by QtCreator 2016-12-01T21:56:35
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qt-configManagerProto
TEMPLATE = app


SOURCES += main.cpp\
        configmanager.cpp \
        Entities/user.cpp \
        Entities/backup.cpp \
        Views/homewindow.cpp \
    Views/authdialogwindow.cpp \
    Views/backupitemwidget.cpp \
    Views/backupformwindow.cpp

HEADERS  += configmanager.h \
        Entities/user.h \
        Entities/backup.h \
        Views/homewindow.h \
    Views/authdialogwindow.h \
    Views/backupitemwidget.h \
    Views/backupformwindow.h

FORMS    += Views/homewindow.ui \
        Views/firstauthdialog.ui \
    Views/backupwidget.ui \
    Views/backupform.ui
