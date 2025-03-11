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


unsigned char AES_KEY[AES_KEY_SIZE] = {
    // 0x60, 0x3d, 0xeb, 0x10, 0x15, 0xca, 0x71, 0xbe,
    // 0x2b, 0x73, 0xae, 0xf0, 0x85, 0x7d, 0x77, 0x81,
    // 0x1f, 0x35, 0x2c, 0x07, 0x3b, 0x61, 0x08, 0xd7,
    // 0x2d, 0x98, 0x10, 0xa3, 0x09, 0x14, 0xdf, 0xf4
};
// Generate a random IV using mbedTLS
void generate_random_iv(unsigned char *iv) {
    mbedtls_entropy_context entropy;
    mbedtls_ctr_drbg_context ctr_drbg;
    
    mbedtls_entropy_init(&entropy);
    mbedtls_ctr_drbg_init(&ctr_drbg);
    mbedtls_ctr_drbg_seed(&ctr_drbg, mbedtls_entropy_func, &entropy, nullptr, 0);
    
    mbedtls_ctr_drbg_random(&ctr_drbg, iv, AES_IV_SIZE);
    
    mbedtls_ctr_drbg_free(&ctr_drbg);
    mbedtls_entropy_free(&entropy);
}

void derive_aes_key(const std::string &password, unsigned char aes_key[AES_KEY_SIZE]) {
    // Use SHA-256 to hash the password into a 32-byte AES key
    mbedtls_sha256_context sha_ctx;
    mbedtls_sha256_init(&sha_ctx);
    mbedtls_sha256_starts(&sha_ctx, 0);  // 0 = SHA-256 (not SHA-224)
    mbedtls_sha256_update(&sha_ctx, (const unsigned char *)password.c_str(), password.length());
    mbedtls_sha256_finish(&sha_ctx, aes_key);
    mbedtls_sha256_free(&sha_ctx);
}

// Function to encrypt using AES-256-CBC
void aes_encrypt(const std::string &input, std::vector<unsigned char> &output, unsigned char *iv) {
    mbedtls_aes_context aes;
    mbedtls_aes_init(&aes);
    
    // Example key (in real-world applications, use a securely generated key)


    mbedtls_aes_setkey_enc(&aes, AES_KEY, AES_KEY_SIZE * 8);  // Set 256-bit key

    // Padding: Ensure the input is a multiple of 16 bytes
    size_t padded_size = ((input.size() / AES_IV_SIZE) + 1) * AES_IV_SIZE;
    std::vector<unsigned char> padded_input(padded_size, 0);
    std::memcpy(padded_input.data(), input.c_str(), input.size());

    // Encrypt
    output.resize(padded_size);
    unsigned char iv_copy[AES_IV_SIZE];  // IV is modified during encryption, so we need a copy
    std::memcpy(iv_copy, iv, AES_IV_SIZE);

    mbedtls_aes_crypt_cbc(&aes, MBEDTLS_AES_ENCRYPT, padded_size, iv_copy, padded_input.data(), output.data());

    mbedtls_aes_free(&aes);
}

// Function to decrypt using AES-256-CBC
void aes_decrypt(const std::vector<unsigned char> &input, std::string &output, unsigned char *iv) {
    mbedtls_aes_context aes;
    mbedtls_aes_init(&aes);

    // const unsigned char AES_KEY[AES_KEY_SIZE] = {
    //     0x60, 0x3d, 0xeb, 0x10, 0x15, 0xca, 0x71, 0xbe,
    //     0x2b, 0x73, 0xae, 0xf0, 0x85, 0x7d, 0x77, 0x81,
    //     0x1f, 0x35, 0x2c, 0x07, 0x3b, 0x61, 0x08, 0xd7,
    //     0x2d, 0x98, 0x10, 0xa3, 0x09, 0x14, 0xdf, 0xf4
    // };

    mbedtls_aes_setkey_dec(&aes, AES_KEY, AES_KEY_SIZE * 8);  // Set 256-bit key

    // Decrypt
    std::vector<unsigned char> decrypted(input.size(), 0);
    unsigned char iv_copy[AES_IV_SIZE];
    std::memcpy(iv_copy, iv, AES_IV_SIZE);

    mbedtls_aes_crypt_cbc(&aes, MBEDTLS_AES_DECRYPT, input.size(), iv_copy, input.data(), decrypted.data());

    // Remove padding
    output.assign(reinterpret_cast<char*>(decrypted.data()));

    mbedtls_aes_free(&aes);
}

int wmain() {

    
    std::cout << "type pw to hash into aes key :\n";
    std::string pw;
    std::getline(std::cin, pw);

    // unsigned char aes_key[AES_KEY_SIZE];
    derive_aes_key(pw, AES_KEY);

    std::cout << "AES key: ";
    for (int i = 0; i < AES_KEY_SIZE; i++)
    {
        printf("%02x", AES_KEY[i]);
    }

    std::cout << "\n";

    std::string message;
    std::cout << "Enter message to encrypt: ";
    std::getline(std::cin, message);

    unsigned char iv[AES_IV_SIZE];
    generate_random_iv(iv);

    std::vector<unsigned char> encrypted;
    aes_encrypt(message, encrypted, iv);

    std::cout << "Encrypted (hex): ";
    for (unsigned char byte : encrypted)
        printf("%02x", byte);
    std::cout << std::endl;

    std::string decrypted;
    aes_decrypt(encrypted, decrypted, iv);

    std::cout << "Decrypted: " << decrypted << std::endl;


    return 0;
}
