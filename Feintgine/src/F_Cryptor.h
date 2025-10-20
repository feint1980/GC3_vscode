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
#pragma once

namespace Feintgine
{
    class F_Cryptor
    {
    public:
        F_Cryptor();
        ~F_Cryptor();

        // Initialize key derivation using password + phrase (derives 32-byte key via SHA-256)
        void init(const std::string & password, const std::string & phrase);

        // Encrypt plaintext (binary-safe), returns ciphertext as std::string.
        // Caller is responsible for sending IV alongside ciphertext.
        std::string encrypt(const std::string &input, const unsigned char * iv);

        // Decrypt ciphertext (binary-safe) using iv pointer, returns plaintext (empty on error).
        std::string decrypt(const std::string &ciphertext, const unsigned char * iv);

        // Legacy helpers (kept for compatibility)
        std::vector<unsigned char> getEncryptFromString(const std::string & data);
        std::string getStringFromEncrypt(const std::vector<unsigned char> & input);

        // Fill iv (AES_IV_SIZE bytes) with cryptographically secure random bytes
        void generateRandomIV(unsigned char * iv);

        bool isReady() const { return m_isReady; }

    private:
        bool m_isReady = false;
        mbedtls_aes_context m_aes;
        unsigned char m_aesKey[AES_KEY_SIZE];
    };
}
