#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include "Entities/user.h"
#include "Services/Crypt.h"

class ConfigManager : public QObject
{
    Q_OBJECT
private:
    User *appUser; // gestion d'un seul uilisateur
    Crypt *crypt;

public:
    explicit ConfigManager();
    explicit ConfigManager(ConfigManager&);
    ~ConfigManager();

    User* getUser();
    void setUser(User&) ;
    bool noUser();

    void delBackup(Backup&);
    void addBackup(Backup&);
    void majBackup(Backup&);

    bool saveConfig() const ;
    bool loadConfig() const;
    void resetConfig();

    bool cryptDirectory(const QString&,const QString&);
    bool decryptDirectory(const QString&, const QString&);
    int cryptDirWithCount(const QString&,const QString&,const quint64,quint64 crypted = 0);
    int decryptDirWithCount(const QString&, const QString&,const quint64,quint64 decrypted = 0);

    quint64 CountFiles(const QString &, quint64 ctn = 0);

    void operator=(ConfigManager&);

signals:
    // utilisé dans de/cryptDirWithCount: évolution du nombre de fichiers dé/cryptés
    //params (nombre de fichiers dé/crytptés, total de fihiers à dé/crypter)
    void cryptInProgress(quint64,quint64);
    void cryptError(QString);

};

#endif // CONFIGMANAGER_H
