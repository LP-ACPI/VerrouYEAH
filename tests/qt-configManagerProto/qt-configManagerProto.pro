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
    Views/addbackupwindow.cpp

HEADERS  += configmanager.h \
        Views/homewindow.h \
        Entities/user.h \
        Entities/backup.h \
    Views/addbackupwindow.h

FORMS    += Views/homewindow.ui \
        Views/firstauthdialog.ui \
    Views/addnewbackup.ui \
    Views/backupwidget.ui
