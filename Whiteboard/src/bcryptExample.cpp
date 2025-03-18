#include <windows.h>
#include <bcrypt.h>
#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>


#pragma comment(lib, "bcrypt.lib")

std::string wcharToString(const wchar_t* wstr) {
    int size_needed = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, nullptr, 0, nullptr, nullptr);
    std::string str(size_needed, 0);
    WideCharToMultiByte(CP_UTF8, 0, wstr, -1, &str[0], size_needed, nullptr, nullptr);
    return str;
}

std::vector<unsigned char> hashPasswordPBKDF2(const std::string& password, const std::vector<unsigned char>& salt, int iterations = 1000) {
    BCRYPT_ALG_HANDLE hAlgorithm;
    DWORD keyLength = 32;  // 256-bit output

    if (BCryptOpenAlgorithmProvider(&hAlgorithm, BCRYPT_SHA256_ALGORITHM, NULL, BCRYPT_ALG_HANDLE_HMAC_FLAG) != 0) {
        throw std::runtime_error("Failed to open SHA-256 HMAC provider.");
    }

    std::vector<unsigned char> derivedKey(keyLength);
    if (BCryptDeriveKeyPBKDF2(hAlgorithm, (PUCHAR)password.data(), password.size(), (PUCHAR)salt.data(), salt.size(), iterations, derivedKey.data(), keyLength, 0) != 0) {
        BCryptCloseAlgorithmProvider(hAlgorithm, 0);
        throw std::runtime_error("Failed to derive key.");
    }

    BCryptCloseAlgorithmProvider(hAlgorithm, 0);
    return derivedKey;
}

int wmain(int argc, wchar_t *argv[]) {
    // std::string password = "securepassword";


    if (argc < 2) 
    {
        std::wcout << "Usage: " << argv[0] << " <password> \n";
        return 1;
    }
    for(int i = 0 ; i < argc ; i ++) std::wcout << L"argv " << i << L" " << argv[i] << L"\n";

    std::string password =wcharToString(argv[1]);

    std::vector<unsigned char> salt = {0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC, 0xDE, 0xF0};  // Example salt

    std::vector<unsigned char> hashed = hashPasswordPBKDF2(password, salt);

    std::cout << "Password: " << password << "\n";

    std::cout << "PBKDF2 Hashed Password: \n";
    for (unsigned char byte : hashed) {
        printf("%02x", byte);
    }


    std::cout << "\n";

    std::string retVal;
    std::cout << "string val \n";
    std::ostringstream oss;
    for (unsigned char byte : hashed) {
        oss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte);
    }

    retVal = oss.str();

    std::cout << retVal << "\n";

    return 0;
}