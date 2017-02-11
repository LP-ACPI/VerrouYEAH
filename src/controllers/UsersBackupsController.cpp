#include "UsersBackupsController.h"
#include "../services/ConfigManager.h"
#include <QDebug>

UsersBackupsController UsersBackupsController::instance = UsersBackupsController();

void UsersBackupsController::setUser(std::string login){
    instance.user = ConfigManager::getInstance().loadUser(login);
}

void UsersBackupsController::createUsersBackup(Backup *backup){
    //TODO cryptage ici + démarrage du scheduler
    //ou plutôt un BackupController qui s'en charge + mise à jour du dossier distant
    instance.user->addBackup(*backup);
    ConfigManager::getInstance().saveUser(user);
}

Backup UsersBackupsController::getUsersBackup(std::string bcpKey){
    return instance.user->getBackupByKey(bcpKey);
}

void UsersBackupsController::updateUsersBackup(Backup *backup){
    //TODO: avertissement "modif' données sauvegardés"
    Backup old_backup = instance.user->getBackupByKey(backup->getKey());
    instance.user->replaceBackup(old_backup,*backup);
    ConfigManager::getInstance().saveUser(instance.user);
}

void UsersBackupsController::deleteUsersBackup(std::string bcKey){
    //TODO: avertissement "suppression données sauvegardés"
    Backup bc_to_delete = instance.user->getBackupByKey(bcKey);
    instance.user->removeBackup(bc_to_delete);
    ConfigManager::getInstance().deleteUsersBackup(instance.user->getLogin(),bcKey);
    ConfigManager::getInstance().saveUser(instance.user);
}

std::list<Backup> UsersBackupsController::getUsersBackupList(){
    return instance.user->getBackups();
}
