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