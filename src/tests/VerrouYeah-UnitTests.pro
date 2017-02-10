QT += network core
QT -= gui

CONFIG += console c++11

TARGET = VerrouYeah-UnitTests
CONFIG -= app_bundle

TEMPLATE = app

LIBS += -lcrypto

win32-g++:{

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
    ../services/ConfigManager.cpp \
    ../services/Ftp.cpp \
    ../controllers/UsersBackupsController.cpp \
    ../controllers/UserController.cpp \
    main.cpp

HEADERS	+=  \
    ../models/Backup.h \
    ../models/Data.h \
    ../models/Directory.h \
    ../models/File.h \
    ../models/Frequency.h \
    ../models/Scheduler.h \
    ../models/User.h \
    ../services/Crypt.h \
    ../services/ConfigManager.h \
    ../services/Ftp.h \
    ../controllers/UsersBackupsController.h \
    ../controllers/UserController.h \
    persistancetest.hpp \
    usertest.hpp \
    datatest.hpp \
    ftptests.hpp
