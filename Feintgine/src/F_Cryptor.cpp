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
        mbedtls_sha256_starts(&sha_ctx, 0);  // 0 = SHA-256
        mbedtls_sha256_update(&sha_ctx, reinterpret_cast<const unsigned char*>(password.data()), password.size());
        mbedtls_sha256_update(&sha_ctx, reinterpret_cast<const unsigned char*>(phrase.data()), phrase.size());
        mbedtls_sha256_finish(&sha_ctx, m_aesKey);
        mbedtls_sha256_free(&sha_ctx);

        m_isReady = true;
    }

    // Binary-safe encrypt: returns ciphertext as std::string (no IV appended)
    std::string F_Cryptor::encrypt(const std::string &input, const unsigned char * iv)
    {
        if (!m_isReady) {
            std::cerr << "F_Cryptor::encrypt called but cryptor not initialized\n";
            return std::string();
        }

        // Set AES key
        int rc = mbedtls_aes_setkey_enc(&m_aes, m_aesKey, AES_KEY_SIZE * 8);
        if (rc != 0) {
            std::cerr << "mbedtls_aes_setkey_enc failed: " << rc << "\n";
            return std::string();
        }

        // PKCS#7 padding
        const size_t block = AES_IV_SIZE;
        size_t padLen = block - (input.size() % block);
        if (padLen == 0) padLen = block; // though formula above already yields block when input.size()%block==0

        size_t padded_size = input.size() + padLen;
        std::vector<unsigned char> padded_input(padded_size);
        if (!input.empty()) {
            std::memcpy(padded_input.data(), input.data(), input.size());
        }
        // fill padding bytes with padLen
        std::memset(padded_input.data() + input.size(), static_cast<unsigned char>(padLen), padLen);

        // Prepare output buffer
        std::vector<unsigned char> encrypted(padded_size);

        // IV copy because mbedtls_aes_crypt_cbc modifies the IV buffer
        unsigned char iv_copy[AES_IV_SIZE];
        std::memcpy(iv_copy, iv, AES_IV_SIZE);

        rc = mbedtls_aes_crypt_cbc(&m_aes, MBEDTLS_AES_ENCRYPT,
                                   static_cast<size_t>(padded_size),
                                   iv_copy,
                                   padded_input.data(),
                                   encrypted.data());
        if (rc != 0) {
            std::cerr << "mbedtls_aes_crypt_cbc (encrypt) failed: " << rc << "\n";
            return std::string();
        }

        // Return binary-safe string
        return std::string(reinterpret_cast<const char*>(encrypted.data()), encrypted.size());
    }

    // Binary-safe decrypt: ciphertext is std::string (binary), iv is AES_IV_SIZE bytes
    std::string F_Cryptor::decrypt(const std::string &ciphertext, const unsigned char * iv)
    {
        if (!m_isReady) {
            std::cerr << "F_Cryptor::decrypt called but cryptor not initialized\n";
            return std::string();
        }

        if (ciphertext.empty()) {
            return std::string();
        }

        if ((ciphertext.size() % AES_IV_SIZE) != 0) {
            std::cerr << "F_Cryptor::decrypt invalid ciphertext size (not multiple of block): " << ciphertext.size() << "\n";
            return std::string();
        }

        int rc = mbedtls_aes_setkey_dec(&m_aes, m_aesKey, AES_KEY_SIZE * 8);
        if (rc != 0) {
            std::cerr << "mbedtls_aes_setkey_dec failed: " << rc << "\n";
            return std::string();
        }

        std::vector<unsigned char> decrypted(ciphertext.size());
        unsigned char iv_copy[AES_IV_SIZE];
        std::memcpy(iv_copy, iv, AES_IV_SIZE);

        rc = mbedtls_aes_crypt_cbc(&m_aes, MBEDTLS_AES_DECRYPT,
                                   static_cast<size_t>(ciphertext.size()),
                                   iv_copy,
                                   reinterpret_cast<const unsigned char*>(ciphertext.data()),
                                   decrypted.data());
        if (rc != 0) {
            std::cerr << "mbedtls_aes_crypt_cbc (decrypt) failed: " << rc << "\n";
            return std::string();
        }

        // PKCS#7 unpadding: validate and strip
        if (decrypted.empty()) return std::string();

        unsigned char last = decrypted.back();
        size_t padLen = static_cast<size_t>(last);

        if (padLen == 0 || padLen > AES_IV_SIZE) {
            std::cerr << "F_Cryptor::decrypt invalid PKCS#7 pad length: " << padLen << "\n";
            return std::string();
        }

        // verify padding bytes
        for (size_t i = 0; i < padLen; ++i) {
            if (decrypted[decrypted.size() - 1 - i] != last) {
                std::cerr << "F_Cryptor::decrypt invalid PKCS#7 padding bytes\n";
                return std::string();
            }
        }

        size_t outSize = decrypted.size() - padLen;
        return std::string(reinterpret_cast<const char*>(decrypted.data()), outSize);
    }

    // Legacy helper: convert string -> vector<unsigned char>
    std::vector<unsigned char> F_Cryptor::getEncryptFromString(const std::string & data)
    {
        std::vector<unsigned char> ret;
        ret.reserve(data.size());
        for (size_t i = 0; i < data.size(); ++i) ret.push_back(static_cast<unsigned char>(data[i]));
        return ret;
    }

    // Legacy helper: convert vector<unsigned char> -> std::string (binary-safe)
    std::string F_Cryptor::getStringFromEncrypt(const std::vector<unsigned char> & input)
    {
        if (input.empty()) return std::string();
        return std::string(reinterpret_cast<const char*>(input.data()), input.size());
    }

    // Generate cryptographically secure IV (AES_IV_SIZE bytes)
    void F_Cryptor::generateRandomIV(unsigned char * iv)
    {
        if (!iv) return;

        mbedtls_entropy_context entropy;
        mbedtls_ctr_drbg_context ctr_drbg;

        mbedtls_entropy_init(&entropy);
        mbedtls_ctr_drbg_init(&ctr_drbg);

        const char *pers = "F_Cryptor_iv";
        int rc = mbedtls_ctr_drbg_seed(&ctr_drbg, mbedtls_entropy_func, &entropy,
                                       reinterpret_cast<const unsigned char*>(pers), strlen(pers));
        if (rc != 0) {
            std::cerr << "generateRandomIV: ctr_drbg_seed failed: " << rc << "\n";
            // fallback: zero iv (not ideal) - but better to signal error upstream
            std::memset(iv, 0, AES_IV_SIZE);
            mbedtls_ctr_drbg_free(&ctr_drbg);
            mbedtls_entropy_free(&entropy);
            return;
        }

        rc = mbedtls_ctr_drbg_random(&ctr_drbg, iv, AES_IV_SIZE);
        if (rc != 0) {
            std::cerr << "generateRandomIV: ctr_drbg_random failed: " << rc << "\n";
            std::memset(iv, 0, AES_IV_SIZE);
        }

        mbedtls_ctr_drbg_free(&ctr_drbg);
        mbedtls_entropy_free(&entropy);
    }

} // namespace Feintgine
