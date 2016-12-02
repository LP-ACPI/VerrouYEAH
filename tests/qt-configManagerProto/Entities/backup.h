#ifndef BACKUP_H
#define BACKUP_H

#include <QApplication>

class Backup
{

private:

    static qint16 cnt;
    qint16  id;
    QString name;
    QString sourceDir;
    QString targetDir;
    QString comment;

public:
    Backup(QString,QString,QString,QString);
    ~Backup();

    qint16 getId();
    QString getName();
    QString getSource();
    QString getTarget();
    QString getComent();

};

#endif // BACKUP_H
