#pragma once

#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <string_view>

/*
    A crude helper function for outputing numbers with commas in them.
    Gives my aging eyes a break.

    I put this together specifically for use with iostreams (cout, cerr), appending to a buffer, etc.
    Probably is not safe for printf or similar functions where you might call commas multiple times prior to using the output.
*/

std::string_view commas(uint64_t val)
{
    static thread_local std::string comma_buffer;

    comma_buffer.clear();
    if (!val)
    {
        comma_buffer = '0';
        return comma_buffer;
    }

    while (val)
    {
        for (uint32_t i = 0; i < 3 && val; i++)
        {
            comma_buffer += '0' + (val % 10);
            val /= 10;
        }
        if (val)
            comma_buffer += ',';
    }
    std::reverse(comma_buffer.begin(), comma_buffer.end());
    return comma_buffer;
}

std::string add_commas(uint64_t n)
{
    struct my_nump : std::numpunct<char>
    {
        std::string do_grouping() const { return "\3"; }
    };

    std::ostringstream s;
    s.imbue(std::locale(s.getloc(), new my_nump));
    s << n;
    return s.str();
}

