//
// Created by Valentin on 05/12/16.
//

#ifndef CRYPT_H
#define CRYPT_H

#include <string>
#include <stdexcept>

#define CRYPT_KEY_SIZE 4
#define CRYPT_BUFFER_SIZE 512

class Crypt {
    char mainKey[CRYPT_KEY_SIZE];//TODO mettre une cle en dur
    void crypt_DES(char* entree, char* sortie,char* raw_key, int type);
    void crypt_file_DES(std::string nom_source, std::string nom_destination, char* cle,int type);
public:
    static char *genKey(size_t);
    static std::string generateHashedPass(std::string);
    void crypt(char* in, char* out, char* raw_key);
    void decrypt(char* in, char* out, char* raw_key);
    void cryptFile(std::string nom_source, std::string nom_destination, char* cle);
    void decryptFile(std::string nom_source, std::string nom_destination, char* cle);
};


#endif //CRYPT_H
