#ifndef PERSISTANCETEST_HPP
#define PERSISTANCETEST_HPP

#include <iostream>
#include <cstdio>
#include <unittest.hpp>
#include "../models/User.h"
#include "../services/ConfigManager.h"

#define PATH_SOURCE "../fichier_source.txt"
#define PATH_VY "../fichier_crypte.vy"
#define PATH_CIBLE "../fichier_cible.txt"
#define LOCAL_CONFIG_FILE "../config.json"
#define TEST_CONFIG_FILE "../config_dist.json"
#define MYKEY "1234"

using namespace std;

class PersistanceTest{

    static void testPreSet(){
        remove(TEST_CONFIG_FILE);
    }

    static void testChargementDUtilisateurs(){
        ConfigManager conf(LOCAL_CONFIG_FILE);
        User* test1 =  conf.loadUser("login_user_1");
        User* test2 =  conf.loadUser("login_user_2");
        Backup test_1_1stBcp = test1->getBackupAt(0);
        Backup test_1_2ndBcp = test1->getBackupAt(1);

        UnitTest<void*>::insertTitle("Test chargement utilisateurs");
        UnitTest<string>::assertEquals("pass == 'azerty' ", test1->getPassword() ,(string) "azerty");
        UnitTest<string>::assertEquals("login == 'login_user_1' ", test1->getLogin() ,(string) "login_user_1");
        UnitTest<string>::assertEquals("pass == 'azerty' ", test2->getPassword() ,(string) "azerty");
        UnitTest<string>::assertEquals("login == 'login_user_2' ", test2->getLogin() ,(string) "login_user_2");
        UnitTest<string>::assertEquals(test_1_1stBcp.getName(),(string) "Ma première sauvegarde");
        UnitTest<string>::assertEquals(test_1_2ndBcp.getName(),(string) "Ma seconde sauvegarde");
    }

    static void testPersistanceDutilisateurs(){
        ConfigManager conf(LOCAL_CONFIG_FILE);
        User test1 = *conf.loadUser("login_user_1");
        User test(test1);
        test.setPassword("qwertz");
        test.setLogin("login_test");
        User toto(test1);
        toto.setPassword("qwertyop");
        toto.setLogin("login_toto");
        toto.removeBackups();
        conf.setUsersJsonFile(TEST_CONFIG_FILE);
        conf.saveUser(&test);
        conf.saveUser(&toto);

        User* test2 = conf.loadUser("login_test");
        Backup test_2_1stBcp = test2->getBackupAt(0);
        Backup test_2_2ndBcp = test2->getBackupAt(1);

        User* testToto = conf.loadUser("login_toto");

        UnitTest<void*>::insertTitle("Test persistance 1er utilisateur (avec login changé)");
        UnitTest<string>::assertEquals("pass == 'qwertz'", (string) "qwertz", test2->getPassword());
        UnitTest<string>::assertEquals("login == 'login_test'", (string) "login_test",test2->getLogin());
        UnitTest<string>::assertEquals((string) "Ma première sauvegarde",test_2_1stBcp.getName());
        UnitTest<string>::assertEquals((string) "Ma seconde sauvegarde", test_2_2ndBcp.getName());

        UnitTest<void*>::insertTitle("Test persistance 2nd utilisateur");
        UnitTest<string>::assertEquals("pass == 'qwertyop'", (string) "qwertyop", testToto->getPassword());
        UnitTest<string>::assertEquals("login == 'logins_toto'", (string) "login_toto",testToto->getLogin());
        UnitTest<size_t>::assertEquals((string) "pas de sauvegardes pour toto",0,toto.getBackups().size());
    }

    static void chargementDesLogin(){
        ConfigManager conf(LOCAL_CONFIG_FILE);
        list<string> users = conf.loadUserList();


    }

public:

    static void executeTests()
    {
        testPreSet();
        testChargementDUtilisateurs();
        testPersistanceDutilisateurs();
        chargementDesLogin();
    }

};


#endif // PERSISTANCETEST_HPP
