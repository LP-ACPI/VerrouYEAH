//
// Created by Valentin on 21/11/16.
//

#include "crypteur.h"

#include <fstream>
#include <iostream>
#include <cstring>

using namespace std;
void Crypteur::crypt_file(string nom_source, string nom_destination, char* cle, int type)
{
    ifstream source(nom_source, ifstream::binary);
    //TODO: Ajouter un throw > Impossible de trouver/ouvrir le fichier source
    if(!source){
        cerr << strerror(errno) << endl;
        return;
    }

    ofstream destination(nom_destination, ofstream::binary);
    //TODO: Ajouter un throw > Impossible de trouver/ouvrir le fichier cible
    if(!destination) {
        cerr << strerror(errno) << endl;
        return;
    }

    char buffer_read[CRYPT_BUFFER_SIZE];
    char buffer_write[CRYPT_BUFFER_SIZE];
    int taille = source.seekg(0,ios::end).tellg();
    source.seekg(0,ios::beg);
    int lu = 0;
    while(lu < taille)
    {
        if(!source || !destination) break;//TODO: Ajouter un throw > Erreur pendant la lecture

        int nb_octet = CRYPT_BUFFER_SIZE;
        if(taille - lu < CRYPT_BUFFER_SIZE)
            nb_octet = taille - lu;

        source.read(buffer_read,nb_octet);
        crypt(buffer_read,buffer_write,cle,type);
        destination.write(buffer_write,nb_octet);

        lu = source.tellg();
    }
    source.close();
    destination.close();
}
/*
 * Fonction de cryptage/décryptage avec un algo de type DES
 * https://www.openssl.org/docs/manmaster/crypto/DES_crypt.html
 * type : Le type d'action à effectuer par l'algo (DES_ENCRYPT / DES_DECRYPT)
 */
void Crypteur::crypt(char* entree, char* sortie, char* raw_key, int type){
    //Préparation de la clef
    DES_cblock key;
    DES_key_schedule schedule;
    memcpy( key, raw_key, CRYPT_KEY_SIZE);
    DES_set_odd_parity( &key );
    DES_set_key_checked( &key, &schedule );
    int n=0;
    DES_cfb64_encrypt( (unsigned char*) entree,
                       (unsigned char*) sortie,
                       CRYPT_BUFFER_SIZE,
                       &schedule,
                       &key,
                       &n,
                       type );
}

