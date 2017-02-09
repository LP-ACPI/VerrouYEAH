QT += core
QT -= gui

CONFIG += console c++11

TARGET = VerrouYeah-UnitTests
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

LIBS += -lcrypto
# pour pouvoir utiliser json.hpp sous windows -specs win32-g++
win32-g++:{
    #pour ceux qui ont des soucis niveau minGW|QT|openSSL
    LIBS += -L$$PWD/../../utilities/openssl/lib/

    INCLUDEPATH += $$PWD/../../utilities/openssl/include
    DEPENDPATH += $$PWD/../../utilities/openssl/include

    PRE_TARGETDEPS += $$PWD/../../utilities/openssl/lib/libcrypto.a
}

INCLUDEPATH +=$$PWD/../../includes

SOURCES	+=  \
    ../models/Backup.cpp \
    ../models/Data.cpp \
    ../models/Directory.cpp \
    ../models/File.cpp \
    ../models/Frequency.cpp \
    ../models/Scheduler.cpp \
    ../models/User.cpp \
    ../services/Crypt.cpp \
    main.cpp \
    ../services/ConfigManager.cpp \
    ../controllers/UsersBackupsController.cpp \
    ../controllers/UserController.cpp

HEADERS	+=  \
    ../models/Backup.h \
    ../models/Data.h \
    ../models/Directory.h \
    ../models/File.h \
    ../models/Frequency.h \
    ../models/Scheduler.h \
    ../models/User.h \
    ../services/Crypt.h \
    persistancetest.hpp \
    usertest.hpp \
    datatest.hpp \
    ../services/ConfigManager.h \
    ../controllers/UsersBackupsController.h \
    ../controllers/UserController.h
