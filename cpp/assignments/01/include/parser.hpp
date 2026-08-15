//
// Created by Kyrylo Pylinskyi on 08/08/2026.
//

#ifndef ASSIGNMENT_01_PARSER_HPP
#define ASSIGNMENT_01_PARSER_HPP

#include <charconv>
#include <iostream>
#include <optional>
#include <string>
#include <string_view>

template<typename T>
    std::optional<T> parseNumber(const std::string_view text ) {
    if ( text.empty() )
        return std::nullopt;

    T value{};
    const char * const begin = text.data();
    const char * const end = text.data() + text.size();

    const auto [ptr, ec] = std::from_chars( begin, end, value );

    if ( ec != std::errc{} || ptr != end )
        return std::nullopt;

    return value;
}

template<typename T>
std::optional<T> parseNumber( const char* text ) {
    if ( text == nullptr )
        return std::nullopt;

    return parseNumber<T>( std::string_view{ text } );
}

template<typename T>
std::optional<T> parseNumber( std::istream& input ) {
    std::string token;

    if ( !(input >> token ) )
        return std::nullopt;

    return parseNumber<T>( token );
}

template<typename T>
bool tryGet(std::string_view text, T& result ) {
    const auto value = parseNumber<T>( text );

    if ( !value )
        return false;

    result = *value;
    return true;
}

template<typename T>
bool tryGet(const char* text, T& result ) {
    if ( text == nullptr )
        return false;

    return tryGet<T>( std::string_view{ text } , result );
}

template<typename T>
bool tryGet(std::istream& input, T& result ) {
    std::string token;

    if ( !(input >> token ) )
        return false;

    return tryGet<T>( std::string_view{ token }, result );
}

#endif //ASSIGNMENT_01_PARSER_HPP
