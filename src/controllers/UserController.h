#ifndef USERCONTROLLER_H
#define USERCONTROLLER_H

#include <iostream>
#include "../models/User.h"
#include "../services/ConfigManager.h"
#define CONFIG_FILE "config.json"

class UserController
{
    static UserController instance;

    std::map<std::string,std::string> userLoginPassCouples;
    std::string generateHashedPass(std::string);

    UserController()
    {}

    User *currentUser;

public:

    static UserController& getInstance(){
        ConfigManager::getInstance().setJsonFile(CONFIG_FILE);
        return instance;
    }
    void loadLoginsPassCouples();

    std::vector<std::string> getLoginList() {
        std::vector<std::string> logins;
        for(auto user : userLoginPassCouples)
            logins.push_back(user.first);
        return logins;
    }

    bool authentifyUser(std::string, std::string);

    bool favoriteUserExists();
    std::string getFavoriteUser();
    void setFavoriteUser(std::string);
    void unsetFavoriteUser();

    std::string getCurrentUserLogin() const
    {   return instance.currentUser->getLogin(); }

    std::string getCurrentUserPass() const
    {   return instance.currentUser->getPassword(); }

    void setCurrentUser(std::string);

    bool updateUser(std::string,std::string);
    bool createUser(std::string,std::string);
    void deleteUser();
};

#endif // USERCONTROLLER_H
