#include "configmanager.h"
#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>

#define DATAFILE "test_config.json"

ConfigManager::ConfigManager()
{
    appUser = new User;
    loadConfig();
}

ConfigManager::~ConfigManager(){

    saveConfig();
    delete appUser;
}

bool ConfigManager::loadConfig() const {

   QFile fileToLoad(QStringLiteral(DATAFILE));

   if (!fileToLoad.open(QIODevice::ReadWrite)) {
       qWarning("impossible d'ouvrir fichier");
       return false;
   }

   QByteArray dataToLoad = fileToLoad.readAll();
   QJsonDocument loadDoc(QJsonDocument::fromJson(dataToLoad));

   QJsonObject user(loadDoc.object());

   appUser->loadUser(user["utilisateur"].toObject());

   return true;
}


bool ConfigManager::saveConfig(){
    //fichier de sauvegarde
    QFile saveFile( QStringLiteral(DATAFILE));

    if (!saveFile.open(QIODevice::WriteOnly)) {
        qWarning("écriture dans fichier échouée.");
        return false;
    }

    QJsonObject conf;//préparation du noeud

    QJsonObject jsonUser;
    appUser->saveUser(jsonUser);

    conf["utilisateur"] = jsonUser;//créer noeud 'utilisateur' avec les attributs correspondants

    QJsonDocument saveDoc(conf); //enregistrer le noeud racine

    saveFile.write(saveDoc.toJson());

    saveFile.close();

    return true;
}

void ConfigManager::resetConfig(){
    appUser = new User;
}

 User* ConfigManager::getUser(){
    return appUser;
}

void ConfigManager::setUser(User &user) {
    appUser = new User(user);
}

bool ConfigManager::noUser(){
    return !appUser->exists();
}
