#include <iostream>
#include <sstream>
#include <string>
//#include <openssl/bn.h>
//#include <openssl/rsa.h> // Алгоритм RSA
//#include <openssl/pem.h>

#define VIN "HGBH41JXMN109186"

#define PRIVAT "./privat.key"
#define PUBLIC "./public.key"
unsigned long adler32(std::string str);

class CAR
{
private:
    unsigned long secretKey;
    unsigned long publicKey, publicKeyTrinket;
    unsigned long hash;
public:
    long getPublicKeyCar() const
    {
        return CAR::publicKey;
    }

    void setPublicKeyTrinket(long publicKeyTrinket)
    {
        CAR::publicKeyTrinket = publicKeyTrinket;
    }

    CAR()
    {
        CAR::secretKey = 0xf21f23112f121f3;//TODO: GENERATE SECRET KEY;
        CAR::publicKey = 0xa124f1313f22ed2;//TODO: GENERATE PRIVATE KEY;
        CAR::publicKeyTrinket = 0;
        std::cout << "--- CAR: Private and public keys recorded ---" << std::endl;
    }

    unsigned long ProcessHandshake(char* mes)
    {
        if (mes == "HELLO")
        {
            srand(time(nullptr));
            std::stringstream ss;
            ss << rand();
            hash = adler32(ss.str());

            //TODO: encrypt the challenge with the car's public key
            unsigned long encryptHash = hash;

            std::cout << "--- CAR -> TRINKET: sending a challenge to verify a signature ---" << std::endl;
            return encryptHash;
        } else
            throw ("Illegal message");
    }

    bool Responce(unsigned long decHash)
    {
        return decHash == hash;
    }

    static void action(bool is_verified)
    {
        if (is_verified) {
            std::cout << "--- The door is open ---" << std::endl;
        } else {
            std::cout << "--- Error: this is not your car ---" << std::endl;
        }
    }
};

class TRINKET
{
private:
    unsigned long secretKey;
    unsigned long publicKey;
public:
    unsigned long getPublicKey() const
    {
            return TRINKET::publicKey;
    }

    ///В конструкторе генерируются серетный и публичный ключи
    TRINKET()
    {
//        RSA *key = RSA_new();
//        BIGNUM* e = BN_new();
//
//        BN_init(e);
//        BN_set_word(e, RSA_F4);
//
//        if (!RSA_generate_key_ex(key, 512, e, NULL))
//        {
//            fprintf(stderr, "RSA_generate_key_ex failed.\n");
//            ERR_print_errors_fp(stderr);
//            return;
//        }


//        RSA * rsa = NULL;
//
//        unsigned long bits = 2048; /* длина ключа в битах */
//
//        FILE *priv_key_file = NULL, *pub_key_file = NULL;
//
//        /* контекст алгоритма шифрования */
//
//        const EVP_CIPHER *cipher = NULL;
//
//        priv_key_file = fopen(PRIVAT, "wb");
//
//        pub_key_file = fopen(PUBLIC, "wb");
//
///* Генерируем ключи */
//
//        rsa = RSA_generate_key_ex(bits, RSA_F4, NULL, NULL);
//
///* Формируем контекст алгоритма шифрования */
//
//        OpenSSL_add_all_ciphers();
//
//        cipher = EVP_get_cipherbyname("bf-ofb");
//
///* Получаем из структуры rsa открытый и секретный ключи и сохраняем в файлах.
//
// * Секретный ключ шифруем с помощью парольной фразы «hello»
//
// */
//
//        PEM_write_RSAPrivateKey(priv_key_file, rsa, cipher,
//
//                                NULL, 0, NULL, (void *) "hello");
//
//        PEM_write_RSAPublicKey(pub_key_file, rsa);
//
///* Освобождаем память, выделенную под структуру rsa */
//
//        RSA_free(rsa);

        TRINKET::secretKey = 0xbfaf21f12f12f3;//TODO: GENERATE SECRET KEY;
        TRINKET::publicKey = 0xfab123f1322ed2;//TODO: GENERATE PRIVATE KEY;
        std::cout << "--- TRINKET: Private and public keys recorded ---" << std::endl;
    }

    static void registration(CAR car, TRINKET trinket)
    {
        ///Привязываем брелок к машине при помощи записи публичного ключа брелка в авто
        car.setPublicKeyTrinket(trinket.getPublicKey());
        std::cout << "--- REGISTRATION: creating a keychain and a car, recording a public key of a keychain in a car ---" << std::endl;
    }

    char* GenerateHandshake()
    {
        std::cout << "--- TRINKET -> CAR: connection request ---" << std::endl;
        return "HELLO";
    }

    unsigned long ProcessChallenge(unsigned long encHash)
    {
        //TODO: decrypt the received challenge using the private key of the keychain
        unsigned long decryptHash = encHash;

        std::cout << "--- TRINKET -> CAR: sending an decrypted challenge for confirmation ---" << std::endl;
        return decryptHash;
    }



};

int main()
{
    CAR car = *new CAR();
    TRINKET trinket = *new TRINKET();
    TRINKET::registration(car, trinket);

    char* connectionInit = trinket.GenerateHandshake();
    unsigned long encHashFromCar = car.ProcessHandshake(connectionInit);
    unsigned long decHashFromTrinket = trinket.ProcessChallenge(encHashFromCar);
    bool answer = car.Responce(decHashFromTrinket);
    CAR::action(answer);

    return 0;
}

unsigned long adler32(std::string str)
{
    unsigned char c;
    unsigned long s1 = 1;
    unsigned long s2 = 0;
    int i = 0;

    while(true) {
        c = str[i];

        if (i == str.size()) break;

        if (i < str.size())
            ++i;

        s1 = (s1 + c) % 65521;
        s2 = (s2 + s1) % 65521;
    }
    return (s2 << 16) + s1;
}