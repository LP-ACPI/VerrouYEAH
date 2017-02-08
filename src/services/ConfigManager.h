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
        Data* parseDataFromJson(Data*,json&);

        ConfigManager() : configFilename("config.json")
        {}

        ConfigManager(ConfigManager const&);

public:
        static ConfigManager& getInstance(){
            static ConfigManager instance;
            return instance;
        }

        User* loadUser(std::string);
        std::list<std::string[2]> loadLoginPassList();
        void loadUsersBackups(User*);

        json saveUser(User*);
        json saveUsersBackup(User*,Backup*);
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
