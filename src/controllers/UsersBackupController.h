#ifndef USERSBACKUPSCONTROLLER_H
#define USERSBACKUPSCONTROLLER_H

#include "../models/User.h"

class UsersBackupController{

    static UsersBackupController instance;

    User* user;

    UsersBackupController()
    { }

public:
    static UsersBackupController& getInstance(){
        return instance;
    }

    void setCurrentUser();

    std::map<std::string,std::string> getUsersBackupInfo(std::string);
    void createUsersBackup(std::map<std::string,std::string>);
    void updateUsersBackup(std::map<std::string,std::string>);
    void deleteUsersBackup(std::string);
    std::list<std::map<std::string,std::string>> getUsersBackupInfoList();
    std::list<std::string> getUsersBackupKeyList();
};

#endif // USERSBACKUPSCONTROLLER_H
