#include <iostream>
#include <string_view>

int isPalindrome(const std::string & s) {


    std::string_view sv(s);

    int middle = s.size() / 2;
    // for(int i = middle; i >0 ; i--) 
    // {
        auto left = s.begin();
        auto right = s.end() - 1;
        while(left < right) 
        {
            if(*left == *right) 
            {
                left++;
                right--;
            } else 
            {
                return false;
            }
        }
        
        if(left >= right)
        {
            return true;
        }

        return false;

}

std::string longestPalindrome(const std::string & s) 
{
    int middle = s.size() / 2;
    bool hasMiddle = false;
    if(s.size() % 2 != 0)
    {
        middle++;
        hasMiddle = true;
        std::cout << "has middle \n";
    }
    for(int i = middle; i > 1 ; i--) 
    {
        int diff = middle - (i - hasMiddle);
        int left = middle - diff;
        int right = middle + diff;
        std::string temp = std::string(s.begin() + left, s.begin() + right);
        std::cout << "temp is " << temp << "\n";
        // if(isPalindrome(temp))
        // {
        //     return temp;
        // }
    }

    for(int i = middle; i < s.size() -1 ; i++) 
    {
        int diff = middle - i;
        int left = middle - diff;
        int right = middle + diff -1;
        std::string temp = std::string(s.begin() + left, s.begin() + right);
        std::cout << "temp is " << temp << "\n";
        // if(isPalindrome(temp))
        // {
        //     return temp;
        // }
    }

 

    return "";
}


int wmain() {
    std::cout << longestPalindrome("babad") << '\n';  
    std::cout << longestPalindrome("cbbd") << '\n';   
    std::cout << longestPalindrome("racecar") << '\n'; 
    return 0;
}