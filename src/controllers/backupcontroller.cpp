#include "backupcontroller.h"
#include "UserController.h"
#include "../services/Crypt.h"
#include "../services/ConfigManager.h"
#include <QDir>

BackupController BackupController::instance = BackupController();

void BackupController::updateBackupData(Backup *backup){

    backup->saveData();

    std::string distant_config = backup->getTarget()
            + QDir::separator().toLatin1()
            + UserController::getInstance().getCurrentUserLogin()
            + ".json";

    ConfigManager::getInstance().setJsonFile(distant_config);

    ConfigManager::getInstance().saveUsersBackupData(
                UserController::getInstance().getCurrentUser(),backup
        );

    ConfigManager::getInstance().setJsonFile(LOCAL_CONFIG_FILE);
}

void BackupController::decryptBackup(std::string backupKey){
    UserController::getInstance().getCurrentUser()->getBackupByKey(backupKey).recoverData();
}

Backup BackupController::getBackupFromInfoMap(std::map<std::string,std::string> backupInfo){

    Backup backup_from_info("");
    backup_from_info.setKey(backupInfo["key"].c_str());
    backup_from_info.setName(backupInfo["name"]);
    backup_from_info.setSource(backupInfo["source_path"]);
    backup_from_info.setTarget(backupInfo["target_path"]);
    backup_from_info.setTargetType(backupInfo["target_type"]);
    backup_from_info.setLastSave(backupInfo["last_save"]);
    backup_from_info.setNote(backupInfo["note"]);
//    backup_from_info->setFrequency(backupInfo["frequency"]);

    return backup_from_info;

}

std::map<std::string,std::string> BackupController::getInfoMapFromBackup(Backup* backupToInfo){

    std::map<std::string,std::string> backup_info;
    backup_info["key"] = backupToInfo->getKey();
    backup_info["name"] = backupToInfo->getName();
    backup_info["source_path"] = backupToInfo->getSource();
    backup_info["target_path"] = backupToInfo->getTarget();
    backup_info["target_type"] = backupToInfo->getTargetType();
    backup_info["last_save"] = backupToInfo->getLastSave();
    backup_info["note"] = backupToInfo->getNote();
    backup_info["frequency"] = backupToInfo->getFrequency().toString();

    return backup_info;

}

const Data* BackupController::getData(std::string la_cle){
    User* user = UserController::getInstance().getCurrentUser();
    Backup backupByKey = user->getBackupByKey(la_cle);
    return backupByKey.getData();
}
