//
// Created by Valentin on 05/12/16.
//
#include "Backup.h"
#include <sstream>

using namespace std;
using json = nlohmann::json;

const char* Backup::target_type_tag[2] = {"NORMAL","FTP"};

Backup::Backup(const Backup &backupToCopy)
    : name(backupToCopy.getName()),
      source(backupToCopy.getSource()),
      target(backupToCopy.getTarget()),
      targetType(backupToCopy.getTargetType()),
      lastSave(backupToCopy.getLastSave()),
      data(backupToCopy.getData())
{
    strcpy(key, backupToCopy.getKey().c_str());
}

//Utile?
Backup::Backup(string name,
               string src,
               string destPath,
               string destType,
               string lastSave,//TODO type Date
               Frequency frequency,
               Data *data)
        : name(name), source(src), target(destPath), targetType(destType),
          lastSave(lastSave),frequency(frequency), data(data)
{
    setKey(Crypt::genKey(32));
}

void Backup::saveData(){
    //TODO sauvegarde des données (data) vers des fichiers .vy
}

void Backup::recoverData(){
    //TODO chargement des données (data) depuis les fichiers .vy
}

string Backup::getKey() const {
    return string(key);
}

string Backup::getName() const
{    return name;   }

string Backup::getSource() const
{    return source; }

string Backup::getTarget() const
{    return target; }

string Backup::getTargetType() const
{    return targetType; }

string Backup::getLastSave() const{
    //TODO type Date
    return lastSave;
}

Frequency Backup::getFrequency() const
{    return frequency;   }

const Data* Backup::getData() const
{    return this->data;  }

string Backup::getNote() const
{    return this->note;  }

void Backup::setKey(const char* key)
{    memcpy(this->key,key,32);     }

void Backup::setName(const string name)
{    this->name = name;      }

void Backup::setSource(const string sourcePath)
{    this->source = sourcePath;     }

void Backup::setTarget(const string targetPath)
{    this->target = targetPath;     }

void Backup::setTargetType(const string targetType)
{    this->targetType = targetType;     }

void Backup::setLastSave(const string lastSave){
    //TODO type Date
    this->lastSave = lastSave;
}

void Backup::setFrequency(const Frequency frequency)
{    this->frequency = frequency;  }

void Backup::setData(const Data *data)
{    this->data = data;     }

void Backup::setNote(const string note)
{   this->note = note;  }

bool Backup::operator==(const Backup &backup){
    return (strcmp(key, backup.getKey().c_str())==0);
}

bool Backup::operator!=(const Backup &backup){
    return !operator==(backup);
}

void Backup::operator=(const Backup &backup){
    strcpy(key,backup.getKey().c_str());
    name        = backup.getName();
    source      = backup.getSource();
    target      = backup.getTarget();
    targetType  = backup.getTargetType();
    lastSave    = backup.getLastSave();
    frequency   = backup.getFrequency();
    data        = backup.getData();
    note        = backup.getNote();
}

ostream& operator<<(ostream &out, const Backup &backup){
    out << "nom: " << backup.name << endl;
    out << "\tclé: " << backup.key << endl;
    out << "\tsource: " << backup.source << endl;
    out << "\tdestination: " << backup.target << endl;
//    out << "\tracine data: " << *backup.data << endl;
    return out;
}


json& operator<<(json &j, const Backup &backup){
    j = {
            {"key", backup.getKey()},
            {"name", backup.getName()},
            {"src", backup.getSource()},
            {"dest",{
                    {"type",backup.getTargetType()},
                    {"path", backup.getTarget()}
                }
            },
            {"freq", backup.getFrequency().toString()},
            {"last_save", backup.getLastSave()},
            {"note", backup.getNote()},
    };
    return j;
}

json Backup::toDistantJson(){
    json jData = data == NULL ? json::object():data->to_json();

    json jOut = json{{
            key,{
                {"name", name},
                {"Data", jData}
            }
    }};
    return jOut ;
}

