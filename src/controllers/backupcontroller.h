#ifndef BACKUPCONTROLLER_H
#define BACKUPCONTROLLER_H

#include "../models/Backup.h"

class BackupController
{
    static BackupController instance;

    BackupController()
    {}

public:
    static BackupController getInstance()
    {   return instance; }

    Backup getBackupFromInfoMap(std::map<std::string,std::string>);
    std::map<std::string,std::string> getInfoMapFromBackup(Backup*);


};

#endif // BACKUPCONTROLLER_H
