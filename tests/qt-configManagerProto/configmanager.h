#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include <QFile>
#include <QJsonObject>
#include <Entities/user.h>



class ConfigManager
{
private:
    User *appUser;

public:
    ConfigManager();
    ~ConfigManager();

    User* getUser();
    void setUser(User&) ;
    bool noUser();

    bool saveConfig() ;
    bool loadConfig() const;
    void resetConfig();

};

#endif // CONFIGMANAGER_H
