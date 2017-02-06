//
// Created by ryweal on 05/12/16.
//

#include "ConfigManager.h"

using namespace std;

list<string[2]>ConfigManager::loadUserList(){
    list<string[2]> loginPassList;
    json user_config = config["users"];

    for (json::iterator it = user_config.begin(); it != user_config.end(); ++it){
        string login = it.key();
        string pass = user_config[it.key()]["password"];
        loginPassList.push_back({login,pass});
    }
    return loginPassList;
}

User* ConfigManager::loadUser(string login){
    json user_config =  config["users"][login];
    string password = user_config["password"];
    User* user = new User(login,password);

    json backups = user_config["backups"];
    for (json bc : backups)
    {
        string key = bc["key"];
        string name = bc["name"];
        string sourcePath = bc["src"];
        string targetType = bc["dest"]["type"];
        string targetPath = bc["dest"]["path"];
        //TODO : DateTime format
        string lastSave = bc["last_save"];

        Backup backup(key.c_str(),name,sourcePath,targetPath,targetType,lastSave);
        user->addBackup(backup);
    }
    return user ;
}

json ConfigManager::saveUser(User *user){
    json jsonUser;
    config["users"] = merge(config["users"],jsonUser << *user);
    persist();
    return jsonUser;
}

json ConfigManager::saveUsersBackup(User *user,Backup *backup){
    json  jsonBackup = backup->toDistantJson();
    config[user->getLogin()]["backups"] += jsonBackup;
    config[user->getLogin()]["password"] = user->getPassword();
    persist();
    return jsonBackup;
}

void ConfigManager::setJsonFile(string newConfigFileName){
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
