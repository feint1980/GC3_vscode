#include <iostream>
#include <mbedtls/mbedtls/rsa.h>
#include <mbedtls/mbedtls/pk.h>
#include <mbedtls/mbedtls/entropy.h>
#include <mbedtls/mbedtls/ctr_drbg.h>
#include <cstring>

#define KEY_SIZE 2048   // RSA key size in bits
#define EXPONENT 65537  // Common public exponent
unsigned char public_key[2048];  // Size depends on the key length
unsigned char private_key[2048];
size_t public_len, private_len;


void handle_mbedtls_error(int ret, const std::string& msg) {
    if (ret != 0) {
        std::cerr << msg << " Error Code: " << ret << std::endl;
        exit(EXIT_FAILURE);
    }
}


int wmain() {
    mbedtls_pk_context keypair;
    mbedtls_entropy_context entropy;
    mbedtls_ctr_drbg_context ctr_drbg;
    
    mbedtls_pk_init(&keypair);
    mbedtls_entropy_init(&entropy);
    mbedtls_ctr_drbg_init(&ctr_drbg);

    const char* pers = "rsa_keygen";  // Personalization string

    // Initialize RNG (random number generator)
    int ret = mbedtls_ctr_drbg_seed(&ctr_drbg, mbedtls_entropy_func, &entropy, 
                                    (const unsigned char*)pers, strlen(pers));
    handle_mbedtls_error(ret, "Failed to initialize RNG");

    // Generate RSA key pair
    ret = mbedtls_pk_setup(&keypair, mbedtls_pk_info_from_type(MBEDTLS_PK_RSA));
    handle_mbedtls_error(ret, "Failed to set up PK context");

    ret = mbedtls_rsa_gen_key(mbedtls_pk_rsa(keypair), mbedtls_ctr_drbg_random, &ctr_drbg, KEY_SIZE, EXPONENT);
    handle_mbedtls_error(ret, "Failed to generate RSA key");

    if (!mbedtls_pk_can_do(&keypair, MBEDTLS_PK_RSA)) {
        std::cerr << "Key is not RSA!" << std::endl;
        return -1;
    }

    // Export Public Key
    ret = mbedtls_pk_write_pubkey_pem(&keypair, public_key, sizeof(public_key));
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

    // Message to encrypt
    const char* message = "Hello, MbedTLS RSA this is a very long text do you even know who I \am ? hsahdshadhsahshdshdshd \
    shdsdshdskdsdskdshkhewkewekhjssdsdsdsdsdsdsdsed!Hello, MbedTLS RSA this is a very long text do you even know who I \am ? hsahdshadhsahshdshdshd \
    shdsdshdskdsdskdshkhewkewekhjssdsdsdsdsdsdsdsed!Hello, MbedTLS RSA this is a very long text do you even know who I \am ? hsahdshadhsahshdshdshd \
    shdsdshdskdsdskdshkhewkewekhjssdsdsdsdsdsdsdsed!\
   ";
    size_t message_len = strlen(message);

    std::cout << "messse size" << message_len << "\n";


    size_t t_key_size = mbedtls_pk_get_len(&keypair);
    // Prepare buffers
    unsigned char encrypted[message_len];  // Ciphertext
    unsigned char decrypted[message_len];  // Decrypted plaintext
    size_t encrypted_len, decrypted_len;

    std::cout << "encrypted size " << sizeof(encrypted) << "\n";
    // Encrypt with public key
    ret = mbedtls_pk_encrypt(&keypair, (const unsigned char*)message, message_len, encrypted, 
                             &encrypted_len, sizeof(encrypted), mbedtls_ctr_drbg_random, &ctr_drbg);
    handle_mbedtls_error(ret, "Encryption failed");

    std::cout << "Encrypted message (" << encrypted_len << " bytes): ";
    for (size_t i = 0; i < encrypted_len; ++i) {
        printf("%02X ", encrypted[i]);  // Print in hex format
    }
    std::cout << std::endl;

    std::cout << "string format : " << encrypted << "\n";


    // Decrypt with private key
    ret = mbedtls_pk_decrypt(&keypair, encrypted, encrypted_len, decrypted, 
                             &decrypted_len, sizeof(decrypted), mbedtls_ctr_drbg_random, &ctr_drbg);
    handle_mbedtls_error(ret, "Decryption failed");

    // Null-terminate decrypted message
    decrypted[decrypted_len] = '\0';

    std::cout << "Decrypted message: " << decrypted << std::endl;

    // Cleanup
    mbedtls_pk_free(&keypair);
    mbedtls_entropy_free(&entropy);
    mbedtls_ctr_drbg_free(&ctr_drbg);

    return 0;
}
