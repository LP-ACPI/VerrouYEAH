#include "UsersBackupController.h"
#include "BackupController.h"
#include "UserController.h"
#include "../services/ConfigManager.h"
#include <QDebug>

UsersBackupController UsersBackupController::instance = UsersBackupController();

void UsersBackupController::setCurrentUser(){
    user = UserController::getInstance().getCurrentUser();
}

std::map<std::string,std::string> UsersBackupController::getUsersBackupInfo(std::string bcpKey){
    Backup backup = user->getBackupByKey(bcpKey);

    std::map<std::string,std::string> backup_info = BackupController::getInstance().getInfoMapFromBackup(&backup);
    return backup_info;
}

std::map<std::string,std::string> UsersBackupController::addNewUsersBackup(std::map<std::string,std::string> backupInfo){
    //TODO :
    //ou plutôt un BackupController qui s'en charge
    backupInfo["key"] = std::string(Crypt::genKey(32));
    Backup new_backup = BackupController::getInstance().getBackupFromInfoMap(backupInfo);
    new_backup.setOwnersLogin(user->getLogin());
    new_backup.setOwnersPass(user->getPassword());
    new_backup.saveData();
    user->addBackup(new_backup);

    ConfigManager::getInstance().updateUser(user);
    return backupInfo;
}

void UsersBackupController::updateUsersBackup(std::map<std::string,std::string> backupInfo){
    //TODO: avertissement "modif' données sauvegardés"
    //déplacer vers nouvelle desti + suppr ancienne -> dans backup.saveData?replaceBackup?
    Backup backup_to_update = BackupController::getInstance().getBackupFromInfoMap(backupInfo);
    backup_to_update.setOwnersLogin(user->getLogin());
    backup_to_update.setOwnersPass(user->getPassword());
    Backup old_backup = user->getBackupByKey(backup_to_update.getKey());
    user->replaceBackup(old_backup,backup_to_update);
    backup_to_update.saveData();
    ConfigManager::getInstance().updateUser(user);
}

void UsersBackupController::deleteUsersBackup(std::string bcKey){
    //TODO: avertissement "suppression données sauvegardés"
    // + supprimer le fichier .vy
    Backup bc_to_delete = user->getBackupByKey(bcKey);
    user->removeBackup(bc_to_delete);
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


std::list<std::map<std::string,std::string>> UsersBackupController::recoverCurrentUserNonRegistrededBackups(std::string confirmPass){
    try {
        if(ConfigManager::getInstance().authentifyDistantBackupsOwner(user->getLogin(),confirmPass)){

        } else {

        }
    } catch (std::exception& e) {
        throw std::runtime_error(e.what());
    }
}

std::list<std::map<std::string,std::string>> UsersBackupController::recoverAnotherUserNonRegistrededBackups(std::string login,std::string pass){

}
