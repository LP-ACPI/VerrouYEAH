#include <QApplication>
#include "ftp.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Q_INIT_RESOURCE(res);

    Ftp ftp;
    ftp.setWindowTitle("transfert pseudo-ftp");
    ftp.setWindowIcon(QPixmap(":/logo_temporaire.png"));

    ftp.show();

    return a.exec();
}
