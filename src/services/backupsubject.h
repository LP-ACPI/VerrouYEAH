#ifndef BACKUPSUBJECT_H
#define BACKUPSUBJECT_H

#include "Observer.h"
#include "../models/Backup.h"
#include "json.hpp"

using json=nlohmann::json;

class BackupSubject{

    Backup *backup;
    std::vector<Observer*> observerList;

public:
    BackupSubject(Backup *_backup)
        : backup(_backup)
    {}

    void notify(){
        for(Observer *o : observerList)
            o->update(backupData);
    }

    void attach(Observer *o){
        observerList.push_back(o);
    }

    void detach(Observer *o){
        observerList.erase(std::remove(observerList.begin(), observerList.end(), o), observerList.end());
    }

};


#endif // BACKUPSUBJECT_H
