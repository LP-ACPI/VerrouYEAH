/*
#include <QApplication>
#include <QLibraryInfo>
#include <QTranslator>
#include <QLocale>
#include "views/authdialog.h"
*/
#include "models/Scheduler.h"

#define PATH_SOURCE "fichier_source.txt"
#define PATH_VY "fichier_crypte.vy"
#define PATH_CIBLE "fichier_cible.txt"


//using namespace std;

/*
 * Main de test temporaire
 */
int main(int argc, char* argv[])
{
    std::cout << "Start scheduler" << std::endl;

    Scheduler scheduler = Scheduler::getInstance();
    Backup b = Backup("name", "src", "destPath", "destType", "lastSave", Frequency(), NULL);
    scheduler.add(b);
    scheduler.start();
    usleep(125000);
    scheduler.stop();
    std::cout << "End scheduler" << std::endl;
    /*
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
     */
}
