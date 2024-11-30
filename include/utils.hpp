#include <iostream>

#ifndef UTILS_HPP
#define UTILS_HPP

// Template function to handle multiple types
template <typename T>
void print(const T& value) {
    std::cout << value << std::endl;
}

#endif
