#include "configmanager.h"
#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>
#include <QFileInfo>
#include <QDir>


#define MYKEY  "1234"

//fichier de sauvegarde à la racine de l'appli
#define DATAFILE "test_config.json"

ConfigManager::ConfigManager(){
    appUser = new User;
    crypt = new Crypt;
    loadConfig();
}

ConfigManager::ConfigManager(ConfigManager &confMan):
    appUser(confMan.getUser())
{}

ConfigManager::~ConfigManager(){
    saveConfig();
    delete appUser;
}

/**
 * chargement de données persistées en Json
 *
 * @brief ConfigManager::loadConfig
 * @return true si lecture du Json réussie
 */
bool ConfigManager::loadConfig() const {
    //fichier de sauvegarde à lire
   QFile fileToLoad(QStringLiteral(DATAFILE));

   if (!fileToLoad.open(QIODevice::ReadWrite)) {
       qWarning("impossible d'ouvrir fichier");
       return false;
   }

   QByteArray dataToLoad = fileToLoad.readAll();//lecture du fichier vers octets
   QJsonDocument loadDoc(QJsonDocument::fromJson(dataToLoad)); //faut être sûr qu'il s'agit d'un Json!

   QJsonObject user(loadDoc.object());//interprétation du doc Json en objet

   appUser->loadUser(user["utilisateur"].toObject()); //cf classe User

   fileToLoad.close();

   return true;
}

/**
 * appelé un peu partout (nouvel utilisateur, ajout(fin de cryptage)/modif/suppression de sauvegarde, à la descrution d'un ConfigManager)
 * + sans vérif si fichier bien lu !
 * -> TODO nettoyer & à éviter à partir d'un gros nombre de données à sauvegarder
 *
 * @brief ConfigManager::saveConfig
 * @return true si sauvegarde réalisée
 */
bool ConfigManager::saveConfig() const{
    //fichier de sauvegarde où écrire
    QFile saveFile( QStringLiteral(DATAFILE));

    if (!saveFile.open(QIODevice::WriteOnly)) {
        qWarning("écriture dans fichier échouée.");
        return false;
    }

    QJsonObject conf;//préparation du noeud principal

    QJsonObject jsonUser;
    appUser->saveUser(jsonUser);//cf classe User

    conf["utilisateur"] = jsonUser;//créer noeud 'utilisateur' avec ses attributs

    QJsonDocument saveDoc(conf); //enregistrer le noeud racine

    saveFile.write(saveDoc.toJson());//écriture dans fichier

    saveFile.close();

    return true;
}

/**
 * supprime toutes les données de l'appli
 * @brief ConfigManager::resetConfig
 */
void ConfigManager::resetConfig(){
    foreach (Backup bc,appUser->getBackups()) {
        delBackup(bc);
    }
    appUser = new User;
}

/**
  * @brief ConfigManager::getUser
  * @return User: utilisateur de l'appli
  */
 User* ConfigManager::getUser(){
    return appUser;
}

 /**
 * @brief ConfigManager::setUser
 * @param user
 */
void ConfigManager::setUser(User &user) {
    appUser = new User(user);
}

/**
 * @brief ConfigManager::noUser
 * @return true si pas d'utilisateur d'application (au dmarrage)
 */
bool ConfigManager::noUser(){
    return !appUser->exists();
}

/**
 * @brief ConfigManager::delBackup
 * @param une sauvegarde backup à supprimer
 */
void ConfigManager::delBackup(Backup &b){
    appUser->removeBackup(b);
}

/**
 * @brief ConfigManager::addBackup
 * @param une sauvegarde backup à ajouter
 */
void ConfigManager::addBackup(Backup &b){
    appUser->addBackup(b);
}

/**
 * @brief ConfigManager::majBackup
 * @param  une sauvegarde backup à modifier
 */
void ConfigManager::majBackup(Backup &b){
    appUser->modifyBackup(b);
}

void ConfigManager::operator=(ConfigManager &confMan){
    appUser = confMan.getUser();
}

/**
 * La lib std de c++ n'a pas l'air d'implémenter le concept de dossiers (concept reconnu avec ajout de librairies telle que Boost)
 * --> utilisation de QDir de Qt
 *
 *  @brief ConfigManager::cryptDirectory
 * @param source: dossier à crypter
 * @param cible : dossier où crypter. Choix <nom_sauvegarde>.vy
 * @return True si cryptage résussi
 */
bool ConfigManager::cryptDirectory(const QString &source,const QString &cible){
    return cryptDirWithCount(source,cible,CountFiles(source)) >= 0;
}

/**
 * @brief ConfigManager::cryptDirWithCount
 * @param source: fichier source à crypter
 * @param cible : fichier cible crypté
 * @param total: nombre total de fichiers à crypter
 * @param crypted : compte courrant de fichiers cryptés
 * @return nombre de fichiers en cours de cryptage
 *
 * avec émission du signal de l'évolution crypted/total de fichiers cryptés
 *
 */
int ConfigManager::cryptDirWithCount(const QString &source,const QString &cible, const quint64 total, quint64 crypted){

        QFileInfo srcFileInfo(source);
        if (srcFileInfo.isDir()) {

            QDir targetDir(cible);
            targetDir.cdUp();

            if (!targetDir.mkdir(QFileInfo(cible).fileName()))
                return -1;

            QDir sourceDir(source);
            QStringList fileNames = sourceDir.entryList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot | QDir::Hidden | QDir::System);

            foreach (const QString &fileName, fileNames) {
                const QString subSource  = source + QLatin1Char('/') + fileName;
                const QString subCible = cible + QLatin1Char('/') + fileName;
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
    return decryptDirWithCount(source,cible, CountFiles(source)) >= 0;
}

/**
 *
 * @brief ConfigManager::decryptDirWithCount
 * @param source
 * @param cible
 * @param total
 * @param decrypted
 * @return
 */
int ConfigManager::decryptDirWithCount(const QString &source,const QString &cible, const quint64 total,quint64 decrypted){

        QFileInfo srcFileInfo(source);
        if (srcFileInfo.isDir()) {

            QDir targetDir(cible);
            targetDir.cdUp();

            if (!targetDir.mkdir(QFileInfo(cible).fileName()))
                return -1;

            QDir sourceDir(source);
            QStringList fileNames = sourceDir.entryList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot | QDir::Hidden | QDir::System);

            foreach (const QString &fileName, fileNames) {
                const QString subSource  = source + QLatin1Char('/') + fileName;
                const QString subCible = cible + QLatin1Char('/') + fileName;
                decrypted = decryptDirWithCount(subSource, subCible,total,decrypted);
            }
        } else {
            crypt->decryptFile(source.toStdString(), cible.toStdString(),(char*) MYKEY);
            decrypted++;
        }
        emit cryptInProgress(decrypted,total);
        return decrypted;
}

/**
 * @brief ConfigManager::CountFiles
 * @param source: dossier source
 * @param ctn : compte courrant de fichiers
 * @return compte final de fichiers (uniquement, pas des dossiers. Y a une méthode QDir::count mais qui compte le nombre total d'éléments dans un dossier)
 */
quint64 ConfigManager::CountFiles(const QString &source, quint64 ctn){
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


