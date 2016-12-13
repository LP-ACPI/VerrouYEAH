#include "Views/homewindow.h"
#include <QTranslator>
#include <QLocale>
#include <QLibraryInfo>
#include <QApplication>
#include <QDebug>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //charger les ressources (images)
    Q_INIT_RESOURCE(resources);

    //traduction des dialogues usuels (textes des bouttons surtout, en anglais par défaut)
    QString locale = QLocale::system().name().section('_',0,0);
    QTranslator tr;
    tr.load(QString("qt_")+locale, QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    a.installTranslator(&tr);

    //fenêtre principale
    HomeWindow w;
    w.show();

    return a.exec();
}
