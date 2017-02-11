#include "UserController.h"
#include <openssl/sha.h>
#include <QDebug>

UserController UserController::instance = UserController();

void UserController::setCurrentUser(std::string login)
{  instance.currentUser = ConfigManager::getInstance().loadUser(login);   }

bool UserController::favoriteUserExists(){
    instance.currentUser = ConfigManager::getInstance().loadAutoLoginUser() ;
    return instance.currentUser != NULL;
}

std::string UserController::getFavoriteUser(){
    if(favoriteUserExists())
        return ConfigManager::getInstance().loadAutoLoginUser()->getLogin();
    return "";
}

void UserController::setFavoriteUser(std::string userLogin){
    ConfigManager::getInstance().setAutoLoginUser(userLogin);
}

void UserController::unsetFavoriteUser(){
    if(favoriteUserExists())
        ConfigManager::getInstance().unsetAutoLoginUser();
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

bool UserController::updateUser(std::string newLogin, std::string newPass){
    deleteUser();
    return createUser(newLogin,newPass);
}

void UserController::deleteUser(){
    ConfigManager::getInstance().deleteUser(currentUser->getLogin());
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

