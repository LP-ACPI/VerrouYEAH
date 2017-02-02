QMAKESPEC = QTDIR/mkspecs/win32-g++
TEMPLATE    =	app
CONFIG	+=  console c++11
CONFIG	-=  app_bundle
CONFIG	-=  qt
TARGET	=   VerrouYEAH

QT  +=	core

unix:	LIBS	+=  -lcrypto

win32:{
	 LIBS	+=  -L$$PWD/utilities/opensslWin64 -llibeay32
	 INCLUDEPATH	+=	$$PWD/utilities/opensslWin64
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
    src/services/Config.cpp \
    src/services/Crypt.cpp \
    src/main.cpp

HEADERS	+=  \
    src/models/Backup.h \
    src/models/Data.h \
    src/models/Directory.h \
    src/models/File.h \
    src/models/Frequency.h \
    src/models/Scheduler.h \
    src/models/User.h \
    src/services/Config.h \
    src/services/Crypt.h

FORMS	+=  \
    src/views/backupform.ui \
    src/views/backupwidget.ui \
    src/views/firstauthdialog.ui \
    src/views/homewindow.ui
