#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include <QFile>
#include <QJsonDocument>



class ConfigManager
{
private:
    QFile configFile;
    QJsonDocument jsonDoc;

public:
    ConfigManager(QString);
    bool saveConfig();
    bool loadConfig();
};

#endif // CONFIGMANAGER_H
