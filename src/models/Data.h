//
// Created by Valentin on 05/12/16.
//

#ifndef DATA_H
#define DATA_H

#include <iostream>
#include <list>
#include "../../includes/json.hpp"

class Data {

protected:
    std::string name;
    std::string path;

public:
    Data(const Data&);

    Data(std::string name = "test",
      std::string path = "test")
        : name(name),path(path)
    {}

    virtual ~Data() {}

    virtual bool isDirData() const = 0;
    virtual nlohmann::json to_json() const = 0;

    std::string getPath() const;
    std::string getName() const;

    void setPath(const std::string);
    void setName(const std::string);

    bool operator==(const Data&);
    bool operator!=(const Data&);

    friend std::ostream& operator<<(std::ostream &, const Data &);
    friend nlohmann::json& operator<<(nlohmann::json&, Data&);

};

#endif //PROJECT_DATA_H
