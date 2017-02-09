
QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE    =	app
CONFIG	+=  c++11
CONFIG	-=  app_bundle
TARGET	=   VerrouYEAH

unix :LIBS	+=  -lcrypto

# pour pouvoir utiliser json.hpp sous windows -specs win32-g++
win32-g++:{
    #pour ceux qui ont des soucis comme moi niveau minGW|QT|openSSL
    LIBS += -L$$PWD/utilities/openssl/lib/ -lcrypto

    INCLUDEPATH += $$PWD/utilities/openssl/include
    DEPENDPATH += $$PWD/utilities/openssl/include

    PRE_TARGETDEPS += $$PWD/utilities/openssl/lib/libcrypto.a
}


INCLUDEPATH +=	$$PWD/includes

SOURCES	+=  \
    src/models/Backup.cpp \
    src/models/Data.cpp \
    src/models/Directory.cpp \
    src/models/File.cpp \
    src/models/Frequency.cpp \
    src/models/Scheduler.cpp \
    src/models/User.cpp \
    src/services/Crypt.cpp \
    src/services/ConfigManager.cpp \
    src/controllers/UserController.cpp \
    src/controllers/UsersBackupsController.cpp \
    src/views/authdialog.cpp \
    src/views/mainwindow.cpp \
    src/views/formsauvegarde.cpp \
    src/main.cpp

HEADERS	+=  \
    src/models/Backup.h \
    src/models/Data.h \
    src/models/Directory.h \
    src/models/File.h \
    src/models/Frequency.h \
    src/models/Scheduler.h \
    src/models/User.h \
    src/services/Crypt.h \
    src/services/ConfigManager.h \
    src/controllers/UserController.h \
    src/controllers/UsersBackupsController.h \
    src/views/authdialog.h \
    src/views/mainwindow.h \
    src/views/formsauvegarde.h

FORMS	+=  \
    src/views/forms/backupform.ui \
    src/views/forms/backupwidget.ui \
    src/views/forms/formsauvegarde.ui \
    src/views/forms/mainwindow.ui \
    src/views/forms/authdialog.ui

RESOURCES += \
    res/res.qrc
