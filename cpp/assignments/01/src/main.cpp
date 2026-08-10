#include <iostream>
#include "parser.hpp"
#include "analysis.hpp"
#include "array_guard.hpp"


int main() {
    std::size_t size = 0;

    if ( !tryGet<std::size_t>( std::cin, size) || size == 0 || size > 100'000 ) {
        std::cerr << "error: invalid size" << std::endl;
        return 1;
    }

    const auto data = new int[size];
    ArrayGuard guard{ data };

    if ( !read_values(data, size) ) {
        std::cerr << "error: invalid data" << std::endl;
        return 1;
    }

    return 0;
}
