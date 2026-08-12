//
// Created by Kyrylo Pylinskyi on 10/08/2026.
//

#include <iostream>
#include <ranges>
// Case 1 - A returned reference
//  const int& larger(int a, int b) {
//     int result = a > b ? a : b;
//     return result; // return temporary local value, lifetime expansion will not be applied
//  }

// Option A - pass const reference - return const reference
const int& larger(const int& a, const int& b) {
    return a > b ? a : b;
}

// Option B - pass by value - return by value
int larger(const int a, const int b) {
    return a > b ? a : b;
}

// Case 2 - Cleanup
// void cleanup() {
//     int* first = new int(10);
//     int* second = new int(20);
//
//     std::cout << *first + *second << '\n';
//     delete first, second; // comma operator. only second will be freed.
// }

void cleanup() {
    int* first = new int(10);
    int* second = new int(20);

    std::cout << *first + *second << '\n';
    delete first;
    delete second;
}

// Case 3

//  void reset(const int* value) {
//      *value = 0;
//  }

void reset(int * const value) {
    *value = 0;
}

// Case 4 - Lost array size
// void print_all(const int values[]) {
//     const std::size_t size = sizeof(values) / sizeof(values[0]);
//
//     for (std::size_t i = 0; i < size; ++i) {
//         std::cout << values[i] << '\n';
//     }
// }

void print_all(const int values[], std::size_t size) {
    for (std::size_t i = 0; i < size; ++i) {
        std::cout << values[i] << '\n';
    }
}

void print_all(const int* begin, const int* end) {
    while (begin != end) {
        std::cout << *begin << '\n';
        ++begin;
    }
}

// Case 5 - Side effects and evaluation order
// int combine() {
//     int value = 1;
//     return value++ + ++value;
// }

int combine() {
    int value = 1;

    const int first = value++;  // first = 1, value becomes 2
    const int second = ++value; // value becomes 3, second = 3

    return first + second; // 1 + 3 = 4
}