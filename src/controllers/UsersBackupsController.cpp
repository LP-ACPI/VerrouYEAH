#include "UsersBackupsController.h"
#include "../services/ConfigManager.h"

void UsersBackupsController::setUser(std::string login){
    user = ConfigManager::getInstance().loadUser(login);
}

void UsersBackupsController::createUsersBackup(Backup *backup){
    //TODO cryptage ici + démarrage du scheduler
    //ou plutôt un BackupController qui s'en charge + mise à jour du dossier distant
    user->addBackup(*backup);
    ConfigManager::getInstance().saveUser(user);
}

Backup UsersBackupsController::getUsersBackup(std::string bcpKey){
    return user->getBackupByKey(bcpKey);
}

void UsersBackupsController::updateUsersBackup(Backup *backup){
    //TODO: avertissement "modif' données sauvegardés"
    Backup old_backup = user->getBackupByKey(backup->getKey());
    user->replaceBackup(old_backup,*backup);
    ConfigManager::getInstance().saveUser(user);
}

void UsersBackupsController::deleteUsersBackup(std::string bcKey){
    //TODO: avertissement "suppression données sauvegardés"
    Backup bc_to_delete = user->getBackupByKey(bcKey);
    user->removeBackup(bc_to_delete);
    ConfigManager::getInstance().deleteUsersBackup(user->getLogin(),bcKey);
    ConfigManager::getInstance().saveUser(user);
}

std::list<Backup> UsersBackupsController::getUsersBackupList(){
    return user->getBackups();
}
