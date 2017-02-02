#ifndef UNITTEST_H
#define UNITTEST_H
#include <iostream>
#include <sstream>

class TestInfo { //nécéssaire car template initialise ses statiques à chaque spécif. de T
protected:
    static int countTests;
    static int countPassed;
    static std::stringstream msg;
};

int TestInfo::countTests = 0;
int TestInfo::countPassed = 0;
std::stringstream TestInfo::msg;

template <class T> class UnitTest : private TestInfo {

public:

    void static assertTrue(bool expression){
        msg << "(test n°" << ++countTests << ") : " ;
        if(expression){
            msg << "OK" << std::endl;
            countPassed++;
        }
        else
            msg << "FAIL - Attendu TRUE. Reçu FALSE" << std::endl;
    }

     void static assertFalse(bool expression){ 
        msg << "(test n°" << ++countTests << ") : " ;
        if(!expression){
            msg << "OK" << std::endl;
            countPassed++;
        }else
             msg << "FAIL - Attendu FALSE. Reçu TRUE" << std::endl;
    }

     void static assertEquals(T objectExpected,T objectTested){
       msg << "(test n°" << ++countTests <<  ") : " ;
        if(objectExpected == objectTested){
           msg << "OK" << std::endl;
            countPassed++;
        }else
           msg << "FAIL - Attendu:'" << objectExpected << "'. Reçu :'" << objectTested << "'"<< std::endl;
    }

     void static assertTrue(std::string tag, bool expression){
         msg << tag << " ";
         assertTrue(expression);
    }

     void static assertFalse(std::string tag, bool expression){
        msg  << tag << " ";
        assertFalse(expression);
    }

    void static assertEquals(std::string tag, T objectExpected,T objectTested){
        msg << tag << " ";
        assertEquals(objectExpected,objectTested);
    }

    void static results(){
        msg <<  "=====================" << std::endl;
        msg <<  "Résutat: " << countPassed << "/" << countTests ;
        std::cout << "\n" << msg.str() << "\n\n";
    }
};

#endif // UNITTEST_H
