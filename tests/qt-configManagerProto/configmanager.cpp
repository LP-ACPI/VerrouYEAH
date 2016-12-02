#include "configmanager.h"
#include <QDebug>
#include <QJsonObject>

ConfigManager::ConfigManager(QString confFilename)
{
    configFile.setFileName(confFilename);
}

bool ConfigManager::loadConfig(){

    QByteArray settings;
    configFile.open(QIODevice::ReadOnly | QIODevice::Text);
    settings = configFile.readAll();
    configFile.close();

    jsonDoc = QJsonDocument::fromJson(settings);

    if(jsonDoc.isNull()) return false;
    return true;
}


bool ConfigManager::saveConfig(){
    bool out;
    configFile.open(QIODevice::WriteOnly);
    if(configFile.write("{'title' : 'test'}")){

        configFile.flush();
        configFile.close();
        if(jsonDoc.isNull()) out = false;
        out = true;
    }
    else out = false;
    return out;
}
