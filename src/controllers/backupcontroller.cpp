#include "backupcontroller.h"
#include "../services/Crypt.h"

BackupController BackupController::instance = BackupController();


Backup BackupController::getBackupFromInfoMap(std::map<std::string,std::string> backupInfo){
    Backup backup_from_info;

    std::map<std::string,std::string>::iterator it = backupInfo.find("key");
    if(it != backupInfo.end())
        backup_from_info.setKey(backupInfo["key"].c_str());
    else backup_from_info.setKey(Crypt::genKey(32));

    std::cout << "getBackupFromInfoMap : clé pif"<<std::endl;
    std::cout << backup_from_info.getKey() << std::endl;

    for(auto bc : backupInfo){
        std::cout << bc.first << ":" << bc.second << std::endl;
    }

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
