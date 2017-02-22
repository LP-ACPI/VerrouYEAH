#include "UsersBackupController.h"
#include "backupcontroller.h"
#include "UserController.h"
#include "targetcontroller.h"
#include "../services/ConfigManager.h"
#include "../services/Ftp.h"
#include "../services/CompressCrypt.h"
#include <QEventLoop>


bool UsersBackupController::anotherBackupAlreadyExists(std::string key, std::string new_name){
    bool backup_name_taken = false;
    for(Backup bc : UserController::getInstance().getCurrentUser()->getBackups())
        if(bc.getName() == new_name && key != bc.getKey())
            backup_name_taken = true;
    return backup_name_taken;
}

bool UsersBackupController::backupAlreadyExists(std::string name){

    bool backup_name_taken = false;
    for(std::string bc_name : UsersBackupController::getInstance().getUsersBackupNameList())
        if(bc_name == name)
            backup_name_taken = true;
    return backup_name_taken;
}

void UsersBackupController::setCurrentUser(){
    user = UserController::getInstance().getCurrentUser();
}

std::map<std::string,std::string> UsersBackupController::getUsersBackupInfo(std::string bcpKey){
    Backup *backup = user->getBackupByKey(bcpKey);

    std::map<std::string,std::string> backup_info = BackupController::getInstance().getInfoMapFromBackup(backup);
    return backup_info;
}

std::map<std::string,std::string> UsersBackupController::addNewUsersBackup(std::map<std::string,std::string> backupInfo){

    char *key = Crypt::genKey(32);
    backupInfo["key"] = std::string(key);
    Backup new_backup = BackupController::getInstance().getBackupFromInfoMap(backupInfo);
    new_backup.setOwnersLogin(user->getLogin());
    new_backup.setOwnersPass(user->getPassword());
    try{
        user->addBackup(new_backup);
        ConfigManager::getInstance().updateUser(user);
        return BackupController::getInstance().getInfoMapFromBackup(&new_backup);
    }catch(std::invalid_argument &e){
        throw std::invalid_argument(e.what());
        return backupInfo;
    }
}

void UsersBackupController::updateUsersBackup(std::map<std::string,std::string> backupInfo){

    try{
        Backup backup_to_update = BackupController::getInstance().getBackupFromInfoMap(backupInfo);
        backup_to_update.setOwnersLogin(user->getLogin());
        backup_to_update.setOwnersPass(user->getPassword());
        Backup *old_backup = user->getBackupByKey(backup_to_update.getKey());
        backup_to_update.saveData();
        user->replaceBackup(*old_backup,backup_to_update);
        ConfigManager::getInstance().updateUser(user);
    }catch(std::invalid_argument &e){
        throw std::invalid_argument(e.what());
    }
}

void UsersBackupController::deleteUsersBackup(std::string bcKey){
    Backup* bc_to_delete = user->getBackupByKey(bcKey);
    user->removeBackup(*bc_to_delete);
    ConfigManager::getInstance().updateUser(user);
}

std::list<std::map<std::string,std::string>> UsersBackupController::getUsersBackupInfoList(){
    std::list<Backup> backup_list = user->getBackups();
    std::list<std::map<std::string,std::string>> backup_list_info;

    for(Backup backup : backup_list)
        backup_list_info.push_back(BackupController::getInstance().getInfoMapFromBackup(&backup));

    return backup_list_info;
}

std::list<std::string> UsersBackupController::getUsersBackupNameList(){
    std::list<std::string> name_list;
    for(std::map<std::string,std::string> info : getUsersBackupInfoList())
        name_list.push_back(info["name"]);
    return name_list;
}

//TODO
json UsersBackupController::findUsersNonRegistrededBackups(std::string login,std::string pass,std::string targetTag){
   std::string target_type = TargetController::getInstance().getFavoriteTargetsType(targetTag);
   std::map<std::string,std::string> targetInfoMap;
   std::string config_file_path;
   json jsonBackupData = json::array();
   bool downOk = true;
   if(target_type == "FTP"){
        targetInfoMap = TargetController::getInstance().favoriteFtpTargetToInfoMap(targetTag);
        int port = stoi(targetInfoMap["port"]);

       while(Ftp::getInstance().isCurrentlyBusy());

        QEventLoop loopDown;
        QObject::connect(&Ftp::getInstance(), SIGNAL(finished()), &loopDown, SLOT(quit()));
        Ftp::getInstance().prepareFtp(targetInfoMap["host"],targetInfoMap["username"],targetInfoMap["pass"],port);
         downOk &= Ftp::getInstance().ftpDownload(targetInfoMap["path"]+"/"+login+".config","tmp_recover");
        loopDown.exec();

        config_file_path = "tmp_recover/"+login+".config";

   }else{
       targetInfoMap = TargetController::getInstance().favoriteNormalTargetToInfoMap(targetTag);
       config_file_path=targetInfoMap["path"] + QDir::separator().toLatin1() + login + ".config";
   }

   std::string hashedPass = Crypt::generateHashedPass(pass);
    try {
       ConfigManager::getInstance().setJsonFile(config_file_path);

       if(ConfigManager::getInstance().authentifyDistantBackupsOwner(login,hashedPass )){
            User *tmp_user = new User(login,hashedPass);
            for(Backup *bc : ConfigManager::getInstance().getUsersDistantBackupList(tmp_user)){
                json tmp_json = json{
                {"key",bc->getKey()},
                {"name",bc->getName()},
                {"target_tag",targetInfoMap["tag"]},
                {"user",login},
                {"pass",hashedPass}
            };
                 json jsonBc;
                 jsonBc << *bc;
                 jsonBackupData += tmp_json;
                 qDebug() <<QString::fromStdString(jsonBc.dump(2));

           }
       } else {
            throw std::invalid_argument("Erreur");
        }
        ConfigManager::getInstance().setJsonFile(LOCAL_CONFIG_FILE);
    } catch (std::exception& e) {
        throw std::runtime_error(e.what());
    }
   return jsonBackupData;
}


