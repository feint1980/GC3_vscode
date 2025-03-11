#include <iostream>
#include <cstring>
#include <mbedtls/mbedtls/rsa.h>
#include <mbedtls/mbedtls/pk.h>
#include <mbedtls/mbedtls/entropy.h>
#include <mbedtls/mbedtls/ctr_drbg.h>
#include <mbedtls/mbedtls/error.h>

#define KEY_SIZE 2048  // RSA key size in bits
#define EXPONENT 65537  // Public exponent
#define MESSAGE "Hello, mbedTLS!"

void generate_keypair(mbedtls_pk_context &pk) {
    mbedtls_pk_init(&pk);
    mbedtls_entropy_context entropy;
    mbedtls_ctr_drbg_context ctr_drbg;

    mbedtls_entropy_init(&entropy);
    mbedtls_ctr_drbg_init(&ctr_drbg);
    mbedtls_ctr_drbg_seed(&ctr_drbg, mbedtls_entropy_func, &entropy, NULL, 0);

    if (mbedtls_pk_setup(&pk, mbedtls_pk_info_from_type(MBEDTLS_PK_RSA)) != 0) {
        std::cerr << "Failed to set up RSA context!" << std::endl;
        return;
    }

    mbedtls_rsa_context *rsa = mbedtls_pk_rsa(pk);
    if (mbedtls_rsa_gen_key(rsa, mbedtls_ctr_drbg_random, &ctr_drbg, KEY_SIZE, EXPONENT) != 0) {
        std::cerr << "RSA key generation failed!" << std::endl;
        return;
    }

    // **Set PKCS#1 v1.5 padding**
    mbedtls_rsa_set_padding(rsa, MBEDTLS_RSA_PKCS_V15, MBEDTLS_MD_NONE);

    std::cout << "RSA Key Pair Generated!" << std::endl;

    mbedtls_entropy_free(&entropy);
    mbedtls_ctr_drbg_free(&ctr_drbg);
}

void encrypt_message(mbedtls_pk_context &pk, const std::string &message, unsigned char *encrypted, size_t &olen) {
    mbedtls_ctr_drbg_context ctr_drbg;
    mbedtls_entropy_context entropy;

    mbedtls_entropy_init(&entropy);
    mbedtls_ctr_drbg_init(&ctr_drbg);
    mbedtls_ctr_drbg_seed(&ctr_drbg, mbedtls_entropy_func, &entropy, NULL, 0);

    int ret = mbedtls_pk_encrypt(&pk, (const unsigned char *)message.c_str(), message.length(),
                                 encrypted, &olen, KEY_SIZE / 8, mbedtls_ctr_drbg_random, &ctr_drbg);
    
    if (ret != 0) {
        char err_buf[256];
        mbedtls_strerror(ret, err_buf, sizeof(err_buf));
        std::cerr << "Encryption failed! Error: " << err_buf << std::endl;
    } else {
        std::cout << "Message encrypted successfully! Encrypted size: " << olen << " bytes." << std::endl;
    }

    mbedtls_entropy_free(&entropy);
    mbedtls_ctr_drbg_free(&ctr_drbg);
}

void decrypt_message(mbedtls_pk_context &pk, unsigned char *encrypted, size_t enc_len) {
    unsigned char decrypted[256] = {0};  // Ensure buffer is large enough
    size_t olen = 0;

    // **Ensure the private key is available for decryption**
    if (!mbedtls_pk_can_do(&pk, MBEDTLS_PK_RSA)) {
        std::cerr << "Error: Private key not available for decryption!" << std::endl;
        return;
    }

    int ret = mbedtls_pk_decrypt(&pk, encrypted, enc_len, decrypted, &olen, sizeof(decrypted), NULL, NULL);
    
    if (ret != 0) {
        char err_buf[256];
        mbedtls_strerror(ret, err_buf, sizeof(err_buf));
        std::cerr << "Decryption failed! Error: " << err_buf << std::endl;
    } else {
        std::cout << "Decrypted Message: " << std::string((char*)decrypted, olen) << std::endl;
    }
}

int wmain() {
    mbedtls_pk_context pk;
    generate_keypair(pk);

    unsigned char encrypted[KEY_SIZE / 8] = {0};  // Ensure correct buffer size
    size_t encrypted_size = 0;

    encrypt_message(pk, MESSAGE, encrypted, encrypted_size);
    decrypt_message(pk, encrypted, encrypted_size);

    mbedtls_pk_free(&pk);
    return 0;
}
