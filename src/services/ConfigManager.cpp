//
// Created by ryweal on 05/12/16.
//

#include "ConfigManager.h"

using namespace std;

User* ConfigManager::loadUser(string login)
{
    json user_config = config.at("users").at(login);
    string password = user_config.at("password").get<string>();
    User* user = new User(login,password);

    list<json> backups = user_config["backups"];

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
    json user_config = config["users"];
    config["users"] = merge(user_config,jsonUser);
    persist();
    return jsonUser;
}


void ConfigManager::setJsonFile(string newConfigFileName){
    filename = newConfigFileName;
    fstream newConfigFile;
    newConfigFile.exceptions( ifstream::failbit | ifstream::badbit );
    try {
        newConfigFile.open(filename);
        newConfigFile >> config;

    } catch (const ifstream::failure &e) {

        ofstream configFile(filename);
        configFile << setw(2) << config << endl;
        configFile.close();
    }
}

void ConfigManager::persist(){
    fstream configFile(filename);
    configFile << setw(2) << config << endl;
    configFile.close();
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


json ConfigManager::jsonifyUser(User *user){

    json usersBackupsToPersist = json::array();

    for(Backup bc : user->getBackups()){
       usersBackupsToPersist += jsonifyBackup(&bc);
    }

    json jsonUserDetails = {
           {"password", user->getPassword()},
            {"backups" , usersBackupsToPersist}
        };

    return json{{user->getLogin(),jsonUserDetails}};
}

ostream& operator <<(ostream &out, const ConfigManager &configuration){
     return out << configuration.config.dump(2);
}

json ConfigManager::merge(const json &a, const json &b)
{
    json result = a.flatten();
    json tmp = b.flatten();

    for (json::iterator it = tmp.begin(); it != tmp.end(); ++it)
    {
        result[it.key()] = it.value();
    }

    return result.unflatten();
}
