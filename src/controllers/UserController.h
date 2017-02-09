#ifndef USERCONTROLLER_H
#define USERCONTROLLER_H

#include <iostream>
#include "../models/User.h"
#include "../services/ConfigManager.h"
#define CONFIG_FILE "config.json"

class UserController
{
    std::map<std::string,std::string> userLoginPassCouples;
    std::string generateHashedPass(std::string);

    UserController()
    {}

public:

    static UserController& getInstance(){
        ConfigManager::getInstance().setJsonFile(CONFIG_FILE);
        static UserController instance;
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
    void updateUser(std::string,std::string,std::string);
    bool createUser(std::string,std::string);
    void deleteUser(std::string);
};

#endif // USERCONTROLLER_H
