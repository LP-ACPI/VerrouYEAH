#ifndef USER_H
#define USER_H

#include <QApplication>
#include "backup.h"

class User
{
private:
    QString nom;
    QString mdp;
    QList<Backup> backup_list;

public:
    User(QString,QString);
    ~User();
};

#endif // USER_H
