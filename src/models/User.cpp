//
// Created by Valentin on 05/12/16.
//
#include "User.h"
#include "../services/ConfigManager.h"
#include "../services/Scheduler.h"
#include <stdexcept>
#include <algorithm>

using namespace std;
using json = nlohmann::json;

User::User(User &user):
        login(user.getLogin()),password(user.getPassword())
{
        setBackups(user.getBackups());
}

void User::addFavoriteTarget(AbsTarget *favTarget){
    if(!hasFavoriteTarget(favTarget))
        favoriteTargets.push_back(favTarget);
    else throw invalid_argument("Il existe déja une destination du même nom...");
    return;
}

list<AbsTarget*> User::getFavoriteTargets() const{
    return favoriteTargets;
}

void User::setFavoriteTargets(const std::list<AbsTarget*> favTargetList){
    favoriteTargets.clear();
    for(AbsTarget *favTarget : favTargetList )
        addFavoriteTarget(favTarget);
}

AbsTarget *User::getFavoriteTargetByTag(const std::string tag){
    for(AbsTarget* targ : getFavoriteTargets())
        if(tag == targ->getTag())
            return targ;

    throw invalid_argument("exception: recherche de destination qui n'existe pas...");
}

void User::replaceFavoriteTarget(AbsTarget *oldTarget, AbsTarget *newTarget){
    if(!hasFavoriteTarget(newTarget)){
        replace(favoriteTargets.begin(),favoriteTargets.end(),oldTarget,newTarget);

        for(auto backup = backups.begin();backup != backups.end();++backup)
            if(backup->getTarget() == oldTarget)
                    backup->setTarget(newTarget);
    }
    else throw invalid_argument("il existe déjà une autre destination de ce nom...");

}

void User::removeFavoriteTarget(AbsTarget *favTarget){
    for(Backup bc : getBackups() )
        if(favTarget == bc.getTarget())
            throw std::invalid_argument("Cette cible est utilisée par " +bc.getName());

    if(hasFavoriteTarget(favTarget))
        favoriteTargets.remove(favTarget);
}

bool User::hasFavoriteTarget(AbsTarget *favTarget){
    bool found = false;
    for(AbsTarget *favT : favoriteTargets){
        if(favT->getTag() == favTarget->getTag()) {
            found = true;
            break;
        }
    }
    return found;
}


Backup* User::getBackupByKey(const string key){
    list<Backup>::iterator it = backups.begin();
    while(key != it->getKey() && it != backups.end())
        ++it;
    if(it != backups.end())
        return &(*it);
    else
        throw invalid_argument("exception: recherche de sauvegarde qui n'existe pas...");
    return NULL;
}

void User::addBackup( Backup &backup){
    if(!hasBackup(backup)){
        backups.push_back(backup);
        Scheduler::getInstance().add(backup);
        backup.saveData();
    }
    else throw invalid_argument("cette sauvegarde existe déjà...");
}

void User::removeBackup(Backup &backup){
    if(hasBackup(backup)){
        backups.remove(backup);
        Scheduler::getInstance().remove(backup);
    }
}

void User::removeBackups(){
    backups.clear();
}

void User::replaceBackup(const Backup &oldBackup,  Backup &newBackup){
    for(auto it = backups.begin(); it != backups.end(); ++it)
        if(oldBackup.getKey() == it->getKey()){
            (*it) = newBackup;
            Scheduler::getInstance().replace(*it,newBackup);
        }
}

void User::setBackups(const list<Backup> newBackups){
    removeBackups();
    for(Backup bc : newBackups )
        addBackup(bc);
}

bool User::hasBackup(const Backup backup){
    bool found = false;
    for(Backup bc : backups){
        if(bc.getName() == backup.getName()) {
            found = true;
            break;
        }
    }
    return found;
}

ostream& operator<<(ostream &o, const User &user){
    o << "login: " << user.login << endl;
    o << "pass: " << user.password << endl;
    o << "backups: " << endl;
    for(Backup backup : user.getBackups())
        o << "\t" << backup << endl;
    return o;
}

json& operator<<(json &j, const User &user){

    json favoriteTargets;

    for(AbsTarget *fvT : user.getFavoriteTargets()){
        json jFavTarg;
        jFavTarg << *fvT;
        favoriteTargets = ConfigManager::getInstance().merge(favoriteTargets,jFavTarg );
    }

    json usersBackupsToPersist = json::array();

    for(Backup bc : user.getBackups()){
        json jsonBc;
        usersBackupsToPersist += jsonBc << bc;
    }

    j = {{user.getLogin(), {
                {"password", user.getPassword()},
                {"fav_dests" , favoriteTargets},
                {"backups" , usersBackupsToPersist}
            }
        }};
    return j;
}
