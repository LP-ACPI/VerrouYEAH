#include <cstring>
#include "crypteur.h"

#define PATH_CPP "main.cpp"
#define PATH_VY "test.vy"
#define PATH_TXT "test.txt"
#define MYKEY "1234"

using namespace std;

int main() {
    Crypteur c;
    c.crypt_file(PATH_CPP,PATH_VY,MYKEY,DES_ENCRYPT);
    c.crypt_file(PATH_VY,PATH_TXT,MYKEY,DES_DECRYPT);
    return (0);
}