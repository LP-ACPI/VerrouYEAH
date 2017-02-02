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

class Config {

    json config;

public:
    Config(std::string configFilePath = "config.json")
    {
        std::ifstream conf_file(configFilePath);
        conf_file >> config;
    }

    User* loadUser(std::string);

    friend std::ostream& operator <<(std::ostream&, const Config&);
};


#endif //CONFIG_H
