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
    User(std::string login="test",std::string pass="test")
        :login(login),password(pass){}
    User(User&);

    std::string getPassword();
    std::string getLogin();
    std::list<Backup> getBackups();

    void setPassword(std::string);
    void setLogin(std::string);
    void setBackups(std::list<Backup>);
};


#endif //USER_H
