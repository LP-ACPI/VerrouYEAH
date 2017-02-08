#ifndef USERCONTROLLER_H
#define USERCONTROLLER_H

#include <iostream>
#include "../models/User.h"

class UserController
{
    std::map<std::string,std::string> userLoginPassCouples;

    UserController()
    {}

public:

    static UserController& getInstance(){
        static UserController instance;
        return instance;
    }

    void loadLoginsPassCouples();
    bool authentificateUser(User*);

    void createUser(std::string,std::string);
    void updateUser(User*);
    void deleteUser(User*);
};

#endif // USERCONTROLLER_H
