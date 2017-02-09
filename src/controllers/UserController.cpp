#include "UserController.h"
#include <openssl/sha.h>
#include <QDebug>


bool UserController::favoriteUserExists(){
    return ConfigManager::getInstance().loadFavoriteUser() != NULL;
}

std::string UserController::getFavoriteUser(){
    return ConfigManager::getInstance().loadFavoriteUser()->getLogin();
}

void UserController::setFavoriteUser(std::string userLogin){
    ConfigManager::getInstance().setFavoriteUser(userLogin);
}

void UserController::unsetFavoriteUser(){
    ConfigManager::getInstance().unsetFavoriteUser();
}

void UserController::loadLoginsPassCouples(){
    userLoginPassCouples = ConfigManager::getInstance().loadLoginPassList();
}

bool UserController::authentifyUser(std::string userLogin, std::string userPass){
    std::string hashed_pass = generateHashedPass(userPass);
    return userLoginPassCouples[userLogin] == hashed_pass;
}


bool UserController::createUser(std::string userLogin, std::string userPass){
    if(!userLoginPassCouples.count(userLogin)){
        std::string hashed_pass = generateHashedPass(userPass);
        ConfigManager::getInstance().saveUser(new User(userLogin,hashed_pass));
        userLoginPassCouples[userLogin] = hashed_pass;
        return true;
    }
    return false;
}

void UserController::updateUser(std::string oldLogin,std::string newLogin, std::string newPass){
    ConfigManager::getInstance().setJsonFile(CONFIG_FILE);
    ConfigManager::getInstance().deleteUser(oldLogin);
    createUser(newLogin,newPass);
}

void UserController::deleteUser(std::string  userLogin){
    ConfigManager::getInstance().setJsonFile(CONFIG_FILE);
    ConfigManager::getInstance().deleteUser(userLogin);
}

std::string UserController::generateHashedPass(std::string userPass){
    unsigned char temp[SHA_DIGEST_LENGTH];
    char buf[SHA_DIGEST_LENGTH*2];

    memset(buf, 0x0, SHA_DIGEST_LENGTH*2);
    memset(temp, 0x0, SHA_DIGEST_LENGTH);

    SHA1((unsigned char *)userPass.c_str(), userPass.size(), temp);

    for(int i=0; i < SHA_DIGEST_LENGTH; i++) {
     sprintf((char*)&(buf[i*2]), "%02x", temp[i]);
    }

    std::string new_hashed_pass(buf);
    return new_hashed_pass;
}

