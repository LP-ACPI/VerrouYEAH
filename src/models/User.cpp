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
    if (backups.size() > position)
    {
        std::list<Backup>::iterator it = backups.begin();
        std::advance(it, position);
        return *it;
    } else return NULL;

}

void User::addBackup(const Backup &backup){
    backups.push_back(backup);
}

void User::removeBackup(const Backup backup){
    backups.remove(backup);
}

string User::getPassword()
{ return password; }

string User::getLogin()
{ return login; }

std::list<Backup> User::getBackups()
{ return backups; }

void User::setPassword(std::string newPass)
{ password = newPass; }

void User:: setLogin(std::string newLogin)
{ login = newLogin; }

void User::setBackups(std::list<Backup> newBackups)
{

    for(Backup bc : newBackups )
    {
        addBackup(bc);
    }

}

ostream& operator<<(ostream &o, const User &user){
    o << "login" << user.login << endl;
    o << "pass:" << user.password << endl;
    return o;
}
