//
// Created by Valentin on 05/12/16.
//

#include "File.h"

using namespace std;
using json=nlohmann::json;

bool File::isDirData() const
{return false;}


json File::to_json() const {
    json j = json{{name, {
                {"path", path},
                {"type", "file"},
            }}
        };
    return j;
}

void File::operator=(const File &file){
    cout << "data = file" << endl;
    name = file.getName();
    path = file.getPath();
}

std::ostream&operator<<(std::ostream &o,const File &f){
    o << "name: " << f.getName() << " (path:" << f.getPath() << ")" << endl;

    return o;
}


