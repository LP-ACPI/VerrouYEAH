#include "configmanager.h"
#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>
#include <QFileInfo>
#include <QDir>


#define MYKEY  "1234"

#define DATAFILE "test_config.json"

ConfigManager::ConfigManager()
{
    appUser = new User;
    crypt = new Crypt;
    loadConfig();
}

ConfigManager::ConfigManager(ConfigManager &confMan){
    appUser = confMan.getUser();
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

void ConfigManager::delBackup(Backup &b)
{
    appUser->removeBackup(b);
}

void ConfigManager::addBackup(Backup &b)
{
    appUser->addBackup(b);
}

void ConfigManager::majBackup(Backup &b)
{
    appUser->modifyBackup(b);
}

void ConfigManager::operator=(ConfigManager &confMan){
    appUser = confMan.getUser();
}

bool ConfigManager::cryptDirectory(const QString &source,const QString &cible){

        QFileInfo srcFileInfo(source);
        if (srcFileInfo.isDir()) {

            QDir targetDir(cible);
            targetDir.cdUp();

            if (!targetDir.mkdir(QFileInfo(cible).fileName()))
                return false;

            QDir sourceDir(source);
            QStringList fileNames = sourceDir.entryList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot | QDir::Hidden | QDir::System);

            foreach (const QString &fileName, fileNames) {
                const QString newsource  = source + QLatin1Char('/') + fileName;
                const QString newcible = cible + QLatin1Char('/') + fileName;

                if (!cryptDirectory(newsource, newcible))
                    return false;
            }
        } else {
            crypt->cryptFile(source.toStdString(), cible.toStdString(), (char*)MYKEY);
        }
        return true;
}

bool ConfigManager::decryptDirectory(const QString &source,const QString &cible){

        QFileInfo srcFileInfo(source);
        if (srcFileInfo.isDir()) {

            QDir targetDir(cible);
            targetDir.cdUp();

            if (!targetDir.mkdir(QFileInfo(cible).fileName()))
                return false;

            QDir sourceDir(source);
            QStringList fileNames = sourceDir.entryList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot | QDir::Hidden | QDir::System);

            foreach (const QString &fileName, fileNames) {
                const QString newsource  = source + QLatin1Char('/') + fileName;
                const QString newcible = cible + QLatin1Char('/') + fileName;

                if (!decryptDirectory(newsource, newcible))
                    return false;
            }
        } else {
            crypt->decryptFile(source.toStdString(), cible.toStdString(),(char*) MYKEY);
        }
        return true;
}

