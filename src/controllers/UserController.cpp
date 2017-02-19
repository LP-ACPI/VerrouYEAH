#include "UserController.h"
#include "../services/ConfigManager.h"
#include "../services/Crypt.h"
#include "../services/Scheduler.h"

void UserController::setCurrentUser(std::string login)
{
    currentUser = ConfigManager::getInstance().loadUser(login);

    //Lancement du scheduler au chargement de l'utilisateur
    Scheduler s = Scheduler::getInstance();
    s.clear();
    s.addFromUser(currentUser);
    s.start();
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
        std::list<Backup>::iterator it = currentUser->getBackups().begin();
        while(it != currentUser->getBackups().end()){
            it->setOwnersLogin(newLogin);
            it->setOwnersPass(hashed_pass);
            ++it;
        }
    }
    return update_user;
}

void UserController::deleteUser() {
    ConfigManager::getInstance().deleteUser(getCurrentUserLogin());
    loadLoginsPassCouples();
}

void UserController::loadLoginsPassCouples(){
    userLoginPassCouples = ConfigManager::getInstance().loadLoginPassCouples();
}


