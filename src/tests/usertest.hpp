#ifndef USERTEST_HPP
#define USERTEST_HPP

#include <unittest.hpp>
#include <iostream>
#include "../models/User.h"

class UserTest{

    static void testUtilisateurTestPardefaut(){
        User test;

        UnitTest<void*>::insertTitle("Test utilisateur 'test'");
        UnitTest<std::string>::assertEquals("login == 'test'","test",test.getLogin());
        UnitTest<std::string>::assertEquals("pass == 'test'","test",test.getPassword());
        UnitTest<size_t>::assertEquals("nb_backups == '0'",0,test.getBackups().size());
    }

    static void testAjoutSauvegardesDoublons(){
        UnitTest<void*>::insertTitle("Test ajout sauvegardes avec clés identiques");

        Backup backup1("test");
        Backup backup2("test");
        Backup backup3("test");
        Backup backup4("test");

        User test;
        test.addBackup(backup1);
        test.addBackup(backup2);
        test.addBackup(backup3);
        test.addBackup(backup4);

        UnitTest<size_t>::assertEquals("testAjout Sauvegardes Doublons",1,test.getBackups().size());
    }

    static void testSuppressionSauvegardes(){

        UnitTest<void*>::insertTitle("Test suppression sauvegardes");

        User test;

        Backup backup1;
        Backup backup2;
        Backup backup3;
        Backup backup4;
        test.addBackup(backup1);
        test.addBackup(backup2);
        test.addBackup(backup3);
        test.addBackup(backup4);
        UnitTest<size_t>::assertEquals("ajout 4 backups",4,test.getBackups().size());

        test.removeBackup(backup1);
        test.removeBackup(backup2);
        test.removeBackup(backup3);
        test.removeBackup(backup4);
        UnitTest<size_t>::assertEquals("suppression 4 backups",0,test.getBackups().size());
    }

public:
    static void executeTests(){
        testUtilisateurTestPardefaut();
        testAjoutSauvegardesDoublons();
        testSuppressionSauvegardes();
    }
};

#endif // USERTEST_HPP
