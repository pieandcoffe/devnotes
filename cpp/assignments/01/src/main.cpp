#include <iostream>
#include <__ranges/reverse_view.h>

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

    const int* begin = data;
    const int* end = data + size;

    std::cout << "count: " << count(begin, end) << std::endl;
    std::cout << "min: " << *find_min(begin, end) << std::endl;
    std::cout << "max: " << *find_max(begin, end) << std::endl;
    std::cout << "sum: " << calculate_sum(begin, end) << std::endl;
    std::cout << "mean: " << calculate_mean(begin, end) << std::endl;
    std::cout << "negative: " << count_if(begin, end, is_negative) << std::endl;
    std::cout << "even: " << count_if(begin, end, is_even) << std::endl;

    reverse_values(data, data + size);
    std::cout << "reversed: ";
    print_values(begin, end);
    std::cout << std::endl;

    std::cout << "frequencies: " << std::endl;
    print_frequencies(begin, end);

    return 0;
}
