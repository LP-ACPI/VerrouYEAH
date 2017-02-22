#include "ConfigManager.h"
#include "Scheduler.h"
#include "../models/Directory.h"
#include "../models/File.h"
#include "../models/FtpTarget.h"
#include "../models/Target.h"
#include <QDebug>

#define LOCAL_CONFIG_FILE "config.json"

using namespace std;

map<string,string>ConfigManager::loadLoginPassCouples(){

    map<string,string> login_pass_couples;
    json user_config = readOrInitUserRoot();

    for (json::iterator it = user_config.begin(); it != user_config.end(); ++it){
        string login = it.key();
        string pass = user_config[it.key()]["password"];
        login_pass_couples[login] = pass;
    }

    return login_pass_couples;
}

User* ConfigManager::loadUser(string login){

    json user_config;
    try{
        user_config = readOrInitUserRoot().at(login);
    }catch(exception){//TODO: Throw
       cerr << "pas d'utilisateur" << login << endl;
       return NULL;
    }

    string password = user_config["password"];
    User* user      = new User(login,password);

    json favorite_targets = user_config["fav_dests"];

    for (json::iterator it = favorite_targets.begin(); it != favorite_targets.end(); ++it){
        string tag   = it.key();
        string type = favorite_targets[it.key()]["type"];
        string path = favorite_targets[it.key()]["path"];

        if(type == "FTP"){
            FtpTarget* fav_trg =new FtpTarget(tag,path);
            fav_trg->setHost(favorite_targets[it.key()]["host"]);
            fav_trg->setUserName(favorite_targets[it.key()]["username"]);
            fav_trg->setFtpPass(favorite_targets[it.key()]["pass"]);
            fav_trg->setPort(favorite_targets[it.key()]["port"]);
            user->addFavoriteTarget(fav_trg);
        } else {
            Target* fav_trg = new Target(tag,path);
            user->addFavoriteTarget(fav_trg);
        }
    }

    json backups = user_config["backups"];
    for (json bc : backups) {

        string key      = bc["key"];
        string name  = bc["name"];
        string sourcePath = bc["src"];
        string note = bc["note"];
        //TODO : DateTime format
        string lastSave = bc["last_save"];
        string frequency = bc["freq"];
        string targetTag = bc["dest"]["tag"];

        Backup backup(key.c_str());
        backup.setName(name);
        backup.setSource(sourcePath);
        backup.setLastSave(lastSave);
        backup.setNote(note);
        backup.setFrequency(frequency);
        backup.setOwnersLogin(login);
        backup.setOwnersPass(password);
        AbsTarget *target = user->getFavoriteTargetByTag(targetTag);
        backup.setTarget(target);
        backup.loadJsonData();

        user->addBackup(backup);
    }

    return user ;
}

void ConfigManager::setAutoLoginUser(std::string login){
    config["VerrouYeah"]["auto_login"] = login;
    persist();
}

void ConfigManager::unsetAutoLoginUser(std::string userLogin){
    json app_root = readOrInitAppRoot();
    if(app_root["auto_login"] == userLogin)
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

    json user_config = readOrInitUserRoot();

    for (json::iterator it = user_config.begin(); it != user_config.end(); ++it)
        if(it.key() == userLogin)
            config.at("users").erase(it.key());
    unsetAutoLoginUser(userLogin);
    persist();
}

void ConfigManager::updateUser(User *user){
    string login               = user->getLogin();
    json user_config    = readOrInitUserRoot()[login];

    user_config << *user;

    config["users"][login]  = user_config[login];
    persist();
}


Backup* ConfigManager::getUserBackupsData(string login, string backupKey){

     json users_backup = readOrInitUserBackups(login)[backupKey];

    if(users_backup["Data"] != NULL){

        Directory *root_data = new Directory(users_backup["Data"]);
        Backup *new_backup = new Backup(backupKey.c_str());
        new_backup->setDataLoaded(root_data ? true : false);
        new_backup->setData(root_data);
        new_backup->setName(users_backup["name"]);
        new_backup->setLastSave(users_backup["last_save"]);
        new_backup->setNote(users_backup["note"]);
        new_backup->setFrequency("5 * * * *");
        return new_backup;

    }    else
        return NULL;
}

list<Backup*> ConfigManager::getUsersDistantBackupList(User* user){

    json users_backups = readOrInitUserBackups(user->getLogin());
    list<Backup*> backup_list;
    for (json::iterator it = users_backups.begin(); it != users_backups.end(); ++it){

        Backup *new_backup = getUserBackupsData(user->getLogin(),it.key().c_str());
        backup_list.push_back(new_backup);
    }
    return backup_list;
}

json ConfigManager::saveUsersBackupData(Backup *backup){

    json jsonBackup      = backup->toDistantJson();
    json usersBackups   = readOrInitUserBackups(backup->getOwnersLogin());

    config[backup->getOwnersLogin()]["backups"]  = merge(usersBackups,jsonBackup);
    config[backup->getOwnersLogin()]["password"] =backup->getOwnersPass();
    persist();
    return jsonBackup;
}

void ConfigManager::deleteUsersBackupData(string userLogin,string bcKey){
    json users_backups = readOrInitUserBackups(userLogin);

    for (json::iterator it = users_backups.begin(); it != users_backups.end(); ++it)
        if(it.key() == bcKey)
            config.at(userLogin).at("backups").erase(it.key());

    persist();
}

bool ConfigManager::authentifyDistantBackupsOwner(string login, string hashedPass) {
    json user_root;
    bool authOk = false;
    try{
         user_root = config.at(login);
         authOk = user_root["password"]  == hashedPass;
         return authOk;
    }catch(const out_of_range&){
        throw runtime_error("Utilisateur non trouvé! ");
    }
    return false;
}

json ConfigManager::merge(const json &a, const json &b) {
    json result = a.flatten();
    json tmp    = b.flatten();

    for (json::iterator it = tmp.begin(); it != tmp.end(); ++it)
        result[it.key()] = it.value();
    return result.unflatten();
}

void ConfigManager::setJsonFile(string newConfigFileName){
    configFilename = newConfigFileName;
    config         = json::object();

    fstream configFile(configFilename, fstream::in);
    if(!configFile){
        configFile.open(configFilename, fstream::in | fstream::out | fstream::app);
    } else {
        try{
            configFile >> config;
        } catch(const std::invalid_argument &e){
            cerr << "erreur lecture fichier : " << e.what() << endl;
        }
    }
    configFile.close();
}

void ConfigManager::persist(){
    fstream configFile;
    configFile.open(configFilename, fstream::in | fstream::out | fstream::trunc );
    configFile << setw(2) << config << endl;
    configFile.close();
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

json ConfigManager::readOrInitUserRoot(){
    json user_root;
    try{
         user_root = config.at("users");
    }catch(const out_of_range&){
        config["users"] = json({});
        user_root = config.at("users");
    }
    return user_root;
}

json ConfigManager::readOrInitUserBackups(string userLogin){
    json bakups_root;
    try{
         bakups_root = config.at(userLogin).at("backups");
    }catch(const out_of_range&){
        config[userLogin]["backups"] = json::array();
        bakups_root = config.at(userLogin).at("backups");
    }
    return bakups_root;
}

ostream& operator<<(ostream &out, const ConfigManager &configuration){
     return out << configuration.config.dump(2);
}
