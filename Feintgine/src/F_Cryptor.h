
#include <iostream>
#include <vector>
#include <cstring>
#include <mbedtls/mbedtls/aes.h>
#include <mbedtls/mbedtls/md.h>
#include <mbedtls/mbedtls/entropy.h>
#include <mbedtls/mbedtls/ctr_drbg.h>
#include <mbedtls/mbedtls/sha256.h>


namespace Feintgine
{
    class F_Cryptor
    {
    public:
        void encrypt(const std::string &input, std::string &output);
        void decrypt(const std::string &input, std::string &output);


    private:
        
    };
}