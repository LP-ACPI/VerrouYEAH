#include "UsersBackupController.h"
#include "backupcontroller.h"
#include "UserController.h"
#include "targetcontroller.h"
#include "../services/ConfigManager.h"
#include "../services/Scheduler.h"
#include "../services/Ftp.h"
#include <QDebug>


void UsersBackupController::setCurrentUser(){
    user = UserController::getInstance().getCurrentUser();
}

std::map<std::string,std::string> UsersBackupController::getUsersBackupInfo(std::string bcpKey){
    Backup backup = user->getBackupByKey(bcpKey);

    std::map<std::string,std::string> backup_info = BackupController::getInstance().getInfoMapFromBackup(&backup);
    return backup_info;
}

std::map<std::string,std::string> UsersBackupController::addNewUsersBackup(std::map<std::string,std::string> backupInfo){
    char *key = Crypt::genKey(32);
    backupInfo["key"] = std::string(key);
    Backup new_backup = BackupController::getInstance().getBackupFromInfoMap(backupInfo);
    new_backup.setOwnersLogin(user->getLogin());
    new_backup.setOwnersPass(user->getPassword());
    new_backup.saveData();
    user->addBackup(new_backup);
    Scheduler::getInstance().add(new_backup);
    ConfigManager::getInstance().updateUser(user);
    return BackupController::getInstance().getInfoMapFromBackup(&new_backup);
}

void UsersBackupController::updateUsersBackup(std::map<std::string,std::string> backupInfo){
    //TODO: avertissement "modif' données sauvegardés"
    //déplacer vers nouvelle desti + suppr ancienne -> dans backup.saveData?replaceBackup?
    Backup backup_to_update = BackupController::getInstance().getBackupFromInfoMap(backupInfo);
    backup_to_update.setOwnersLogin(user->getLogin());
    backup_to_update.setOwnersPass(user->getPassword());
    Backup old_backup = user->getBackupByKey(backup_to_update.getKey());
    backup_to_update.saveData();
    user->replaceBackup(old_backup,backup_to_update);

//    Scheduler::getInstance().remove(old_backup);
//    Scheduler::getInstance().add(backup_to_update);
    ConfigManager::getInstance().updateUser(user);
}

void UsersBackupController::deleteUsersBackup(std::string bcKey){
    //TODO: avertissement "suppression données sauvegardés"
    // + supprimer le fichier .vy?
    Backup bc_to_delete = user->getBackupByKey(bcKey);
    user->removeBackup(bc_to_delete);
//    Scheduler::getInstance().remove(bc_to_delete);
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
std::list<std::map<std::string,std::string>> UsersBackupController::recoverUsersNonRegistrededBackups(std::string login,std::string pass,std::string targetId){
   std::string target_type = TargetController::getInstance().getFavoriteTargetsType(targetId);
   std::map<std::string,std::string> targetInfoMap;
   if(target_type == "FTP"){
        targetInfoMap = TargetController::getInstance().favoriteFtpTargetToInfoMap(targetId);

//        Ftp::getInstance().prepareFtp(targetInfoMap["host"],targetInfoMap["username"],pass,port);
//         saveOk &= Ftp::getInstance().ftpUpload(temp_dest_crypt+".vy",ftpTarget->getPath());
//        loopUp.exec();
//        saveOk &=  Ftp::getInstance().ftpUpload(temp_dest_data,ftpTarget->getPath());
   }else
       targetInfoMap = TargetController::getInstance().favoriteNormalTargetToInfoMap(targetId);

   std::string hashedPass = Crypt::generateHashedPass(pass);
    try {
        if(ConfigManager::getInstance().authentifyDistantBackupsOwner(login,hashedPass )){

        } else {
            throw std::invalid_argument("Erreur Authentification");
        }
        ConfigManager::getInstance().setJsonFile(LOCAL_CONFIG_FILE);
    } catch (std::exception& e) {
        throw std::runtime_error(e.what());
    }
}
