//
// Created by Valentin on 05/12/16.
//

#ifndef USER_H
#define USER_H

#include <string>
#include <list>
#include "Backup.h"

class User {
    std::string login;
    std::string password;
    std::list<Backup> backups;
public:
    User(std::string log,std::string pass):
            login(log),password(pass)
    {}
};


#endif //USER_H
