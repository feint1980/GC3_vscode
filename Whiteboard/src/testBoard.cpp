#include <iostream>

void divide(int a, int b) {
    try {
        if (b == 0) {
            throw std::runtime_error("Division by zero is not allowed.");
        }
        std::cout << "Result: " << a / b << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

int wmain() {
    // divide(10, 2); // Works fine
    // divide(10, 0); // Throws an error
    std::cout << 10/0 << "\n";
    return 0;
}