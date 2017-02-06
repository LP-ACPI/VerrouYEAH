//
// Created by Valentin on 05/12/16.
//
#include "User.h"
#include <stdexcept>
#include <algorithm>

using namespace std;
using json = nlohmann::json;

User::User(User &user):
        login(user.getLogin()),password(user.getLogin())
{
        setBackups(user.getBackups());
}

Backup User::getBackupAt(const unsigned position){
    if (backups.size() > position){
        list<Backup>::iterator it = backups.begin();
        advance(it, position);
        return *it;
    } else throw invalid_argument("exception: recherche de sauvegarde qui n'existe pas...");
}

void User::addBackup(const Backup backup){
    if(!hasBackup(backup))
        backups.push_back(backup);
}

void User::removeBackup(const Backup backup){
    if(hasBackup(backup))
        backups.remove(backup);
}

string User::getPassword() const
{ return password; }

string User::getLogin() const
{ return login; }

list<Backup> User::getBackups() const
{ return backups; }

void User::setPassword(const std::string newPass)
{ password = newPass; }

void User:: setLogin(const std::string newLogin)
{ login = newLogin; }

void User::removeBackups(){
    backups.clear();
}

void User::replaceBackup(const Backup oldBackup, const Backup newBackup){
    replace(backups.begin(),backups.end(),oldBackup,newBackup);
}


void User::replaceBackupAt(const unsigned position,const Backup newBackup){
    replaceBackup(getBackupAt(position),newBackup);
}

void User::setBackups(const list<Backup> newBackups){
    removeBackups();
    for(Backup bc : newBackups )
        addBackup(bc);
}

bool User::hasBackup(const Backup backup){
    bool found = false;
    for(Backup bc : backups){
        if(bc == backup) {
            found = true;
            break;
        }
    }
    return found;
}

ostream& operator<<(ostream &o, const User &user){
    o << "login" << user.login << endl;
    o << "pass:" << user.password << endl;
    return o;
}

json& operator<<(json &j, const User &user){

    json usersBackupsToPersist = json::array();

        for(Backup bc : user.getBackups()){
            json jsonBc;
            usersBackupsToPersist += jsonBc << bc;
        }

    j = {{user.getLogin(), {
                {"password", user.getPassword()},
                {"backups" , usersBackupsToPersist}
            }
        }};
    return j;
}
