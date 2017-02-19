#include "TargetController.h"
#include "UserController.h"
#include "../services/ConfigManager.h"
#include <QDebug>

TargetController TargetController::instance = TargetController();


std::map<std::string,std::string>TargetController::favoriteFtpTargetToInfoMap(std::string key){
    FtpTarget *ftp_target =  (FtpTarget*)UserController::getInstance().getCurrentUser()->getFavoriteTargetByKey(key);
    std::map<std::string,std::string> ftp_target_info_map;
    ftp_target_info_map["tag"] =ftp_target->getTag();
    ftp_target_info_map["path"] = ftp_target->getPath();
    ftp_target_info_map["host"] = ftp_target->getHost();
    ftp_target_info_map["username"] = ftp_target->getUserName();
    ftp_target_info_map["pass"] = ftp_target->getFtpPass();
    ftp_target_info_map["port"] = ftp_target->getPort();
    ftp_target_info_map["target_id"] = key;
    ftp_target_info_map["type"] = "FTP";

    return ftp_target_info_map;
}

FtpTarget *TargetController::getFtpTargetFromInfoMap(std::map<std::string,std::string> infoMap){
    FtpTarget *target = new FtpTarget(infoMap["tag"]);
    target->setPath(infoMap["path"]);
    target->setHost(infoMap["host"]);
    target->setUserName(infoMap["username"]);
    target->setFtpPass(infoMap["pass"]);
    target->setPort(infoMap["port"]);
    if(infoMap["target_id"] != "null")
         target->setId(infoMap["target_id"]);

    return target;
}

std::map<std::string,std::string> TargetController::favoriteNormalTargetToInfoMap(std::string key){
    Target *target = (Target*) UserController::getInstance().getCurrentUser()->getFavoriteTargetByKey(key);
    std::map<std::string,std::string> target_info_map;
    target_info_map["tag"] = target->getTag();
    target_info_map["path"] = target->getPath();
    target_info_map["target_id"] = key;
    target_info_map["type"] = "NORMAL";

    return target_info_map;
}

Target *TargetController::getNormalTargetFromInfoMap(std::map<std::string,std::string> infoMap){
    Target  *target = new Target(infoMap["tag"]);
    target->setPath(infoMap["path"]);
    if(infoMap["target_id"] != "null")
         target->setId(infoMap["target_id"]);
    return target;
}

std::string TargetController::getFavoriteTargetsType(std::string targetKey){
    return  UserController::getInstance().getCurrentUser()->getFavoriteTargetByKey(targetKey)->getType();
}

void TargetController::updateFavoriteNormalTarget( std::map<std::string,std::string> infoMap){
    Target *old_target =(Target *) UserController::getInstance().getCurrentUser()->getFavoriteTargetByKey(infoMap["target_id"]);
    Target *new_target = getNormalTargetFromInfoMap(infoMap);

    UserController::getInstance().getCurrentUser()->replaceFavoriteTarget(old_target,new_target);
    ConfigManager::getInstance().updateUser(UserController::getInstance().getCurrentUser());
}

void TargetController::updateFavoriteFtpTarget( std::map<std::string,std::string> infoMap){
    FtpTarget *old_target = (FtpTarget *)UserController::getInstance().getCurrentUser()->getFavoriteTargetByKey(infoMap["target_id"]);
    FtpTarget *new_target = getFtpTargetFromInfoMap(infoMap);
    UserController::getInstance().getCurrentUser()->replaceFavoriteTarget(old_target,new_target);
    ConfigManager::getInstance().updateUser(UserController::getInstance().getCurrentUser());
}

void TargetController::addNewFavoriteNormalTarget(std::map<std::string,std::string> infoMap){
    Target *new_target = getNormalTargetFromInfoMap(infoMap);
    UserController::getInstance().getCurrentUser()->addFavoriteTarget(new_target);
    ConfigManager::getInstance().updateUser(UserController::getInstance().getCurrentUser());
}

void TargetController::addNewFavoriteFtpTarget(std::map<std::string,std::string> infoMap){
    FtpTarget *new_target = getFtpTargetFromInfoMap(infoMap);
    UserController::getInstance().getCurrentUser()->addFavoriteTarget(new_target);
    ConfigManager::getInstance().updateUser(UserController::getInstance().getCurrentUser());
}

void TargetController::deleteFavoriteTarget(std::string targetKey){
    AbsTarget *target_to_delete = UserController::getInstance().getCurrentUser()->getFavoriteTargetByKey(targetKey);
    UserController::getInstance().getCurrentUser()->removeFavoriteTarget(target_to_delete);
    ConfigManager::getInstance().updateUser(UserController::getInstance().getCurrentUser());
}

std::list<std::string> TargetController::listlFavoriteNormalTargetTags(){
    std::list<std::string> tag_list;
    for(AbsTarget *tg : UserController::getInstance().getCurrentUser()->getFavoriteTargets())
        if(tg->getType()=="NORMAL")
            tag_list.push_back(tg->getTag());
    return tag_list;
}

std::list<std::string> TargetController::listFavoriteFtpTargetTags(){
    std::list<std::string> tag_list;
    for(AbsTarget *tg : UserController::getInstance().getCurrentUser()->getFavoriteTargets())
        if(tg->getType()=="FTP")
            tag_list.push_back(tg->getTag());
    return tag_list;
}


std::map<std::string,std::string> TargetController::targetCouplesTagKey(){
    std::map<std::string,std::string> tg_key_map;
    for(AbsTarget *tg : UserController::getInstance().getCurrentUser()->getFavoriteTargets())
        tg_key_map[tg->getTag()] = tg->getId();
    return tg_key_map;
}
