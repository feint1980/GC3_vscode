#include "F_Cryptor_sodium.h"


namespace Feintgine
{

    void F_Cryptor_sodium::init(const std::string & password, const std::string & phrase)
    {
        if(sodium_init() < 0)
        {
            std::cout << "Sodium init failed \n";

            return;
        }

        std::string combined = password + ":" + phrase;
        crypto_generichash(m_key, sizeof(m_key),
                        reinterpret_cast<const unsigned char*>(combined.data()),
                        combined.size(), nullptr, 0);

    }


    std::string F_Cryptor_sodium::encrypt(const std::string& message)
    {
        unsigned char nonce[crypto_secretbox_NONCEBYTES];
        randombytes_buf(nonce, sizeof(nonce));

        std::string ciphertext;
        ciphertext.resize(crypto_secretbox_MACBYTES + message.size());

        crypto_secretbox_easy(
            reinterpret_cast<unsigned char*>(&ciphertext[0]),
            reinterpret_cast<const unsigned char*>(message.data()),
            message.size(),
            nonce, m_key);

        // Combine nonce + ciphertext into one string
        std::string result(reinterpret_cast<char*>(nonce), sizeof(nonce));
        result += ciphertext;
        return result;
    }

    std::string F_Cryptor_sodium::decrypt(const std::string& combined)
    {
        if (combined.size() < crypto_secretbox_NONCEBYTES + crypto_secretbox_MACBYTES)
        {
            std::cout << "invalid decrypted message size\n";
            return {};
        }
            

        const unsigned char* nonce = reinterpret_cast<const unsigned char*>(combined.data());
        const unsigned char* ciphertext = nonce + crypto_secretbox_NONCEBYTES;
        size_t ciphertext_len = combined.size() - crypto_secretbox_NONCEBYTES;

        std::string decrypted;
        decrypted.resize(ciphertext_len - crypto_secretbox_MACBYTES);

        if (crypto_secretbox_open_easy(
                reinterpret_cast<unsigned char*>(&decrypted[0]),
                ciphertext, ciphertext_len, nonce, m_key) != 0)
                {
            std::cout << "crypto_secretbox_open_easy failed\n";
            return {}; // failed to decrypt (tampered or wrong key)
        }

        return decrypted;
    }


}