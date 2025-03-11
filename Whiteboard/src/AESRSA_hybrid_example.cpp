#include <iostream>
#include <mbedtls/mbedtls/aes.h>
#include <mbedtls/mbedtls/pk.h>
#include <mbedtls/mbedtls/ctr_drbg.h>
#include <mbedtls/mbedtls/entropy.h>
#include <cstring>

// AES Key & IV sizes
#define AES_KEY_SIZE 32  // AES-256
#define AES_IV_SIZE 16   // CBC mode IV

// Generates a random AES key & IV
void generate_random_bytes(unsigned char *buffer, size_t length, mbedtls_ctr_drbg_context *ctr_drbg) {
    mbedtls_ctr_drbg_random(ctr_drbg, buffer, length);
}

// Encrypt with AES-256-CBC
int aes_encrypt(const unsigned char *key, const unsigned char *iv, const unsigned char *input, size_t input_len,
                unsigned char *output, size_t &output_len) {
    mbedtls_aes_context aes;
    mbedtls_aes_init(&aes);
    mbedtls_aes_setkey_enc(&aes, key, AES_KEY_SIZE * 8);
    
    // Ensure the input is padded to 16-byte blocks
    size_t padded_len = ((input_len + 15) / 16) * 16;
    unsigned char padded_input[padded_len];
    memcpy(padded_input, input, input_len);
    memset(padded_input + input_len, 0, padded_len - input_len);

    // Encrypt with CBC mode
    output_len = padded_len;
    mbedtls_aes_crypt_cbc(&aes, MBEDTLS_AES_ENCRYPT, output_len, iv, padded_input, output);
    
    mbedtls_aes_free(&aes);
    return 0;
}

// Decrypt with AES-256-CBC
int aes_decrypt(const unsigned char *key, const unsigned char *iv, const unsigned char *input, size_t input_len,
                unsigned char *output) {
    mbedtls_aes_context aes;
    mbedtls_aes_init(&aes);
    mbedtls_aes_setkey_dec(&aes, key, AES_KEY_SIZE * 8);
    
    mbedtls_aes_crypt_cbc(&aes, MBEDTLS_AES_DECRYPT, input_len, (unsigned char *)iv, input, output);
    
    mbedtls_aes_free(&aes);
    return 0;
}

// Encrypt AES key with RSA public key
int rsa_encrypt_aes_key(mbedtls_pk_context *pk, unsigned char *aes_key, size_t key_len,
                        unsigned char *encrypted_key, size_t &encrypted_key_len, mbedtls_ctr_drbg_context *ctr_drbg) {
    return mbedtls_pk_encrypt(pk, aes_key, key_len, encrypted_key, &encrypted_key_len, 256, mbedtls_ctr_drbg_random, ctr_drbg);
}

// Decrypt AES key with RSA private key
int rsa_decrypt_aes_key(mbedtls_pk_context *pk, unsigned char *encrypted_key, size_t encrypted_key_len,
                        unsigned char *decrypted_key, size_t &decrypted_key_len) {
    return mbedtls_pk_decrypt(pk, encrypted_key, encrypted_key_len, decrypted_key, &decrypted_key_len, 256, nullptr, nullptr);

    
}

