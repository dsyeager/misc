#pragma once

#include <stdint.h>
#include <time.h>

#include <iomanip>
#include <iostream>

uint64_t get_nanoseconds()
{       
        timespec ts;
        clock_gettime(CLOCK_REALTIME, &ts);
        uint64_t ret = ts.tv_nsec;
        ret += ts.tv_sec * 1000000000;
        return ret;
}

void show_times(const char* description, uint64_t start, uint32_t cnt)
{
    uint64_t end = get_nanoseconds();
    double each = (end - start) / cnt; 
    double per_sec = 1000000000 / each;

    std::cout << description << ": ns total: " << (end - start) << ", ns each: " << std::setprecision(1) << each << ", per second: " << per_sec << std::endl;
}

