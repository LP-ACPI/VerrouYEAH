//
// Created by Valentin on 05/12/16.
//

#ifndef DIRECTORY_H
#define DIRECTORY_H

#include "Data.h"
#include <list>
#include <QFileInfo>
#include <json.hpp>
using json=nlohmann::json;

class Directory : public Data {

protected:
  // Liste des composants
  std::list< Data* > dataList;

public:

  Directory(const Directory&);

  Directory(json&);

  Directory(QFileInfo&,std::string rootPath = "");

  Directory(std::string name = "test",
          std::string path = "test")
      : Data(name,path)
  {}

  ~Directory(){
        for(Data *dt : getDataList())
            delete dt;
  }
    void addData(Data*);
    void removeData(Data*);
    Data& getDataAt(const unsigned);

    std::list<Data*> getDataList() const;
    void setDataList(const std::list<Data*>);

    bool hasData(const Data*);

    virtual bool isDirData() const override;
    virtual nlohmann::json to_json() const override;

    void operator=(const Directory&);

};


#endif //DIRECTORY_H
