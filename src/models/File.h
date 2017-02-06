//
// Created by Valentin on 05/12/16.
//

#ifndef FILE_H
#define FILE_H

#include "Data.h"
#include <json.hpp>


class File : public Data {

public:
    File(const Data &data):Data(data)
    {}
    File(const File &file):Data(file)
    {}

    File(std::string name = "test",
            std::string path = "test"
    ) : Data(name,path){}

    bool isDirData() const override;
    virtual nlohmann::json to_json() const override;

//    void operator=(const Data&);
    void operator=(const File&);
};


#endif //FILE_H
