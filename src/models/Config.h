//
// Created by Valentin on 05/12/16.
//

#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <fstream>
#include "json.h"
#include "User.h"
#include "Backup.h"

class Config {
    nlohmann::json config;
public:
    Config()
    {
        std::ifstream conf_file("config.json");
        conf_file >> config;
    }
    /*
     * Exemple de création d'objet à partir du fichier json
     */
    User* loadUser(std::string login)
    {
        //On se place dans l'objet users,
        //puis à l'intérieur dans l'objet qui a pour cle le login de l'utilisateur en paramètre
        nlohmann::json user_config = config.at("users").at(login);
        //Une fois dans le bon objet json, on recherche la valeur du champ password en type std::string
        std::string password = user_config.at("password").get<std::string>();

        return new User(login,password);
    }
    std::string toString()
    {
        return config.dump(4);
    }
};


#endif //PROJECT_CONFIG_H
