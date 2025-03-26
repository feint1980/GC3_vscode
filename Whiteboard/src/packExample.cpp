
#include <iostream>
#include <cmath>
// Base case: when no digits are left

template <int n, int step>
int getDecFromBy() {
    // std::cout << n << "\n";
    // std::cout << step << "\n";
    
    return n;
    // std::cout << std::endl;
}

// Variadic template to print binary representation
template <int n, int step, bool first,bool... rest>
int getDecFromBy() {
    
 
    if(first)
    {
        std::cout << "got step " << step << "\n"; ;
        std::cout << "n now is " << step << "\n";
        return getDecFromBy< step + n ,step * 2 ,rest...>();
    }
    else
    {
        std::cout << "no \n";
        std::cout << "n now is " << n << "\n";
        return getDecFromBy< n ,step * 2 ,rest...>();
    }

     // Recursive call to process the rest
}

int wmain() {
    std::cout <<  getDecFromBy<0,1, 1, 0, 1, 1>(); 
    // std::cout << t << "\n";
    return 0;
}

