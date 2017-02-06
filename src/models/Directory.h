//
// Created by Valentin on 05/12/16.
//

#ifndef DIRECTORY_H
#define DIRECTORY_H

#include "Data.h"
#include <list>
#include <json.hpp>

class Directory : public Data {

protected:
  // Liste des composants
  std::list< Data* > dataList;

public:
  Directory(const Data &data):Data(data){
      if(data.isDirData()){
          Directory dir = data;
          setDataList(dir.getDataList());
      }

  }//TODO exception

  Directory(const Directory &dir):Data(dir)
  {setDataList(dir.getDataList());}

  Directory(std::string name = "test",
          std::string path = "test")
      : Data(name,path){}

    void addData(Data*);
    void removeData(Data*);
    Data& getDataAt(const unsigned);

    std::list<Data*> getDataList() const;
    void setDataList(const std::list<Data*>);

    bool hasData(const Data*);

    virtual bool isDirData() const override;
    virtual nlohmann::json to_json() const override;

//    void operator=(const Data&);
    void operator=(const Directory&);

};


#endif //DIRECTORY_H
