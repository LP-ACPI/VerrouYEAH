//
// Created by Valentin on 05/12/16.
//

#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <fstream>

#include "../models/User.h"
#include "../models/Backup.h"

#include "json.hpp"
using json = nlohmann::json;

class ConfigManager {
    private:
        json config;
        std::string configFilename;
        static ConfigManager instance;

        json jsonifyUser(User*);
        json jsonifyBackup(Backup*);
        json merge(const json&, const json&);

    public:
        ConfigManager(std::string configFilePath = "config.json")
        {
            setUsersJsonFile(configFilePath);
        }
        User* loadUser(std::string);
        std::list<std::string> loadUserList();

        json saveUser(User*);

        void setUsersJsonFile(std::string);
        void persist();

    friend std::ostream& operator <<(std::ostream&, const ConfigManager&);

};

#endif //CONFIG_H
