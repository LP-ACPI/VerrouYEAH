#ifndef MAINTESTS
#define MAINTESTS

#include <string>
#include <unittest.hpp>
#include "../models/User.h"
#include "../services/Config.h"

#define PATH_SOURCE "../fichier_source.txt"
#define PATH_VY "../fichier_crypte.vy"
#define PATH_CIBLE "../fichier_cible.txt"
#define CONFIG_FILE "../config.json"
#define MYKEY "1234"

using namespace std;

int main(){

    Config conf(CONFIG_FILE);
     User* test =  conf.loadUser("login_user_1");

     UnitTest<string>::assertEquals("pass == 'azerty' ", test->getPassword() ,(string) "azerty");
     UnitTest<string>::assertEquals("login == 'login_user_1' ", test->getLogin() ,(string) "login_user_1");
     UnitTest<int>::assertEquals("3==3?",3,3);
     UnitTest<int>::assertEquals("2==3?",2,3);
     UnitTest<int>::assertEquals("6*2==12?",6*2,12);

     UnitTest<void*>::results();

}

#endif
