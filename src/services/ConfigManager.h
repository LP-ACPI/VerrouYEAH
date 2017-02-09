//
// Created by Valentin on 05/12/16.
//

#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <fstream>

#include "../models/User.h"
#include "../models/Backup.h"

#define LOCAL_CONFIG_FILE "../config.json"
#define DISTANT_BACKUP_CONFIG_FILE "../config_dist.json"
#include <json.hpp>

using json = nlohmann::json;

class ConfigManager {

private:
        json config;
        std::string configFilename;

        json readOrInitRootUsers();
        json readOrInitAppRoot();

        ConfigManager() : configFilename("config.json")
        {}

        ConfigManager(ConfigManager const&);

public:
        static ConfigManager& getInstance(){
            static ConfigManager instance;
            return instance;
        }

        std::map<std::string,std::string>loadLoginPassList();

        User* loadUser(std::string);
        void loadUsersBackupData(User*,std::string);
        void loadUsersBackupList(User*);

        void setFavoriteUser(std::string);
        void unsetFavoriteUser();
        User* loadFavoriteUser();
        json saveUser(User*);
        json saveUsersBackup(User*,Backup*);

        void deleteUser(std::string);
        void deleteUsersBackup(std::string,std::string);

        void setJsonFile(std::string);
        void persist();

        json getConfig() const
        {   return config;  }

        std::string getFilename() const
        {   return configFilename;  }

        json merge(const json&, const json&);
        void operator=(ConfigManager const&)  = delete;
        friend std::ostream& operator<<(std::ostream&, const ConfigManager&);
};

#endif //CONFIG_H
