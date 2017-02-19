//
// Created by Valentin on 05/12/16.
//
#include "Backup.h"
#include "../services/CompressCrypt.h"
#include "../services/ConfigManager.h"
#include "../services/Ftp.h"
#include <QDebug>
#include <QEventLoop>

using namespace std;
using json = nlohmann::json;

Backup::Backup(const Backup &backupToCopy)
     : name(backupToCopy.getName()),
        lastSave(backupToCopy.getLastSave()),
        source(backupToCopy.getSource()),
        target(backupToCopy.getTarget()),
        frequency(backupToCopy.getFrequency()),
        data(backupToCopy.getData()),
        note(backupToCopy.getNote()),
        dataIsLoaded(backupToCopy.hasLoadedData())
{
    setKey(backupToCopy.getKey().c_str());
    setOwnersLogin(backupToCopy.getOwnersLogin());
    setOwnersPass( backupToCopy.getOwnersPass() );
}

bool Backup::saveData(){
    //TODO sauvegarde des données (data) vers des fichiers .vy

    QFileInfo info(QString::fromStdString(getSource()));
    Data* root_dir = new Directory(info);
    setData(root_dir);
    setDataLoaded(true);

    //TODO :FTP

    if(target->getType() == "NORMAL"){
        return saveNormalData();
    }else{
        return saveFtpData();
    }

}

void Backup::recoverData(){
    //Decrypt cible vers source

    //TODO chargement des données (data) depuis les fichiers .vy
    // -> form de choix de destinations preferes à scanner pour éventuelle sauvegarde
    // TODO : FTP
    //
    if(target->getType() == "NORMAL"){
        restoreNormalData();
    } else {
        restoreFtpData();
    }
}

bool Backup::saveNormalData(){
    bool saveOk = true;
    saveOk += compressCryptFromTo(source,target->getPath() +"/"+ name);

    std::string distant_config = target->getPath()
            + QDir::separator().toLatin1()
            + getOwnersLogin()+".config";

    saveOk += saveJsonDataTo(distant_config);
    return saveOk;
}

void Backup::restoreNormalData(){
    decryptDecompressFromTo(target->getPath()+"/"+ name,"decrypt/"+name);
}

bool Backup::saveFtpData(){
    string temp_dest_crypt = "tmp/"+name;
    string temp_dest_data  = "tmp/"+getOwnersLogin()+".config";
    compressCryptFromTo(source, temp_dest_crypt);
    saveJsonDataTo(temp_dest_data);

    FtpTarget *ftpTarget = (FtpTarget *)target;
    string host = ftpTarget->getHost();
    string username = ftpTarget->getUserName();
    string pass = ftpTarget->getFtpPass();
    int port = stoi(ftpTarget->getPort());

    QEventLoop loopUp;
    QObject::connect(&Ftp::getInstance(), SIGNAL(finished()), &loopUp, SLOT(quit()));
    Ftp::getInstance().prepareFtp(host,username,pass,port);
    Ftp::getInstance().ftpUpload(temp_dest_crypt+".vy",ftpTarget->getPath());
    loopUp.exec();
    Ftp::getInstance().ftpUpload(temp_dest_data,ftpTarget->getPath());
    loopUp.exec();

    QDir dir("tmp");
    dir.removeRecursively();
}

void Backup::restoreFtpData(){

    FtpTarget *ftpTarget = (FtpTarget *)target;
    string host = ftpTarget->getHost();
    string username = ftpTarget->getUserName();
    string pass = ftpTarget->getFtpPass();
    int port = stoi(ftpTarget->getPort());

    QEventLoop loopUp;
    QObject::connect(&Ftp::getInstance(), SIGNAL(finished()), &loopUp, SLOT(quit()));
    Ftp::getInstance().prepareFtp(host,username,pass,port);
    Ftp::getInstance().ftpDownload(target->getPath()+"/"+name+".vy","tmp");
    loopUp.exec();

    decryptDecompressFromTo("tmp/"+name,"decrypt/"+name);

    QDir dir("tmp");
    dir.removeRecursively();
}

