//
// Created by Valentin on 05/12/16.
//

#include <iostream>
#include "services/Crypt.h"
#include "services/Config.h"

#define PATH_SOURCE "fichier_source.txt"
#define PATH_VY "fichier_crypte.vy"
#define PATH_CIBLE "fichier_cible.txt"
#define CONFIG_FILE "config.json"
#define MYKEY "1234"


using namespace std;

/*
 * Main de test temporaire
 */
int main()
{
    Config conf(CONFIG_FILE);
    cout << conf << endl;

    Crypt c;
    cout << "Cryptage" << endl;
    c.cryptFile(PATH_SOURCE,PATH_VY,(char*)MYKEY);
    cout << "Decryptage" << endl;
    c.decryptFile(PATH_VY,PATH_CIBLE,(char*)MYKEY);
}
