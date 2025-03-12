#pragma once

#include <iostream>
#include <vector>
#include <cstring>
#include <mbedtls/mbedtls/aes.h>
#include <mbedtls/mbedtls/md.h>
#include <mbedtls/mbedtls/entropy.h>
#include <mbedtls/mbedtls/ctr_drbg.h>
#include <mbedtls/mbedtls/sha256.h>

#define AES_KEY_SIZE 32  // AES-256 key size (32 bytes)
#define AES_IV_SIZE 16   // AES block size (16 bytes for IV)

namespace Feintgine
{
    class F_Cryptor
    {
    public:
        F_Cryptor();
        ~F_Cryptor();

        void init(const std::string & password, const std::string & phrase);

        std::vector<unsigned char> getEncryptFromString(const std::string & data); 

        std::vector<unsigned char> encrypt(const std::string &input, unsigned char * iv);
        std::string decrypt(const std::vector<unsigned char> & input, unsigned char * iv);

        std::string getStringFromEncrypt(const std::vector<unsigned char> & input);

        void generateRandomIV(unsigned char * iv);

    private:
        bool m_isReady = false;
        mbedtls_aes_context m_aes;

        unsigned char m_aesKey[AES_KEY_SIZE];
        // unsigned char m_iv[AES_IV_SIZE];

    };
}