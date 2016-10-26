#include <cstring>
//apt-get install libssl-dev pour openssl
#include <openssl/des.h>
#include <string>
#include <iostream>

using namespace std;

char* crypt(char*, char*,int, int, int);

int main() {

    char cle[]="azerty";
    char msg[]="Un message";
    char* msg_decrypt;
    char* msg_encrypt;

    cout << "Message : " << msg << endl;

    msg_encrypt = crypt(cle, msg, sizeof(cle), sizeof(msg), DES_ENCRYPT);
    cout << "Message crypté: " << msg_encrypt << endl;

    msg_decrypt = crypt(cle,msg_encrypt,sizeof(cle),sizeof(msg),DES_DECRYPT);
    cout << "Message décrypté: " << msg_decrypt << endl;

    return (0);
}

/*
 * Fonction de cryptage/décryptage avec un algo de type DES
 * https://www.openssl.org/docs/manmaster/crypto/DES_crypt.html
 * my_key : Le cle de cryptage
 * msg : Le message à crypter
 * key_size : La taille de la cle
 * msg_size : La taille du message
 * type : Le type d'action à effectuer par l'algo (DES_ENCRYPT / DES_DECRYPT)
 */
char* crypt(char* my_key, char* msg,int key_size, int msg_size, int type){

    char* res;//Tableau d'octet résultat
    int n=0;//Un nombre différent permet d'éviter que le même message soit crypté de la même façon, mais ici osef...

    DES_cblock key; //La cle
    DES_key_schedule schedule; //cle préparée

    res = (char*) malloc( msg_size );

    //Mise en place de la clef sous form d'un objet DES_cblock
    memcpy( key, my_key, key_size);
    DES_set_odd_parity( &key );

    //Mise en place du schedule
    DES_set_key_checked( &key, &schedule );

    //Algo de cryptage / décryptage
    DES_cfb64_encrypt( (unsigned char*) msg,
                       (unsigned char*) res,
                       msg_size,
                       &schedule,
                       &key,
                       &n,
                       type );

    return res;
}