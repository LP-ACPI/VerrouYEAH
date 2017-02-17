#include "BackupController.h"
#include "UserController.h"
#include "TargetController.h"
#include "../views/progressdialog.h"
#include "../services/Crypt.h"
#include "../services/ConfigManager.h"
#include <QDir>

BackupController BackupController::instance = BackupController();

bool BackupController::updateDataIfAccessible(Backup *backup){

    //TODO FTP
    if(backup->getTarget()->getType() == "NORMAL"){
        std::string distant_config = backup->getTarget()->getPath()
                + QDir::separator().toLatin1()
                + UserController::getInstance().getCurrentUserLogin()
                + ".json";

        ConfigManager::getInstance().setJsonFile(distant_config);

       Backup *distant_backup =  ConfigManager::getInstance().getUsersDistantBackup(
                UserController::getInstance().getCurrentUserLogin(),
                backup->getKey()
            );
       backup->setData(distant_backup->getData());

        ConfigManager::getInstance().setJsonFile(LOCAL_CONFIG_FILE);
    }
    return backup->getData() != NULL;
}


void BackupController::restoreBackupData(std::string backupKey){
    UserController::getInstance().getCurrentUser()->getBackupByKey(backupKey).recoverData();
}

bool BackupController::isBackupFtp(std::string backupKey){
    return UserController::getInstance().getCurrentUser()->getBackupByKey(backupKey).getTarget()->getType() == "FTP";
}

Backup BackupController::getBackupFromInfoMap(std::map<std::string,std::string> backupInfo){

    Backup backup_from_info(backupInfo["key"] .c_str());
    backup_from_info.setName(backupInfo["name"]);
    backup_from_info.setSource(backupInfo["source_path"]);

    AbsTarget *target = UserController::getInstance().
            getCurrentUser()->getFavoriteTargetByKey(backupInfo["target_id"]);

    backup_from_info.setTarget(target);
    backup_from_info.setLastSave(backupInfo["last_save"]);
    backup_from_info.setNote(backupInfo["note"]);
//    backup_from_info.setFrequency(std::string("20-10-5-5-5"));

    return backup_from_info;

}

std::map<std::string,std::string> BackupController::getInfoMapFromBackup(Backup* backupToInfo){

    std::map<std::string,std::string> backup_info;
    backup_info["key"]                   = backupToInfo->getKey();
    backup_info["name"]               = backupToInfo->getName();
    backup_info["source_path"] = backupToInfo->getSource();
    backup_info["target_id"]       = backupToInfo->getTarget()->getId();
    backup_info["target_tag"]     = backupToInfo->getTarget()->getTag();
    backup_info["last_save"]       = backupToInfo->getLastSave();
    backup_info["note"]                = backupToInfo->getNote();
    backup_info["frequency"]     = backupToInfo->getFrequency().toString();
    backup_info["data_loaded"] = backupToInfo->hasLoadedData() ? "true" : "false";

    return backup_info;

}



json BackupController::getJsonifiedDataTree(std::string la_cle){
    User* user = UserController::getInstance().getCurrentUser();
    Backup backupByKey = user->getBackupByKey(la_cle);
    return backupByKey.getData()->to_json();
}
