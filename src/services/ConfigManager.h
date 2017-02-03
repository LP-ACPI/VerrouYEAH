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
        std::string filename;

        json jsonifyUser(User*);
        json jsonifyBackup(Backup*);
        json merge(const json&, const json&);

    public:
        ConfigManager(std::string configFilePath = "config.json")
        {
            setJsonFile(configFilePath);
        }

        User* loadUser(std::string);
        Backup loadBackup(std::string);

        json saveUser(User*);

        void setJsonFile(std::string);
        void persist();

    friend std::ostream& operator <<(std::ostream&, const ConfigManager&);
};


#endif //CONFIG_H
