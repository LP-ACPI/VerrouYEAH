//
// Created by Valentin on 05/12/16.
//

#ifndef FILE_H
#define FILE_H

#include "Data.h"
#include <json.hpp>


class File : public Data {

public:
    File(const File &file):Data(file)
    {}

    File(std::string name = "test",
            std::string path = "test"
    ) : Data(name,path){}

    bool isDirData() const override;
    virtual nlohmann::json to_json() const override;
    virtual Data* from_json(const nlohmann::json) override;

    void operator=(const File&);
    friend std::ostream& operator<<(std::ostream&,const Data&);
//    friend Data& operator>>(const nlohmann::json&, Data&);
};


#endif //FILE_H
