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

    std::string getPassword() const;
    std::string getLogin() const;
    std::list<Backup> getBackups() const;

    Backup getBackupAt(const unsigned);
    Backup getBackupByKey(const std::string);
    void addBackup(const Backup);
    void removeBackup(const Backup);
    void replaceBackupAt(const unsigned,const Backup);
    void replaceBackup(const Backup, const Backup);

    void removeBackups();
    void setBackups(const std::list<Backup>);

    bool hasBackup(const Backup);

    void setPassword(const std::string);
    void setLogin(const std::string);

    friend std::ostream& operator<<(std::ostream&, const User&);
    friend nlohmann::json& operator<<(nlohmann::json&, const User&);
};


#endif //USER_H