bool Backup::loadJsonData(){
    if(target->getType() == "FTP")
        return loadFtpJson();
    else
        return loadNormalJson();
}

bool Backup::loadFtpJson() {

    string json_data = getOwnersLogin()+".config";

    FtpTarget *ftpTarget = (FtpTarget *)target;
    string host = ftpTarget->getHost();
    string username = ftpTarget->getUserName();
    string pass = ftpTarget->getFtpPass();
    int port = stoi(ftpTarget->getPort());
    QEventLoop loopUp;
    QObject::connect(&Ftp::getInstance(), SIGNAL(finished()), &loopUp, SLOT(quit()));
    Ftp::getInstance().prepareFtp(host,username,pass,port);
    Ftp::getInstance().ftpDownload(target->getPath()+"/"+json_data, "tmp");
    loopUp.exec();

    bool loadOk = loadJsonDataFrom( "tmp/"+json_data);

    QDir dir("tmp");
    dir.removeRecursively();

    return loadOk;
}

bool Backup::loadNormalJson() {
    std::string config_file = getTarget()->getPath()
            + QDir::separator().toLatin1()
            + getOwnersLogin()
            + ".config";

    return loadJsonDataFrom(config_file);
}

bool Backup::compressCryptFromTo(std::string source_dir,std::string dest_file){
    bool compCryptOk = true;
    QString crypt_from = QString::fromStdString(source_dir);
    QString crypt_to = QString::fromStdString(dest_file);

    compCryptOk &= CompressCrypt::getInstance().cryptDir(crypt_from ,crypt_to+"_temp",key);
    compCryptOk &= CompressCrypt::getInstance().compressDir(crypt_to+"_temp",crypt_to+".vy");

    QDir dir(crypt_to+"_temp");
    dir.removeRecursively();

    return compCryptOk;
}

bool Backup::decryptDecompressFromTo(std::string source_file,std::string dest_dir){
    bool decompCryptOk = true;

    QString decrypt_from = QString::fromStdString(source_file);
    QString decrypt_to = QString::fromStdString(dest_dir);

    decompCryptOk &= CompressCrypt::getInstance().decompressDir(decrypt_from+".vy",decrypt_from+"_temp");
    decompCryptOk &= CompressCrypt::getInstance().decryptDir(decrypt_from+"_temp",decrypt_to,key);

    QDir dir(decrypt_from+"_temp");
    dir.removeRecursively();

    return decompCryptOk;
}

bool Backup::saveJsonDataTo(string configFile){
    ConfigManager::getInstance().setJsonFile(configFile);
    ConfigManager::getInstance().deleteUsersBackupData(getOwnersLogin(),key );
    auto  res = ConfigManager::getInstance().saveUsersBackupData(this);
    ConfigManager::getInstance().setJsonFile(LOCAL_CONFIG_FILE);
    return res != NULL;
}

bool Backup::loadJsonDataFrom(std::string configFile){
    QFile file(QString::fromStdString(configFile));
    if(file.exists()){
        ConfigManager::getInstance().setJsonFile(configFile);
        Backup *distant_partial_backup =  ConfigManager::getInstance().getUserBackupsData(getOwnersLogin(),key );
        if(distant_partial_backup){
            setDataLoaded(distant_partial_backup->hasLoadedData());
            setData(distant_partial_backup->getData());
            setLastSave(distant_partial_backup->getLastSave());
            setNote(distant_partial_backup->getNote());
        }
        ConfigManager::getInstance().setJsonFile(LOCAL_CONFIG_FILE);
        return true && hasLoadedData();
    }
    return false;
}

