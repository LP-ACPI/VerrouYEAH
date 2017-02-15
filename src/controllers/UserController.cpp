#include "UserController.h"
#include "../services/Crypt.h"


UserController UserController::instance = UserController();

void UserController::setCurrentUser(std::string login) {
  currentUser = ConfigManager::getInstance().loadUser(login);
}

bool UserController::favoriteUserExists() {
    std::string user_login = ConfigManager::getInstance().loadAutoLoginUserLogin() ;
    return user_login != "";
}

std::string UserController::getFavoriteUser(){
    return ConfigManager::getInstance().loadAutoLoginUserLogin();;
}

void UserController::setFavoriteUser(std::string userLogin){
    ConfigManager::getInstance().setAutoLoginUser(userLogin);
}

void UserController::unsetFavoriteUser(std::string userLogin){
    if(favoriteUserExists())
        ConfigManager::getInstance().unsetAutoLoginUser(userLogin);
}

void UserController::loadLoginsPassCouples(){
    userLoginPassCouples = ConfigManager::getInstance().loadLoginPassCouples();
}

bool UserController::authentifyUser(std::string userLogin, std::string userPass){
    std::string hashed_pass = Crypt::generateHashedPass(userPass);
    return userLoginPassCouples[userLogin] == hashed_pass;
}


bool UserController::createUser(std::string userLogin, std::string userPass){
    if(!userLoginPassCouples.count(userLogin)) {
        std::string hashed_pass = Crypt::generateHashedPass(userPass);
        ConfigManager::getInstance().saveUser(new User(userLogin,hashed_pass));
        userLoginPassCouples[userLogin] = hashed_pass;
        return true;
    }
    return false;
}

bool UserController::updateUser(std::string newLogin, std::string newPass){
    bool update_user;
    std::string hashed_pass = Crypt::generateHashedPass(newPass);

    if(newLogin != getCurrentUserLogin()){
        deleteUser();
        update_user = createUser(newLogin,newPass);
    } else {
        ConfigManager::getInstance().saveUser(new User(newLogin,hashed_pass));
        update_user = true;
    }

    if(update_user){
        setCurrentUser(newLogin);
        userLoginPassCouples[newLogin] = hashed_pass;
    }

    return update_user;
}

void UserController::deleteUser() {
    ConfigManager::getInstance().deleteUser(getCurrentUserLogin());
    loadLoginsPassCouples();
}

