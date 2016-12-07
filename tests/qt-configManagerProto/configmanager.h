#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include <Entities/user.h>
#include <Services/Crypt.h>



class ConfigManager
{
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

    void operator=(ConfigManager&);
};

#endif // CONFIGMANAGER_H
