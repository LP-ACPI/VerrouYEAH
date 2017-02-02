//
// Created by Valentin on 05/12/16.
//

#ifndef BACKUP_H
#define BACKUP_H

#include <string.h>
#include <string>
#include "Data.h"

class Backup {
    char key[32];
    std::string name;
    std::string source;
    std::string target;
    std::string last_save;//TODO type Date
    Data data;

public:
    Backup(const Backup&);
    Backup(
            std::string name="test",
            char* key= (char*)malloc(sizeof(char)*32),
            std::string source="test",
            std::string target = "test"
            ,std::string last_save= "1/1/1970")
        : name(name),source(source),target(target),last_save(last_save)
    {
        strcpy(this->key,key);
    }

    void saveData();//TODO sauvegarde des données (data) vers des fichiers .vy

    void recoverData();//TODO chargement des données (data) depuis les fichiers .vy

    char* getKey() const;
    std::string getName() const;
    std::string getSource() const;
    std::string getTarget() const;
    std::string getLastSave() const;//TODO type Date
    Data getData() const;
};


#endif //BACKUP_H
