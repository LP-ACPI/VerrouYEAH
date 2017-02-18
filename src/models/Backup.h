//
// Created by Valentin on 05/12/16.
//

#ifndef BACKUP_H
#define BACKUP_H

#include "../services/Crypt.h"
#include <iostream>
#include <string.h>
#include <string>
#include "Data.h"
#include "Directory.h"
#include "Frequency.h"
#include "FtpTarget.h"

#include "../../includes/json.hpp"

class Backup {

    char key[32];
    std::string name;
    std::string lastSave;//TODO type Date -> prop: QDateTime (?) -> créer unu en accord avec Frequency?
    std::string source;
    const AbsTarget *target;
    Frequency frequency;
    const Data* data;
    std::string note;
    bool dataIsLoaded;
    std::string ownerLogPass[2];

    void saveFtpData();
    void restoreFtpData();

    void saveNormalData();
    void restoreNormalData();

public:
    Backup(const Backup&);
    Backup(
            const char* _key = Crypt::genKey(32),
            std::string name="test",
            std::string lastSave= "1/1/1970",
            std::string source="test",
            const AbsTarget *target = NULL,
            Frequency freq = Frequency(),
            const Data *data = NULL,
            std::string note = "test",
            bool data_loaded = false)
        : name(name),
          lastSave(lastSave),
          source(source),
          target(target),
          frequency(freq),
          data(data),
          note(note),
          dataIsLoaded(data_loaded)
    {
        setKey(_key);
    }

    void saveData();//TODO sauvegarde des données (data) vers des fichiers .vy

    void recoverData();//TODO chargement des données (data) depuis les fichiers .vy

    std::string getKey() const;
    std::string getName() const;
    std::string getSource() const;
    const AbsTarget *getTarget() const;
    std::string getLastSave() const;//TODO type Date
    std::string getNote() const;
    Frequency getFrequency() const;
    const Data* getData() const;
    bool hasLoadedData() const;
    std::string getOwnersLogin() const;
    std::string getOwnersPass() const;

    void setKey(const char*);
    void setName(const std::string);
    void setSource(const std::string);
    void setTarget(const AbsTarget*);
    void setLastSave(const std::string);//TODO type Date
    void setNote(const std::string);
    void setFrequency(const Frequency);
    void setData(const Data*);
    void setDataLoaded(const bool);
    void setOwnersLogin(const std::string);
    void setOwnersPass(const std::string);

    bool operator==(const Backup&);
    bool operator!=(const Backup&);
    void operator=(const Backup&);

    friend std::ostream& operator<<(std::ostream&, const Backup&);
    friend nlohmann::json& operator<<(nlohmann::json&, const Backup&);
    nlohmann::json toDistantJson();

};


#endif //BACKUP_H
