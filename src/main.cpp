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

#define PATH_SOURCE "fichier_source.txt"
#define PATH_VY "fichier_crypte.vy"
#define PATH_CIBLE "fichier_cible.txt"


using namespace std;

/*
 * Main de test temporaire
 */
int main(int argc, char* argv[])
{
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
