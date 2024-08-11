#pragma once

#include <unistd.h>

#include <fstream>

/*
    Helper functions for finding rough memory usage of an app from within the app.

    Usage, perform a bunch of allocations and or collections building, call memory usage to find the memory used.
*/

auto memory_usage()
{
    uint64_t tSize = 0;
    uint64_t resident = 0;
    uint64_t share = 0;
    std::ifstream buffer("/proc/self/statm");
    buffer >> tSize >> resident >> share;
    buffer.close();

    uint64_t page_size = sysconf(_SC_PAGE_SIZE); // in case x86-64 is configured to use 2MB pages
    uint64_t rss = resident * page_size;

    uint64_t shared_mem = share * page_size;

    return std::make_pair(shared_mem, rss - shared_mem);
}

void print_memory_usage(const char *context)
{
    auto [smem, pmem] = memory_usage();
    const uint64_t GB = 1024lu * 1024lu * 1024lu;
    printf("%s: Shared mem: %0.2f GB, private mem: %0.2f GB\n", context, double(smem) / GB, double(pmem) / GB);
}
