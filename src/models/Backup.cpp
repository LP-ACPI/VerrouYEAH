//
// Created by Valentin on 05/12/16.
//
#include "Backup.h"

using namespace std;

Backup::Backup(const Backup &backupToCopy)
    : name(backupToCopy.getName()),
      source(backupToCopy.getSource()),
      target(backupToCopy.getTarget()),
      last_save(backupToCopy.getLastSave())
{
    strcpy(key, backupToCopy.getKey());
}

char* Backup::getKey() const{
    char * copyKey = (char*) malloc(sizeof(char)*32);
    strcpy(copyKey,key);
    return copyKey;
}
string Backup::getName() const{
    return name;
}

string Backup::getSource() const{
    return source;
}
string Backup::getTarget() const{
    return target;
}
string Backup::getLastSave() const{
    //TODO type Date
    return last_save;
}
Frequency Backup::getFrequency() const{
    return frequency;
}
Data Backup::getData() const{
    return data;
}


bool Backup::operator==(const Backup &backup){
    return (strcmp(key, backup.getKey())==0);
}


bool Backup::operator!=(const Backup &backup){
    return !operator==(backup);
}

void Backup::operator=(const Backup &backup){
    strcpy(key,backup.getKey());
    data = backup.getData();
    name = backup.getName();
    source = backup.getSource();
    target = backup.getTarget();
    last_save = backup.getLastSave();
    frequency = backup.getFrequency();
}

ostream& operator<<(ostream &out, const Backup &backup){
    out << "nom: " << backup.name << endl;
    out << "\tclé: " << backup.key << endl;
    out << "\tsource: " << backup.source << endl;
    out << "\tdestination: " << backup.target << endl;
    return out;
}

