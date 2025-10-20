#include <libsodium/sodium.h>
#include <string>
#include <vector>
#include <iostream>

#define crypto_secretbox_KEYBYTES 32

namespace Feintgine
{
    class F_Cryptor_sodium
    {
public:
        void init(const std::string & password, const std::string & phrase);

        std::string encrypt(const std::string& message);

        std::string decrypt(const std::string& combined);


private:
    unsigned char m_key[crypto_secretbox_KEYBYTES];
    };


}