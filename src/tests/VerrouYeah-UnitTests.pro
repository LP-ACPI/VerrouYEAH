QT += network core
QT -= gui

CONFIG += console c++11

TARGET = VerrouYeah-UnitTests
CONFIG -= app_bundle

TEMPLATE = app

INCLUDEPATH +=$$PWD/../../includes

win32: {
    LIBS += -L$$PWD/../../utilities/openssl/lib/ -lcrypto
    INCLUDEPATH += $$PWD/../../utilities/openssl/include
    DEPENDPATH += $$PWD/../../utilities/openssl/include

    win32:!win32-g++: PRE_TARGETDEPS += $$PWD/../../utilities/openssl/lib/crypto.lib
    else:win32-g++: PRE_TARGETDEPS += $$PWD/../../utilities/openssl/lib/libcrypto.a
}
else : LIBS += -lcrypto

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
    ../models/Scheduler.h \
    ../models/User.h \
    ../services/Crypt.h \
    ../services/ConfigManager.h \
    ../services/Ftp.h \
    ../controllers/UsersBackupController.h \
    ../controllers/UserController.h \
    ../controllers/BackupController.h \
    persistancetest.hpp \
    usertest.hpp \
    datatest.hpp \
    ftptests.hpp



