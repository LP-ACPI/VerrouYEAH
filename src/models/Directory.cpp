//
// Created by Valentin on 05/12/16.
//

#include "Directory.h"
#include "File.h"
#include "../services/ConfigManager.h"
#include <stdexcept>

using namespace std;
using json=nlohmann::json;

//
// Donnée :     un fichier json
// Stratégie :  construit récursivement un arbre formé de Datas (Directory et Files) ayant pour base un Directory (càd l'objet implicite).
//
Directory::Directory(json &jsonData)
{

    for (json::iterator it = jsonData.begin(); it != jsonData.end(); it++){

        bool isAFile = it.key() == "file";

        // Create a new File and add it to the Directory data
        if( isAFile ){

            string fileName = it.value()["name"];
            string filePath = it.value()["path"];
            Data* newData = new File(fileName,filePath);
            addData(newData);

        // Else, create a new Directory and add it to the Directory data
        }else{
            Data* newData = new Directory(it.value()["data"]);
            newData->setPath(it.value()["path"]);
            newData->setName(it.key());
            addData(newData);
        }
    }
}



void Directory::addData(Data *data){
    if(!hasData(data))
        dataList.push_back(data);
}

void Directory::removeData(Data *data){
    if(hasData(data))
        dataList.remove(data);
}

Data& Directory::getDataAt(const unsigned position){
    if (dataList.size() > position){
        list<Data*>::iterator it = dataList.begin();
        advance(it, position);
        return *(*it);
    } else throw invalid_argument("Exception: pas de sous-données!");
}

bool Directory::hasData(const Data *data){
    bool found = false;
    for(auto &dt : dataList){
        if(dt == data) {
            found = true;
            break;
        }
    }
    return found;
}

list<Data*> Directory::getDataList() const {
    return dataList;
}

void Directory::setDataList(const std::list<Data*> newDataList){
    dataList.clear();
    for(Data *dt : newDataList){
        addData(dt);
    }
}


bool Directory::isDirData() const
{return true;}


void Directory::operator=(const Directory &dir){
    setDataList(dir.getDataList());
    setName(dir.getName());
    setPath(dir.getPath());
}

json Directory::to_json() const{
    json dataCol;
    for(Data *data : getDataList())
        dataCol = ConfigManager::getInstance().merge( dataCol, data->to_json() );

    json jOut = json{{getName(), {
                {"path", path},
                {"data", dataCol == NULL ? json::object():dataCol}
          }
    }};
    return jOut;
}


std::ostream& operator<<(std::ostream &o,const Directory &d){
    o << "name: " << d.getName() << " (path:" << d.getPath() << ")" << endl;
    o << "data: " << endl;
         for(Data *data : d.getDataList())
             o << "\t->" << *data;
    return o;
}

