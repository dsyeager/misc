#include <algorithm>
#include <string>
#include <string_view>

/*
    A crude helper function for outputing numbers with commas in them.
    Gives my aging eyes a break.

    I put this together specifically for use with iostreams (cout, cerr).
    Probably is not safe for printf or similar functions.
*/

std::string_view commas(uint64_t val)
{
    static thread_local std::string comma_buffer;

    comma_buffer.clear();
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
