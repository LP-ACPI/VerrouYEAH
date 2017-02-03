TEMPLATE    =	app
CONFIG	+=  console c++11
CONFIG	-=  app_bundle
CONFIG	-=  qt
TARGET	=   VerrouYEAH

QT  +=	core

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
    src/main.cpp \
    src/services/ConfigManager.cpp

HEADERS	+=  \
    src/models/Backup.h \
    src/models/Data.h \
    src/models/Directory.h \
    src/models/File.h \
    src/models/Frequency.h \
    src/models/Scheduler.h \
    src/models/User.h \
    src/services/Crypt.h \
    src/services/ConfigManager.h

FORMS	+=  \
    src/views/backupform.ui \
    src/views/backupwidget.ui \
    src/views/firstauthdialog.ui \
    src/views/homewindow.ui
