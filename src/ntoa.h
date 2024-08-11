#pragma once

#include <algorithm>
#include <charconv>
#include <iostream>
#include <limits>
#include <string>
#include <string_view>


/*
    A generic number -> string utility function.

    Alternatives tested are std::to_string
                            std::to_chars_result to_chars( char* first, char* last,
                                value, int base = 10 );


*/

template <typename NUMB> std::string_view ntoa(NUMB val, std::string &dest, uint8_t base = 10)
{
    // TODO figure out how to convert directly into dest instead of using the str buffer
    const size_t initial_length = dest.length();
    char str[25];
    auto [ptr, ec] = std::to_chars(str, str + 25, val, base);
    dest.append(str, ptr - str);
    return std::string_view(dest).substr(initial_length);
}
