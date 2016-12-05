//
// Created by Valentin on 05/12/16.
//
#include <iostream>
#include "models/Crypt.h"
#include "models/Config.h"

#define PATH_SOURCE "../VerrouYEAH/src/fichier_source.txt"
#define PATH_VY "../VerrouYEAH/src/fichier_crypte.vy"
#define PATH_CIBLE "../VerrouYEAH/src/fichier_cible.txt"
#define MYKEY "1234"

using namespace std;
/*
 * Main de test temporaire
 */
int main()
{
    Config conf;
    cout << conf.toString() << endl;

    Crypt c;
    cout << "Cryptage" << endl;
    c.cryptFile(PATH_SOURCE,PATH_VY,MYKEY);
    cout << "Decryptage" << endl;
    c.decryptFile(PATH_VY,PATH_CIBLE,MYKEY);
}