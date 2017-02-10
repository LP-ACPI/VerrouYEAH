#ifndef USERSBACKUPSCONTROLLER_H
#define USERSBACKUPSCONTROLLER_H

#include "../models/User.h"

class UsersBackupsController{

    User* user;

    UsersBackupsController()
    { }

public:
    static UsersBackupsController& getInstance(){
        static UsersBackupsController instance;
        return instance;
    }

    void setUser(std::string);

    User* getUsersBackup() const
    {   return user;    }

    void createUsersBackup(Backup*);
    Backup getUsersBackup(std::string);
    void updateUsersBackup(Backup*);
    void deleteUsersBackup(std::string);
    std::list<Backup> getUsersBackupList();
};

#endif // USERSBACKUPSCONTROLLER_H
