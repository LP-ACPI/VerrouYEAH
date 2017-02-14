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
    std::cout << user->getLogin()<<std::endl;
    std::map<std::string,std::string> backup_info = BackupController::getInstance().getInfoMapFromBackup(&backup);
    return backup_info;
}

void UsersBackupController::createUsersBackup(std::map<std::string,std::string> backupInfo){
    //TODO cryptage ici + démarrage du scheduler
    //ou plutôt un BackupController qui s'en charge + mise à jour du dossier distant (normal/ftp)

    Backup new_backup = BackupController::getInstance().getBackupFromInfoMap(backupInfo);
    user->addBackup(new_backup);
    ConfigManager::getInstance().updateUser(user);
}

void UsersBackupController::updateUsersBackup(std::map<std::string,std::string> backupInfo){
    //TODO: avertissement "modif' données sauvegardés"
    Backup backup_to_update = BackupController::getInstance().getBackupFromInfoMap(backupInfo);
    Backup old_backup = user->getBackupByKey(backup_to_update.getKey());
    user->replaceBackup(old_backup,backup_to_update);
    ConfigManager::getInstance().updateUser(user);
}

void UsersBackupController::deleteUsersBackup(std::string bcKey){
    //TODO: avertissement "suppression données sauvegardés"
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


std::list<std::string> UsersBackupController::getUsersBackupKeyList(){
    std::list<std::string> key_list;
    for(std::map<std::string,std::string> info : getUsersBackupInfoList())
        key_list.push_back(info["key"]);
    return key_list;

}

