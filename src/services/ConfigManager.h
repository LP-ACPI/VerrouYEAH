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
        json merge(const json&, const json&);

    public:
        ConfigManager(std::string configFilePath = "config.json")
        {
            setJsonFile(configFilePath);
        }
        User* loadUser(std::string);
        std::list<std::string[2]> loadUserList();

        json saveUser(User*);
        json saveUsersBackup(User*,Backup*);
        //TODO loadDistantBackupList(User*)

        void setJsonFile(std::string);
        void persist();
        json getConfig() const;

    friend std::ostream& operator <<(std::ostream&, const ConfigManager&);

};

#endif //CONFIG_H
