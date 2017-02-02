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
{ backups  = newBackups; }