void Backup::deleteFromJson(){
    std::string config_file;
    if(target->getType() == "FTP"){

    }else{
         config_file = getTarget()->getPath()
                + QDir::separator().toLatin1()
                + getOwnersLogin()
                + ".config";
    }

    ConfigManager::getInstance().setJsonFile(config_file);
    ConfigManager::getInstance().deleteUsersBackupData(getOwnersLogin(),key);
    ConfigManager::getInstance().setJsonFile(LOCAL_CONFIG_FILE);
}

string Backup::getKey() const
{    return string(key);    }
string Backup::getName() const
{    return name;   }
string Backup::getSource() const
{    return source; }
const AbsTarget* Backup::getTarget() const
{    return target; }
string Backup::getLastSave() const
    //TODO type Date
{    return lastSave;   }
Frequency Backup::getFrequency() const
{    return frequency;   }
const Data* Backup::getData() const
{    return this->data;  }
string Backup::getNote() const
{    return this->note;  }
bool Backup::hasLoadedData() const
{   return dataIsLoaded; }
std::string Backup::getOwnersLogin() const
{   return ownerLogPass[0]; }
std::string Backup::getOwnersPass() const
{   return ownerLogPass[1]; }

void Backup::setKey(const char* _key)
{   memcpy(key,_key,32);     }
void Backup::setName(const string _name)
{    this->name = _name;      }
void Backup::setSource(const string sourcePath)
{    this->source = sourcePath;     }
void Backup::setTarget(const AbsTarget *_target)
{    this->target = _target;     }
void Backup::setLastSave(const string _lastSave)
    //TODO type Date
{    this->lastSave = _lastSave;    }
void Backup::setFrequency(const Frequency _frequency)
{    this->frequency = _frequency;  }
void Backup::setData(const Data *_data)
{    this->data = _data;     }
void Backup::setNote(const string _note)
{    this->note = _note;  }
void  Backup::setDataLoaded(const bool loadedData)
{   dataIsLoaded = loadedData; }
void Backup::setOwnersLogin(const std::string login)
{   ownerLogPass[0] = login; }
void Backup::setOwnersPass(const std::string pass)
{   ownerLogPass[1] = pass; }

bool Backup::operator==(const Backup &backup)
{   return (strcmp(key, backup.getKey().c_str())==0 && name == backup.getName())  ;  }

bool Backup::operator!=(const Backup &backup){
    return !operator==(backup);
}

void Backup::operator=(const Backup &backup){
    name                = backup.getName();
    source              = backup.getSource();
    target               = backup.getTarget();
    lastSave           = backup.getLastSave();
    frequency       = backup.getFrequency();
    data                   = backup.getData();
    note                   = backup.getNote();
    dataIsLoaded = backup.hasLoadedData();
    setKey(backup.getKey().c_str());
    setOwnersLogin(backup.getOwnersLogin());
    setOwnersPass( backup.getOwnersPass() );
}

ostream& operator<<(ostream &out, const Backup &backup){
    out << "nom: " << backup.name << endl;
    out << "\tclé: " << backup.key << endl;
    out << "\tsource: " << backup.source << endl;
    out << "\tdestination: " << backup.target->getTag() << endl;
    out << "\tracine data: " << *backup.data << endl;
    return out;
}


json& operator<<(json &j, const Backup &backup){
    j = {
            {"key", backup.getKey()},
            {"name", backup.getName()},
            {"src", backup.getSource()},
            {"dest",{
                    {"type",backup.getTarget()->getType()},
                    {"tag", backup.getTarget()->getTag()}
                }
            },
            {"freq", backup.getFrequency().toString()},
            {"last_save", backup.getLastSave()},
            {"note", backup.getNote()},
    };
    return j;
}

json Backup::toDistantJson(){
    json jData = data == NULL ? json::object():data->to_json();

    json jOut = json{{
            key,{
                {"Data", jData},
                {"name", name},
                {"last_save", lastSave},
                 {"note", note}
            }
    }};
    return jOut ;
}

