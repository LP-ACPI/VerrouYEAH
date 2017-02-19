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
    ../services/Crypt.cpp \
    ../services/ConfigManager.cpp \
    ../services/Ftp.cpp \
    ../services/Scheduler.cpp \
    ../services/CompressCrypt.cpp \
    ../controllers/UsersBackupController.cpp \
    ../controllers/UserController.cpp \
    ../controllers/BackupController.cpp \
    main.cpp

HEADERS	+=  \
    ../models/Backup.h \
    ../models/Data.h \
    ../models/Directory.h \
    ../models/File.h \
    ../models/Frequency.h \
    ../models/User.h \
    ../services/Crypt.h \
    ../services/Scheduler.h \
    ../services/ConfigManager.h \
    ../services/Ftp.h \
    ../services/CompressCrypt.h \
    ../controllers/UsersBackupController.h \
    ../controllers/UserController.h \
    ../controllers/BackupController.h \
    persistancetest.hpp \
    usertest.hpp \
    datatest.hpp \
    ftptests.hpp



