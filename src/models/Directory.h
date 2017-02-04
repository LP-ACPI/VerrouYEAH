//
// Created by Valentin on 05/12/16.
//

#ifndef DIRECTORY_H
#define DIRECTORY_H

#include "Data.h"
#include <list>

class Directory : private Data {

    std::list<Data> data;

};


#endif //DIRECTORY_H