int wmain() {
    mbedtls_pk_context keypair;
    mbedtls_ctr_drbg_context ctr_drbg;
    mbedtls_entropy_context entropy;
    
    // Initialize
    mbedtls_pk_init(&keypair);
    mbedtls_ctr_drbg_init(&ctr_drbg);
    mbedtls_entropy_init(&entropy);
    
    // Seed RNG
    mbedtls_ctr_drbg_seed(&ctr_drbg, mbedtls_entropy_func, &entropy, nullptr, 0);
    
    // Setup keypair (RSA-2048)
    mbedtls_pk_setup(&keypair, mbedtls_pk_info_from_type(MBEDTLS_PK_RSA));
    mbedtls_rsa_gen_key(mbedtls_pk_rsa(keypair), mbedtls_ctr_drbg_random, &ctr_drbg, 2048, 65537);
    
    // Generate AES key & IV
    unsigned char aes_key[AES_KEY_SIZE], aes_iv[AES_IV_SIZE];
    generate_random_bytes(aes_key, AES_KEY_SIZE, &ctr_drbg);
    generate_random_bytes(aes_iv, AES_IV_SIZE, &ctr_drbg);
    
    // Message to encrypt
    const char *message = "Hybrid encryption with AES & RSA!";
    size_t message_len = strlen(message);
    
    // Encrypt message with AES
    unsigned char encrypted_message[256];
    size_t encrypted_message_len;
    aes_encrypt(aes_key, aes_iv, (const unsigned char *)message, message_len, encrypted_message, encrypted_message_len);
    

    mbedtls_rsa_set_padding(mbedtls_pk_rsa(keypair), MBEDTLS_RSA_PKCS_V15, MBEDTLS_MD_NONE);

    std::cout << "AES Message Encrypted! \b" ;

    std::cout << encrypted_message << "\n";

    
    // Encrypt AES key with RSA public key
    unsigned char encrypted_aes_key[256];
    size_t encrypted_aes_key_len;
    // if (rsa_encrypt_aes_key(&keypair, aes_key, AES_KEY_SIZE, encrypted_aes_key, encrypted_aes_key_len, &ctr_drbg) != 0) {
    //     std::cerr << "RSA encryption of AES key failed!" << std::endl;
    //     return -1;
    // }
    
    if(mbedtls_pk_encrypt(&keypair, aes_key, AES_KEY_SIZE, encrypted_aes_key, &encrypted_aes_key_len, 
        MBEDTLS_MPI_MAX_SIZE, mbedtls_ctr_drbg_random, &ctr_drbg))
    {
        std::cerr << "RSA encryption of AES key failed!" << std::endl;
        return -1;
    }
        

    std::cout << "AES Key Encrypted with RSA!" << std::endl;
    
    unsigned char public_key[2048];  // Size depends on the key length
    unsigned char private_key[2048];

    int ret = mbedtls_pk_write_pubkey_pem(&keypair, public_key, sizeof(public_key));
    if (ret == 0) {
        std::cout << "Public Key:\n" << public_key << std::endl;
    }

    // Export Private Key
    ret = mbedtls_pk_write_key_pem(&keypair, private_key, sizeof(private_key));
    if (ret != 0) {
        std::cerr << "Private key writing failed! Error code: " << ret << std::endl;
    }
    else 
    {
        std::cout << "Private Key:\n" << private_key << std::endl;
    }

    // Decrypt AES key with RSA private key
    unsigned char decrypted_aes_key[256];
    size_t decrypted_aes_key_len;


    // if (rsa_decrypt_aes_key(&keypair, encrypted_aes_key, encrypted_aes_key_len, decrypted_aes_key, decrypted_aes_key_len) != 0) {
    //     std::cerr << "RSA decryption of AES key failed!" << std::endl;
    //     return -1;
    // }

    int tRet = mbedtls_pk_decrypt(&keypair, encrypted_aes_key, encrypted_aes_key_len, decrypted_aes_key, 
        &decrypted_aes_key_len, MBEDTLS_MPI_MAX_SIZE, nullptr, nullptr);
    if( tRet != 0)
    {


        std::cerr << "RSA decryption of AES key failed! return code " << tRet << "\n";   
        return -1;
    }

    
    std::cout << "AES Key Decrypted!" << std::endl;
    
    // Decrypt message with AES
    unsigned char decrypted_message[256];
    aes_decrypt(decrypted_aes_key, aes_iv, encrypted_message, encrypted_message_len, decrypted_message);
    
    std::cout << "Decrypted Message: " << decrypted_message << std::endl;
    
    // Cleanup
    mbedtls_pk_free(&keypair);
    mbedtls_ctr_drbg_free(&ctr_drbg);
    mbedtls_entropy_free(&entropy);
    
    return 0;
}
