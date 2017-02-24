#include "UserController.h"
#include "../services/ConfigManager.h"
#include "../services/Crypt.h"
#include "../services/Scheduler.h"

void UserController::setCurrentUser(std::string login)
{
    //Lancement du scheduler au chargement de l'utilisateur
    currentUser = ConfigManager::getInstance().loadUser(login);
    Scheduler::getInstance().clear();
    Scheduler::getInstance().addFromUser(currentUser);
    Scheduler::getInstance().start();
}

bool UserController::favoriteUserExists() {
    std::string user_login = ConfigManager::getInstance().loadAutoLoginUserLogin() ;
    return user_login != "";
}

std::string UserController::getFavoriteUser(){
    return ConfigManager::getInstance().loadAutoLoginUserLogin();
}

void UserController::setFavoriteUser(std::string userLogin){
    ConfigManager::getInstance().setAutoLoginUser(userLogin);
}

void UserController::unsetFavoriteUser(std::string userLogin){
    ConfigManager::getInstance().unsetAutoLoginUser(userLogin);
}

std::vector<std::string> UserController::getLoginList() {
    loadLoginsPassCouples();
    std::vector<std::string> logins;
    for(auto user : userLoginPassCouples)
        logins.push_back(user.first);
    return logins;
}

bool UserController::authentifyUser(std::string userLogin, std::string enteredUserPass){
    std::string hashed_pass = Crypt::generateHashedPass(enteredUserPass);
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

bool UserController::saveCurrentUser(){
   return ConfigManager::getInstance().saveUser(currentUser) != NULL;
}

bool UserController::updateUser(std::string newLogin, std::string newPass){

    std::string hashed_pass = Crypt::generateHashedPass(newPass);

    User *tmp_user = new User(newLogin,hashed_pass);
    for(AbsTarget *tg: currentUser->getFavoriteTargets())
        tmp_user->addFavoriteTarget(tg);

    for(Backup bc : currentUser->getBackups())
        tmp_user->addBackup(bc);

    deleteUser();
    ConfigManager::getInstance().saveUser(tmp_user);

    setCurrentUser(newLogin);
    userLoginPassCouples[newLogin] = hashed_pass;

    delete tmp_user;
    return true;
}

void UserController::deleteUser() {
    ConfigManager::getInstance().deleteUser(getCurrentUserLogin());
    loadLoginsPassCouples();
}

void UserController::loadLoginsPassCouples(){
    userLoginPassCouples = ConfigManager::getInstance().loadLoginPassCouples();
}


