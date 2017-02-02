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
    char * copyKey = (char*)malloc(sizeof(char)*32);
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
Data Backup::getData() const{
    return data;
}
