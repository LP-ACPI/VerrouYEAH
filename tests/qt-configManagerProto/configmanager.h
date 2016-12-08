#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include <Entities/user.h>
#include <Services/Crypt.h>



class ConfigManager : public QObject
{
    Q_OBJECT
private:
    User *appUser;
    Crypt *crypt;

public:
    ConfigManager();
    ConfigManager(ConfigManager&);
    ~ConfigManager();

    User* getUser();
    void setUser(User&) ;
    bool noUser();

    void delBackup(Backup&);
    void addBackup(Backup&);
    void majBackup(Backup&);

    bool saveConfig() ;
    bool loadConfig() const;
    void resetConfig();

    bool cryptDirectory(const QString&,const QString&);
    bool decryptDirectory(const QString&, const QString&);
    quint64 cryptDirWithCount(const QString&,const QString&,const quint64,quint64 crypted = 0);
    quint64 decryptDirWithCount(const QString&, const QString&,const quint64,quint64 decrypted = 0);
    int CountFiles(const QString &, int ctn = 0);

    void operator=(ConfigManager&);

signals:
    void cryptInProgress(quint64,quint64);
    void cryptError(QString);

};

#endif // CONFIGMANAGER_H
