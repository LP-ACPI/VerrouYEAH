//
// Created by Valentin on 05/12/16.
//

#ifndef BACKUP_H
#define BACKUP_H

#include <iostream>
#include <string.h>
#include <string>
#include "Data.h"
#include "Directory.h"
#include "Frequency.h"
#include "../services/Crypt.h"

#include "json.hpp"

class Backup {


    enum target_type{
        normal = 0,
        ftp = 1
    };
    static const char *target_type_tag[];

    char key[32];
    std::string name;
    std::string source;
    std::string target;
    std::string targetType;
    std::string lastSave;//TODO type Date
    Frequency frequency;
    const Data* data;
    std::string note;

public:
    Backup(const Backup&);
    Backup(
            const char* key = "null",
            std::string name="test",
            std::string source="test",
            std::string target = "test",
            std::string targetType = target_type_tag[target_type::normal],
            std::string lastSave= "1/1/1970",
            Frequency freq = Frequency(),
            std::string note = "test",
            const Data *data = NULL)
        : name(name),
          source(source),
          target(target),
          targetType(targetType),
          lastSave(lastSave),
          frequency(freq),
          data(data),
          note(note)
    {
        if(strcmp("null",key) == 0)
            memcpy(this->key,Crypt::genKey(32),32);
        else
            strcpy(this->key,key);
    }
    Backup(std::string,std::string,std::string,std::string,std::string,Frequency,Data*);

    void saveData();//TODO sauvegarde des données (data) vers des fichiers .vy

    void recoverData();//TODO chargement des données (data) depuis les fichiers .vy

    std::string getKey() const;
    std::string getName() const;
    std::string getSource() const;
    std::string getTarget() const;
    std::string getTargetType() const;
    std::string getLastSave() const;//TODO type Date
    Frequency getFrequency() const;
    const Data* getData() const;
    std::string getNote() const;

    void setKey(const char*);
    void setName(const std::string);
    void setSource(const std::string);
    void setTarget(const std::string);
    void setTargetType(const std::string);
    void setLastSave(const std::string);//TODO type Date
    void setFrequency(const Frequency);
    void setData(const Data*);
    void setNote(const std::string);


    bool operator==(const Backup&);
    bool operator!=(const Backup&);
    void operator=(const Backup&);

    friend std::ostream& operator<<(std::ostream&, const Backup&);
    friend nlohmann::json& operator<<(nlohmann::json&, const Backup&);
    nlohmann::json toDistantJson();

};


#endif //BACKUP_H
