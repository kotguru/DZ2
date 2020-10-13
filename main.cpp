#include <iostream>
#include <openssl/bn.h>
#include <openssl/rsa.h> // Алгоритм RSA
#include <openssl/pem.h>

///VIN номер автомобиля будем использовать в качестве SALT при вычислении хэша
#define VIN "1HGBH41JXMN109186"

#define PRIVAT "./privat.key"
#define PUBLIC "./public.key"
unsigned long adler32(std::string str, std::string salt);

class CAR
{
private:
    long secretKey;
    long publicKey, publicKeyTrinket;
public:
    long getPublicKeyCar() const
    {
        return CAR::publicKey;
    }

    void setPublicKeyTrinket(long publicKeyTrinket) {
        CAR::publicKeyTrinket = publicKeyTrinket;
    }

    CAR()
    {
        CAR::secretKey = 0xf21f23112f121f3;//TODO: GENERATE SECRET KEY;
        CAR::publicKey = 0xa124f1313f22ed2;//TODO: GENERATE PRIVATE KEY;
        CAR::publicKeyTrinket = 0;
    }

    long ProcessHandshake(char* mes)
    {
        if (mes == "HELLO")
        {
            srand(time(nullptr));
            return adler32(std::string(reinterpret_cast<const char *>(rand())), VIN);
        } else
            throw ("Illegal message");
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
    long secretKey;
    long publicKey;
public:
        long getPublicKey() const
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
    }

    static void registration(CAR car, TRINKET trinket)
    {
        ///Привязываем брелок к машине при помощи записи публичного ключа бролока в авто
        car.setPublicKeyTrinket(trinket.getPublicKey());
    }

    char* GenerateHandshake()
    {
        return "HELLO";
    }

    void ProcessHandshake()
    {

    }



};

int main()
{
    new TRINKET();
    return 0;
}

unsigned long adler32(std::string str, std::string salt)
{
    unsigned char c;
    unsigned long s1 = 1;
    unsigned long s2 = 0;
    int i = 0;

    while(true) {
        c = str[i] + std::stoi(salt);

        if (i == str.size()) break;

        if (i < str.size())
            ++i;

        s1 = (s1 + c) % 65521;
        s2 = (s2 + s1) % 65521;
    }
    return (s2 << 16) + s1;
}