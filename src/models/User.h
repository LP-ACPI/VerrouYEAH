//
// Created by Valentin on 05/12/16.
//

#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>
#include <list>
#include "Backup.h"

class User {
    std::string login;
    std::string password;
    std::list<Backup> backups;
public:
    User(User&);
    User(std::string login="test",std::string pass="test")
        :login(login),password(pass){}

    std::string getPassword();
    std::string getLogin();
    std::list<Backup> getBackups();

    Backup getBackupAt(unsigned);
    void addBackup(const Backup);
    void removeBackup(const Backup);

    void removeBackups();
    void setBackups(std::list<Backup>);

    bool hasBackup(const Backup);

    void setPassword(std::string);
    void setLogin(std::string);


    friend std::ostream& operator<<(std::ostream&, const User&);
};


#endif //USER_H
