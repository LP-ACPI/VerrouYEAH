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
    src/models/User.cpp \
    src/models/FtpTarget.cpp \
    src/controllers/UserController.cpp \
    src/controllers/BackupController.cpp \
    src/controllers/UsersBackupController.cpp \
    src/controllers/TargetController.cpp \
    src/services/Scheduler.cpp \
    src/services/Crypt.cpp \
    src/services/ConfigManager.cpp \
    src/services/Ftp.cpp \
    src/services/CompressCrypt.cpp \
    src/views/authdialog.cpp \
    src/views/mainwindow.cpp \
    src/views/backupform.cpp \
    src/views/userform.cpp \
    src/views/backupwidget.cpp \
    src/views/progressdialog.cpp \
    src/views/targetformdialog.cpp \
    src/views/targetchoicedialog.cpp \
    src/views/QJsonModel.cpp \
    src/main.cpp \
    src/models/absTarget.cpp \
    src/models/Target.cpp \
    src/views/backupdetailsdialog.cpp \
    src/views/filesystemmodel.cpp

HEADERS	+=  \
    src/models/Backup.h \
    src/models/Data.h \
    src/models/Directory.h \
    src/models/File.h \
    src/models/Frequency.h \
    src/models/User.h \
    src/models/FtpTarget.h \
    src/controllers/UserController.h \
    src/controllers/UsersBackupController.h \
    src/controllers/BackupController.h \
    src/controllers/TargetController.h \
    src/services/Scheduler.h \
    src/services/CompressCrypt.h \
    src/services/Crypt.h \
    src/services/ConfigManager.h \
    src/services/Ftp.h \
    src/views/authdialog.h \
    src/views/mainwindow.h \
    src/views/backupform.h \
    src/views/userform.h \
    src/views/backupwidget.h \
    src/views/progressdialog.h  \
    src/views/targetchoicedialog.h \
    src/views/targetformdialog.h \
    src/views/QJsonModel.h \
    src/models/absTarget.h \
    src/models/Target.h \
    src/views/backupdetailsdialog.h \
    src/views/filesystemmodel.h

FORMS	+=  \
    src/views/forms/backupwidget.ui \
    src/views/forms/mainwindow.ui \
    src/views/forms/authdialog.ui \
    src/views/forms/userformdialog.ui \
    src/views/forms/backupformdialog.ui \
    src/views/forms/progressdialog.ui \
    src/views/forms/targetformdialog.ui \
    src/views/forms/targetchoicedialog.ui \
    src/views/forms/frequencydialog.ui \
    src/views/forms/backupdetailsdialog.ui \
    src/views/forms/recoverbackupsdialog.ui

RESOURCES += \
    res/res.qrc

