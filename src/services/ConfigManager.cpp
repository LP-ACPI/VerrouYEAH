#include "ConfigManager.h"
#include "../models/Directory.h"
#include "../models/File.h"
#include <QDebug>

using namespace std;

map<string,string>ConfigManager::loadLoginPassList(){

    map<string,string> loginPassList;
    json user_config = readOrInitRootUsers();

    for (json::iterator it = user_config.begin(); it != user_config.end(); ++it){
        string login = it.key();
        string pass = user_config[it.key()]["password"];
        loginPassList[login] = pass;
    }

    return loginPassList;
}

User* ConfigManager::loadUser(string login){

    json user_config;
    try{
        user_config = readOrInitRootUsers().at(login);
    }catch(exception){//TODO: Throw
       cerr << "pas d'utilisateur" << login << endl;
       return NULL;
    }

    string password = user_config["password"];
    User* user      = new User(login,password);

    json backups = user_config["backups"];
    for (json bc : backups) {

        string key = bc["key"];
        string name = bc["name"];
        string sourcePath = bc["src"];
        string targetType = bc["dest"]["type"];
        string targetPath = bc["dest"]["path"];
        //TODO : DateTime format
        string lastSave = bc["last_save"];
        string frequency = bc["freq"];

        Backup backup;
        backup.setKey(key.c_str());
        backup.setName(name);
        backup.setSource(sourcePath);
        backup.setTarget(targetPath);
        backup.setTargetType(targetType);
        backup.setLastSave(lastSave);
        backup.setFrequency(frequency);
        user->addBackup(backup);
    }

    return user ;
}


void ConfigManager::loadUsersBackupData(User *user, string backupKey){

    json users_backup = config.at(user->getLogin())["backups"][backupKey];

    if(users_backup["Data"] != NULL){

        Directory *abstract_root = new Directory(users_backup["Data"]);
        Data *root_data = &abstract_root->getDataAt(0);

        Backup new_backup = user->getBackupByKey(backupKey);
        new_backup.setData(root_data);
        Backup old_backup = user->getBackupByKey(backupKey);
        user->replaceBackup(old_backup,new_backup);
    }
}

void ConfigManager::loadUsersBackupList(User* user){

        json users_backups = config.at(user->getLogin()).at("backups");

        for (json::iterator it = users_backups.begin(); it != users_backups.end(); ++it){

            loadUsersBackupData(user,it.key().c_str());
        }
}


void ConfigManager::setAutoLoginUser(std::string login){
    config["VerrouYeah"]["auto_login"] = login;
    persist();
}

void ConfigManager::unsetAutoLoginUser(){
    config["VerrouYeah"]["auto_login"] = "";
    persist();
}

std::string ConfigManager::loadAutoLoginUserLogin(){
    json app_root = readOrInitAppRoot();
    return app_root["auto_login"];
}

json ConfigManager::saveUser(User *user){
    json jsonUser;
    config["users"] = merge(config["users"],jsonUser << *user);
    persist();
    return jsonUser;
}


void ConfigManager::deleteUser(std::string userLogin) {

    json user_config = readOrInitRootUsers();

    for (json::iterator it = user_config.begin(); it != user_config.end(); ++it)
        if(it.key() == userLogin)
            config.at("users").erase(it.key());
    persist();
}


json ConfigManager::saveUsersBackup(User *user,Backup *backup){

    json jsonBackup = backup->toDistantJson();
    json usersBackups = config[user->getLogin()]["backups"];
    config[user->getLogin()]["backups"] = merge(usersBackups,jsonBackup);
    config[user->getLogin()]["password"] = user->getPassword();
    persist();
    return jsonBackup;
}


void ConfigManager::deleteUsersBackup(string userLogin,string bcKey){
    json users_backups = config.at(userLogin).at("backups");

    for (json::iterator it = users_backups.begin(); it != users_backups.end(); ++it)
        if(it.key() == bcKey)
            config.at(userLogin).at("backups").erase(it.key());
    persist();

}


void ConfigManager::setJsonFile(string newConfigFileName){
    configFilename = newConfigFileName;
    config         = json::object();

    fstream configFile;
    configFile.open(configFilename, fstream::in);
    if(!configFile){
        configFile.open(configFilename, fstream::in | fstream::out | fstream::app);
    } else {
        try{
            configFile >> config;
        }catch(const std::invalid_argument&){}
    }
    configFile.close();
}

void ConfigManager::persist(){
    fstream configFile;
    configFile.open(configFilename, fstream::in | fstream::out | fstream::trunc );
    configFile << setw(2) << config << endl;
    configFile.close();
}

json ConfigManager::merge(const json &a, const json &b)
{
    json result = a.flatten();
    json tmp    = b.flatten();

    for (json::iterator it = tmp.begin(); it != tmp.end(); ++it)
        result[it.key()] = it.value();
    return result.unflatten();
}

json ConfigManager::readOrInitAppRoot(){
    json app_root;
    try{
         app_root = config.at("VerrouYeah");
    }catch(const out_of_range&){
        config["VerrouYeah"]["auto_login"] = "";
        app_root = config.at("VerrouYeah");
    }
    return app_root;
}

json ConfigManager::readOrInitRootUsers(){
    json user_root;
    try{
         user_root = config.at("users");
    }catch(const out_of_range&){
        config["users"] = json({});
        user_root = config.at("users");
    }
    return user_root;
}

ostream& operator<<(ostream &out, const ConfigManager &configuration){
     return out << configuration.config.dump(2);
}
