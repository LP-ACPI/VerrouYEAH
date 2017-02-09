//
// Created by Valentin on 05/12/16.
//

#include <QApplication>
#include <QLibraryInfo>
#include <QTranslator>
#include <QLocale>
#include "views/authdialog.h"

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

    QApplication a(argc, argv);
    //traduction des dialogues usuels (textes des bouttons surtout, en anglais par défaut)
    QString locale = QLocale::system().name().section('_',0,0);
    QTranslator tr;
    tr.load(QString("qt_")+locale, QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    a.installTranslator(&tr);

    AuthDialog auth;
    auth.show();

    return a.exec();
}
