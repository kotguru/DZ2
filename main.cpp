#include <iostream>
#include <openssl/rsa.h> // Алгоритм RSA
//#include <openssl/bn.h>
//#include <openssl/pem.h> // Для работы с файлами ключей
//#include <openssl/sha.h> // Для работы с файлами ключей
//#include "openssl/ossl_typ.h"

class CAR
{
private:
    long long int secretKey;
    long long int publicKey, publicKeyTrinket;
public:
    long long int getPublicKeyCar() const
    {
        return CAR::publicKey;
    }

    void setPublicKeyTrinket(long long int publicKeyTrinket) {
        CAR::publicKeyTrinket = publicKeyTrinket;
    }

    CAR()
    {
        CAR::secretKey = 0xf21f12ff3;//TODO: GENERATE SECRET KEY;
        CAR::publicKey = 0xff1322ed2;//TODO: GENERATE PRIVATE KEY;
        CAR::publicKeyTrinket = 0;
    }

    int ProcessHandshake()
    {
        srand(time(nullptr));
        return rand();
    }

    bool Responce()
    {

    }

    static void action(bool is_verified)
    {
        if (is_verified) {
            std::cout << "The door is open" << std::endl;
        } else {
            std::cout << "Error: this is not your car" << std::endl;
        }
    }
};

class TRINKET
{
private:
    long long int secretKey;
    long long int publicKey;
public:
    long long int getPublicKey() const
    {
        return TRINKET::publicKey;
    }

    TRINKET()
    {
        RSA *key = RSA_new();
        BIGNUM* e = BN_new();

//        BN_init(e);
        BN_set_word(e, RSA_F4);

        if (!RSA_generate_key_ex(key, 512, e, NULL))
        {
            fprintf(stderr, "RSA_generate_key_ex failed.\n");
//            ERR_print_errors_fp(stderr);
            return;
        }

        TRINKET::secretKey = 0xf21f12ff3;//TODO: GENERATE SECRET KEY;
        TRINKET::publicKey = 0xff1322ed2;//TODO: GENERATE PRIVATE KEY;
    }

    static void registration(CAR car, TRINKET trinket)
    {
        car.setPublicKeyTrinket(trinket.getPublicKey());
    }

    void GenerateHandshake()
    {

    }

    void ProcessHandshake()
    {

    }



};

int main() {
    return 0;
}
