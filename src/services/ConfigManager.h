//
// Created by Valentin on 05/12/16.
//

#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <fstream>

#include "../models/User.h"
#include "../models/Backup.h"
#include <json.hpp>

#define LOCAL_CONFIG_FILE "config.json"

using json = nlohmann::json;

class ConfigManager {

private:
        json config;
        std::string configFilename;

        json readOrInitUserRoot();
        json readOrInitUserBackups(std::string);
        json readOrInitAppRoot();

        ConfigManager()
        {}

        ConfigManager(ConfigManager const&);

public:
        static ConfigManager& getInstance(){
            static ConfigManager instance;
            return instance;
        }

        std::map<std::string,std::string>loadLoginPassCouples();

        json saveUser(User*);
        User* loadUser(std::string);
        void deleteUser(std::string);
        void updateUser(User*);

        json saveUsersBackupData(Backup*);
        Backup* getUserBackupsData(std::string,std::string);
        void deleteUsersBackupData(std::string,std::string);
        std::list<Backup*> getUsersDistantBackupList(User*);

        std::string loadAutoLoginUserLogin();
        void setAutoLoginUser(std::string);
        void unsetAutoLoginUser(std::string);

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
