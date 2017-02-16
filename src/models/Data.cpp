//
// Created by Valentin on 05/12/16.
//

#include "Data.h"
#include "Directory.h"
#include "File.h"

using namespace std;

Data::Data(const Data &data)
    : name(data.getName()),path(data.getPath())
{}

string Data::getPath() const{
    return this->path;
}
string Data::getName() const{
    return this->name;
}
void Data::setPath(const string path){
    this->path = path;
}
void Data::setName(const string name){
    this->name = name;
}

bool Data::operator==(const Data &data){
    return (name==data.getName() && path == data.getPath());
}

bool Data::operator!=(const Data &data){
    return !(operator ==(data));
}

ostream& operator<<(ostream &out, const Data &data){
    return out << data << endl;
}

nlohmann::json& operator<<(nlohmann::json &j, Data &data){
    j = data.to_json();
    return j;
}
