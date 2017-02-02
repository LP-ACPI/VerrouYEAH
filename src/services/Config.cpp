//
// Created by ryweal on 05/12/16.
//

#include "Config.h"

User* Config::loadUser(std::string login)
{

    //On se place dans l'objet users,
    //puis à l'intérieur dans l'objet qui a pour cle le login de l'utilisateur en paramètre
    json user_config = config.at("users").at(login);
    //Une fois dans le bon objet json, on recherche la valeur du champ password en type std::string
    std::string password = user_config.at("password").get<std::string>();

    return new User(login,password);
}

 std::ostream& operator <<(std::ostream &out, const Config &configuration){
     return out << configuration.config.dump(4);
}

