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



int wmain() {
    std::cout << longestPalindrome("babad") << '\n';  
    std::cout << longestPalindrome("cbbd") << '\n';   
    std::cout << longestPalindrome("racecar") << '\n'; 
    std::cout << longestPalindrome("asdasdracecar") << '\n'; 
    std::cout << longestPalindrome("racecarasdasd") << '\n'; 

    return 0;
}