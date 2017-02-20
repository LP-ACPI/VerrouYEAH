#ifndef BACKUPCONTROLLER_H
#define BACKUPCONTROLLER_H

#include "../models/Backup.h"
#include <json.hpp>

class BackupController
{

    BackupController()
    {}

public:
    static BackupController &getInstance()
    {       static BackupController instance;
            return instance;
    }

    void subscribeObserverToBackup(Observer*,std::string);
    void unsubscribeObserverFromBackup(Observer*,std::string);

    bool updateDataIfAccessible(Backup*);
    void restoreBackupData(std::string);

    bool isBackupFtp(std::string);
    bool hasBackupLoadedData(std::string);

    Backup getBackupFromInfoMap(std::map<std::string,std::string>);
    std::map<std::string,std::string> getInfoMapFromBackup(Backup*);

    void operator=(BackupController const&) = delete;

   nlohmann::json getJsonifiedDataTree(std::string);
};

#endif // BACKUPCONTROLLER_H
