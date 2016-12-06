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
    Backup(QString nom = "",QString src="",QString trg="",QString com="");
    ~Backup();

    qint16 getId();
    QString getName();
    QString getSource();
    QString getTarget();
    QString getComent();


    void setId(qint16);
    void setName(QString);
    void setSource(QString);
    void setTarget(QString);
    void setComent(QString);

    void saveBackup(QJsonObject&) const;
    void loadBackup(QJsonObject&);

    void operator =(const Backup &b);
    friend bool operator ==(const Backup&,const Backup&);
    friend bool operator !=(const Backup&,const Backup&);

};

#endif // BACKUP_H
