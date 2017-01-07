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
    // TODO fréquence

public:
    Backup(QString nom = "",QString src="",QString trg="",QString com="");
    ~Backup();

    qint16 getId() const;
    QString getName() const;
    QString getSource() const;
    QString getTarget() const;
    QString getComent() const;

    void setId(const qint16);
    void setName(const QString);
    void setSource(const QString);
    void setTarget(const QString);
    void setComent(const QString);

    void saveBackup(QJsonObject&) const;
    void loadBackup(const QJsonObject&);

    void operator =(const Backup &b);
    friend bool operator ==(const Backup&,const Backup&);
    friend bool operator !=(const Backup&,const Backup&);
    friend std::ostream& operator <<(std::ostream&, const Backup&);

};

#endif // BACKUP_H
