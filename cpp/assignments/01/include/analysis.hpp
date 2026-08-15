//
// Created by Kyrylo Pylinskyi on 08/08/2026.
//

#ifndef ASSIGNMENT_01_ANALYSIS_HPP
#define ASSIGNMENT_01_ANALYSIS_HPP

#include <cstddef>
#include <map>

bool read_values(int* data, std::size_t size);

std::size_t count(const int* begin, const int* end );

const int* find_min(const int* begin, const int* end);
const int* find_max(const int* begin, const int* end);

long long calculate_sum(const int* begin, const int* end);
double calculate_mean(const int* begin, const int* end);

void swap_values(int& lhs, int& rhs);
void reverse_values(int* begin, int* end);

bool is_negative(int value);
bool is_even(int value);

std::size_t count_if( const int* begin, const int* end, bool (*predicate)(int) );

std::map<int, std::size_t> frequencies(const int* begin, const int* end);

void print_values(const int* begin, const int* end);

void print_frequencies(const int* begin, const int* end);

#endif //ASSIGNMENT_01_ANALYSIS_HPP
