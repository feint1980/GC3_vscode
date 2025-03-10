
#include <mbedtls/mbedtls/sha256.h>
#include <iostream>


#include <mbedtls/mbedtls/md5.h>

#include <map>
#include <string>
#include <vector>

#include <cstdio>
#include <dirent.h>
#define BUFFER_SIZE 4096  // Read the file in 4KB chunks


struct file_info {
    std::string filename;
    std::vector<std::string> m_duplicatedFiles;
};

std::map<std::string, file_info> m_fileMap;

void hash_file_md5(const std::string &filename) {
    FILE *file = fopen(filename.c_str(), "rb");
    if (!file) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    mbedtls_md5_context md5_ctx;
    mbedtls_md5_init(&md5_ctx);
    mbedtls_md5_starts(&md5_ctx);

    unsigned char buffer[BUFFER_SIZE];
    size_t bytesRead;

    while ((bytesRead = fread(buffer, 1, BUFFER_SIZE, file)) > 0) {
        mbedtls_md5_update(&md5_ctx, buffer, bytesRead);
    }
    fclose(file);

    unsigned char output[16];  // MD5 hash is 16 bytes
    mbedtls_md5_finish(&md5_ctx, output);
    mbedtls_md5_free(&md5_ctx);

    // Print the MD5 hash in hexadecimal format
    std::cout << filename << "\t\t\t| MD5:|";
    for (int i = 0; i < 16; i++)
        printf("%02x", output[i]);
    std::cout <<"|\n";

    std::string hash = std::string(reinterpret_cast<char*>(output), 32);
    if(m_fileMap.find(hash) == m_fileMap.end())
    {
        file_info info;
        info.filename = filename;
        m_fileMap[hash] = info;
    }
    else
    {
        std::cout << "found duplicate \n";
        m_fileMap[hash].m_duplicatedFiles.push_back(filename);
    }
}

void hash_file_sha256(const std::string &filename) {


    FILE *file = fopen(filename.c_str(), "rb");
    if (!file) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    mbedtls_sha256_context sha256_ctx;
    mbedtls_sha256_init(&sha256_ctx);
    mbedtls_sha256_starts(&sha256_ctx, 0);  // 0 = SHA-256 (not SHA-224)

    unsigned char buffer[BUFFER_SIZE];
    size_t bytesRead;
    
    while ((bytesRead = fread(buffer, 1, BUFFER_SIZE, file)) > 0) {
        mbedtls_sha256_update(&sha256_ctx, buffer, bytesRead);
    }
    fclose(file);

    unsigned char output[32];  // SHA-256 hash is 32 bytes
    mbedtls_sha256_finish(&sha256_ctx, output);
    mbedtls_sha256_free(&sha256_ctx);

    // Print the hash in hexadecimal format
    std::cout << filename << "| SHA-256 Hash: |";
    for (int i = 0; i < 32; i++)
    {
        printf("%02x", output[i]);
    }
    std::cout << "|\n";


    // m_fileMap[hash].m_duplicatedFiles.push_back(filename);
}


int scan_dir(const std::string & path, int level)
	{
		
        //std::cout << "scan on " << path << "\n";
        //std::cout << "level start -----" << level << "\n";
        DIR *dir = nullptr;
        struct dirent *entry = nullptr;

        if (!(dir = opendir(path.c_str())))
        {
            std::cout << "dir failed \n";
            return 0;
        }

        if (!(entry = readdir(dir)))
        {
            std::cout << "entry failed \n";
            return 0;
        }
        do
        {
            if (entry->d_type == DT_DIR)
            {
                std::string sub_path = path + "/" + entry->d_name;
                if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                {
                    continue;
                }

				// stop printing to increase speed
                //printf("%*s[%s]\n", level * 2, "", entry->d_name);
        
                scan_dir(sub_path, level + 1);
            }
            else
            {
                std::string file_path = path + "/" + entry->d_name;
                hash_file_md5( file_path );
			
            }
        } while (entry = readdir(dir));

        closedir(dir);
       // std::cout << "level end -----" << level << "\n";
        return 0;
    }


int wmain(int argc, char const *argv[]) {
    //std::string filename = "test.txt";  // Change this to your file
    //hash_file_sha256(filename);

    // scan_dir("./", 0);

    if(argc != 2)
    {
        std::cout << "wrong number of arguments, only use 1, the path to scane \n";
        return 0;
    }

    scan_dir(argv[1],0);
    std::cout << "done ||||| \n";
    for(int i = 0 ; i < 5 ; i++)
    {
    std::cout << "############################################################################ \n";

    }
    std::cout << "result : ";
    for(auto it = m_fileMap.begin(); it != m_fileMap.end(); it++)
    {
        if(it->second.m_duplicatedFiles.size() > 0)
        {
            std::cout << "file " << it->second.filename << " has " << it->second.m_duplicatedFiles.size() << " duplicates: \n";
            for(int i = 0 ; i < it->second.m_duplicatedFiles.size() ; i++)
            {
                std::cout << it->second.m_duplicatedFiles[i] << "\n";
            }
        }

    }
    std::cout << "process done !! \n";

    return 0;
}
