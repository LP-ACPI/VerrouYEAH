//
// Created by Valentin on 05/12/16.
//

#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>
#include <list>
#include "Backup.h"
#include "absTarget.h"

class User {
    std::string login;
    std::string password;
    std::list<Backup> backups;
    std::list<AbsTarget*> favoriteTargets;
public:
    User(User&);
    User(std::string login="test",std::string pass="test")
        :login(login),password(pass){}

    ~User(){
        for(AbsTarget *tg : getFavoriteTargets())
            delete tg;
    }
    void addFavoriteTarget(AbsTarget*);
    std::list<AbsTarget*> getFavoriteTargets() const;
    void setFavoriteTargets(const std::list<AbsTarget*>);
    AbsTarget* getFavoriteTargetByKey(const std::string);
    AbsTarget* getFavoriteTargetByTag(const std::string);
    void removeFavoriteTarget(AbsTarget*);
    void replaceFavoriteTarget(AbsTarget*, AbsTarget*);
    bool hasFavoriteTarget(AbsTarget*);

    Backup getBackupAt(const unsigned);
    Backup getBackupByKey(const std::string);
    void addBackup( Backup);
    void removeBackup( Backup);
    void replaceBackupAt(const unsigned, Backup);
    void replaceBackup(const Backup,  Backup);
    void removeBackups();
    void setBackups(const std::list<Backup>);
    bool hasBackup(const Backup);
    std::list<Backup> getBackups() const
    { return backups; }

    std::string getPassword() const
    { return password; }
    std::string getLogin() const
    { return login; }

    void setPassword(const std::string newPass)
    { password = newPass; }
    void setLogin(const std::string newLogin)
    { login = newLogin; }

    friend std::ostream& operator<<(std::ostream&, const User&);
    friend nlohmann::json& operator<<(nlohmann::json&, const User&);
};

#endif //USER_H
