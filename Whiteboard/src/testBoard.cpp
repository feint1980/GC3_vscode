#include <iostream>
#include <string_view>

std::string_view expandFromCenter(std::string_view s, int left, int right) {
    while (left >= 0 && right < s.size() && s[left] == s[right]) 
    {
        left--;
        right++;
    }
    return s.substr(left + 1, right - left - 1);  
}

std::string longestPalindrome(std::string_view s) {
    if (s.empty()) return "";

    std::string_view longest;
    
    for (int i = 0; i < s.size(); ++i) 
    {
        std::string_view odd  = expandFromCenter(s, i, i);     
        std::string_view even = expandFromCenter(s, i, i + 1);  

        if (odd.size() > longest.size())
        {
            longest = odd;
        } 
        if (even.size() > longest.size())
        {
            longest = even;
        } 
    }
    
    return std::string(longest);
}


// int wmain() {
//     std::cout << longestPalindrome("babad") << '\n';  
//     std::cout << longestPalindrome("cbbd") << '\n';   
//     std::cout << longestPalindrome("racecar") << '\n'; 
//     std::cout << longestPalindrome("asdasdracecar") << '\n'; 
//     std::cout << longestPalindrome("racecarasdasd") << '\n'; 

//     return 0;
// }

#include <iostream>
#include <chrono>

struct PlayerDirect {
    int gridX, gridY;
};

struct PlayerSetter {
private:
    int gridX, gridY;
public:
    void setGridX(int x) { gridX = x; }
    void setGridY(int y) { gridY = y; }
};

struct PlayerSetterInline {
private:
    int gridX, gridY;
public:
    inline void setGridX(int x) { gridX = x; }
    inline void setGridY(int y) { gridY = y; }
};

template<typename Func>
long long benchmark(Func f, int iterations) {
    auto start = std::chrono::high_resolution_clock::now();
    f();
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
}

volatile long long int sink = 0;  // volatile to prevent optimization
int wmain() {
    long long int N = 500'000'000;

    PlayerDirect pd;
    PlayerSetter ps;
    PlayerSetterInline psi;

    auto timeDirect = benchmark([&]() {
        for (long long int i = 0; i < N; ++i) {
            pd.gridX = i;
            pd.gridY = i;
            sink = pd.gridX;
        }
        
    }, N);

    auto timeSetter = benchmark([&]() {
        for (long long int i = 0; i < N; ++i) {
            ps.setGridX(i);
            ps.setGridY(i);
            sink = pd.gridX;
        }
        
    }, N);

    auto timeSetterInline = benchmark([&]() {
        for (long long int i = 0; i < N; ++i) {
            psi.setGridX(i);
            psi.setGridY(i);
            sink = pd.gridX;
        }
        
    }, N);

    
    std::cout << "Direct assign: " << timeDirect << " ms\n";
    std::cout << "Normal setter: " << timeSetter << " ms\n";
    std::cout << "Inline setter: " << timeSetterInline << " ms\n";

    std::cout << sink; 
    return 0;
}
