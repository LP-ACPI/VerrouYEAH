#ifndef MAINTESTS
#define MAINTESTS

#define PATH_SOURCE "../fichier_source.txt"
#define PATH_VY "../fichier_crypte.vy"
#define PATH_CIBLE "../fichier_cible.txt"
#define CONFIG_FILE "../config.json"
#define MYKEY "1234"


#include <QtCore/QCoreApplication>
#include "persistancetest.hpp"
#include "usertest.hpp"
#include "datatest.hpp"
#include "ftptests.hpp"

using namespace std;

int main(int argc, char* argv[])
{
    QCoreApplication app(argc,argv);

    ConfigManager::getInstance().setJsonFile(CONFIG_FILE);
    cout << ConfigManager::getInstance() << endl;

    Crypt c;
    cout << "Cryptage" << endl;
    c.cryptFile(PATH_SOURCE,PATH_VY,(char*)MYKEY);
    cout << "Decryptage" << endl;
    c.decryptFile(PATH_VY,PATH_CIBLE,(char*)MYKEY);

    UserTest::executeTests();
    PersistanceTest::executeTests();
    DataTest::executeTests();
    FtpTest::executeTests();

    UnitTest<void*>::results();

    return EXIT_SUCCESS;
}


#endif
