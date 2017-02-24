QT += network core
QT -= gui

CONFIG += console c++11

TARGET = VerrouYeah-UnitTests
CONFIG -= app_bundle

TEMPLATE = app

INCLUDEPATH +=$$PWD/../../includes

LIBS += -lcrypto

SOURCES	+=  \
    ../models/Backup.cpp \
    ../models/Data.cpp \
    ../models/Directory.cpp \
    ../models/File.cpp \
    ../models/Frequency.cpp \
    ../models/User.cpp \
    ../models/FtpTarget.cpp \
    ../services/Scheduler.cpp \
    ../services/Crypt.cpp \
    ../services/ConfigManager.cpp \
    ../services/Ftp.cpp \
    ../services/CompressCrypt.cpp \
    ../models/absTarget.cpp \
    ../models/Target.cpp \
            main.cpp


HEADERS	+=  \
    ../models/Backup.h \
    ../models/Data.h \
    ../models/Directory.h \
    ../models/File.h \
    ../models/Frequency.h \
    ../models/User.h \
    ../models/FtpTarget.h \
    ../services/Scheduler.h \
    ../services/CompressCrypt.h \
    ../services/Crypt.h \
    ../services/ConfigManager.h \
    ../services/Ftp.h \
    ../services/Observer.h \
    usertest.hpp \
    persistanceTest.hpp \
    datatest.hpp \
    ftptests.hpp



