#ifndef USER_H
#define USER_H

#include <QApplication>
#include <QJsonObject>
#include <QString>

#include "backup.h"

class User
{
private:
    QString nom;
    QString mdp;
    QList<Backup> backupList;

public:
    User(User&);
    User(QString nom="",QString mdp="");
    ~User();

    QString getNom() const;
    QString getMdp() const;
    QList<Backup> getBackups() const;

    void addBackup(const Backup&);
    void removeBackup(Backup&);
    void modifyBackup(Backup&);

    void saveUser(QJsonObject&) const;
    void loadUser(QJsonObject &);

    bool exists();
    void operator=(User&) ;

//friend bool operator ==(User&, const User&);
//friend bool operator !=(User&, const User&);
};

#endif // USER_H
