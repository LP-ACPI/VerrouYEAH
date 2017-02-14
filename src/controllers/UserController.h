#ifndef USERCONTROLLER_H
#define USERCONTROLLER_H

#include <iostream>
#include "../models/User.h"
#include "../services/ConfigManager.h"

class UserController
{
    static UserController instance;

    std::map<std::string,std::string> userLoginPassCouples;
    void loadLoginsPassCouples();

    UserController()
    {}

    User *currentUser;

public:

    static UserController& getInstance(){
        return instance;
    }

    std::vector<std::string> getLoginList() {
        instance.loadLoginsPassCouples();
        std::vector<std::string> logins;
        for(auto user : userLoginPassCouples)
            logins.push_back(user.first);
        return logins;
    }

    bool authentifyUser(std::string, std::string);

    bool favoriteUserExists();
    std::string getFavoriteUser();
    void setFavoriteUser(std::string);
    void unsetFavoriteUser(std::string);

    std::string getCurrentUserLogin() const
    {   return currentUser->getLogin(); }

    User* getCurrentUser() const
    {   return currentUser; }

    std::string getCurrentUserPass() const
    {   return currentUser->getPassword(); }

    void setCurrentUser(std::string);

    bool updateUser(std::string,std::string);
    bool createUser(std::string,std::string);
    void deleteUser();

    void operator=(UserController const&) = delete;
};

#endif // USERCONTROLLER_H
