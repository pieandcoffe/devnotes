//
// Created by Kyrylo Pylinskyi on 08/08/2026.
//

#include "analysis.hpp"
#include "parser.hpp"

bool read_values(int* data, const std::size_t size) {
    for ( std::size_t i = 0; i < size ; ++i ) {
        int value;

        if ( !tryGet<int>( std::cin , value) ) return false;

        data[i] = value;
    }

    return true;
}

std::size_t count(const int* begin, const int* end ) {
    if ( begin == end ) return 0;
    return end - begin;
}

const int* find_min(const int* begin, const int* end) {
    if ( begin == end ) return end;

    const int* min = begin;

    while ( begin != end ) {
        if (*begin < *min ) min = begin;
        ++begin;
    }

    return min;
}

const int* find_max(const int* begin, const int* end) {
    if ( begin == end ) return end;

    const int* max = begin;

    while ( begin != end ) {
        if (*begin > *max ) max = begin;
        ++begin;
    }

    return max;
}

long long calculate_sum(const int* begin, const int* end) {
    if ( begin == end ) return 0L;

    long long sum = 0;

    while ( begin != end ) {
        sum += *(begin++);
    }

    return sum;
}

double calculate_mean(const int* begin, const int* end) {
    if ( begin == end ) return 0.0;

    return static_cast<double>( calculate_sum(begin, end) ) / static_cast<double>( count(begin, end) );
}

void swap_values(int& lhs, int& rhs) {
    const int tmp = lhs;
    lhs = rhs;
    rhs = tmp;
}

void reverse_values(int* begin, int* end) {
    while ( begin != end && begin != --end ) {
        swap_values(*begin, *end);
        ++begin;
    }
}

bool is_negative(int value) {
    return value < 0;
}

bool is_even(int value) {
    return (value & 1) == 0;
}

std::size_t count_if( const int* begin, const int* end, bool (*predicate)(int) ) {
    int count = 0;
    while ( begin != end ) {
        if (predicate(*begin++)) ++count;
    }

    return count;
}

std::map<int, std::size_t> frequencies(const int* begin, const int* end) {
    std::map<int, std::size_t> result;

    while ( begin != end ) {
        ++result[*(begin++)];
    }

    return result;
}

void print_values(const int* begin, const int* end) {
    while ( begin != end ) {
        const int value = *begin;
        std::cout << value << " ";
        ++begin;
    }
}

void print_frequencies(const int* begin, const int* end) {
    for (const std::map<int, std::size_t> freq = frequencies(begin, end); const auto& [value, count] : freq) {
        std::cout << value << ":" << count << std::endl;
    }
}