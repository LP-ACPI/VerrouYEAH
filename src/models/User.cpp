//
// Created by Valentin on 05/12/16.
//
#include "User.h"

 using namespace std;

User::User(User &user):
        login(user.getLogin()),password(user.getLogin())
{
        setBackups(user.getBackups());
}

Backup User::getBackupAt(unsigned position){
    if (backups.size() > position){
        list<Backup>::iterator it = backups.begin();
        advance(it, position);
        return *it;
    } else return NULL;
}

void User::addBackup(const Backup backup){
    if(!hasBackup(backup))
        backups.push_back(backup);
}

void User::removeBackup(const Backup backup){
    if(hasBackup(backup))
        backups.remove(backup);
}

string User::getPassword()
{ return password; }

string User::getLogin()
{ return login; }

list<Backup> User::getBackups()
{ return backups; }


void User::setPassword(std::string newPass)
{ password = newPass; }

void User:: setLogin(std::string newLogin)
{ login = newLogin; }

void User::removeBackups(){
    backups.clear();
}

void User::setBackups(list<Backup> newBackups)
{
    for(Backup bc : newBackups )
    {
        addBackup(bc);
    }
}

bool User::hasBackup(Backup backup){
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
