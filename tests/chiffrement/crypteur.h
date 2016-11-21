//
// Created by Valentin on 21/11/16.
//

#ifndef CRYPTEUR_H
#define CRYPTEUR_H

#include <string>
#include <openssl/des.h>
//TODO cle de 256/8 octets
#define CRYPT_KEY_SIZE 4
#define CRYPT_BUFFER_SIZE 1024

class Crypteur {
public:
    void crypt(char* entree, char* sortie, char* raw_key, int type);
    void crypt_file(std::string nom_source, std::string nom_destination, char* cle,int type);
};


#endif //TEST_CRYPTEUR_H
