#-------------------------------------------------
#
# Project created by QtCreator 2016-12-01T21:56:35
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qt-configManagerProto
TEMPLATE = app


INCLUDEPATH += $$PWD/opensslWin64

SOURCES += main.cpp\
        configmanager.cpp \
        Entities/user.cpp \
        Entities/backup.cpp \
        Views/homewindow.cpp \
    Views/authdialogwindow.cpp \
    Views/backupitemwidget.cpp \
    Views/backupformwindow.cpp \
    Services/Crypt.cpp \

HEADERS  += configmanager.h \
        Entities/user.h \
        Entities/backup.h \
        Views/homewindow.h \
    Views/authdialogwindow.h \
    Views/backupitemwidget.h \
    Views/backupformwindow.h \
    Services/Crypt.h \
    Views/authdialogWindow.h

FORMS    += Views/homewindow.ui \
        Views/firstauthdialog.ui \
    Views/backupwidget.ui \
    Views/backupform.ui



unix: LIBS += -lcrypto


win32: LIBS += -L$$PWD/opensslWin64/ -llibeay32

INCLUDEPATH += $$PWD/opensslWin64
DEPENDPATH += $$PWD/opensslWin64
