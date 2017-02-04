#ifndef MAINTESTS
#define MAINTESTS

#include "persistancetest.hpp"
#include "usertest.hpp"

using namespace std;

int main()
{

    UserTest::executeTests();
    PersistanceTest::executeTests();

    UnitTest<void*>::results();

}


#endif
