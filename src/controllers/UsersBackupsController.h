#ifndef USERSBACKUPSCONTROLLER_H
#define USERSBACKUPSCONTROLLER_H

#include "../models/User.h"

class UsersBackupsController{

    static UsersBackupsController instance;
    User* user;

    UsersBackupsController()
    { }

public:
    static UsersBackupsController& getInstance(){
        return instance;
    }

    void setUser(std::string);

    User* getUsersBackup() const
    {   return instance.user;    }

    void createUsersBackup(Backup*);
    Backup getUsersBackup(std::string);
    void updateUsersBackup(Backup*);
    void deleteUsersBackup(std::string);
    std::list<Backup> getUsersBackupList();
};

#endif // USERSBACKUPSCONTROLLER_H
