
#include <mbedtls/mbedtls/sha256.h>
#include <iostream>


#include <mbedtls/mbedtls/md5.h>

#include <map>
#include <string>
#include <vector>
#include <future>

#include <cstdio>
#include <dirent.h>

#include <queue>

#include <stack>

#include <chrono>
#include <ctime>

#include <functional>

#include <thread>
#include <atomic>
#define BUFFER_SIZE 4096  // Read the file in 4KB chunks


// typedef std::vector<std::thread> thread_pool; 

// std::vector<thread> m_threadPools;


std::atomic_int m_threadPoolIndex = 0;



struct file_info {
    
    std::wstring filename;
    std::vector<std::wstring> m_duplicatedFiles;
};
typedef std::vector<std::thread> thread_pool; 


typedef std::stack<std::function<void()>> taskQueue;


taskQueue m_taskQueues[32]; // max 32 but only workk up to std::thread::hardware_concurrency() which can be 8/16/32


// thread_pool threadPools[4];
// std::map< ,std::future<file_info>> m_FutureFiles;


void executeTask(int index)
{

    while(!m_taskQueues[index].empty())
    {
        m_taskQueues[index].top()();
        m_taskQueues[index].pop();
    }

}


void hash_file_md5(const std::wstring &filename, std::map<std::wstring, file_info> &m_fileMap) {
    FILE *file = _wfopen(filename.c_str(), L"rb");
    if (!file) {
        std::wcerr << "Error opening file: " << filename << L"\n";
        return;
    }

    std::wstring data = L"sdsadsd";

    // FILE * tt = _wfopen(data.c_str(), L"rb");

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
    // std::cout << filename << "\t\t\t| MD5:|";
    // for (int i = 0; i < 16; i++)
    //     printf("%02x", output[i]);
    // std::cout <<"|\n";

    std::wstring hash = std::wstring(reinterpret_cast<wchar_t*>(output), 32);
    if(m_fileMap.find(hash) == m_fileMap.end())
    {
        file_info info;
        info.filename = filename;
        m_fileMap[hash] = info;
    }
    else
    {
        // std::cout << "found duplicate " << filename << "| orgiginal | " << m_fileMap[hash].filename << "\n";
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
    // std::cout << filename << "| SHA-256 Hash: |";
    // for (int i = 0; i < 32; i++)
    // {
    //     printf("%02x", output[i]);
    // }
    // std::cout << "|\n";


    // m_fileMap[hash].m_duplicatedFiles.push_back(filename);
}


int scan_dir(const std::wstring & path, int level, std::map<std::wstring, file_info> &m_fileMap)
	{
		
        //std::cout << "scan on " << path << "\n";
        //std::cout << "level start -----" << level << "\n";
        _WDIR *dir = nullptr;
        struct _wdirent *entry = nullptr;

        if (!(dir = _wopendir(path.c_str())))
        {
            std::cout << "dir failed \n";
            return 0;
        }

        if (!(entry = _wreaddir(dir)))
        {
            std::cout << "entry failed \n";
            return 0;
        }
        do
        {
            if (entry->d_type == DT_DIR)
            {
                std::wstring sub_path = path + L"/" + entry->d_name;
                if (wcscmp(entry->d_name, L".") == 0 || wcscmp(entry->d_name, L"..") == 0)
                {
                    continue;
                }

				// stop printing to increase speed
                //printf("%*s[%s]\n", level * 2, "", entry->d_name);
        
                scan_dir(sub_path, level + 1, m_fileMap);
            }
            else
            {
                std::wstring file_path = path + L"/" + entry->d_name;

                // std::thread t = std::thread(hash_file_md5, file_path);

                // thread_pool[m_threadPoolIndex]

                m_taskQueues[m_threadPoolIndex].push([file_path, &m_fileMap]() { hash_file_md5(file_path, m_fileMap);} );
                m_threadPoolIndex ++;
                if(m_threadPoolIndex >= std::thread::hardware_concurrency())
                {
                    m_threadPoolIndex = 0;
                }

                // m_threads
                // if(t.joinable())
                // {
                //     t.join();
                // }
                // m_threadPools[m_threadPoolIndex].push_back(std::move(t));
                // m_threadPoolIndex ++;
                // if(m_threadPoolIndex >= std::thread::hardware_concurrency())
                // {
                //     m_threadPoolIndex = 0;
                // }
                // m_threadPoolIndex = (m_threadPoolIndex + 1) % std::thread::hardware_concurrency();

                // m_threads.push_back(std::move(t));
                // hash_file_md5( file_path );
			
            }
        } while (entry = _wreaddir(dir));

        _wclosedir(dir);
       // std::cout << "level end -----" << level << "\n";
        return 0;
    }


int wmain(int argc, wchar_t const *argv[]) {
    //std::string filename = "test.txt";  // Change this to your file
    //hash_file_sha256(filename);

    std::map<std::wstring, file_info> m_fileMap;

    if(argc != 2)
    {
        std::cout << "wrong number of arguments, only use 1, the path to scane \n";
        return 0;
    }
    auto start =  std::chrono::system_clock::now();

    std::cout << "scanning \n";

    scan_dir(argv[1],0, m_fileMap);

    std::vector<std::future<void>> futures;

    for(int i = 0 ; i < std::thread::hardware_concurrency() ; i++)
    {
        futures.push_back(std::async(std::launch::async, [i]() { executeTask(i); }));
    }

    for (auto &f : futures) {
        f.get();  // Wait for each async task to finish
    }
    std::cout << "done ||||| \n";

    std::cout << "result : ";
    for(auto it = m_fileMap.begin(); it != m_fileMap.end(); it++)
    {
        if(it->second.m_duplicatedFiles.size() > 0)
        {
            std::wcout << L"file " << it->second.filename << L" has " << it->second.m_duplicatedFiles.size() << L" duplicates: \n";
            for(int i = 0 ; i < it->second.m_duplicatedFiles.size() ; i++)
            {
                std::wcout << it->second.m_duplicatedFiles[i] << "\n";
            }
            std::wcout << L"#################################################################################### \n";
    
        }
    }
    std::cout << "process done !! \n";

    auto end = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";
    return 0;
}
