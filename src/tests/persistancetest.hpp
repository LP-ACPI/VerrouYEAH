#ifndef PERSISTANCETEST_HPP
#define PERSISTANCETEST_HPP

#include <iostream>
#include <cstdio>
#include <unittest.hpp>
#include "../models/File.h"
#include "../models/User.h"
#include "../services/ConfigManager.h"

#define PATH_SOURCE "../fichier_source.txt"
#define PATH_VY "../fichier_crypte.vy"
#define PATH_CIBLE "../fichier_cible.txt"
#define LOCAL_CONFIG_FILE "../config.json"
#define TEST_CONFIG_FILE "../config_test.json"
#define DISTANT_BACKUP_CONFIG_FILE "../config_dist.json"
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
        conf.setJsonFile(TEST_CONFIG_FILE);
        conf.saveUser(&test);
        conf.saveUser(&toto);


        User* test2 = conf.loadUser("login_test");
        User* testToto = conf.loadUser("login_toto");
        Backup test_2_1stBcp= test2->getBackupAt(0);
        Backup test_2_2ndBcp= test2->getBackupAt(1);
        Backup test_toto_1stBcp;
        Backup test_toto_2ndBcp;

        try {
            test_toto_1stBcp = testToto->getBackupAt(0);
            test_toto_2ndBcp = testToto->getBackupAt(1);
        }
        catch( const invalid_argument &e) {
            cerr <<  e.what() << endl;
        }

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

    static void chargementCouplesLoginPass(){
        ConfigManager conf(LOCAL_CONFIG_FILE);
        list<string[2]> users = conf.loadUserList();

        string loginsAttendus[2] = {"login_user_1","login_user_2"};
        string passAttendus[2] = {"azerty","azerty"};

        UnitTest<void*>::insertTitle("Test chargement couples login-mot de passe");

        unsigned i = 0;
        for(string user[2] : users){
            UnitTest<string>::assertEquals("login == " +loginsAttendus[i],(string)loginsAttendus[i],  user[0]);
            UnitTest<string>::assertEquals("pass == "+passAttendus[i],(string)passAttendus[i], user[1]);
            i++;
        }
    }

    static void testPersistanceLesSauvegardesDUtilisateur(){
        ConfigManager conf(LOCAL_CONFIG_FILE);
        User test_user = *conf.loadUser("login_user_1");

        conf.setJsonFile(DISTANT_BACKUP_CONFIG_FILE);
        Directory backup_dir("dir_name_1","dir_path_1");
        Directory test_dir_2("dir_name_2","dir_path_2");
        Directory test_dir_3("dir_name_3","dir_path_3");
        File test_file_1("file_name_1","file_path_1");
        File test_file_2("file_name_2","file_path_2");
        File test_file_3("file_name_3","file_path_3");

        backup_dir.addData(&test_file_1);
        backup_dir.addData(&test_file_2);
        test_dir_2.addData(&test_file_3);
        backup_dir.addData(&test_dir_2);
        backup_dir.addData(&test_dir_3);

        Backup newBackup(test_user.getBackupAt(1));
        newBackup.setData(&backup_dir);
        test_user.replaceBackupAt(1,newBackup);
        Backup *backup_1 = new Backup(test_user.getBackupAt(0));
        Backup *backup_2 = new Backup(test_user.getBackupAt(1));
        json test = conf.saveUsersBackup(&test_user,backup_2);
        conf.saveUsersBackup(&test_user,backup_1);

//TODO tests

    }

public:

    static void executeTests()
    {
        testPreSet();
        testChargementDUtilisateurs();
        testPersistanceDutilisateurs();
        chargementCouplesLoginPass();
        testPersistanceLesSauvegardesDUtilisateur();
    }

};


#endif // PERSISTANCETEST_HPP
