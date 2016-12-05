//
// Created by Valentin on 05/12/16.
//

#ifndef CONFIG_H
#define CONFIG_H

#include <fstream>
#include "json.h"

class Config {
    nlohmann::json config;
public:
    Config()
    {
        std::ifstream conf_file("../VerrouYEAH/src/config.json");
        conf_file >> config;
    }
    std::string toString()
    {
        return config.dump(4);
    }
};


#endif //PROJECT_CONFIG_H
