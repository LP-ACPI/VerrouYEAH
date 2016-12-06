#include "Views/homewindow.h"
#include <QTranslator>
#include <QLocale>
#include <QLibraryInfo>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString locale = QLocale::system().name().section('_',0,0);
    QTranslator tr;
    tr.load(QString("qt_")+locale, QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    a.installTranslator(&tr);

    HomeWindow w;
    w.show();

    return a.exec();
}
