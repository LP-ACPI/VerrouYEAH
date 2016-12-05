//
// Created by Valentin on 05/12/16.
//

#ifndef BACKUP_H
#define BACKUP_H

#include <string>
#include "Data.h"

class Backup {
    std::string name;
    char key [32];
    std::string source;
    std::string target;
    std::string last_save;//TODO type Date
    Data data;
public:
    Backup(std::string name,char* key,std::string source,std::string target,std::string last_save)//TODO
    {}
    void saveData();//TODO sauvegarde des données (data) vers des fichiers .vy
    void recoverData();//TODO chargement des données (data) depuis les fichiers .vy
};


#endif //BACKUP_H
