
QT += network core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE    =	app
CONFIG	+=  c++11
CONFIG	-=  app_bundle
TARGET	=   VerrouYEAH

LIBS	+=  -lcrypto

INCLUDEPATH +=$$PWD/includes/

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
    src/services/Ftp.cpp \
    src/controllers/UserController.cpp \
    src/views/authdialog.cpp \
    src/views/mainwindow.cpp \
    src/main.cpp \
    src/views/backupform.cpp \
    src/views/userform.cpp \
    src/views/backupwidget.cpp \
    src/controllers/BackupController.cpp \
    src/controllers/UsersBackupController.cpp \
    src/services/CompressCrypt.cpp \
    src/views/progressdialog.cpp \
    src/views/detailssauvegarde.cpp \
    src/models/qjsonmodel.cpp


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
    src/services/Ftp.h \
    src/controllers/UserController.h \
    src/views/authdialog.h \
    src/views/mainwindow.h \
    src/views/backupform.h \
    src/views/userform.h \
    src/views/backupwidget.h \
    src/controllers/UsersBackupController.h \
    src/controllers/BackupController.h \
    src/services/CompressCrypt.h \
    src/views/progressdialog.h  \
    src/views/detailssauvegarde.h \
    src/models/qjsonmodel.h

FORMS	+=  \
    src/views/forms/backupwidget.ui \
    src/views/forms/mainwindow.ui \
    src/views/forms/authdialog.ui \
    src/views/forms/userformdialog.ui \
    src/views/forms/backupformdialog.ui \
    src/views/forms/progressdialog.ui \
    src/views/forms/detailssauvegarde.ui \
    src/views/forms/frequencydialog.ui

RESOURCES += \
    res/res.qrc

