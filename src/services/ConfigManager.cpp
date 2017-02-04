//
// Created by ryweal on 05/12/16.
//

#include "ConfigManager.h"

using namespace std;

list<string>ConfigManager::loadUserList(){
    //TODO exception domaine "users" non trouvé à gérer
    list<string> loginList;
    json user_config = config["users"];

    for (json::iterator it = user_config.begin(); it != user_config.end(); ++it){
        loginList.push_back(it.key());
    }
    return loginList;
}

User* ConfigManager::loadUser(string login){
    //TODO exception domaine "users" non trouvé à gérer
    json user_config = config.at("users").at(login);
    string password = user_config.at("password").get<string>();
    User* user = new User(login,password);

    json backups = user_config.at("backups");

    for (json bc : backups)
    {
        string key = bc["key"];
        string name = bc["name"];
        string sourcePath = bc["src"];
        string targetPath = bc["dest"];
        //TODO : DateTime format
        string lastSave = bc["last_save"];

        Backup backup(key.c_str(),name,sourcePath,targetPath,lastSave);
        user->addBackup(backup);
    }
    return user ;
}

json ConfigManager::saveUser(User* user){
    json jsonUser = jsonifyUser(user);
    config["users"] = merge(config["users"],jsonUser);
    persist();
    return jsonUser;
}

void ConfigManager::setUsersJsonFile(string newConfigFileName){
    configFilename = newConfigFileName;
    fstream newConfigFile;
    newConfigFile.exceptions( ifstream::failbit | ifstream::badbit );
    try {
        config = json::object();
        newConfigFile.open(configFilename);
        newConfigFile >> config;

    } catch (const ifstream::failure &e) {
        ofstream configFile(configFilename);
        configFile.close();
    }
}

void ConfigManager::persist(){
    fstream configFile(configFilename);
    configFile << setw(2) << config << endl;
    configFile.close();
}

json ConfigManager::jsonifyUser(User *user){

    //? -> persisté comme 'null' au lieu de '[]' si pas de sauvegardes, normal sinon.
    json usersBackupsToPersist = json::array();

    for(Backup bc : user->getBackups())
        usersBackupsToPersist += jsonifyBackup(&bc);

    json jsonUserDetails = {
            {"password", user->getPassword()},
            {"backups" , usersBackupsToPersist}
        };

    return json{{user->getLogin(),jsonUserDetails}};
}

json ConfigManager::jsonifyBackup(Backup* backup){

    json jsonBackup = {
        {"key", backup->getKey()},
        {"name", backup->getName()},
        {"src", backup->getSource()},
        {"dest", backup->getTarget()},
        {"freq", backup->getLastSave()},
        {"last_save", backup->getLastSave()},
    };
    return jsonBackup;
}

json ConfigManager::merge(const json &a, const json &b)
{
    json result = a.flatten();
    json tmp = b.flatten();

    for (json::iterator it = tmp.begin(); it != tmp.end(); ++it)
        result[it.key()] = it.value();
    return result.unflatten();
}


ostream& operator <<(ostream &out, const ConfigManager &configuration){
     return out << configuration.config.dump(2);
}
