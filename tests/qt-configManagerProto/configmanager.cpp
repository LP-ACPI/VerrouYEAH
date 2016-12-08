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
    return cryptDirWithCount(source,cible,CountFiles(source)) > 0;
}

quint64 ConfigManager::cryptDirWithCount(const QString &source,const QString &cible, const quint64 total, quint64 crypted){

        QFileInfo srcFileInfo(source);
        if (srcFileInfo.isDir()) {

            QDir targetDir(cible);
            targetDir.cdUp();

            if (!targetDir.mkdir(QFileInfo(cible).fileName()))
                return 0;

            QDir sourceDir(source);
            QStringList fileNames = sourceDir.entryList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot | QDir::Hidden | QDir::System);

            foreach (const QString &fileName, fileNames) {
                const QString subSource  = source + QLatin1Char('/') + fileName;
                const QString subCible = cible + QLatin1Char('/') + fileName;
//NEIN!! - compteur RAZ au passage à  autre dossier

                   crypted =  cryptDirWithCount(subSource, subCible,total,crypted);
            }
        } else {
            crypt->cryptFile(source.toStdString(), cible.toStdString(), (char*)MYKEY);
            crypted++;
        }
        emit cryptInProgress(crypted,total);
        return crypted;
}

bool ConfigManager::decryptDirectory(const QString &source,const QString &cible){
    return decryptDirWithCount(source,cible, CountFiles(source)) > 0;
}

quint64 ConfigManager::decryptDirWithCount(const QString &source,const QString &cible, const quint64 total,quint64 decrypted){

        QFileInfo srcFileInfo(source);
        if (srcFileInfo.isDir()) {

            QDir targetDir(cible);
            targetDir.cdUp();

            if (!targetDir.mkdir(QFileInfo(cible).fileName()))
                return 0;

            QDir sourceDir(source);
            QStringList fileNames = sourceDir.entryList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot | QDir::Hidden | QDir::System);

            foreach (const QString &fileName, fileNames) {
                const QString subSource  = source + QLatin1Char('/') + fileName;
                const QString subCible = cible + QLatin1Char('/') + fileName;
                decrypted = decryptDirWithCount(subSource, subCible,total,decrypted);
            }
        } else {
            crypt->decryptFile(source.toStdString(), cible.toStdString(),(char*) MYKEY);
            emit cryptInProgress( decrypted,total);
        }
        return decrypted;
}

int ConfigManager::CountFiles(const QString &source, int ctn){
    QFileInfo srcInfo(source);
    if (srcInfo.isDir()) {
        QDir srcDir(source);

        QStringList elements = srcDir.entryList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot | QDir::Hidden | QDir::System);

        foreach (const QString &el, elements) {
            const QString subEl  = source + QLatin1Char('/') + el;
            QFileInfo srcInfo(subEl);
             if (srcInfo.isDir())
                 ctn+=CountFiles(subEl);
             else
                 ctn++;
        }
    }
    return ctn;


}


