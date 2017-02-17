#ifndef BACKUPCONTROLLER_H
#define BACKUPCONTROLLER_H

#include "../models/Backup.h"
#include <json.hpp>

class BackupController
{

    static BackupController instance;
    
    BackupController()
    {}

public:
    static BackupController &getInstance()
    {   return instance; }

    bool updateDataIfAccessible(Backup*);

    void restoreBackupData(std::string);

    bool isBackupFtp(std::string);

    Backup getBackupFromInfoMap(std::map<std::string,std::string>);
    std::map<std::string,std::string> getInfoMapFromBackup(Backup*);

    void operator=(BackupController const&) = delete;

   nlohmann::json getJsonifiedDataTree(std::string);

};

#endif // BACKUPCONTROLLER_H
