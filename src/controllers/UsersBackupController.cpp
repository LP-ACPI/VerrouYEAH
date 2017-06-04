#include "UsersBackupController.h"
#include "BackupController.h"
#include "UserController.h"
#include "TargetController.h"
#include "../services/Ftp.h"
#include "../services/Scheduler.h"
#include "../services/CompressCrypt.h"
#include "../services/ConfigManager.h"
#include <QEventLoop>
#include <QDesktopServices>


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
        new_backup.saveData();
        user->addBackup(new_backup);
        Scheduler::getInstance().add(new_backup);
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
        Scheduler::getInstance().replace(*old_backup,backup_to_update);
        ConfigManager::getInstance().updateUser(user);
    }catch(std::invalid_argument &e){
        throw std::invalid_argument(e.what());
    }
}

void UsersBackupController::deleteUsersBackup(std::string bcKey){
    Backup* bc_to_delete = user->getBackupByKey(bcKey);
    user->removeBackup(*bc_to_delete);
    Scheduler::getInstance().remove(*bc_to_delete);
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
json UsersBackupController::recoverUsersNonRegistrededBackups(std::string login,std::string pass,std::string targetTag){
   AbsTarget *abs_target = user->getFavoriteTargetByTag(targetTag);
   std::string config_file_path;
   std::string tmp_config_dir = "tmp_recover";

   json jsonBackupData;
   json existing_backups = json::array();
   json new_backups = json::array();

   bool downOk = true;
   if(abs_target->isFtp()){
       FtpTarget  *ftp_target =(FtpTarget *)abs_target;
        int port = stoi(ftp_target->getPort());

       while(Ftp::getInstance().isCurrentlyBusy());

        QEventLoop loopDown;
        QObject::connect(&Ftp::getInstance(), SIGNAL(finished()), &loopDown, SLOT(quit()));
        Ftp::getInstance().prepareFtp(
                    ftp_target->getHost(),
                    ftp_target->getUserName(),
                    ftp_target->getFtpPass(),
                    port);
         downOk &= Ftp::getInstance().ftpDownload(ftp_target->getPath()+"/"+login+".config",tmp_config_dir);
        loopDown.exec();

        config_file_path = tmp_config_dir+QDir::separator().toLatin1()+login+".config";

   }else{
       Target  *target = (Target*) abs_target;
       config_file_path=target->getPath() + QDir::separator().toLatin1() + login + ".config";
   }

   std::string hashedPass = Crypt::generateHashedPass(pass);
    try {
       ConfigManager::getInstance().setJsonFile(config_file_path);

       if(ConfigManager::getInstance().authentifyDistantBackupsOwner(login,hashedPass )){

           User *tmp_user = new User(login,hashedPass);
            for(Backup *bc : ConfigManager::getInstance().getUsersDistantBackupList(tmp_user)){

                try{
                bc->setTarget(abs_target);

                bc->setOwnersLogin(user->getLogin());
                bc->setOwnersPass(user->getPassword());
                if( bc->getData()){
                    QDir source( QString::fromStdString(bc->getData()->getPath()));
                    if(source.exists())
                        bc->setSource(bc->getData()->getPath());
                    else {
                        bc->recoverData();
                        bc->setSource("decrypt/"+bc->getName()+"_"+user->getLogin());
                        QString path = QDir::toNativeSeparators("decrypt");
                        QDesktopServices::openUrl(QUrl::fromLocalFile(path));
                    }
                }

                    user->addBackup(*bc);
                    Scheduler::getInstance().add(*bc);
                    new_backups +=  json{
                         {"key", bc->getKey()},
                         {"name" , bc->getName()}
                    };

                } catch(const std::invalid_argument){
                    existing_backups += json{{"name",bc->getName()}};
                }

            }
            jsonBackupData = json{
                    {"found", new_backups},
                    {"exist", existing_backups}
              };

            delete tmp_user;
            QDir tmp_dir(QString::fromStdString(tmp_config_dir));
            if(tmp_dir.exists())
                tmp_dir.removeRecursively();

       } else {
            throw std::invalid_argument("Erreur");
        }
        ConfigManager::getInstance().setJsonFile(LOCAL_CONFIG_FILE);
        ConfigManager::getInstance().updateUser(user);
    } catch (std::exception& e) {
        throw std::runtime_error(e.what());
    }
   return jsonBackupData;
}


