
#include "F_Cryptor.h"


namespace Feintgine
{
    F_Cryptor::F_Cryptor()
    {
        mbedtls_aes_init(&m_aes);
    }

    F_Cryptor::~F_Cryptor()
    {
        mbedtls_aes_free(&m_aes);
    }

    void F_Cryptor::init(const std::string & password, const std::string & phrase)
    {

        mbedtls_sha256_context sha_ctx;
        mbedtls_sha256_init(&sha_ctx);
        mbedtls_sha256_starts(&sha_ctx, 0);  // 0 = SHA-256 (not SHA-224)
        mbedtls_sha256_update(&sha_ctx, (const unsigned char *)password.c_str(), password.length());
        mbedtls_sha256_update(&sha_ctx, (const unsigned char *)phrase.c_str(), phrase.length());
        mbedtls_sha256_finish(&sha_ctx, m_aesKey);
        mbedtls_sha256_free(&sha_ctx);

        m_isReady = true;

        std::cout << " key gen : \n";
        for (int i = 0 ; i < AES_KEY_SIZE ; i++)
        {
            printf("%02x", m_aesKey[i]);
        }
        std::cout << "\n";
    }        
    

    std::vector<unsigned char> F_Cryptor::encrypt(const std::string &input, unsigned char * iv)
    {
        std::vector<unsigned char> retVal;
        if(!m_isReady)
        {
            return retVal;
        }

        
        // mbedtls_aes_init(&m_aes);

        mbedtls_aes_setkey_enc(&m_aes, m_aesKey, AES_KEY_SIZE * 8);  // Set 256-bit key

        // Padding: Ensure the input is a multiple of 16 bytes
        size_t padded_size = ((input.size() / AES_IV_SIZE) + 1) * AES_IV_SIZE;
        std::vector<unsigned char> padded_input(padded_size, 0);
        std::memcpy(padded_input.data(), input.c_str(), input.size());

        // Encrypt
        retVal.resize(padded_size);
        unsigned char iv_copy[AES_IV_SIZE];  // IV is modified during encryption, so we need a copy
        std::memcpy(iv_copy, iv, AES_IV_SIZE);

        mbedtls_aes_crypt_cbc(&m_aes, MBEDTLS_AES_ENCRYPT, padded_size, iv_copy, padded_input.data(), retVal.data());
        // mbedtls_aes_free(&m_aes);
        return retVal;

    }


    std::vector<unsigned char> F_Cryptor::getEncryptFromString(const std::string & data)
    {
        std::vector<unsigned char> retVal;
        for(unsigned int i = 0; i < data.length(); i++)
        {
            retVal.push_back(data[i]);
        }

        return retVal;
    }

    std::string F_Cryptor::decrypt(const std::vector<unsigned char> & input, unsigned char * iv)
    {
        std::string retVal;

        mbedtls_aes_setkey_dec(&m_aes, m_aesKey, AES_KEY_SIZE * 8);  // Set 256-bit key

        // Decrypt
        std::vector<unsigned char> decrypted(input.size(), 0);
        unsigned char iv_copy[AES_IV_SIZE];
        std::memcpy(iv_copy, iv, AES_IV_SIZE);
    
        mbedtls_aes_crypt_cbc(&m_aes, MBEDTLS_AES_DECRYPT, input.size(), iv_copy, input.data(), decrypted.data());
    
        // Remove padding
        retVal.assign(reinterpret_cast<char*>(decrypted.data()));
    
        // mbedtls_aes_free(&m_aes);

        return retVal;

    }

    void F_Cryptor::generateRandomIV(unsigned char * iv)
    {
        mbedtls_entropy_context entropy;
        mbedtls_ctr_drbg_context ctr_drbg;
        
        mbedtls_entropy_init(&entropy);
        mbedtls_ctr_drbg_init(&ctr_drbg);
        mbedtls_ctr_drbg_seed(&ctr_drbg, mbedtls_entropy_func, &entropy, nullptr, 0);
        
        mbedtls_ctr_drbg_random(&ctr_drbg, iv, AES_IV_SIZE);
        
        mbedtls_ctr_drbg_free(&ctr_drbg);
        mbedtls_entropy_free(&entropy);
    }

    std::string F_Cryptor::getStringFromEncrypt(const std::vector<unsigned char> & input)
    {
        std::string retVal;
        retVal.reserve(input.size());
        
        for(int i = 0 ; i < input.size(); i++)
        {
            retVal.push_back(input[i]);
        }

        return retVal;
    }

}