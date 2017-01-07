#ifndef USER_H
#define USER_H

#include "backup.h"
#include <QApplication>
#include <QJsonObject>
#include <QString>


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

    void setNom(const QString) ;
    void setMdp(const QString);
    void setBackups(const QList<Backup>);

    QString getNom() const;
    QString getMdp() const;
    QList<Backup> getBackups() const;

    void addBackup(Backup&);
    void removeBackup(const Backup&);
    void modifyBackup(Backup&);

    void saveUser(QJsonObject&) const;
    void loadUser(const QJsonObject&);

    bool exists();
    void operator=(User&) ;

//friend bool operator ==(User&, const User&);
//friend bool operator !=(User&, const User&);
};

#endif // USER_H
