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


    static void testChargementDUtilisateurs(){

        ConfigManager::getInstance().setJsonFile(LOCAL_CONFIG_FILE);
        User* test1 =  ConfigManager::getInstance().loadUser("login_user_1");
        User* test2 =  ConfigManager::getInstance().loadUser("login_user_2");
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
        ConfigManager::getInstance().setJsonFile(LOCAL_CONFIG_FILE);
        User test1 = *ConfigManager::getInstance().loadUser("login_user_1");
        User test(test1);
        test.setPassword("qwertz");
        test.setLogin("login_test");
        User toto(test1);
        toto.setPassword("qwertyop");
        toto.setLogin("login_toto");
        toto.removeBackups();
        ConfigManager::getInstance().setJsonFile(TEST_CONFIG_FILE);
        ConfigManager::getInstance().saveUser(&test);
        ConfigManager::getInstance().saveUser(&toto);

        User* test2 = ConfigManager::getInstance().loadUser("login_test");
        User* testToto = ConfigManager::getInstance().loadUser("login_toto");
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
        UnitTest<string>::assertEquals("login == 'login_toto'", (string) "login_toto",testToto->getLogin());
        UnitTest<uint32_t>::assertEquals((string) "pas de sauvegardes pour toto",0,toto.getBackups().size());
    }

    static void chargementCouplesLoginPass(){
        ConfigManager::getInstance().setJsonFile(TEST_CONFIG_FILE);
        map<string,string> users = ConfigManager::getInstance().loadLoginPassList();

        string loginsAttendus[2] = {"login_test","login_toto"};
        string passAttendus[2] = {"qwertz","qwertyop"};

        UnitTest<void*>::insertTitle("Test chargement couples login-mot de passe");

        unsigned i = 0;
        for(auto user : users) {
            UnitTest<string>::assertEquals("login == " +loginsAttendus[i],(string)loginsAttendus[i],  user.first);
            UnitTest<string>::assertEquals("pass == "+passAttendus[i],(string)passAttendus[i], user.second);
            i++;
        }
    }


    static void testSuppressionDUtilisateur(){
        ConfigManager::getInstance().setJsonFile(TEST_CONFIG_FILE);

        ConfigManager::getInstance().deleteUser("login_toto");
        map<string,string> users = ConfigManager::getInstance().loadLoginPassList();

        UnitTest<void*>::insertTitle("Test suppression d'utilisateur");
        UnitTest<int>::assertEquals("nombre d'utilisateurs == 1",1,users.size());

    }

    static void testPersistanceDesSauvegardesDUtilisateur(){
        ConfigManager::getInstance().setJsonFile(LOCAL_CONFIG_FILE);
        User test_user = *ConfigManager::getInstance().loadUser("login_user_1");

        ConfigManager::getInstance().setJsonFile(DISTANT_BACKUP_CONFIG_FILE);
        Directory backup_dir("dir_name_1","dir_path_1");
        Directory test_dir_2("dir_name_2","dir_path_2");
        Directory test_dir_3("dir_name_3","dir_path_3");
        File test_file_1("file_name_1","file_path_1");
        File test_file_2("file_name_2","file_path_2");
        File test_file_3("file_name_3","file_path_3");

        test_dir_2.addData(&test_file_1);
        backup_dir.addData(&test_file_2);
        test_dir_2.addData(&test_file_3);
        backup_dir.addData(&test_dir_2);
        backup_dir.addData(&test_dir_3);

        Backup newBackup(test_user.getBackupAt(1));
        newBackup.setData(&backup_dir);
        test_user.replaceBackupAt(1,newBackup);
        Backup *backup_1 = new Backup(test_user.getBackupAt(0));
        Backup *backup_2 = new Backup(test_user.getBackupAt(1));
        //Dans contrôleur correspondant: choix de telle ou telle sauvegarde à persister
        // dans backup.getTarget
        ConfigManager::getInstance().saveUsersBackup(&test_user,backup_2);
        ConfigManager::getInstance().saveUsersBackup(&test_user,backup_1);


//TODO tests
        UnitTest<void*>::insertTitle("Test persistance donneés de sauvegardes");

        json test;
        test << backup_dir;
        cout << test.dump(2) << endl;

    }

    static void testChargementDeSauvegardeDUtilisateur(){
        UnitTest<void*>::insertTitle("Test chargement de donneés de sauvegardes");

        ConfigManager::getInstance().setJsonFile(LOCAL_CONFIG_FILE);
        User test_user = *ConfigManager::getInstance().loadUser("login_user_1");
//        Backup backup  = test_user.getBackupAt(0);

        ConfigManager::getInstance().setJsonFile(DISTANT_BACKUP_CONFIG_FILE);
        ConfigManager::getInstance().loadUsersBackupData(&test_user,"2");

        Backup backup_test = test_user.getBackupByKey("2");

        const Data* data_test = backup_test.getData();

//        cout << "unit-test: "<< data_test->to_json().dump(2);
//TODO Tests : debuggage en cours
    }

public:

    static void executeTests()
    {
        testChargementDUtilisateurs();
        testPersistanceDutilisateurs();
        chargementCouplesLoginPass();
        testSuppressionDUtilisateur();
        testPersistanceDesSauvegardesDUtilisateur();
        testChargementDeSauvegardeDUtilisateur();
    }
};


#endif // PERSISTANCETEST_HPP
