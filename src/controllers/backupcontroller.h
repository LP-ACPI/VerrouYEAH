#ifndef BACKUPCONTROLLER_H
#define BACKUPCONTROLLER_H

#include "../models/Backup.h"

class BackupController
{
    static BackupController instance;

    BackupController()
    {}

public:
    static BackupController &getInstance()
    {   return instance; }

    void updateBackupData(Backup*);
    void decryptBackup(std::string);

    Backup getBackupFromInfoMap(std::map<std::string,std::string>);
    std::map<std::string,std::string> getInfoMapFromBackup(Backup*);

    void operator=(BackupController const&) = delete;

};

#endif // BACKUPCONTROLLER_H
