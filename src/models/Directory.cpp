//
// Created by Valentin on 05/12/16.
//

#include "Directory.h"
#include "File.h"
#include "../services/ConfigManager.h"
#include <stdexcept>
#include <QDir>
#include <QDebug>
#include <QDirIterator>

using namespace std;
using json = nlohmann::json;


Directory::Directory(const Directory &dir)
    : Data(dir){

    setDataList(dir.getDataList());
}


/**
 * @brief Directory::Directory
 * @param nlohmann::json jsonDataTree
 *
 * Stratégie :  construit récursivement un arbre
 *      formé de Datas (Directory et Files) ayant pour base
 *      un Directory (càd l'objet implicite)
 */
Directory::Directory(json &jsonDataTree){
    for (json::iterator it = jsonDataTree.begin(); it != jsonDataTree.end(); it++){
        string type  = it.value()["type"];
        bool isADir = type == "dir";

        string dataName = it.key();
        string dataPath = it.value()["path"];
        if( isADir ){
            setName(dataName);
            setPath(dataPath);
            Data* newData = new Directory(it.value()["data"]);
            addData(newData);
        }else{
            Data* newData = new File(dataName,dataPath);
            addData(newData);
        }
    }
}

/**
 * @brief Directory::Directory
 * @param QString : rootDirTree
 *
 * Comme c++ standard n'as pas de notion concrète de dossier
 * (sans lib de type boost ou l'API Windows. Mais Qt fait le boulot)
 * ce constructeur parcours récursivement un dossier dont le chemin est passé en paramètre
 * pour s'enregistrer ses données.
 */
Directory::Directory(QFileInfo &rootDirTree,string rootPath){

    if(rootDirTree.isDir()){

        rootPath += rootDirTree.absolutePath().toStdString() +"/";

        QDir dir(rootDirTree.filePath());
        setName(rootDirTree.fileName().toStdString());
        setPath(rootPath);
        const QFileInfoList element_list = dir.entryInfoList();

        for (QFileInfo el_info : element_list) {
            if (el_info.fileName() != ".." && el_info.fileName() != ".") {
                if (el_info.isFile()){
                    string file_name = el_info.fileName().toStdString();
                    string file_path = rootPath+file_name;
                    Data *sub_data   = new File(file_name,file_path);
                    addData(sub_data);
                } else {
                    Data *sub_data = new Directory(el_info,rootPath);
                    addData(sub_data);
                }
            }
        }
    } else {
        cerr << rootPath << " n'est pas un repertoire!" << endl;
    }
}

void Directory::addData(Data *data){
    if(!hasData(data)){
        dataList.push_back(data);
    }
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

list<Data*> Directory::getDataList() const
{    return dataList;   }

void Directory::setDataList(const std::list<Data*> newDataList){
    dataList.clear();
    for(Data *dt : newDataList){
        addData(dt);
    }
}

bool Directory::isDirData() const
{   return true;    }


void Directory::operator=(const Directory &dir){
    setDataList(dir.getDataList());
    setName(dir.getName());
    setPath(dir.getPath());
}

json Directory::to_json() const{
    json dataCol;
    for(Data *data : getDataList()){
        dataCol = ConfigManager::getInstance().merge( dataCol , data->to_json());
    }

    json jOut = json{{getName(), {
                {"type", "dir"},
                {"path", path},
                {"data", dataCol}
          }
    }};
    return jOut;
}


std::ostream&operator<<(std::ostream &o,const Directory &d){
    o << "name: " << d.getName() << " (path:" << d.getPath() << ")" << endl;
    o << "data: " << endl;
         for(Data *data : d.getDataList())
             o << "\t->" << *data;
    return o;
}

