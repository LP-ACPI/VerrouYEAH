//
// Created by Valentin on 05/12/16.
//
#include "Backup.h"
#include "../services/CompressCrypt.h"
#include "../services/ConfigManager.h"
#include <QDebug>

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

void Backup::saveData(){
    //TODO sauvegarde des données (data) vers des fichiers .vy

    QFileInfo info(QString::fromStdString(getSource()));
    Data* root_dir = new Directory(info);
    setData(root_dir);

    //TODO :FTP

    if(target->getType() == "NORMAL"){
        saveNormalData();
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

void Backup::saveNormalData(){
    QString target_path = QString::fromStdString(target->getPath() +"/"+ name);
    QString source_path = QString::fromStdString(source);
    CompressCrypt::getInstance().cryptDir(source_path ,target_path+"_temp",key);
    CompressCrypt::getInstance().compressDir(target_path+"_temp",target_path+".vy");
    QDir dir(target_path+"_temp");
    dir.removeRecursively();

    std::string distant_config = target->getPath()
            + QDir::separator().toLatin1()
            + getOwnersLogin()+".config";

    ConfigManager::getInstance().setJsonFile(distant_config);
    ConfigManager::getInstance().deleteUsersBackupData(getOwnersLogin(),key );
    ConfigManager::getInstance().saveUsersBackupData(this);
    ConfigManager::getInstance().setJsonFile(LOCAL_CONFIG_FILE);
}

void Backup::restoreNormalData(){
    QString decrypt_from = QString::fromStdString(target->getPath()+"/"+ name);
    QString decrypt_to = QString::fromStdString("decrypt/"+name);
    qDebug() << decrypt_from;
    qDebug() << decrypt_to;

    CompressCrypt::getInstance().decompressDir(decrypt_from+".vy",decrypt_from+"_temp");
    CompressCrypt::getInstance().decryptDir(decrypt_from+"_temp",decrypt_to,key);
    QDir dir(decrypt_from+"_temp");
    dir.removeRecursively();
}

void Backup::saveFtpData(){

}

void Backup::restoreFtpData(){

}

bool Backup::loadDistantJson(){
    if(target->getType() == "FTP")
        return loadFtpJson();
    else
        return loadNormalJson();
}

bool Backup::loadFtpJson() {

}

bool Backup::loadNormalJson() {
    std::string distant_config = getTarget()->getPath()
            + QDir::separator().toLatin1()
            + getOwnersLogin()
            + ".config";

    QFile file(QString::fromStdString(distant_config));
    if(file.exists()){
        ConfigManager::getInstance().setJsonFile(distant_config);
        Backup *distant_partial_backup =  ConfigManager::getInstance().getUserBackupsData(getOwnersLogin(),key );
        if(distant_partial_backup){
            setDataLoaded(distant_partial_backup->hasLoadedData());
            setData(distant_partial_backup->getData());
            setLastSave(distant_partial_backup->getLastSave());
            ConfigManager::getInstance().setJsonFile(LOCAL_CONFIG_FILE);
        }
        return true && hasLoadedData();
    }
    return false;
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
{   return (strcmp(key, backup.getKey().c_str())==0) ;  }

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
                {"last_save", lastSave}
            }
    }};
    return jOut ;
}

