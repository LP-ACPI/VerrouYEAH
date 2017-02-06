#ifndef MAINTESTS
#define MAINTESTS

#include "persistancetest.hpp"
#include "usertest.hpp"
#include "datatest.hpp"


using namespace std;

int main()
{

    UserTest::executeTests();
    PersistanceTest::executeTests();
    DataTest::executeTests();

    UnitTest<void*>::results();

}


#endif
