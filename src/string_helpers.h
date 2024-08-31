#pragma once

#include <charconv>
#include <string>
#include <string_view>


std::string& operator<< (std::string &dest, std::string_view src)
{
    dest.append(src);
    return dest;
}

std::string& operator<< (std::string &dest, char src)
{
    dest.push_back(src);
    return dest;
}

std::string& operator<< (std::string &dest, uint32_t src)
{
    char buff[50];
    auto [ptr, ec2] = std::to_chars(buff, buff + 50, src, 10);
    dest.append(buff, ptr - buff);
    return dest;
}

std::string& operator<< (std::string &dest, uint64_t src)
{
    char buff[50];
    auto [ptr, ec2] = std::to_chars(buff, buff + 50, src, 10);
    dest.append(buff, ptr - buff);
    return dest;
}
