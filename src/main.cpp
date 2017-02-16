//
// Created by Valentin on 05/12/16.
//

#include <QApplication>
#include <QLibraryInfo>
#include <QTranslator>
#include <QLocale>
#include <QDebug>
#include "views/authdialog.h"
#include "views/mainwindow.h"
#include "controllers/UserController.h"

#define LOCAL_CONFIG_FILE "config.json"

using namespace std;

/*
 * Main de test temporaire
 */
int main(int argc, char* argv[])
{

    ConfigManager::getInstance().setJsonFile(LOCAL_CONFIG_FILE);

    Q_INIT_RESOURCE(res);

    QApplication app(argc, argv);
    //traduction des dialogues usuels (textes des bouttons surtout, en anglais par défaut)
    QString locale = QLocale::system().name().section('_',0,0);
    QTranslator tr;
    tr.load(QString("qt_")+locale, QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    app.installTranslator(&tr);

    AuthDialog *aWindow = new AuthDialog;


    if(UserController::getInstance().favoriteUserExists()){

        std::string userLogin = UserController::getInstance().getFavoriteUser();
        aWindow->proceedToMainWindow(userLogin);

   } else {
        aWindow->show();
    }
    return app.exec();
}
