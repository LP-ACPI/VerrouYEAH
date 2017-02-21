#ifndef UNITTEST_H
#define UNITTEST_H
#include <sstream>
#include <iostream>

class TestInfo {
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
        std::cout << "(test n°" << ++countTests << ") : " ;
        if(expression){
            std::cout << "OK" << std::endl;
            countPassed++;
        }
        else
            std::cout << "FAIL - Attendu TRUE. Reçu FALSE" << std::endl;
    }

     void static assertFalse(bool expression){ 
	std::cout << "(test n°" << ++countTests << ") : " ;
        if(!expression){
	    std::cout << "OK" << std::endl;
            countPassed++;
        }else
	     std::cout << "FAIL - Attendu FALSE. Reçu TRUE" << std::endl;
    }

     void static assertEquals(T objectExpected,T objectTested){
       std::cout << "(test n°" << ++countTests <<  ") : " ;
        if(objectExpected == objectTested){
	   std::cout << "OK" << std::endl;
            countPassed++;
        }else
	   std::cout << "FAIL - Attendu:'" << objectExpected << "'. Reçu :'" << objectTested << "'"<< std::endl;
    }

     void static assertTrue(std::string tag, bool expression){
	 std::cout << tag << "\t";
         assertTrue(expression);
    }

     void static assertFalse(std::string tag, bool expression){
	std::cout  << tag << "\t";
        assertFalse(expression);
    }

    void static assertEquals(std::string tag, T objectExpected,T objectTested){
	std::cout << tag << "\t";
        assertEquals(objectExpected,objectTested);
    }

    void static results(){
	msg <<  "=================================" << std::endl;
	msg <<  "\n\tRésutat: " << countPassed << "/" << countTests ;
	std::cout << "\n" << msg.str() << "\n\n\n";
    }

    void static insertTitle(std::string title){
	std::cout << std::endl << "\t";
	for(unsigned i=0;i<title.length();i++)
	    std::cout << "-";
	std::cout << std::endl << "\t" << title << std::endl;
	std::cout << "\t";
	for(unsigned i=0;i<title.length();i++)
	    std::cout << "-";
	std::cout << std::endl ;
    }
};

#endif // UNITTEST_H
